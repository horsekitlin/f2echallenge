type action =
  | ADD_TODO
  | EDIT_TODO
  | DELETE_TODO;

type statusType = 
  | LOW
  | MID
  | HIGH
  | URGENT;

type todoItem = {
  processingTime: int,
  status: statusType,
  priority: string,
  title: string,
  content: string,
  annotation: string
};

type state = {
  todos: list(todoItem),
};

[@react.component]
let make = () => {
  let (state, dispatch) = React.useReducer((state, action) => switch(action) {
  | _ => state
  }, {todos: []});

  <NavgationWrapper>
    <div className="tabs">
      <input type_="radio" name="tab-group" id="tab1" checked=true ariaHidden=true />
      <label htmlFor="tab1" ariaHidden=true>{ReasonReact.string("Tab 1")}</label>
      <div>
        <h3>{ReasonReact.string("Tab 1 content")}</h3>
      </div>
      
      <input type_="radio" name="tab-group" id="tab2" ariaHidden=true />
      <label htmlFor="tab2" ariaHidden=true>{ReasonReact.string("Tab 2")}</label>
      <div>
        <h3>{ReasonReact.string("Tab 2 content")}</h3>
      </div>
      <input type_="radio" name="tab-group" id="tab3" ariaHidden=true />
      <label htmlFor="tab3" ariaHidden=true>{ReasonReact.string("Tab 3")}</label>
      <div>
        <h3>{ReasonReact.string("Tab 1 content")}</h3>
      </div>
    </div>
  </NavgationWrapper>;
}
