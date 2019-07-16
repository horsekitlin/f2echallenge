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

[@react.component]
let make = (~taskId: string) => {
  let (state, dispatch) =
    React.useReducer(
      (state, action) =>
        switch (action) {
        | _ => state
        },
      {
        todos: [],
        text: "",
      },
    );
  <div>
    {ReasonReact.string("Pomodoro screen task id: " ++ taskId)}
  </div>
}
