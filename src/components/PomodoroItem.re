let pickClasses = [|"small", "primary"|];
let defaultClasses = [|"small"|];

let pickClasses = (todoStatus, targetStatus) =>
  todoStatus === targetStatus ? pickClasses : defaultClasses;
[@react.component]
let make =
    (
      ~handleDeleteTodo,
      ~handleTodoDetail,
      ~index,
      ~title,
      ~todoStatus,
      ~handleChangeStatus,
    ) => {
  <div className="col-sm-12 card fluid">
    <div className="section">
      <p> {title |> ReasonReact.string} </p>
      <div className="button-group">
        <button
          onClick={_event_ => handleChangeStatus("Low")}
          className={
            pickClasses(todoStatus, "Low") |> Js.Array.joinWith(" ")
          }>
          {"Low" |> ReasonReact.string}
        </button>
        <button
          onClick={_event_ => handleChangeStatus("Middle")}
          className={
            pickClasses(todoStatus, "Middle") |> Js.Array.joinWith(" ")
          }>
          {"Middle" |> ReasonReact.string}
        </button>
        <button
          onClick={_event_ => handleChangeStatus("High")}
          className={
            pickClasses(todoStatus, "High") |> Js.Array.joinWith(" ")
          }>
          {"High" |> ReasonReact.string}
        </button>
        <button
          onClick={_event_ => handleChangeStatus("Urgent")}
          className={
            pickClasses(todoStatus, "Urgent") |> Js.Array.joinWith(" ")
          }>
          {"Urgent" |> ReasonReact.string}
        </button>
      </div>
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