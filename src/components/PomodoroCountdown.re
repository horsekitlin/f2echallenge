type mode =
  | Pomodoro
  | ShortBreak
  | LongBreak;

type status =
  | Start
  | Stop;

type action =
  | TogglePlay(string)
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
        | _ => state
        },
      {timeLeft: 300, status: "pause", mode: Pomodoro, play: false},
    );

  <div className="col-sm-6 fluid">
    <div className="row">
      <p> {ReasonReact.string({j|開始專心|j})} </p>
    </div>
    <div className="row">
      <div className="bordered circular">
        <p> {state.timeLeft |> convertedTime |> ReasonReact.string} </p>
      </div>
    </div>
    <div className="row"> <ActionButton status={state.status} handleTooglePlay={(status) => (event_) => dispatch(TogglePlay(status))} /> </div>
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