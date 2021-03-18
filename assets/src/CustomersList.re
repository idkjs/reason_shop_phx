open Prelude;

let customers_list =
    (
      customersMap: Belt.Map.Int.t(Customer.t),
      selectCustomer: Customer.t => unit,
      selectedCustomer: option(Customer.t),
    )
    : React.element =>
  customersMap
  |> Map.intMapToArray
  |> Belt.Array.map(_, (customer: Customer.t) =>
       <CustomerCard
         key={string_of_int(customer.id)}
         customer
         selectCustomer
         selectedCustomer
       />
     )
  |> React.array;

[@react.component]
let make =
    (
      ~customers: Belt.Map.Int.t(Customer.t),
      ~selectCustomer: Customer.t => unit,
      ~selectedCustomer: option(Customer.t),
    ) => {
  customers_list(customers, selectCustomer, selectedCustomer);
};
