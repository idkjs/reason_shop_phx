open Phoenix;
open Prelude;
open Css;

module Styles = {
  let mainContainer =
    style([display(flexBox), flexDirection(row), backgroundColor(white)]);

  let customersColumn =
    style([
      display(flexBox),
      flexDirection(column),
      backgroundColor(ghostwhite),
      width(vw(20.0)),
    ]);

  let productsColumn =
    style([
      display(flexBox),
      flexDirection(row),
      flexWrap(wrap),
      backgroundColor(ghostwhite),
      width(vw(80.0)),
    ]);
};

type state = {
  customers: Belt.Map.Int.t(Customer.t),
  products: Belt.Map.Int.t(Product.t),
  current_customer: option(Customer.t),
};

let loadJoinDataToState = (data: InitialState.t): state => {
  customers: List.listToIntMap(data.customers, Customer.getId),
  products: List.listToIntMap(data.products, Product.getId),
  current_customer: None,
};

type action =
  | ReceiveJoinData(InitialState.t)
  | SelectCustomer(Customer.t);

let reducer = (state: state, action: action) =>
  switch (action) {
  | ReceiveJoinData(data) => loadJoinDataToState(data)
  | SelectCustomer(customer) => {...state, current_customer: Some(customer)}
  };

let initialState = {
  customers: Belt.Map.Int.empty,
  products: Belt.Map.Int.empty,
  current_customer: None,
};
[@react.component]
let make = _ => {
  let (state, dispatch) = React.useReducer(reducer, initialState);
  let selectCustomer = (customer: Customer.t): unit => {
    dispatch(SelectCustomer(customer));
  };

  let joinEventHandler = result =>
    switch (result) {
    | Belt.Result.Ok(data) => dispatch(ReceiveJoinData(data))
    | Belt.Result.Error(error) => Js.log(error)
    };
  React.useEffect0(() => {
    ShopChannel.onJoin()->Promise.get(result => joinEventHandler(result));
    None;
  });
  // React.useEffect0(() => {
  //   ShopChannel.onJoin()
  //   ->Promise.get(result =>
  //       switch (result) {
  //       | Belt.Result.Ok(data) => dispatch(ReceiveJoinData(data))
  //       | Belt.Result.Error(error) => Js.log(error)
  //       }
  //     );
  //   None;
  // });

  // ->Promise.getOk(result => result|>joinEventHandler)
  // ->Promise.getOk(result => result|>joinEventHandler)
  // None;
  // });
  <div className=Styles.mainContainer>
    <div className=Styles.customersColumn>
      <CustomersList
        customers={state.customers}
        selectCustomer
        selectedCustomer={state.current_customer}
      />
    </div>
    <div className=Styles.productsColumn>
      <ProductsList
        products={state.products}
        selectedCustomer={state.current_customer}
      />
    </div>
  </div>;
};
