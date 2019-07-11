let publicurl = [%raw {|
  process.env.PUBLIC_URL
|}];

let pushPath = (route) => (_event) => {
  ReasonReactRouter.push(publicurl ++ route);
};

[@react.component]
let make = () => {
  <NavgationWrapper>
      <p>{ReasonReact.string("Page content")}</p>
  </NavgationWrapper>;
}