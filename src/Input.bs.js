// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE
'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");

function Input(Props) {
  var caption = Props.caption;
  var match = Props.type_;
  var type_ = match !== undefined ? match : "text";
  var onChange = Props.onChange;
  var value = Props.value;
  return React.createElement("div", undefined, caption, React.createElement("input", {
                  type: type_,
                  value: value,
                  onChange: (function (e) {
                      console.log("ReactEvent.Form.currentTarget(e)##value", e.currentTarget.value);
                      return Curry._1(onChange, e.currentTarget.value);
                    })
                }));
}

var make = Input;

exports.make = make;
/* react Not a pure module */
