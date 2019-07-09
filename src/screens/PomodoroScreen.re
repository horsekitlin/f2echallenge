
[@react.component]
let make = (~taskId: string) => {
  <div>
    {ReasonReact.string("Pomodoro screen task id: " ++ taskId)}
  </div>
}
