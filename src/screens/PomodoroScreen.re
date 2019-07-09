[@react.component]
let make = (~taskId: string) => {

  <div className="card">
    {ReasonReact.string("Pomodoro screen task id: " ++ taskId)}
  </div>
}
