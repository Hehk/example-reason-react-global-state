type filter =
  | Completed
  | UnCompleted
  | None;

type item = {
  name: string,
  completed: bool
};

type state = {
  input: string,
  items: list(item),
  filter
};

let initialState = () => {
  input: "test",
  items: [{name: "initial item", completed: true}, {name: "kewl\n  item", completed: false}],
  filter: None
};

type action =
  | AddItem(item)
  | RemoveItem(item)
  | ChangeInput(string)
  | ToggleItem(string)
  | ChangeFilter(filter);

let reducer = (action, state) =>
  switch action {
  | AddItem(item) => {...state, items: [item, ...state.items], input: ""}
  | RemoveItem(item) => {...state, items: List.filter((elem: item) => elem.name != item.name, state.items)}
  | ChangeInput(input) => {...state, input}
  | ToggleItem(name) => {
      ...state,
      items:
        List.map(
          (item) =>
            if (name == item.name) {
              {...item, completed: ! item.completed}
            } else {
              item
            },
          state.items
        )
    }
  | ChangeFilter(filter) => {...state, filter}
  };

let createItem = (~name, ()) => {name, completed: false};

let component = ReasonReact.statelessComponent("App");

let make = (~dispatch, ~todoState, _children) => {
  ...component,
  render: (_self) =>
    <div>
      <input value=todoState.input onChange=((e) => dispatch(ChangeInput(Obj.magic(e)##target##value))) />
      <button onClick=((_e) => dispatch(AddItem(createItem(~name=todoState.input, ()))))>
        (ReasonReact.stringToElement("add"))
      </button>
      <ul>
        (
          todoState.items
          |> List.filter(
               (item) =>
                 switch todoState.filter {
                 | None => true
                 | Completed => item.completed
                 | UnCompleted => ! item.completed
                 }
             )
          |> List.map(
               ({name, completed}) =>
                 <li
                   key=name
                   className=(completed ? "strike-through" : "")
                   onClick=((_e) => dispatch(ToggleItem(name)))>
                   (ReasonReact.stringToElement(name))
                 </li>
             )
          |> Array.of_list
          |> ReasonReact.arrayToElement
        )
      </ul>
      <ul className="filter-list">
        <li
          className=(todoState.filter == None ? "filter__active filter" : "filter")
          onClick=((_e) => dispatch(ChangeFilter(None)))>
          (ReasonReact.stringToElement("No Filter"))
        </li>
        <li
          className=(todoState.filter == Completed ? "filter__active filter" : "filter")
          onClick=((_e) => dispatch(ChangeFilter(Completed)))>
          (ReasonReact.stringToElement("Completed"))
        </li>
        <li
          className=(todoState.filter == UnCompleted ? "filter__active filter" : "filter")
          onClick=((_e) => dispatch(ChangeFilter(UnCompleted)))>
          (ReasonReact.stringToElement("UnCompleted"))
        </li>
      </ul>
    </div>
};
