# FlowAgentToolkit

FlowAgentToolkit owns the editor tooling for inspecting, validating, importing, and editing Flow
graphs through the FlowAgent JSON format. It also owns Flow's agent skill and shared agent knowledge base.

The editor-only `FlowAgentToolkit` module depends on the Flow plugin and ToolsetRegistry. The Flow
plugin redirects reflected references from the previous module name.

See the [MCP integration guide](docs/MCPIntegration.md), the [FlowAgent format guide](agent-docs/FlowAgentFormat.md),
and the [Flow agent skill](.agents/skills/flow/SKILL.md).

For agent guidance covering all seven official Flow plugins, start at the
[official plugins index](agent-docs/OfficialPluginsIndex.md).
