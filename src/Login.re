module Input = {
  [@react.component]
  let make = (~caption, ~type_="text", ~onChange, ~value) => {
    <div>
      {React.string(caption)}
      <input
        type_
        value
        onChange={e => e->ReactEvent.Form.currentTarget##value |> onChange}
      />
    </div>;
  };
};

type loginType =
  | NewUser
  | ExistingUser
  | PasswordReset;

type loginStatusT =
  | NotLoggedIn
  | LoginInProgress
  | LoggedIn(string)
  | LoginError(string)
  | ChangingPassword(Aws.Amplify.userT, string);

type action =
  | Login
  | LoginFailed(string)
  | LoginSuccess(string)
  | ChangeView(loginType)
  | ChangeUsername(string)
  | ChangePassword(string)
  | ResetPassword(Aws.Amplify.userT, string, string)
  | NewPassword(Aws.Amplify.userT, string);

type state = {
  loginStatus: loginStatusT,
  username: string,
  password: string,
};

let errorMessage = (~error, ~visible) =>
  visible ? <div> {React.string(error)} </div> : React.null;

[@react.component]
let make = (~onLoginSuccess) => {
  let (state, dispatch) =
    React.useReducer(
      (state, action) =>
        switch (action) {
        | ChangeView(_view) => state
        | Login => {...state, loginStatus: LoginInProgress}

        | LoginFailed(error) => {...state, loginStatus: LoginError(error)}
        | LoginSuccess(token) =>
          onLoginSuccess(token);
          {...state, loginStatus: LoggedIn(token)};
        | ChangeUsername(username) => {...state, username}
        | ChangePassword(password) => {...state, password}
        | ResetPassword(user, oldPassword, newPassword) => {
            ...state,
            loginStatus: LoginInProgress,
          }
        //   //  /* Aws.Amplify.changePassword(~oldPassword, ~newPassword, user) */
        //   Aws.Amplify.completeNewPassword(~newPassword, user)
        //   // |> then_(result => {
        //   //      Js.log2("result", result);
        //   //      resolve();
        //   //    });
        | NewPassword(user, newPassword) => {
            ...state,
            loginStatus: ChangingPassword(user, newPassword),
          }
        },
      {loginStatus: NotLoggedIn, username: "", password: ""},
    );
  let handleLogin = () => {
    Js.log2("current_status", state.loginStatus);
    dispatch(Login) |> ignore;
    let {username, password} = state;
    Js.log2(username, password);
    Js.Promise.(
      Aws.Amplify.signIn(~username, ~password)
      |> then_(result => {
           Js.log2("SignInResult: ", result);
           Aws.Amplify.(
             switch (result) {
             | LoginSuccessful(data) => Js.log2("success", data)
             | LoginChallenge(data, user) =>
               Js.log3("challenge", data, user);
               dispatch(NewPassword(user, ""));
             | LoginFailure(error) =>
               switch (error) {
               | Message(msg) => dispatch(LoginFailed(msg))
               | Response(res) =>
                 dispatch(
                   LoginFailed(
                     res
                     |> Js.Json.stringifyAny
                     |> Js.Option.getWithDefault(""),
                   ),
                 )
               }
             }
           );
           resolve();
         })
      |> catch(err => {
           Js.log(err);
           let errMsg = "An error occurred: " ++ Js.String.make(err);
           dispatch(LoginFailed(errMsg));
           resolve();
         })
      |> ignore
    );
    switch (state.loginStatus) {
    | ChangingPassword(_user, newPassword) =>
      Js.log2("Changing password", newPassword)
    | NotLoggedIn => Js.log("Not logged in!!!")
    | LoggedIn(login) => Js.log2("Logged in", login)
    | LoginError(error) => Js.log2("Login error", error)
    | LoginInProgress =>
      Js.Promise.(
        Aws.Amplify.signIn(~username, ~password)
        |> then_(result => {
             Js.log2("SignInResult: ", result);
             Aws.Amplify.(
               switch (result) {
               | LoginSuccessful(data) => Js.log2("success", data)
               | LoginChallenge(data, user) =>
                 Js.log3("challenge", data, user);
                 dispatch(NewPassword(user, ""));
               | LoginFailure(error) =>
                 switch (error) {
                 | Message(msg) => dispatch(LoginFailed(msg))
                 | Response(res) =>
                   dispatch(
                     LoginFailed(
                       res
                       |> Js.Json.stringifyAny
                       |> Js.Option.getWithDefault(""),
                     ),
                   )
                 }
               }
             );
             resolve();
           })
        |> catch(err => {
             Js.log(err);
             let errMsg = "An error occurred: " ++ Js.String.make(err);
             dispatch(LoginFailed(errMsg));
             resolve();
           })
        |> ignore
      )
    };
  };
  /* helper components */
  let inputs = (username, password) =>
    <div>
      <Input
        value=username
        caption="Username"
        onChange={value => {
          Js.log2("value", value);
          dispatch(ChangeUsername(value));
        }}
      />
      <Input
        value=password
        caption="Password"
        onChange={value => dispatch(ChangePassword(value))}
      />
    </div>;

  let loginButton = (~onClick) =>
    <div>
      <button className="login-button" onClick>
        {React.string("Login")}
      </button>
    </div>;

  /* render login form */
  <form className="login" onSubmit={e => ReactEvent.Form.preventDefault(e)}>
    {switch (state.loginStatus) {
     | LoginInProgress => <div> {React.string("Logging in...")} </div>
     | LoginError(error) =>
       <div>
         {inputs(state.username, state.password)}
         {errorMessage(~error, ~visible=true)}
         {loginButton(~onClick=_e => dispatch(Login))}
       </div>
     | ChangingPassword(user, newPassword) =>
       <div>
         <div> {React.string("Reset password")} </div>
         <Input
           value=newPassword
           caption="New password"
           onChange={value => dispatch(NewPassword(user, value))}
         />
         {loginButton(~onClick=_e =>
            dispatch(ResetPassword(user, state.password, newPassword))
          )}
       </div>
     | _ =>
       <div>
         {inputs(state.username, state.password)}
         {loginButton(~onClick=_e => handleLogin())}
       </div>
     }}
  </form>;
};