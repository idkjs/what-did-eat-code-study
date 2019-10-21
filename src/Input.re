
[@react.component]
let make = (~caption, ~type_="text", ~onChange, ~value) => {
  <div>
    {React.string(caption)}
    <input
      type_
      value
      onChange={e => {
        Js.log2(
          "ReactEvent.Form.currentTarget(e)##value",
          ReactEvent.Form.currentTarget(e)##value,
        );
        e->ReactEvent.Form.currentTarget##value
        |> onChange;
      }}
    />
  </div>;
};