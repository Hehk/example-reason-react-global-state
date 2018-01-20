type state = {count: int};

let initialState = () => {count: 0};

type action =
  | Increment
  | Decrement;

let reducer = (action, state) =>
  switch action {
  | Increment => ReasonReact.Update({count: state.count + 1})
  | Decrement => ReasonReact.Update({count: state.count - 1})
  };

let reducer_2 = (action, state) =>
  switch action {
  | Increment => {count: state.count + 1}
  | Decrement => {count: state.count - 1}
  };

let component = ReasonReact.statelessComponent("Counter");

let make = (~dispatch, ~counterState, _children) => {
  ...component,
  render: (_self) =>
    <div>
      <h1> (ReasonReact.stringToElement(string_of_int(counterState.count))) </h1>
      <button onClick=((_e) => dispatch(Increment))> (ReasonReact.stringToElement("+")) </button>
      <button onClick=((_e) => dispatch(Decrement))> (ReasonReact.stringToElement("-")) </button>
    </div>
};
