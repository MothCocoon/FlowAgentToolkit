# FlowActors Agent Knowledge Base - Index

$KB:flow:guide:flowactors-index
keywords: FlowActors actors spawning fight teleport FlowAgent

## What this is

FlowActors is an official extension to FlowGraph. Its `FlowActorsRuntime` module provides actor-
focused runtime systems, including actor spawning, fight nodes, teleport nodes, and the supporting
spawn-record and actor-spawning infrastructure.

The plugin depends on FlowGraph. Its source repository and README describe the plugin release and
setup; use the live FlowAgentToolkit catalog for the reflected fields and pins of available nodes.

## Choosing FlowActors

Use FlowActors when a graph needs to spawn actors, coordinate actor fights, or teleport actors.
Choose the node or addon that matches the requested behavior, then inspect its full catalog entry
before authoring. Do not infer pin names or property values from a display label or a neighboring
node.

Call `FindFlowNodeTypes` with the target asset class and a query for the desired actor operation.
Use the returned class descriptions and reflected shape to select a node or addon, then follow the
generic Flow authoring workflow.

## Concepts

- $KB:flow:concept:spawn-and-fight-actors - when to use the one-shot Spawn Actors node or the
  tracked Fight Actors node, and how selectors, spawn records, cohorts, and reinforcement fit together.

## See also

- $KB:flow:guide:official-plugins-index
- $KB:flow:guide:flowgraph-index
- $KB:flow:guide:aiflowactors-index
