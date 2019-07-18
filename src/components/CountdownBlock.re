let formatTime = (time: int) =>
  time < 10 ? "0" ++ string_of_int(time) : string_of_int(time);

let convertedTime = seconds => {
  let minutes = seconds / 60;
  let secondsRemaining = seconds mod 60;
  let minutesRemaining = minutes mod 60;

  formatTime(minutesRemaining) ++ ":" ++ formatTime(secondsRemaining);
};

[@react.component]
let make =
    (
      ~timeLeft,
      ~status,
      ~handleTooglePlay,
      ~handleCountdown
    ) => {

  React.useEffect0(() => {
    let timerId =
      Js.Global.setInterval(() => handleCountdown(timeLeft),1000);
    Some(() => Js.Global.clearInterval(timerId));
  });

  <div>
    <div className="row">
      <div className="bordered circular">
        <p> {timeLeft |> convertedTime |> ReasonReact.string} </p>
      </div>
    </div>
    <div className="row"> <ActionButton status handleTooglePlay /> </div>
  </div>;
};