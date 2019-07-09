Uitls.require("./index.css");
Uitls.require("mini.css");
[@bs.module "./serviceWorker"]
external register_service_worker : unit => unit = "register";
[@bs.module "./serviceWorker"]
external unregister_service_worker : unit => unit = "unregister";

ReactDOMRe.renderToElementWithId(
  <App />,
  "root",
);

unregister_service_worker();
