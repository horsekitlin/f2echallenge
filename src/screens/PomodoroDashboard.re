type action =
  | ADD_TODO
  | EDIT_TODO
  | DELETE_TODO;

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
  content: string,
  annotation: string
};

type state = {
  todos: list(todoItem),
};

[@react.component]
let make = () => {
  let (state, dispatch) = React.useReducer((state, action) => switch(action) {
  | _ => state
  }, {todos: []});

  <div>
    {ReasonReact.string("Pomodoro dashboard screen")}
  </div>
}
