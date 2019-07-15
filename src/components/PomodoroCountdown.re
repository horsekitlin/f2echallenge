type status =
  | Start
  | Stop;

type state = {countNum: int};

[@react.component]
let make = () => {
  let (state, dispatch) =
    React.useReducer(
      (state, action) =>
        switch (action) {
        | _ => state
        },
      {countNum: 300},
    );
  <div className="col-sm-6 fluid">
    <div className="row">
      <p> {ReasonReact.string({j|開始專心|j})} </p>
    </div>
    <div className="row">
      <div className="bordered circular">
        <p> {ReasonReact.string("25:00")} </p>
      </div>
    </div>
    <div className="row"> <button className="fa fa-play" /> </div>
    <div className="row">
      <div className="col-sm-8 bordered">
        <input type_="checkbox" />
        {ReasonReact.string({j|專心閱讀|j})}
      </div>
      <div className="col-sm-4 bordered">
        <p> {ReasonReact.string("2019-07-15")} </p>
      </div>
    </div>
  </div>;
};