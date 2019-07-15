type statusType =
  | LOW
  | MID
  | HIGH
  | URGENT;

type todoItem = {
  processingTime: int,
  status: statusType,
  priority: string,
  title: string,
  annotation: string,
};

type action =
  | CHANGE_TEXT(string)
  | ADD_TODO(string)
  | EDIT_TODO(int, todoItem)
  | DELETE_TODO(int);

type state = {
  todos: list(todoItem),
  doneTodos: list(todoItem),
  text: string,
};

let basicItem = {
  processingTime: 0,
  status: LOW,
  priority: "",
  title: "",
  annotation: "",
};

let makeTodoItem = (text: string): todoItem => {...basicItem, title: text};

let perTodos = Localstorage.getTodos();

[@react.component]
let make = () => {
  let (state, dispatch) =
    React.useReducer(
      (state, action) =>
        switch (action) {
        | ADD_TODO(text) =>
          text === ""
            ? state
            : {
              let todos = [makeTodoItem(text), ...state.todos];
              Localstorage.saveTodos(todos);
              {...state, text: "", todos};
            }
        | DELETE_TODO(index) => {
            ...state,
            todos: Utils.removeInListByIndex(index, state.todos),
          }
        | EDIT_TODO(index, nextItem) => {
            ...state,
            todos: Utils.setElementAt(~index, ~value=nextItem, state.todos),
          }
        | CHANGE_TEXT(text) => {...state, text}
        | _ => state
        },
      {todos: perTodos, text: "", doneTodos: []},
    );

  let handleDeleteTodo = (index: int, evnet: ReactEvent.Mouse.t) => {
    dispatch(DELETE_TODO(index));
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
                     title={todo.title}
                     handleDeleteTodo
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
                   <PomodoroItem
                     index
                     title={todo.title}
                     handleDeleteTodo
                     handleTodoDetail={_evnet =>
                       ReasonReactRouter.push("/pomodoro/1")
                     }
                   />,
                 state.todos,
               ),
             ),
           )}
        </div>
        <PomodoroCountdown />
      </div>
    </div>
  </NavgationWrapper>;
};