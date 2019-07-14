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


[@react.component]
let make = () => {
  let (state, dispatch) =
    React.useReducer(
      (state, action) =>
        switch (action) {
        | ADD_TODO(text) => 
          text === "" 
            ? state
            : ({
              ...state,
              text: "",
              todos: [makeTodoItem(text), ...state.todos],
            })
        | DELETE_TODO(index) => {
            ...state,
            todos: Uitls.removeInListByIndex(index, state.todos),
          }
        | EDIT_TODO(index, nextItem) => {
            ...state,
            todos: Uitls.setElementAt(~index, ~value=nextItem, state.todos),
          }
        | CHANGE_TEXT(text) => {...state, text}
        | _ => state
        },
      {
        todos: [],
        text: "",
      },
    );

  let handleDeleteTodo = 
    (index:int) =>
      (evnet: ReactEvent.Mouse.t) => {
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
        <ul className="col-sm-12">
          {React.array(
             Array.of_list(List.mapi(
               (index, todo) => 
                <PomodoroItem
                  index={index}
                  title={todo.title}
                  handleDeleteTodo={handleDeleteTodo}
                />, state.todos)),
           )}
        </ul>
      </div>
    </div>
  </NavgationWrapper>;
};