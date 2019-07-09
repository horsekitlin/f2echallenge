type url = {
  /* path takes window.location.pathname, like "/book/title/edit" and turns it into `["book", "title", "edit"]` */
  path: list(string),
  /* the url's hash, if any. The # symbol is stripped out for you */
  hash: string,
  /* the url's query params, if any. The ? symbol is stripped out for you */
  search: string
};

let handleClick = (_event) => Js.log("clicked!");

[@react.component]
let make = () => {
  let url = ReasonReactRouter.useUrl();

  switch (url.path) {
  | ["pomodoro", "dashboard"] => <PomodoroDashboard />
  | ["pomodoro", "report"] => <PomodoroReport />
  | ["pomodoro", taskId] => <PomodoroScreen taskId=taskId />
  | _ => <HomeScreen />
  };
}