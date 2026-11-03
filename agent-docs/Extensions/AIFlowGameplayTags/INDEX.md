# AIFlowGameplayTags Agent Knowledge Base - Index

$KB:flow:guide:aiflowgameplaytags-index
keywords: AIFlowGameplayTags GameplayTag GameplayTagContainer blackboard AIFlowGraph

## What this is

AIFlowGameplayTags connects GameplayTag blackboard support to AIFlowGraph. It provides typed
blackboard value extensions for tags and tag containers, plus tag-query addons for AIFlowGraph.

The plugin depends on AIFlowGraph, BlackboardGameplayTags, and GameplayAbilities. It also requires
the compatible FlowGraph release listed by the plugin repository. Check those dependencies before
debugging missing classes or keys.

## Using the extension

Use the blackboard value extensions when an AIFlowGraph node needs to read, write, or compare a tag
or tag-container key. Use the tag-query addons when a graph condition should evaluate GameplayTag
requirements. Call `FindFlowNodeTypes` with the target asset class and a query for the desired
blackboard or tag predicate behavior; inspect the full reflected entry before selecting fields or
pins.

For the underlying key types and Blueprint access rules, see BlackboardGameplayTags. For general
AIFlowGraph blackboard values, see its extension index.

## See also

- $KB:flow:guide:official-plugins-index
- $KB:flow:guide:blackboardgameplaytags-index
- $KB:flow:guide:aiflowgraph-index
- $KB:flow:guide:flowgraph-index
