type element =
  | Todo
  | Counter;

type state = {
  todo: Todo.state,
  counter: Counter.state,
  activeElement: element
};

type action =
  | Todo(Todo.action)
  | Counter(Counter.action)
  | ChangeElement(element);

let component = ReasonReact.reducerComponent("App");

let make = (_children) => {
  ...component,
  initialState: () => {todo: Todo.initialState(), counter: Counter.initialState(), activeElement: Todo},
  reducer: (action, state) =>
    switch action {
    | Todo(todoAction) => ReasonReact.Update({...state, todo: Todo.reducer(todoAction, state.todo)})
    | Counter(counterAction) =>
      ReasonReact.Update({...state, counter: Counter.reducer(counterAction, state.counter)})
    | ChangeElement(element) => ReasonReact.Update({...state, activeElement: element})
    },
  /* render: (self) => <div> </div> */
  render: ({state, send}) =>
    <div>
      <button onClick=((_e) => send(ChangeElement(Todo)))> (ReasonReact.stringToElement("todo")) </button>
      <button onClick=((_e) => send(ChangeElement(Counter)))> (ReasonReact.stringToElement("counter")) </button>
      <h1>(ReasonReact.stringToElement("Component"))</h1>
      (
        switch state.activeElement {
        | Todo => <Todo todoState=state.todo dispatch=((action) => send(Todo(action))) />
        | Counter => <Counter counterState=state.counter dispatch=((action) => send(Counter(action))) />
        }
      )
    </div>
};
