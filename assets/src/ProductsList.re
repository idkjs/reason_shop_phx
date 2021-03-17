open Prelude;

let products_list =
    (
      customersMap: Belt.Map.Int.t(Product.t),
      selectedCustomer: option(Customer.t),
    )
    : ReasonReact.reactElement =>
  customersMap
  |> Map.intMapToArray
  |> Belt.Array.map(_, (product: Product.t) =>
       <ProductCard
         key={string_of_int(product.id)}
         product
         selectedCustomer
       />
     )
  |> ReasonReact.array;

[@react.component]
let make =
    (
      ~products: Belt.Map.Int.t(Product.t),
      ~selectedCustomer: option(Customer.t),
    ) => {
  products_list(products, selectedCustomer);
};
