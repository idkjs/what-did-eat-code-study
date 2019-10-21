type loginStatusT =
  | LoggedIn(string)
  | NotLoggedIn;

type action =
  | Login(string)
  | Logout;

type state = {loginStatus: loginStatusT};
let initialState = {loginStatus: NotLoggedIn};
let reducer = (_state, action) =>
  switch (action) {
  | Login(token) => {loginStatus: LoggedIn(token)}
  | Logout => {loginStatus: NotLoggedIn}
  };
[@react.component]
let make = (~token: option(string)) => {
  let (state, dispatch) = React.useReducer(reducer, initialState);
  React.useEffect1(
    () => {
      Js.log2("token: ", token |> Js.Option.getWithDefault("No token"));
      None;
    },
    [|token|],
  );
  <div>
    {switch (state.loginStatus) {
     | NotLoggedIn =>
       <Login onLoginSuccess={token => dispatch(Login(token))} />
     | LoggedIn(token) => <div> {React.string("Logged in: " ++ token)} </div>
     }}
  </div>;
};