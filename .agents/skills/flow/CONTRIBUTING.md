# Contributing to the flow skill

For anyone editing this skill's own files. If you are here to do Flow work, go back to `SKILL.md`.

## Where new content goes

- A new op the toolset exposes: `references/flow-ops.md`.
- A new request shape that works for any `FlowAsset` subclass: a new archetype section in
  `references/workflows.md`.
- A request shape that only makes sense for one official plugin's asset subclass: its section under
  `agent-docs/Extensions/<Plugin>/`, plus a skill under `.agents/skills/` when it needs a dedicated
  workflow.
- Knowledge-base authoring or maintenance procedure: this repository's contributor docs.
  `flow-ops.md` and `workflows.md` are about editing graph content, not the documents that describe it.
- Anything that fits none of the above: a new reference file, plus a sentence in `SKILL.md`'s
  "Where to go next" naming when to read it.

## Portable scope

This skill ships with FlowAgentToolkit and describes generic FlowGraph authoring. Keep every
instruction usable with the official FlowGraph and FlowAgentToolkit plugins. Keep official
extension-specific articles and skills in this repository; keep consuming-project dialects and
content in that project's own agent docs. Keep the frontmatter description focused on when to load
this skill; keep detailed procedures in the body and references.

