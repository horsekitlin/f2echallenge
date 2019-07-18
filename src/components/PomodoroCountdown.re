type modeType =
  | Pomodoro
  | Break;

type status =
  | Start
  | Stop;

type action =
  | TogglePlay(string)
  | ChangeMode
  | Tick
  | Done
  | Reset;

type state = {
  timeLeft: int,
  status: string,
  mode: modeType,
  play: bool,
};

let getNextMode = (mode) => switch mode {
| Pomodoro => Break
| Break => Pomodoro
};

let getNextTimeLeft = mode =>
  switch (mode) {
  | Pomodoro => 1500
  | Break => 300
  };

let tickTimeLeft = (status, timeLeft) => status === "pause"? timeLeft: timeLeft - 1;

[@react.component]
let make = () => {
  let (state, dispatch) =
    React.useReducer(
      (state, action) =>
        switch (action) {
        | TogglePlay(status) => {...state, status}
        | ChangeMode => {
          let nextMode = state.mode === Break ? Pomodoro : Break;
          let nextTimeLeft = getNextTimeLeft(nextMode);
          {...state, mode: nextMode, timeLeft: nextTimeLeft};
        }
        | Tick =>
          let {timeLeft, status, mode} = state;
          let shouldChangeMode = timeLeft === 0;
          let nextMode = shouldChangeMode ?  getNextMode(mode): mode;
          let nextStatus = shouldChangeMode ? "pause": status;
          let nextTimeLeft = shouldChangeMode?  getNextTimeLeft(mode): tickTimeLeft(status, timeLeft);
          {
            ...state,
            status: nextStatus,
            mode: nextMode,
            timeLeft: nextTimeLeft
          };
        | _ => state
        },
      {timeLeft: getNextTimeLeft(Pomodoro), status: "pause", mode: Pomodoro, play: false},
    );

  let handleTooglePlay = (status, event_) => dispatch(TogglePlay(status));

  <div className="col-sm-6 fluid">
    <div className="row">
      <p> {ReasonReact.string({j|開始專心|j})} </p>
    </div>
    <CountdownBlock
      handleTooglePlay
      handleCountdown={(event_) => dispatch(Tick)}
      status={state.status}
      timeLeft={state.timeLeft}
    />
    <div className="row">
      <div className="col-sm-8 bordered">
        // <input type_="checkbox" />
         <p> {ReasonReact.string({j|專心閱讀|j})} </p> </div>
      <div className="col-sm-4 bordered">
        <p> {ReasonReact.string("2019-07-15")} </p>
      </div>
    </div>
  </div>;
};