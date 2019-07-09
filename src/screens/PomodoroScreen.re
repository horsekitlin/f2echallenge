[@react.component]
let make = (~taskId: string) => {
  Js.log(taskId);

  <div>
    {ReasonReact.string("Pomodoro screen task id: " ++ taskId)}
  </div>
}
