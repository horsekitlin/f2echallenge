type statusType =
  | LOW
  | MIDDLE
  | HIGH
  | URGENT;

type todoItem = {
  processingTime: int,
  status: statusType,
  pauseCount: int,
  title: string,
};

type action =
  | CHANGE_TEXT(string)
  | ADD_TODO(string)
  | EDIT_TODO(int, todoItem)
  | WATCH_TODO(int)
  | DELETE_TODO(int)
  | CHANGE_STATUS(int, statusType);

type state = {
  todos: list(todoItem),
  watchIndex: int,
  doneTodos: list(todoItem),
  text: string,
};

let basicItem = {
  processingTime: 0,
  status: LOW,
  pauseCount: 0,
  title: "",
};

let makeTodoItem = (text: string): todoItem => {...basicItem, title: text};
let parseStatusString = (status) => switch status {
| LOW => "Low"
| MIDDLE => "Middle"
| HIGH => "High"
| URGENT => "Urgent"
};
let parseStatusType = (status) => switch status {
  | "Low" => LOW
  | "Middle" => MIDDLE
  | "High" => HIGH
  | "Urgent" => URGENT
};
let perTodos = Localstorage.getTodos();

[@react.component]
let make = () => {
  let (state, dispatch) =
    React.useReducer(
      (state, action) =>
        switch (action) {
        | WATCH_TODO(index) => {...state, watchIndex: index}
        | CHANGE_STATUS(index, status) => {
          let nextTodos = List.mapi((i, t) => {
            index === i
              ? {...t, status}
              : t;
          }, state.todos);
          Localstorage.saveTodos(nextTodos);
          {...state, todos: nextTodos}
        }
        | ADD_TODO(text) =>
          text === ""
            ? state
            : {
              let todos = [makeTodoItem(text), ...state.todos];
              Localstorage.saveTodos(todos);
              {...state, text: "", todos};
            }
        | DELETE_TODO(index) => {
          let nextTodos = Utils.removeInListByIndex(index, state.todos);
          Localstorage.saveTodos(nextTodos);
          { ...state, todos: nextTodos}
        }
        | EDIT_TODO(index, nextItem) => {
            ...state,
            todos: Utils.setElementAt(~index, ~value=nextItem, state.todos),
          }
        | CHANGE_TEXT(text) => {...state, text}
        | _ => state
        },
      {todos: perTodos, text: "", watchIndex: -1, doneTodos: []},
    );

  let handleDeleteTodo = (index: int, evnet_: ReactEvent.Mouse.t) => {
    dispatch(DELETE_TODO(index));
  };
  let handleChangeStatus = (index:int, status: string, _event_) => {
    let nextStatus = parseStatusType(status);
    dispatch(CHANGE_STATUS(index, nextStatus));
  };

  <NavgationWrapper>
    <div className="container fluid">
      <div className="row input-group fluid">
        <input
          type_="text"
          id="Username"
          placeholder="add Task"
          value={state.text}
          onChange={event =>
            dispatch(CHANGE_TEXT(ReactEvent.Form.target(event)##value))
          }
        />
        <button
          className="primary"
          onClick={event => dispatch(ADD_TODO(state.text))}>
          {ReasonReact.string({j|新增|j})}
        </button>
      </div>
      <div className="row">
        <div className="col-sm-6">
          <div className="col-sm-12 card fluid">
            <div className="section">
              <h3> {ReasonReact.string("Todo")} </h3>
            </div>
          </div>
          {React.array(
             Array.of_list(
               List.mapi(
                 (index, todo) =>
                   <PomodoroItem
                    index
                     handleChangeStatus={handleChangeStatus}
                     key={"todo-" ++ string_of_int(index)}
                     title={todo.title}
                     handleDeleteTodo
                     todoStatus={parseStatusString(todo.status)}
                     handleTodoDetail={_evnet =>
                       ReasonReactRouter.push("/pomodoro/1")
                     }
                   />,
                 state.todos,
               ),
             ),
           )}
          <div className="col-sm-12 card fluid">
            <div className="section">
              <h3> {ReasonReact.string("Done")} </h3>
            </div>
          </div>
          {React.array(
             Array.of_list(
               List.mapi(
                 (index, todo) =>
                   <p>{"dont todo" |> ReasonReact.string}</p>,
                 state.doneTodos,
               ),
             ),
           )}
        </div>
        <PomodoroCountdown />
      </div>
    </div>
  </NavgationWrapper>;
};