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
  | DONE_TODO(int)
  | ADD_PAUSE_COUNT(int, todoItem)
  | CHANGE_STATUS(int, statusType);

type state = {
  todos: list(todoItem),
  watchIndex: int,
  doneTodos: list(todoItem),
  text: string,
};

let basicItem = {processingTime: 0, status: LOW, pauseCount: 0, title: ""};

let makeTodoItem = (text: string): todoItem => {...basicItem, title: text};
let parseStatusString = status =>
  switch (status) {
  | LOW => "Low"
  | MIDDLE => "Middle"
  | HIGH => "High"
  | URGENT => "Urgent"
  };
let parseStatusType = statusStr =>
  switch (statusStr) {
  | "Low" => LOW
  | "Middle" => MIDDLE
  | "High" => HIGH
  | "Urgent" => URGENT
  | _ => LOW
  };

let perTodos = Localstorage.getTodos();
let perDoneTodos = Localstorage.getDoneTodos();

[@react.component]
let make = () => {
  let (state, dispatch) =
    React.useReducer(
      (state, action) =>
        switch (action) {
        | WATCH_TODO(index) => {...state, watchIndex: index}
        | ADD_PAUSE_COUNT(index, nextItem) =>
          let nextTodos =
            Utils.setElementAt(~index, ~value=nextItem, state.todos);
          Localstorage.saveTodos(nextTodos);
          {...state, todos: nextTodos};
        | CHANGE_STATUS(index, status) =>
          let nextTodos =
            List.mapi(
              (i, t) => index === i ? {...t, status} : t,
              state.todos,
            );
          Localstorage.saveTodos(nextTodos);
          {...state, todos: nextTodos};
        | ADD_TODO(text) =>
          text === ""
            ? state
            : {
              let todos = [makeTodoItem(text), ...state.todos];
              Localstorage.saveTodos(todos);
              {...state, text: "", todos};
            }
        | DONE_TODO(index) =>
          let todo = List.nth(state.todos, index);
          let nextTodos = Utils.removeInListByIndex(index, state.todos);
          Js.log(nextTodos);
          let doneTodos = [todo, ...state.doneTodos];
          Localstorage.saveTodos(nextTodos);
          Localstorage.saveDoneTodos(doneTodos);
          {...state, todos: nextTodos};
        | DELETE_TODO(index) =>
          let nextTodos = Utils.removeInListByIndex(index, state.todos);
          Localstorage.saveTodos(nextTodos);
          {...state, todos: nextTodos};
        | EDIT_TODO(index, nextItem) => {
            ...state,
            todos: Utils.setElementAt(~index, ~value=nextItem, state.todos),
          }
        | CHANGE_TEXT(text) => {...state, text}
        | _ => state
        },
      {todos: perTodos, text: "", watchIndex: (-1), doneTodos: perDoneTodos},
    );

  let handleDeleteTodo = (index: int, _evnet_: ReactEvent.Mouse.t) => {
    dispatch(DELETE_TODO(index));
  };
  let handleAddPauseCount = (index: int) => {
    let todo = List.nth(state.todos, index);
    let nextTodo = {...todo, pauseCount: todo.pauseCount + 1};
    dispatch(ADD_PAUSE_COUNT(index, nextTodo));
  };
  let handleWatchTodo = (index: int, _event_) => {
    dispatch(WATCH_TODO(index));
  };
  let handleDoneTodo = (index: int) => {
    dispatch(DONE_TODO(index));
  };
  let handleChangeStatus = (index: int, status: string, _event_) => {
    let nextStatus = parseStatusType(status);
    dispatch(CHANGE_STATUS(index, nextStatus));
  };
Js.log(state.doneTodos);
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
                     handleChangeStatus
                     handleWatchTodo
                     key={"todo-" ++ string_of_int(index)}
                     title={todo.title}
                     pauseCount={todo.pauseCount}
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
          // {React.array(
          //    Array.of_list(
          //      List.map(
          //        (todo) =>
          //         <div className="col-sm-12 card fluid">
          //            <p> 
          //             {todo.title |> ReasonReact.string}
          //            </p>
          //            <p>
          //              {"pause count: " |> ReasonReact.string}
          //              {todo.pauseCount |> string_of_int |> ReasonReact.string}
          //            </p>
          //            <p>
          //              {"status: " |> ReasonReact.string}
          //              {todo.status |> parseStatusString |> ReasonReact.string}
          //            </p>
          //          </div>,
          //        state.doneTodos,
          //      ),
          //    ),
          //  )}
        </div>
        <PomodoroCountdown
          handleAddPauseCount
          handleDoneTodo
          watchIndex={state.watchIndex}
        />
      </div>
    </div>
  </NavgationWrapper>;
};