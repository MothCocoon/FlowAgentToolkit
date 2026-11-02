// Copyright https://github.com/MothCocoon/FlowGraph/graphs/contributors
using UnrealBuildTool;

public class FlowAgentToolkit : ModuleRules
{
	public FlowAgentToolkit(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",
				"Flow",
				"FlowEditor",
				"ToolsetRegistry"
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"UnrealEd",
				"AssetRegistry",
				"Json",
				"JsonUtilities",
				"Projects",
				"SourceControl"
			}
		);
	}
}
