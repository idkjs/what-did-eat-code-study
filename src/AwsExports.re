[@bs.module "./aws-exports.js"] external json: Js.t('a) = "default";
external castFromJst: Js.t('a) => 'a = "%identity";
type t = {
  aws_project_region: string,
  identityPoolId: string,
  cognitoRegion: string,
  userPoolId: string,
  userPoolWebClientId: string,
  aws_appsync_graphqlEndpoint: string,
  aws_appsync_region: string,
  aws_appsync_authenticationType: string,
  aws_appsync_apiKey: string,
};

[@bs.deriving abstract]
type awsExportsJs = {
  aws_project_region: string,
  aws_cognito_identity_pool_id: string,
  aws_cognito_region: string,
  aws_user_pools_id: string,
  aws_user_pools_web_client_id: string,
  aws_appsync_graphqlEndpoint: string,
  aws_appsync_region: string,
  aws_appsync_authenticationType: string,
  aws_appsync_apiKey: string,
};
let awsExportsFromJs: awsExportsJs => t =
  data => {
    aws_project_region: aws_project_regionGet(data),
    identityPoolId: aws_cognito_identity_pool_idGet(data),
    cognitoRegion: aws_cognito_regionGet(data),
    userPoolId: aws_user_pools_idGet(data),
    userPoolWebClientId: aws_user_pools_web_client_idGet(data),
    aws_appsync_graphqlEndpoint: aws_appsync_graphqlEndpointGet(data),
    aws_appsync_region: aws_appsync_regionGet(data),
    aws_appsync_authenticationType: aws_appsync_authenticationTypeGet(data),
    aws_appsync_apiKey: aws_appsync_apiKeyGet(data),
  };
let data: awsExportsJs = json->castFromJst;
let config = awsExportsFromJs(data);
let identityPoolId = config.identityPoolId;
let region = config.cognitoRegion;
let userPoolId = config.userPoolId;
let userPoolWebClientId = config.userPoolWebClientId;
/* Js.log2("aws_project_config", config.aws_user_pools_id)*/
// Js.log2("aws_project_config", config);