# Flow Agent Knowledge Base - Index

$KB:flow:guide:flowgraph-index

## What this is

The FlowAgentToolkit plugin owns the agent-facing knowledge base and skills for all seven official
Flow plugins. It lives beside `docs/`, the published website. Start here for concepts and authoring
guidance; query `FindFlowNodeTypes` for facts about a particular node or addon class.

## Placement rule

Shared concepts and authoring guides live at this root. Official extension-specific articles live
under `Extensions/<Plugin>/`. A particular class's guidance lives in its `FFlowAgentDoc`, not in a
separate article.

The `Authoring/` guide covers C++ and Blueprint authoring supported by the official Flow plugins.

## Layout

- **No per-class node/addon articles.** A class's documentation lives on the class itself
  (`FFlowAgentDoc`, read via the catalog with `FindFlowNodeTypes`), not as a markdown file.
- `Concept` articles for generic ecosystem semantics (e.g. the FlowAgent format, the addon attachment handshake, subgraph composition).
- `Authoring/` guides for how to build a new generic node/addon.

## Conventions

Each article declares one `$KB:<domain>:<kind>:<id>` tag on its own line near the top. Use `flow`
for this plugin's domain and `concept`, `pattern`, or `guide` for the kind. Resolve a reference by
searching the exact tag across this root's official plugin articles. The tag id matches the filename
after case, hyphen, and underscore normalization; `INDEX.md` is exempt. Link to the tag rather than
to a section number so links survive file moves.

Keep one concept or pattern per article. Put class-specific guidance in `FFlowAgentDoc`, where the
catalog serves it beside reflected pins and properties. A class's `Articles` entries use
`concept:<id>` or `pattern:<id>` to connect it to shared articles. Mark content that agents may
change only on explicit instruction with `<!-- KB-LOCK -->` and `<!-- /KB-LOCK -->`.

## Available guides

- $KB:flow:guide:flowagent-format - the FlowAgent v2 JSON document: what its fields mean and what
  a document does when applied (identity, apply order, merge behavior, addon parentage, pin names,
  the error model). The exact schema is published live by `describe_toolset`; read this for meaning,
  not shape.

## Scripts (`Scripts/`)

- `kb_lint.py` - generic KB consistency checker (dangling `$KB:` references, filename/tag
  mismatches, orphan articles) across any set of `agent-docs/` roots. Pure Python, no Unreal/MCP
  dependency. Run it on this root alone for a standalone check, or pass every linked official plugin
  root together when its articles link across roots.

## Concepts (`Concepts/`)

Generic ecosystem semantics that don't belong to any single node/addon class.

- $KB:flow:concept:subgraphs - `FlowNode_SubGraph` composition: embedding one `FlowAsset` inside
  another, the `CustomInput`/`CustomOutput` named-interface mechanism, and when to decompose a
  graph into a sub-asset vs. keep it inline.
- $KB:flow:concept:structuring-coherent-graphs - domain-agnostic composition guidance: node vs
  addon vs pin, multiple entry points vs branch inline, decomposition, readability habits. A
  companion skill for an official extension can layer its own domain-specific patterns on top.
- $KB:flow:concept:pin-identities - distinguishes a pin's connection key from its displayed
  canvas label.

## Authoring (`Authoring/`)

How to create new **generic** Flow nodes/addons. Extension-specific authoring guides live under
`Extensions/<Plugin>/` in this repository.

- $KB:flow:guide:authoring-a-node - node vs addon, C++ vs Blueprint, the creation workflow for each
  (incl. the Flow-Blueprint-asset-type trap), and AddOn attachment eligibility (the two-sided
  accept/reject handshake).
- $KB:flow:concept:declaring-pins - the full pin surface: exec, static, data, auto-generated, and context pins.

## Official plugin set

- $KB:flow:guide:official-plugins-index - overview of all seven official Flow plugins, their
  capabilities, and links to their documentation.
- $KB:flow:guide:aiflowgraph-index - AIFlowGraph concepts for Behavior Tree blackboard values.
- $KB:flow:guide:flowactors-index - actor spawning, fight, and teleport systems in FlowActors.
- $KB:flow:guide:aiflowactors-index - the EQS actor-spawn record extension for FlowActors.
- $KB:flow:guide:blackboardgameplaytags-index - GameplayTag blackboard key types and access.
- $KB:flow:guide:aiflowgameplaytags-index - GameplayTag blackboard bindings for AIFlowGraph.

## Extension docs

Official plugin-specific agent articles live under `Extensions/<Plugin>/` in this repository. Use
the official plugin index to find their scope and entry points.
