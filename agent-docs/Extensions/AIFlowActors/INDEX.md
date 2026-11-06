# AIFlowActors Agent Knowledge Base - Index

$KB:flow:guide:aiflowactors-index
keywords: AIFlowActors EQS actor spawn record FlowActors

## What this is

AIFlowActors adds AI-specific runtime extensions to FlowActors. Its initial extension is an EQS-
backed actor spawn record, which lets FlowActors actor spawning use an Environment Query System
query to select spawn locations.

The plugin depends on FlowActors. Consult its repository README for setup details and the live
FlowAgentToolkit catalog for the spawn nodes and reflected configuration supported by the enabled
plugin set.

## Choosing AIFlowActors

Use this extension when an actor-spawn request needs EQS to find locations. Use the generic
FlowActors spawn workflow for the surrounding graph behavior, and configure the EQS-backed record
only after inspecting its catalog description and reflected properties. This extension supplies a
spawn record; it does not replace FlowActors' spawn node or actor-spawning system.

## See also

- $KB:flow:guide:official-plugins-index
- $KB:flow:guide:flowactors-index
- $KB:flow:guide:flowgraph-index
