# Official Flow Plugins - Agent Index

$KB:flow:guide:official-plugins-index
keywords: FlowGraph FlowActors FlowAgentToolkit AIFlowGraph BlackboardGameplayTags AIFlowGameplayTags AIFlowActors

## Scope

The official Mothcocoon Flow ecosystem has seven plugins maintained in separate GitHub repositories.
Agent-facing documentation and skills for all seven are centralized in FlowAgentToolkit. This
index covers the full plugin set, including plugins whose detailed guidance currently lives in
their repository documentation and reflected node catalog.

Use the generic Flow skill for graph operations, then consult the relevant plugin entry below for
extension behavior. When a plugin is enabled, query `FindFlowNodeTypes` for its node and addon
classes; the catalog is the source for reflected pins, properties, and class guidance.

## Plugins

| Plugin | Role | Documentation |
| --- | --- | --- |
| **FlowGraph** | Core event graph runtime and editor | [Repository and published docs](https://github.com/MothCocoon/FlowGraph), [wiki](https://github.com/MothCocoon/FlowGraph/wiki) |
| **FlowActors** | Actor-focused nodes, addons, and gameplay actor manipulation infrastructure | [Agent docs](Extensions/FlowActors/INDEX.md), [repository and README](https://github.com/MothCocoon/FlowActors) |
| **FlowAgentToolkit** | Agent tools for discovering, inspecting, validating, importing, and editing Flow graphs | [Repository](https://github.com/MothCocoon/FlowAgentToolkit), [MCP integration](../docs/MCPIntegration.md), [agent docs](INDEX.md) |
| **AIFlowGraph** | AI module support, including Behavior Tree blackboard nodes and addons | [Repository and README](https://github.com/MothCocoon/AIFlowGraph), [agent docs](Extensions/AIFlowGraph/INDEX.md) |
| **BlackboardGameplayTags** | GameplayTag and GameplayTagContainer blackboard entry types | [Agent docs](Extensions/BlackboardGameplayTags/INDEX.md), [repository and README](https://github.com/MothCocoon/BlackboardGameplayTags) |
| **AIFlowGameplayTags** | AIFlowGraph bindings for gameplay-tag blackboard keys | [Agent docs](Extensions/AIFlowGameplayTags/INDEX.md), [repository and README](https://github.com/MothCocoon/AIFlowGameplayTags) |
| **AIFlowActors** | EQS extensions for actor spawning through FlowActors | [Agent docs](Extensions/AIFlowActors/INDEX.md), [repository and README](https://github.com/MothCocoon/AIFlowActors) |

## Authoring scope

All seven plugins are in scope for FlowAgentToolkit guidance. Their plugin READMEs and FlowGraph's
published documentation provide setup and feature context; use the live catalog for class-specific
facts. Keep agent-facing concepts and skills for these plugins in this FlowAgentToolkit repository.

## See also

- $KB:flow:guide:flowgraph-index
- $KB:flow:guide:aiflowgraph-index
