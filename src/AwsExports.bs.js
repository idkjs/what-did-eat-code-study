// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE
'use strict';

var AwsExportsJs = require("./aws-exports.js");

var json = AwsExportsJs.default;

function awsExportsFromJs(data) {
  return /* record */[
          /* aws_project_region */data.aws_project_region,
          /* identityPoolId */data.aws_cognito_identity_pool_id,
          /* cognitoRegion */data.aws_cognito_region,
          /* userPoolId */data.aws_user_pools_id,
          /* userPoolWebClientId */data.aws_user_pools_web_client_id,
          /* aws_appsync_graphqlEndpoint */data.aws_appsync_graphqlEndpoint,
          /* aws_appsync_region */data.aws_appsync_region,
          /* aws_appsync_authenticationType */data.aws_appsync_authenticationType,
          /* aws_appsync_apiKey */data.aws_appsync_apiKey
        ];
}

var config = awsExportsFromJs(json);

var identityPoolId = config[/* identityPoolId */1];

var region = config[/* cognitoRegion */2];

var userPoolId = config[/* userPoolId */3];

var userPoolWebClientId = config[/* userPoolWebClientId */4];

var data = json;

exports.json = json;
exports.awsExportsFromJs = awsExportsFromJs;
exports.data = data;
exports.config = config;
exports.identityPoolId = identityPoolId;
exports.region = region;
exports.userPoolId = userPoolId;
exports.userPoolWebClientId = userPoolWebClientId;
/* json Not a pure module */
