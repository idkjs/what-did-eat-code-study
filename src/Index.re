let token = Util.LocalStorage.get("token");
Js.log2("token", token);
open AwsExports;
Aws.Amplify.configure(
  ~identityPoolId,
  ~region,
  ~userPoolId,
  ~userPoolWebClientId,
);


ReactDOMRe.renderToElementWithId(<App token />, "app");