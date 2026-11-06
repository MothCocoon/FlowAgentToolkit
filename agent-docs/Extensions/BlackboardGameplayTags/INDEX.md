# BlackboardGameplayTags Agent Knowledge Base - Index

$KB:flow:guide:blackboardgameplaytags-index
keywords: BlackboardGameplayTags GameplayTag GameplayTagContainer blackboard

## What this is

BlackboardGameplayTags adds Behavior Tree blackboard entry types for `GameplayTag` and
`GameplayTagContainer`. It can be used independently or alongside Flow, AIFlowGraph, and
AIFlowGameplayTags.

## Blueprint access

Blueprint callers must use the plugin's static functions to get and set these values. The tag types
are not integrated as member functions on `UBlackboardComponent`, so do not recommend the usual
blackboard member accessors for these keys.

Use the plugin README for setup details and its `BlackboardGameplayTagFunctionLibrary` API for
Blueprint access. When the request is about Flow graph nodes or addons, consult the AIFlowGameplayTags
entry as well.

## See also

- $KB:flow:guide:official-plugins-index
- $KB:flow:guide:aiflowgameplaytags-index
- $KB:flow:guide:aiflowgraph-index
