open Css;

module Styles = {
  let customerCardBox = (isCustomerSelected: bool) =>
    style([
      flexDirection(column),
      width(vw(10.0)),
      isCustomerSelected
        ? border(px(3), solid, green) : border(px(3), none, green),
    ]);
};

let isCustomerSelected =
    (currentCustomer: Customer.t, selectedCustomer: option(Customer.t)): bool => {
  switch (selectedCustomer) {
  | Some(selectedCustomer) => currentCustomer.id === selectedCustomer.id
  | None => false
  };
};

[@react.component]
let make =
    (
      ~customer: Customer.t,
      ~selectCustomer: Customer.t => unit,
      ~selectedCustomer: option(Customer.t),
      _,
    ) => {
  <div
    className={Styles.customerCardBox(
      isCustomerSelected(customer, selectedCustomer),
    )}
    onClick={_event => selectCustomer(customer)}>
    <div> {React.string(customer.name)} </div>
  </div>;
};
