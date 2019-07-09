type url = {
  /* path takes window.location.pathname, like "/book/title/edit" and turns it into `["book", "title", "edit"]` */
  path: list(string),
  /* the url's hash, if any. The # symbol is stripped out for you */
  hash: string,
  /* the url's query params, if any. The ? symbol is stripped out for you */
  search: string
};

let handleClick = (_event) => Js.log("clicked!");

[@react.component]
let make = (~message) => {
  let url = ReasonReactRouter.useUrl();
  Js.log(url);

  <div onClick={handleClick}>
    {ReasonReact.string(message)}
  </div>;
}