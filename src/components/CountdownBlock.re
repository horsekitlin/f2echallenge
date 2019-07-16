[@react.component]
let make = (~timeLeft, ~status, ~handleTooglePlay, ~handleTick) => {
  React.useEffect0(() => {
    let timerId = Js.Global.setInterval(handleTick, 1000);
  Some(() => Js.Global.clearInterval(timerId));
  });

  <div>
    <div className="row">
      <div className="bordered circular">
        <p> {timeLeft |> ReasonReact.string} </p>
      </div>
    </div>
    <div className="row"> <ActionButton status handleTooglePlay /> </div>
  </div>;
};