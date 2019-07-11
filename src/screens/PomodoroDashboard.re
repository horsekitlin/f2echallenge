
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
  | EDIT_TODO(string)
  | DELETE_TODO(int);

type state = {todos: list(todoItem), text: string};

let makeTodoItem = (text: string): todoItem => ({
  processingTime: 0,
  status: LOW,
  priority: "",
  title: text,
  annotation: "",
});

[@react.component]
let make = () => {
  let (state, dispatch) =
    React.useReducer(
      (state, action) =>
        switch (action) {
        | ADD_TODO(text) => {...state, todos: [makeTodoItem(text), ...state.todos]}
        | CHANGE_TEXT(text) => {...state, text}
        | DELETE_TODO(index) => {...state, todos: []}
        | _ => state
        },
      {todos: [], text: ""},
    );

  <NavgationWrapper>
    <div className="container fluid">
      <div className="row input-group fluid">
        <input
          type_="text"
          id="Username"
          placeholder="add Task"
          value={state.text}
          onChange={(event) => dispatch(CHANGE_TEXT(ReactEvent.Form.target(event)##value))}
          />
          <button className="primary">
            {ReasonReact.string({j|新增|j})}
          </button>
      </div>
      <div className="row">
        <ul className="col-sm-12">
          <PomodoroItem />
          <PomodoroItem />
          <PomodoroItem />
        </ul>
      </div>
    </div>
  </NavgationWrapper>;
};