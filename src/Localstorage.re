[@bs.val] external unsafeJsonParse: string => 'a = "JSON.parse";

let localStorageNamespace = "reason-react-todos";
let doneTodosNamespace = "reason-react-done-todos";

let saveDoneTodos = todos => {
  switch (Js.Json.stringifyAny(todos)) {
    | None => ()
    | Some(stringifiedTodos) =>
      Dom.Storage.(
        localStorage |> setItem(doneTodosNamespace, stringifiedTodos)
      )
    };
};

let getDoneTodos = () => {
  let todos =
  switch (Dom.Storage.(localStorage |> getItem(doneTodosNamespace))) {
  | None => []
  | Some(todos) => unsafeJsonParse(todos)
  };
todos;
};

let saveTodos = todos => {
  switch (Js.Json.stringifyAny(todos)) {
  | None => ()
  | Some(stringifiedTodos) =>
    Dom.Storage.(
      localStorage |> setItem(localStorageNamespace, stringifiedTodos)
    )
  };
};

let getTodos = () => {
  let todos =
    switch (Dom.Storage.(localStorage |> getItem(localStorageNamespace))) {
    | None => []
    | Some(todos) => unsafeJsonParse(todos)
    };
  todos;
};