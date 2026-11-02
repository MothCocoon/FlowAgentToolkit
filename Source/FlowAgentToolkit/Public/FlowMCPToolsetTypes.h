// Copyright https://github.com/MothCocoon/FlowGraph/graphs/contributors
#pragma once

#include "Containers/Array.h"
#include "Containers/Map.h"
#include "Containers/UnrealString.h"
#include "CoreTypes.h"
#include "Find/FindInFlowEnums.h"
#include "FlowCatalogQuery.h"
#include "FlowMCPMutationContext.h"
#include "Math/IntPoint.h"
#include "UObject/ObjectMacros.h"

#include "FlowMCPToolsetTypes.generated.h"

USTRUCT(BlueprintType)
struct FLOWAGENTTOOLKIT_API FFlowMCPExportFlowAssetRequest
{
	GENERATED_BODY()

	/** Full object path, e.g. "/Game/MyFlows/MyFlow.MyFlow". */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowAgent")
	FString AssetPath;
};

USTRUCT(BlueprintType)
struct FLOWAGENTTOOLKIT_API FFlowMCPExportFlowAssetResult
{
	GENERATED_BODY()

	/** Echo of the requested asset path. */
	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString AssetPath;

	/** The full FlowAgent v2 JSON document. */
	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString ExportedText;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	int32 TextLength = 0;

	/** One entry per disagreement between the editor graph and the runtime node map: a node drawn
	 * but not executable, a node executable but not drawn, or a connection whose endpoint is not in
	 * the node map. Empty on a healthy asset.
	 *
	 * ExportedText above is generated from the runtime node map alone, so it cannot show any of
	 * these - the map agrees with itself by construction. Check this before treating an export as
	 * proof that a mutation landed correctly. */
	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	TArray<FString> GraphIntegrityIssues;
};

USTRUCT(BlueprintType)
struct FLOWAGENTTOOLKIT_API FFlowMCPImportAndRegraphFlowAssetRequest
{
	GENERATED_BODY()

	/** A full FlowAgent v2 JSON document (formatVersion 2). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowAgent")
	FString FlowGraphText;

	/** Full object path for the new asset; fails if one already exists there. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowAgent")
	FString AssetPath;

	/** Save and transaction policy for creating the asset. Dry runs are unsupported. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowAgent")
	FFlowMCPMutationOptions Mutation;
};

USTRUCT(BlueprintType)
struct FLOWAGENTTOOLKIT_API FFlowMCPImportAndRegraphFlowAssetResult
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString AssetPath;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString PackageName;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString AssetName;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	int32 NodeCount = 0;

	/** Requested connections that did not land on the asset after import; the
	  * mutation still reports as applied, but these specific wires need investigation. Empty
	  * when every requested connection is verified present. */
	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	TArray<FString> Findings;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FFlowMCPMutationReport Mutation;
};

/** No parameters - lists every FlowAsset subclass in the project. */
USTRUCT(BlueprintType)
struct FLOWAGENTTOOLKIT_API FFlowMCPListFlowAssetTypesRequest
{
	GENERATED_BODY()
};

USTRUCT(BlueprintType)
struct FLOWAGENTTOOLKIT_API FFlowMCPFlowAssetTypeSummary
{
	GENERATED_BODY()

	/** Bare stem, e.g. "MyProjectFlowAsset". */
	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString ClassName;

	/** The authoritative identifier - use this in AssetClassName filters elsewhere. */
	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString ClassPath;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString Description;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString Keywords;

	/** Node classes legal on this FlowAsset subclass - count only; call FindFlowNodeTypes with AssetClassName to see the actual classes. */
	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	int32 AllowedNodeCount = 0;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	int32 AllowedAddonCount = 0;
};

USTRUCT(BlueprintType)
struct FLOWAGENTTOOLKIT_API FFlowMCPListFlowAssetTypesResult
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	TArray<FFlowMCPFlowAssetTypeSummary> AssetTypes;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	int32 FoundCount = 0;
};

USTRUCT(BlueprintType)
struct FLOWAGENTTOOLKIT_API FFlowMCPCheckAddonAttachmentEligibilityRequest
{
	GENERATED_BODY()

	/** Stem, short class name, or full class path of the node or addon the addon would attach to. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowAgent")
	FString ParentClassName;

	/** Stem, short class name, or full class path of the addon to check. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowAgent")
	FString AddonClassName;
};

USTRUCT(BlueprintType)
struct FLOWAGENTTOOLKIT_API FFlowMCPCheckAddonAttachmentEligibilityResult
{
	GENERATED_BODY()

	/** Resolved full path of ParentClassName. */
	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString ParentClass;

	/** Resolved full path of AddonClassName. */
	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString AddonClass;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	bool bEligible = false;

	/** The raw EFlowAddOnAcceptResult handshake outcome (e.g. "Accept", "Reject", "Undetermined"). */
	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString Result;

	/** Populated only on rejection. */
	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString Reason;
};

USTRUCT(BlueprintType)
struct FLOWAGENTTOOLKIT_API FFlowMCPPropertyDescriptor
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString Name;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString Type;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString PinBinding;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString Description;

	/** The class that actually declares this property - the queried class itself, or an ancestor. */
	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString DeclaringClass;

	/** Terse stringified current default (bare enum name, not fully scoped; "N elements" for arrays). Empty for opaque struct types. */
	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString Value;
};

USTRUCT(BlueprintType)
struct FLOWAGENTTOOLKIT_API FFlowMCPPinDescriptor
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString Name;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString Type;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString Description;
};

/** The hand-authored documentation layer for one class. */
USTRUCT(BlueprintType)
struct FLOWAGENTTOOLKIT_API FFlowMCPAgentDoc
{
	GENERATED_BODY()

	bool IsEmpty() const { return Guidance.IsEmpty() && Tags.IsEmpty(); }

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString Guidance;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	TArray<FString> Tags;
};

/** One resolved node or addon class. Which fields are populated depends on the requested Sections. */
USTRUCT(BlueprintType)
struct FLOWAGENTTOOLKIT_API FFlowMCPClassDetail
{
	GENERATED_BODY()

	/** The class's bare stem, or its full short name when the stem collides within this response. */
	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString Name;

	/** The only authoritative identifier - use this for round-tripping into other ops. */
	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString ClassPath;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString Description;

	/** How the class was authored. Derived, never supplied by a caller. */
	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	EFlowClassOrigin Origin = EFlowClassOrigin::Unknown;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	bool bDeprecated = false;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FFlowMCPAgentDoc Doc;

	/** Knowledge-base article slugs this class is a member of. */
	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	TArray<FString> Articles;

	/**
	 * Every configurable or pin-bound property across the class's full ancestor chain, each tagged
	 * with its DeclaringClass - the queried class's own knobs and its inherited ones are both listed
	 * in full, never collapsed into an inherited-only count.
	 */
	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	TArray<FFlowMCPPropertyDescriptor> Properties;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	TArray<FFlowMCPPinDescriptor> InputPins;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	TArray<FFlowMCPPinDescriptor> OutputPins;
};

USTRUCT(BlueprintType)
struct FLOWAGENTTOOLKIT_API FFlowMCPCatalogFacet
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString Value;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	int32 Count = 0;
};

/**
 * Search the project catalog of Flow node and addon CLASSES by asset type, keyword, article, or name.
 * ClassNames is exclusive - when non-empty, it is the only filter applied (all others below are
 * ignored), and it resolves deprecated classes regardless of bIncludeDeprecated. Sections controls
 * what each row carries; the default, "shape", returns histograms and no rows at all.
 */
USTRUCT(BlueprintType)
struct FLOWAGENTTOOLKIT_API FFlowMCPFindFlowNodeTypesRequest
{
	GENERATED_BODY()

	/** Restrict to classes legal on this FlowAsset subclass (short name or full path); empty = whole project. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowAgent")
	FString AssetClassName;

	/** Stems, short names, or full class paths. When non-empty, this is the ONLY filter applied. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowAgent")
	TArray<FString> ClassNames;

	/** Search nodes, addons, or both. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowAgent")
	EFlowCatalogKind Kind = EFlowCatalogKind::Any;

	/** Case-insensitive substring match over class name & description. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowAgent")
	FString Query;

	/** Exact, lower-cased. A class matches if it carries ANY listed keyword or authored tag. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowAgent")
	TArray<FString> Keywords;

	/** Exact. A class matches if it is in ANY listed category. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowAgent")
	TArray<FString> Categories;

	/** Article slugs ("pattern:<slug>"). A class matches if it carries ANY listed slug. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowAgent")
	TArray<FString> Articles;

	/** A class matches if it declares a pin of ANY listed type. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowAgent")
	TArray<FString> PinTypes;

	/** Restrict to one origin; defaults to Any. Where a class's doc has to be written differs per origin. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowAgent")
	EFlowClassOrigin Origin = EFlowClassOrigin::Any;

	/**
	 * Comma-separated sections: names, doc, properties, pins, articles, usage, origin, deprecation,
	 * signature - or a preset: "shape" (default, histograms only), "brief" (names + description), "full".
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowAgent")
	FString Sections;

	/** Deprecated classes are hidden by default; set this to include them in a filtered query. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowAgent")
	bool bIncludeDeprecated = false;

	/** 0 = unlimited. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowAgent")
	int32 Limit = 0;

	/** Number of matching rows to skip before returning results. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowAgent")
	int32 Offset = 0;
};

/** Category/tag/article histograms over the matched scope - what the "shape" section returns. */
USTRUCT(BlueprintType)
struct FLOWAGENTTOOLKIT_API FFlowMCPCatalogShape
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	int32 NodeCount = 0;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	int32 AddonCount = 0;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	int32 DocumentedCount = 0;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	int32 DeprecatedCount = 0;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	TArray<FFlowMCPCatalogFacet> Categories;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	TArray<FFlowMCPCatalogFacet> Keywords;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	TArray<FFlowMCPCatalogFacet> Tags;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	TArray<FFlowMCPCatalogFacet> Articles;
};

/** A requested stem that more than one class could have meant. Deliberately left unresolved. */
USTRUCT(BlueprintType)
struct FLOWAGENTTOOLKIT_API FFlowMCPAmbiguousClassName
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString Stem;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	TArray<FString> Candidates;
};

USTRUCT(BlueprintType)
struct FLOWAGENTTOOLKIT_API FFlowMCPFindFlowNodeTypesResult
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	TArray<FFlowMCPClassDetail> Nodes;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	TArray<FFlowMCPClassDetail> Addons;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	int32 NodeCount = 0;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	int32 AddonCount = 0;

	/** Pre-paging match counts (i.e. before Limit/Offset are applied). */
	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	int32 TotalNodeCount = 0;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	int32 TotalAddonCount = 0;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	bool bTruncated = false;

	/** Echo of the sections actually applied. */
	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString Sections;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FFlowMCPCatalogShape Shape;

	/** Names in ClassNames[] that resolved to nothing. */
	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	TArray<FString> UnresolvedClassNames;

	/** Stems in ClassNames[] that matched more than one class. Nothing was guessed on your behalf. */
	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	TArray<FFlowMCPAmbiguousClassName> AmbiguousClassNames;
};

/**
 * Write the hand-authored documentation layer onto one node or addon class.
 *
 * Guidance/Tags/Articles only - AgentDoc has no description field. A class's "what does this do for
 * me?" text lives on the class itself (Blueprint description / native or script doc comment, read
 * back via GetNodeToolTip()) and is edited there directly, not through this op.
 *
 * Origin-aware by necessity: a Blueprint class stores its doc as a saved default, while a native or
 * script class returns a compiled-in constant, so for those the op reports Persisted false and hands
 * back the source to paste rather than performing a write that vanishes on restart.
 */
USTRUCT(BlueprintType)
struct FLOWAGENTTOOLKIT_API FFlowMCPSetFlowAgentDocRequest
{
	GENERATED_BODY()

	/** Stem, short class name, or full class path of the class to document. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowAgent")
	FString ClassName;

	/** When to use, when NOT to use, and gotchas. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowAgent")
	FString Guidance;

	/** Intent words a designer would search for. Lower-case. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowAgent")
	TArray<FString> Tags;

	/** Article slugs of the form "pattern:<slug>" or "concept:<slug>". */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowAgent")
	TArray<FString> Articles;

	/** Save and transaction policy for a Blueprint class documentation write. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowAgent")
	FFlowMCPMutationOptions Mutation;
};

USTRUCT(BlueprintType)
struct FLOWAGENTTOOLKIT_API FFlowMCPSetFlowAgentDocResult
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString ClassPath;

	/** How the class was authored, which decides where its doc can live. Derived, not supplied. */
	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	EFlowClassOrigin Origin = EFlowClassOrigin::Unknown;

	/** True only when the write will survive an editor restart. */
	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	bool bPersisted = false;

	/** For a class whose defaults are compiled in, the exact GetAgentDoc() override to paste. */
	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString SourceSnippet;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString Note;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FFlowMCPMutationReport Mutation;
};

/** Where a node or addon class is actually used in shipped content. */
USTRUCT(BlueprintType)
struct FLOWAGENTTOOLKIT_API FFlowMCPFindFlowNodeUsageRequest
{
	GENERATED_BODY()

	/** Stem, short class name, or full class path. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowAgent")
	FString ClassName;

	/** Maximum example assets to return; 0 uses a small default. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowAgent")
	int32 Limit = 0;

	/** Snippets are the expensive part of the payload, so they are opt-in only. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowAgent")
	bool bIncludeSnippets = false;
};

/** One containing asset, smallest graph first so the most readable example leads. */
USTRUCT(BlueprintType)
struct FLOWAGENTTOOLKIT_API FFlowMCPFlowNodeUsageExample
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString AssetPath;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	int32 InstanceCount = 0;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	int32 AssetNodeCount = 0;
};

USTRUCT(BlueprintType)
struct FLOWAGENTTOOLKIT_API FFlowMCPFindFlowNodeUsageResult
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString ClassPath;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	int32 InstanceCount = 0;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	int32 AssetCount = 0;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	TArray<FFlowMCPFlowNodeUsageExample> Examples;

	/** Classes commonly attached alongside this one - the only view of addon-contributed pins. */
	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	TArray<FFlowMCPCatalogFacet> CoAttachedAddOns;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	TArray<FString> Snippets;
};

USTRUCT(BlueprintType)
struct FLOWAGENTTOOLKIT_API FFlowMCPNodeSummary
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString NodeGuid;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString Title;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString ClassPath;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	bool bIsEntryPoint = false;
};

USTRUCT(BlueprintType)
struct FLOWAGENTTOOLKIT_API FFlowMCPFindFlowNodesRequest
{
	GENERATED_BODY()

	/** Full object path of the FlowAsset to search. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowAgent")
	FString AssetPath;

	/** Case-insensitive substring of the live editor node title; empty matches any title. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowAgent")
	FString TitleFilter;

	/** Node class short name or full path; empty matches any class. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowAgent")
	FString ClassFilter;

	/** Return only nodes with no incoming connections. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowAgent")
	bool bEntryPointsOnly = false;
};

USTRUCT(BlueprintType)
struct FLOWAGENTTOOLKIT_API FFlowMCPFindFlowNodesResult
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString AssetPath;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	TArray<FFlowMCPNodeSummary> Nodes;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	int32 NodeCount = 0;
};

USTRUCT(BlueprintType)
struct FLOWAGENTTOOLKIT_API FFlowMCPExportFlowSubgraphRequest
{
	GENERATED_BODY()

	/** Full object path of the FlowAsset containing the start node. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowAgent")
	FString AssetPath;

	/** GUID of the node the undirected reachability search starts from - must exist on AssetPath. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowAgent")
	FString StartNodeGuid;
};

USTRUCT(BlueprintType)
struct FLOWAGENTTOOLKIT_API FFlowMCPExportFlowSubgraphResult
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString AssetPath;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString StartNodeGuid;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString ExportedText;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	int32 NodeCount = 0;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	int32 TextLength = 0;
};

USTRUCT(BlueprintType)
struct FLOWAGENTTOOLKIT_API FFlowMCPPlanFlowSubgraphFromSelectionRequest
{
	GENERATED_BODY()

	/** Full object path of the FlowAsset containing the selected nodes. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowAgent")
	FString TargetAssetPath;

	/** GUIDs of the top-level nodes to move into the new sub-graph asset. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowAgent")
	TArray<FString> SelectionGuids;

	/** New asset name, without a package path. Flow requires the Subgraph_ prefix. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowAgent")
	FString NewAssetName;
};

USTRUCT(BlueprintType)
struct FLOWAGENTTOOLKIT_API FFlowMCPFlowSubgraphSelectionPlan
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	bool bCanApply = false;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	int32 SelectedNodeCount = 0;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	int32 EntryCount = 0;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	int32 ExitCount = 0;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	TArray<FString> Errors;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	TArray<FString> Warnings;

	/** Names exposed as inputs on the generated SubGraph node. */
	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	TArray<FString> InterfaceInputs;

	/** Names exposed as outputs on the generated SubGraph node. */
	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	TArray<FString> InterfaceOutputs;
};

USTRUCT(BlueprintType)
struct FLOWAGENTTOOLKIT_API FFlowMCPPlanFlowSubgraphFromSelectionResult
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString TargetAssetPath;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString NewAssetName;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FFlowMCPFlowSubgraphSelectionPlan Plan;
};

USTRUCT(BlueprintType)
struct FLOWAGENTTOOLKIT_API FFlowMCPCreateFlowSubgraphFromSelectionRequest
{
	GENERATED_BODY()

	/** Full object path of the FlowAsset containing the selected nodes. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowAgent")
	FString TargetAssetPath;

	/** GUIDs of top-level nodes to move into the child asset. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowAgent")
	TArray<FString> SelectionGuids;

	/** New child asset name without a package path; requires the Subgraph_ prefix. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowAgent")
	FString NewAssetName;

	/** Save and transaction policy; this operation requires its own transaction. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowAgent")
	FFlowMCPMutationOptions Mutation;
};

USTRUCT(BlueprintType)
struct FLOWAGENTTOOLKIT_API FFlowMCPCreateFlowSubgraphFromSelectionResult
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString TargetAssetPath;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString NewAssetPath;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString SubgraphNodeGuid;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	bool bApplySucceeded = false;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FFlowMCPFlowSubgraphSelectionPlan Plan;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FFlowMCPMutationReport Mutation;
};

USTRUCT(BlueprintType)
struct FLOWAGENTTOOLKIT_API FFlowMCPFindOrCreateFlowNodeRequest
{
	GENERATED_BODY()

	/** Full object path of the FlowAsset to search or update. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowAgent")
	FString TargetAssetPath;

	/** Class path or short name of the node to find or create. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowAgent")
	FString NodeType;

	/** Exact-match property name/value pairs (export-text strings). A node of NodeType matches only if every listed property is equal. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowAgent")
	TMap<FString, FString> MatchProperties;

	/** Save and transaction policy when a node needs to be created. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowAgent")
	FFlowMCPMutationOptions Mutation;
};

USTRUCT(BlueprintType)
struct FLOWAGENTTOOLKIT_API FFlowMCPFindOrCreateFlowNodeResult
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString AssetPath;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	bool bCreated = false;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString NodeGuid;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FFlowMCPMutationReport Mutation;
};

/**
 * Creates a Blueprint that Flow will actually recognise as a node or add-on.
 *
 * The asset class is not a choice the caller makes - it is decided by the parent class, because both
 * the Flow palette and the FlowAgent catalog gather by asset class rather than by generated class. A
 * plain Blueprint parented to a Flow node compiles, and is then invisible to both.
 */
USTRUCT(BlueprintType)
struct FLOWAGENTTOOLKIT_API FFlowMCPCreateFlowNodeBlueprintRequest
{
	GENERATED_BODY()

	/** Destination package folder, e.g. "/Game/FlowNodes". No asset name. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowAgent")
	FString PackagePath;

	/** Asset name without a path or extension. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowAgent")
	FString AssetName;

	/**
	 * Short name or full path of the class to derive from. Must be under UFlowNode or under
	 * UFlowNodeAddOn - which one decides the asset class, so UFlowNodeBase itself is rejected as
	 * ambiguous rather than guessed at.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowAgent")
	FString ParentClass;

	/** Palette title. Optional: when empty the node falls back to its class name. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowAgent")
	FString DisplayName;

	/** Palette tooltip. Optional: when empty the node falls back to its class tooltip. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowAgent")
	FString Description;

	/** Save and transaction policy for creating the Blueprint asset. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowAgent")
	FFlowMCPMutationOptions Mutation;
};

USTRUCT(BlueprintType)
struct FLOWAGENTTOOLKIT_API FFlowMCPCreateFlowNodeBlueprintResult
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString AssetPath;

	/**
	 * The asset class created from the parent. Check that it is a Flow node or addon Blueprint class;
	 * a plain "/Script/Engine.Blueprint" is not discoverable through the Flow catalog.
	 */
	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString AssetClassPath;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString GeneratedClassPath;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString ParentClassPath;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	bool bCompiled = false;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	TArray<FString> CompileErrors;

	/**
	 * Whether the new class resolves through the same catalog path FindFlowNodeTypes uses. False
	 * means the asset exists but the palette will not offer it.
	 */
	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	bool bResolvedInCatalog = false;

	/** Non-fatal observations, such as a display name or description left to fall back. */
	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString Note;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FFlowMCPMutationReport Mutation;
};

USTRUCT(BlueprintType)
struct FLOWAGENTTOOLKIT_API FFlowMCPAutoFormatFlowGraphRequest
{
	GENERATED_BODY()

	/** Full object path of the FlowAsset whose editor nodes will be arranged. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowAgent")
	FString TargetAssetPath;

	/** Empty formats the whole graph. Non-empty formats only these nodes, anchored to their own pre-format bounding box rather than the graph origin, so unselected nodes are never overlapped. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowAgent")
	TArray<FString> SelectionGuids;

	/** Preview, save, and transaction policy for the layout change. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowAgent")
	FFlowMCPMutationOptions Mutation;
};

USTRUCT(BlueprintType)
struct FLOWAGENTTOOLKIT_API FFlowMCPAutoFormatFlowGraphResult
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString AssetPath;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	int32 NodeCount = 0;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	TMap<FString, FIntPoint> Positions;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	TArray<FString> UnresolvedGuids;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FFlowMCPMutationReport Mutation;
};

USTRUCT(BlueprintType)
struct FLOWAGENTTOOLKIT_API FFlowMCPReconstructFlowGraphRequest
{
	GENERATED_BODY()

	/** A FlowAsset whose editor graph should be rebuilt from its runtime nodes/connections. Use
	 * this after DuplicateFlowAsset/AssetTools.duplicate to repoint a fresh duplicate's connections
	 * at its own node GUIDs, without opening the asset in the Flow editor. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowAgent")
	FString TargetAssetPath;

	/** Preview, save, and transaction policy for rebuilding the editor graph. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowAgent")
	FFlowMCPMutationOptions Mutation;
};

USTRUCT(BlueprintType)
struct FLOWAGENTTOOLKIT_API FFlowMCPReconstructFlowGraphResult
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString AssetPath;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	int32 NodeCount = 0;

	/** Editor nodes destroyed because their runtime node was no longer registered. A non-zero count
	 * means this call repaired existing damage rather than merely rebuilding. */
	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	int32 OrphanedEditorNodesRemoved = 0;

	/** Remaining disagreements between the editor graph and the runtime node map after the rebuild.
	 * Empty is the expected result; anything here survived a full reconstruct. */
	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	TArray<FString> GraphIntegrityIssues;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FFlowMCPMutationReport Mutation;
};

USTRUCT(BlueprintType)
struct FLOWAGENTTOOLKIT_API FFlowMCPExportFlowCatalogRequest
{
	GENERATED_BODY()

	/** Absolute path of the UTF-8 JSON file to write. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowAgent")
	FString OutputFilePath;

	/** Optional FlowAsset class to scope the export to (e.g. "/Script/Flow.FlowAsset"). Empty
	 * exports every node/addon class known to the catalog regardless of asset type. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowAgent")
	FString AssetClassName;
};

USTRUCT(BlueprintType)
struct FLOWAGENTTOOLKIT_API FFlowMCPExportFlowCatalogResult
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString OutputFilePath;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	bool bSucceeded = false;
};

USTRUCT(BlueprintType)
struct FLOWAGENTTOOLKIT_API FFlowMCPConnectionRef
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString SourceGuid;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString SourcePin;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString TargetGuid;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString TargetPin;
};

/**
 * One addon-level difference under a changed node, flattened out of the recursive C++-only
 * FFlowGraphDiffAddOn tree (FlowGraphDiff.h) so it can be reflected: UHT forbids a USTRUCT
 * holding a TArray of itself. ParentGuid is the owning node's GUID for a top-level addon, or the
 * parent addon's GUID for a nested addon-of-addon (mirrors FFlowReconcileAddonEntry::OwnerNodeGuid).
 */
USTRUCT(BlueprintType)
struct FLOWAGENTTOOLKIT_API FFlowMCPAddonDiffEntry
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString AddonGuid;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString ParentGuid;

	// "added" | "removed" | "changed"
	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString ChangeType;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString AddonType;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	TMap<FString, FString> ChangedProperties;
};

USTRUCT(BlueprintType)
struct FLOWAGENTTOOLKIT_API FFlowMCPChangedNode
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString NodeGuid;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	TMap<FString, FString> ChangedProperties;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	bool bPosChanged = false;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString OldPos;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString NewPos;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	TArray<FFlowMCPAddonDiffEntry> AddonDiffs;
};

USTRUCT(BlueprintType)
struct FLOWAGENTTOOLKIT_API FFlowMCPDiffFlowAssetRequest
{
	GENERATED_BODY()

	/** A FlowAsset object path, or a raw FlowAgent v2 JSON document - either is accepted for both sides. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowAgent")
	FString Old;

	/** Same rules as Old. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowAgent")
	FString New;
};

USTRUCT(BlueprintType)
struct FLOWAGENTTOOLKIT_API FFlowMCPDiffFlowAssetResult
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString OldSource;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString NewSource;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	bool bHasDifferences = false;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	TArray<FString> AddedNodes;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	TArray<FString> RemovedNodes;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	TArray<FFlowMCPChangedNode> ChangedNodes;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	TArray<FFlowMCPConnectionRef> AddedConnections;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	TArray<FFlowMCPConnectionRef> RemovedConnections;
};

USTRUCT(BlueprintType)
struct FLOWAGENTTOOLKIT_API FFlowMCPReconcileAddonEntry
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString OwnerNodeGuid;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString AddonGuid;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString AddonType;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	TMap<FString, FString> Properties;
};

USTRUCT(BlueprintType)
struct FLOWAGENTTOOLKIT_API FFlowMCPReconcileAssetPropertyEntry
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString Name;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString PreviousValue;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString ProposedValue;
};

// Every array here is a verified claim about post-apply state, checked against the asset after
// applying, never populated from the request. An item requested but not achieved appears as a
// Findings entry instead.
USTRUCT(BlueprintType)
struct FLOWAGENTTOOLKIT_API FFlowMCPReconcilePlan
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	TArray<FString> NodesAdded;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	TArray<FString> NodesUpdated;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	TArray<FString> NodesDeleted;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	TArray<FString> ConnectionsAdded;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	TArray<FString> ConnectionsRemoved;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	TArray<FFlowMCPReconcileAddonEntry> AddonsAdded;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	TArray<FFlowMCPReconcileAddonEntry> AddonsUpdated;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	TArray<FFlowMCPReconcileAddonEntry> AddonsDeleted;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	TArray<FFlowMCPReconcileAssetPropertyEntry> AssetPropertiesChanged;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	bool bIsEmpty = true;
};

USTRUCT(BlueprintType)
struct FLOWAGENTTOOLKIT_API FFlowMCPValidationFinding
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString Severity;

	/**
	 * Stable machine-readable identifier for what went wrong, e.g. "ExecFanOut", "DanglingEndpoint",
	 * "PinNotFound", "UnresolvedAlias". Branch on this rather than matching against Message - the
	 * message wording is free text and may be reworded, the code is a contract.
	 */
	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString Code;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString SourceDocumentPath;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString Message;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString NodeGuid;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString AddonGuid;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString PinName;
};

USTRUCT(BlueprintType)
struct FLOWAGENTTOOLKIT_API FFlowMCPReconcileMetrics
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	int32 NodesTouched = 0;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	int32 NodesPreserved = 0;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	int32 InputSizeBytes = 0;
};

USTRUCT(BlueprintType)
struct FLOWAGENTTOOLKIT_API FFlowMCPReplaceFlowNodeClassRequest
{
	GENERATED_BODY()

	/** Full object path of the FlowAsset containing the node. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowAgent")
	FString AssetPath;

	/** GUID of the node to replace; the replacement retains this identity. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowAgent")
	FString NodeGuid;

	/** Full class path of the replacement Flow node. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowAgent")
	FString NewNodeClass;

	/** Source property name to replacement property name. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowAgent")
	TMap<FString, FString> PropertyMappings;

	/** Source pin name to replacement pin name for affected connections. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowAgent")
	TMap<FString, FString> PinMappings;

	/** Addon GUID string to replacement addon class path. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowAgent")
	TMap<FString, FString> AddOnClassMappings;

	/** "AddonGuid.SourceProperty" to replacement addon property name. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowAgent")
	TMap<FString, FString> AddOnPropertyMappings;

	/** Permit a save to remint duplicate addon GUIDs elsewhere in the asset. Duplicates on the
	 * target node still block replacement. Use only when those identity changes are accepted. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowAgent")
	bool bAllowDuplicateAddonGuidRepair = false;

	/** Preview, save, and transaction policy for the class replacement. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowAgent")
	FFlowMCPMutationOptions Mutation;
};

USTRUCT(BlueprintType)
struct FLOWAGENTTOOLKIT_API FFlowMCPReplaceFlowNodeClassResult
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString AssetPath;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString NodeGuid;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString PreviousClass;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString NewClass;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	bool bCanReplace = false;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	bool bReplaced = false;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	TArray<FString> ReplacedAddOnGuids;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	TArray<FString> Findings;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FFlowMCPMutationReport Mutation;
};

USTRUCT(BlueprintType)
struct FLOWAGENTTOOLKIT_API FFlowMCPApplyFlowPatchRequest
{
	GENERATED_BODY()

	/** Existing asset to patch, or a new one to create if AssetClass is set in MutationText and nothing exists at this path yet. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowAgent")
	FString TargetAssetPath;

	/** A FlowAgent v2 JSON document. Patch mode changes only what it mentions; Full mode is authoritative over the whole asset. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowAgent")
	FString MutationText;

	/** Preview, save, and transaction policy for applying the patch. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowAgent")
	FFlowMCPMutationOptions Mutation;
};

USTRUCT(BlueprintType)
struct FLOWAGENTTOOLKIT_API FFlowMCPApplyFlowPatchResult
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString AssetPath;

	/** Check this, not the absence of an error - a blocked apply still returns a populated Result rather than raising. */
	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	bool bApplySucceeded = false;

	/** Always populated, even when blocked - what the patch would have changed. */
	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FFlowMCPReconcilePlan Plan;

	/** newAlias -> minted GUID for every alias the document defined. */
	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	TMap<FString, FString> AliasMap;

	/** Free-text messages; ValidationFindings below is the structured equivalent and should be preferred. */
	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	TArray<FString> Findings;

	/** Per-issue severity, message, and node/addon/pin location. Any Error-severity entry means bHasBlockingError is true and nothing was applied. */
	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	TArray<FFlowMCPValidationFinding> ValidationFindings;

	/** True when ValidationFindings contains an Error - the whole apply was blocked and the asset was not modified. */
	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	bool bHasBlockingError = false;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FFlowMCPReconcileMetrics Metrics;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FFlowMCPMutationReport Mutation;
};

/** How a FlowAgent v2 op field relates to a given op Kind. */
UENUM(BlueprintType)
enum class EFlowMCPAgentFieldLegality : uint8
{
	/** Must always be set on this Kind. */
	Required,
	/** Must be set only when the op creates a new node/addon (Guid empty, NewAlias set). */
	RequiredOnCreate,
	/** May be set on this Kind; omitting it is always legal. */
	Optional,
	/** Setting this field on this Kind is a validation error (FieldNotLegalForKind). */
	Illegal,
};

USTRUCT(BlueprintType)
struct FLOWAGENTTOOLKIT_API FFlowMCPAgentFieldGrammar
{
	GENERATED_BODY()

	/** FFlowAgentOp field name, in the JSON's camelCase spelling (e.g. "parentGuid"). */
	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString FieldName;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	EFlowMCPAgentFieldLegality Legality = EFlowMCPAgentFieldLegality::Optional;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString Notes;
};

/**
 * A set of two or more field names where exactly one must be set; the individual fields'
 * Legality in FFlowMCPAgentOpKindGrammar.Fields is Optional for each member of the group, since
 * no single one of them is independently required. This group is what actually carries the
 * requirement: at least one member must be set, and setting more than one is ambiguous.
 */
USTRUCT(BlueprintType)
struct FLOWAGENTTOOLKIT_API FFlowMCPAgentFieldGroup
{
	GENERATED_BODY()

	/** Field names in the group, e.g. ["guid", "newAlias"] or ["source.nodeGuid", "source.nodeAlias"]. */
	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	TArray<FString> FieldNames;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString Notes;
};

USTRUCT(BlueprintType)
struct FLOWAGENTTOOLKIT_API FFlowMCPAgentOpKindGrammar
{
	GENERATED_BODY()

	/** FFlowAgentOp.Kind value, e.g. "UpsertNode". */
	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString Kind;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString Description;

	/** Legality of every FFlowAgentOp field for this Kind. */
	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	TArray<FFlowMCPAgentFieldGrammar> Fields;

	/** Exactly-one-of constraints across two or more fields in this Kind, e.g. guid/newAlias. */
	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	TArray<FFlowMCPAgentFieldGroup> ExactlyOneOfGroups;
};

USTRUCT(BlueprintType)
struct FLOWAGENTTOOLKIT_API FFlowMCPDescribeFlowAgentGrammarRequest
{
	GENERATED_BODY()
};

USTRUCT(BlueprintType)
struct FLOWAGENTTOOLKIT_API FFlowMCPDescribeFlowAgentGrammarResult
{
	GENERATED_BODY()

	/** Every legal FFlowAgentOp.Kind value and its per-field legality. */
	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	TArray<FFlowMCPAgentOpKindGrammar> Kinds;

	/** Legality notes for the top-level FFlowAgentDocument fields (formatVersion, mode, assetClass, etc.), independent of Kind. */
	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	TArray<FFlowMCPAgentFieldGrammar> DocumentFields;
};

USTRUCT(BlueprintType)
struct FLOWAGENTTOOLKIT_API FFlowMCPSearchMatchedPin
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString PinName;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString Direction;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	bool bConnected = false;
};

USTRUCT(BlueprintType)
struct FLOWAGENTTOOLKIT_API FFlowMCPSearchResultItem
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString AssetPath;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString NodeGuid;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString NodeTitle;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString NodeType;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	int32 MatchedFlags = 0;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString MatchedSnippet;

	/** Populated when the query matched the Pin Names category, qualified by the request's PinDirection/PinConnection filters. */
	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	TArray<FFlowMCPSearchMatchedPin> MatchedPins;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	bool bIsSubgraphNode = false;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString SubgraphOwnerAssetPath;
};

USTRUCT(BlueprintType)
struct FLOWAGENTTOOLKIT_API FFlowMCPSearchFlowAssetsRequest
{
	GENERATED_BODY()

	/** Whitespace-delimited tokens, ANDed together - every token must match for a node to be a hit. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowAgent")
	FString Query;

	/** EFlowSearchFlags bitmask of what to search (titles, comments, classes, property values, ...). 0 means the default flag set, not "search nothing". */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowAgent", Meta = (Bitmask, BitmaskEnum = "/Script/FlowEditor.EFlowSearchFlags"))
	int32 Flags = 0;

	/** ThisAssetOnly and AllOfThisType both require ContextAssetPath to be set. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowAgent")
	EFlowSearchScope Scope = EFlowSearchScope::AllFlowAssets;

	/** How many subgraph levels FlowNode_SubGraph recursion follows before it stops. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowAgent")
	int32 MaxDepth = 3;

	/** Required when Scope is ThisAssetOnly or AllOfThisType; ignored for AllFlowAssets. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowAgent")
	FString ContextAssetPath;

	/** "any"/"input"/"output" - qualifies a Pin Names category match by pin direction. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowAgent")
	FString PinDirection = TEXT("any");

	/** "any"/"connected"/"unconnected" - qualifies a Pin Names category match by connection state. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowAgent")
	FString PinConnection = TEXT("any");
};

USTRUCT(BlueprintType)
struct FLOWAGENTTOOLKIT_API FFlowMCPSearchFlowAssetsResult
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	TArray<FFlowMCPSearchResultItem> Results;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	int32 ResultCount = 0;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString Query;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString Scope;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	int32 Flags = 0;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString PinDirection;

	UPROPERTY(BlueprintReadOnly, Category = "FlowAgent")
	FString PinConnection;
};
