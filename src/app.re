type url = {
  path: list(string),
  hash: string,
  search: string
};

let handleClick = (_event) => Js.log("clicked!");

[@react.component]
let make = () => {
  let url = ReasonReactRouter.useUrl();

  switch (url.path) {
  | ["f2echallenge", "w2"] => <F2echallengeW2RE show={true} message="myBanner" />

  | ["pomodoro", "dashboard"] => <PomodoroDashboard />
  | ["f2echallenge", "pomodoro", "dashboard"] => <PomodoroDashboard />
  | ["pomodoro", "report"] => <PomodoroReport />
  | ["f2echallenge", "pomodoro", "report"] => <PomodoroReport />
  | ["pomodoro", taskId] => <PomodoroScreen taskId=taskId />
  | ["f2echallenge", "pomodoro", taskId] => <PomodoroScreen taskId=taskId />
  | _ => <HomeScreen />
  };
}