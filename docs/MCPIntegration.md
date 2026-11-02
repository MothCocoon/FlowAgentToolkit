# FlowAgentToolkit and MCP

`FlowAgentToolkit` is an editor plugin that exposes Flow graph discovery, inspection, validation,
and mutation through an Epic ToolsetRegistry toolset. It does not require a particular MCP server.
An MCP host that exposes registered Unreal toolsets can discover
`FlowAgentToolkit.FlowMCPToolset` and publish its reflected request and result schemas.

The FlowAgent v2 JSON document format is described in
[`agent-docs/FlowAgentFormat.md`](../agent-docs/FlowAgentFormat.md). The live toolset schema is
authoritative for parameter names and types.

## Setup

Use Unreal Engine 5.8 or later, and enable the FlowAgentToolkit plugin and Epic's `ToolsetRegistry`
plugin in an Unreal Editor build. FlowAgentToolkit depends on Flow and ToolsetRegistry. The
`FlowAgentToolkit` editor module registers `UFlowMCPToolset` after engine initialization and
unregisters it at shutdown. Its operations are static `UFUNCTION(meta = (AICallable))` methods on a
`UToolsetDefinition` subclass, with reflected request and result structs. A host can use the
registry's discovery and invocation APIs without linking directly to FlowAgentToolkit.

For a direct C++ integration, add `FlowAgentToolkit` to an editor module's private dependencies
and include `FlowMCPToolset.h`. Call its static functions on the game thread in an editor context.
Never link the editor module into a runtime target.

## Operations

| Task | Operation |
| --- | --- |
| Discover legal asset, node, and addon classes | `ListFlowAssetTypes`, `FindFlowNodeTypes`, `CheckAddonAttachmentEligibility` |
| Find instances and examples | `FindFlowNodes`, `FindFlowNodeUsage`, `SearchFlowAssets` |
| Inspect graphs | `ExportFlowAsset`, `ExportFlowSubgraph`, `DiffFlowAsset`, `DescribeFlowAgentGrammar` |
| Create or edit graphs | `ImportAndRegraphFlowAsset`, `ApplyFlowPatch`, `FindOrCreateFlowNode`, `ReplaceFlowNodeClass` |
| Refactor and arrange | `PlanFlowSubgraphFromSelection`, `CreateFlowSubgraphFromSelection`, `AutoFormatFlowGraph`, `ReconstructFlowGraph` |
| Author node classes and guidance | `CreateFlowNodeBlueprint`, `SetFlowAgentDoc`, `ExportFlowCatalog` |

`ImportAndRegraphFlowAsset` creates a new asset and rejects an occupied path. Use `ApplyFlowPatch`
to change an existing graph. Export before an edit, apply a small FlowAgent patch with
`mutation.bDryRun` first, then apply it and compare with `DiffFlowAsset`. Check
`validationFindings`, `bApplySucceeded`, and graph integrity findings; a successful transport call
alone does not prove that every intended connection landed.

All mutation request structs carry `FFlowMCPMutationOptions`. `bDryRun` requires an owned editor
transaction and cannot run inside an existing transaction. Source control checkout and optional
save are managed by the mutation context. The result reports checked out and modified packages.
`ImportAndRegraphFlowAsset` does not support a dry run because it creates a package.

## Host integration

An MCP host should expose ToolsetRegistry's live discovery and per-operation schemas, then invoke
the operation with one reflected `request` struct. For example, `ApplyFlowPatch` receives a full
asset path, a FlowAgent JSON string, and nested mutation options. The host should validate argument
names and types before dispatch, report tool errors without dropping structured validation results,
and avoid truncating large graph exports. It may provide script execution beside the editor to
summarize large exports before returning them to an agent.

Graph mutations run on the game thread. Do not issue them during Play-in-Editor. If a host receives
requests on another thread, marshal calls to the game thread before loading or changing assets.
The host's authentication and authorization policy remains its own responsibility.
