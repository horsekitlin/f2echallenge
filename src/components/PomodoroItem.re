[@react.component]
let make = () => {
  <li>
    <div className="col-sm-12">
      <div className="section">
        <p> {ReasonReact.string("task 1")} </p>
        <p> {ReasonReact.string("status 1")} </p>
        <div className="section button-group">
          <button className="tertiary">
            {ReasonReact.string({j|開始|j})}
          </button>
          <button className="secondary">
            {ReasonReact.string({j|刪除|j})}
          </button>
        </div>
      </div>
    </div>
  </li>;
};