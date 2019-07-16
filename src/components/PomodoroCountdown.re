type mode =
  | Pomodoro
  | ShortBreak
  | LongBreak;

type status =
  | Start
  | Stop;

type action =
  | TogglePlay(string)
  | Tick
  | Done
  | Reset;

type state = {
  timeLeft: int,
  status: string,
  mode,
  play: bool,
};

let formatTime = (time: int) =>
  time < 10 ? "0" ++ string_of_int(time) : string_of_int(time);

let convertedTime = seconds => {
  let minutes = seconds / 60;
  let secondsRemaining = seconds mod 60;
  let minutesRemaining = minutes mod 60;

  formatTime(minutesRemaining) ++ ":" ++ formatTime(secondsRemaining);
};

[@react.component]
let make = () => {
  let (state, dispatch) =
    React.useReducer(
      (state, action) =>
        switch (action) {
        | TogglePlay(status) => {...state, status}
        | Tick => {...state, timeLeft: state.timeLeft - 1}
        | _ => state
        },
      {timeLeft: 300, status: "pause", mode: Pomodoro, play: false},
    );

  let handleTooglePlay = (status, event_) => dispatch(TogglePlay(status));
  <div className="col-sm-6 fluid">
    <div className="row">
      <p> {ReasonReact.string({j|開始專心|j})} </p>
    </div>
    <CountdownBlock
      handleTooglePlay
      handleTick={_event => dispatch(Tick)}
      status={state.status}
      timeLeft={state.timeLeft |> convertedTime}
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