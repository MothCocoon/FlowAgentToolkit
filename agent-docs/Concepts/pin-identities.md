# Pin Identity and Display Names (Concept)

$KB:flow:concept:pin-identities
keywords: pins pinname pinfriendlyname identity display label connection FlowAgent

## Identity

Every Flow pin has a logical `PinName`. Graph connections and FlowAgent v2 pin fields use this value
as the connection key. `PinName` is also the name used when activating an exec pin at runtime.

Changing `PinName` changes the key a connection or FlowAgent document refers to. Treat it as an
identity change and migrate existing references when needed.

## Display label

`PinFriendlyName` is an optional editor-only label. It can change the text shown on a graph pin while
leaving `PinName` and graph connections unchanged. Use it when a pin needs a clearer canvas label
but its logical identity should stay stable.

FlowAgent v2's `pins[].name` and connection `pin` fields carry `PinName`, not `PinFriendlyName`.
FlowAgent v2 has no separate field for the canvas label. `PinToolTip` is editor-only hover text and
does not change the pin's connection key.

When describing a pin whose label differs from its logical name, show both values and identify which
one belongs in a connection.

## See also

- $KB:flow:concept:declaring-pins
- $KB:flow:guide:flowagent-format
