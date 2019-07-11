let publicurl = [%raw {|
  process.env.PUBLIC_URL
|}];

let pushPath = (route) => (_event) => {
  ReasonReactRouter.push(publicurl ++ route);
};

[@react.component]
let make = (~children) => {
  <div>
    <header>
      <label htmlFor="drawer-checkbox" className="button drawer-toggle"></label>
      <a href={publicurl ++ "/"} className="logo">{ReasonReact.string("f2echallenge")}</a>
      <button onClick=pushPath("/pomodoro/dashboard")>{ReasonReact.string("w1-pomodoro")}</button>
      <span>{ReasonReact.string("|")}</span>
    </header>
    <div className="container">
      children
    </div>
  </div>;
}