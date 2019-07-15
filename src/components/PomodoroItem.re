[@react.component]
let make = (~handleDeleteTodo, ~handleTodoDetail, ~index, ~title: string) => {
    <div className="col-sm-12 card fluid">
      <div className="section">
        <p> {ReasonReact.string(title)} </p>
        <p> {ReasonReact.string("status 1")} </p>
        <div className="section button-group">
          <button className="tertiary" onClick=handleTodoDetail>
            {ReasonReact.string({j|開始|j})}
          </button>
          <button className="secondary" onClick={handleDeleteTodo(index)}>
            {ReasonReact.string({j|刪除|j})}
          </button>
        </div>
      </div>
    </div>;
};