[@react.component]
let make = () => {
  let publicurl = [%raw {|
    process.env.PUBLIC_URL
  |}];

  <div>
    <header>
      <label htmlFor="drawer-checkbox" className="button drawer-toggle"></label>
      <a href={publicurl ++ "/"} className="logo">{ReasonReact.string("f2echallenge")}</a>
      <a href={publicurl ++ "/pomodoro/dashboard"} className="button">{ReasonReact.string("w1-pomodoro")}</a>
      <span>{ReasonReact.string("|")}</span>
    </header>
    <div className="container">
    <div className="row">
    <div className="col-sm-12 col-md-12 col-lg-12">
      <p>{ReasonReact.string("Page content")}</p>
    </div>
    </div>
    </div>
  </div>;
}