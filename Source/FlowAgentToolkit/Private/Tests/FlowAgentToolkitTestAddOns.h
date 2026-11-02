// Copyright https://github.com/MothCocoon/FlowGraph/graphs/contributors
#pragma once

#include "AddOns/FlowNodeAddOn.h"

#include "FlowAgentToolkitTestAddOns.generated.h"

// Shared nested settings let importer tests prove that preview and execution both notify
// a cached-pin AddOn for dotted struct and array property paths.
USTRUCT()
struct FFlowAgentToolkitTestCachedPinSettings
{
	GENERATED_BODY()

	// Values are normalized by the fixture callback before their generated pins are rebuilt.
	UPROPERTY(EditAnywhere, Category = "FlowAgent Test")
	TArray<int32> Values;

	// Added to each value so two dotted writes must be visible to the same final pin rebuild.
	UPROPERTY(EditAnywhere, Category = "FlowAgent Test")
	int32 Offset = 0;
};

// A no-op parent fixture for constructing a nested AddOn tree in direction tests.
UCLASS()
class FLOWAGENTTOOLKIT_API UFlowAgentToolkitTestCompositeAddOn : public UFlowNodeAddOn
{
	GENERATED_BODY()
};

// This AddOn caches output pins; only its editor property callback rebuilds them after FlowAgent writes.
UCLASS()
class FLOWAGENTTOOLKIT_API UFlowAgentToolkitTestCachedPinAddOn : public UFlowNodeAddOn
{
	GENERATED_BODY()

public:
	UFlowAgentToolkitTestCachedPinAddOn();

	// Top-level cache input used by the whole-array replacement regression.
	UPROPERTY(EditAnywhere, Category = "FlowAgent Test")
	TArray<int32> Thresholds;

	// Nested cache inputs used to exercise dotted paths and multiple writes to one callback member.
	UPROPERTY(EditAnywhere, Category = "FlowAgent Test")
	FFlowAgentToolkitTestCachedPinSettings Settings;

	virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;

private:
	// Rebuilds OutputPins from the authored properties after the callback normalizes them.
	void RebuildOutputPins();
};

// Supplies a typed nested input for directional aggregation coverage.
UCLASS()
class FLOWAGENTTOOLKIT_API UFlowAgentToolkitTestInputPinAddOn : public UFlowNodeAddOn
{
	GENERATED_BODY()

public:
	UFlowAgentToolkitTestInputPinAddOn();
};

// Supplies a typed nested output for directional aggregation coverage.
UCLASS()
class FLOWAGENTTOOLKIT_API UFlowAgentToolkitTestOutputPinAddOn : public UFlowNodeAddOn
{
	GENERATED_BODY()

public:
	UFlowAgentToolkitTestOutputPinAddOn();
};
