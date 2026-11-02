// Copyright https://github.com/MothCocoon/FlowGraph/graphs/contributors
#pragma once

#include "Components/ActorComponent.h"
#include "FlowAsset.h"
#include "Nodes/Graph/FlowNode_Finish.h"
#include "Nodes/Graph/FlowNode_Start.h"

#include "FlowAgentToolkitSubGraphReuseTestTypes.generated.h"

class UFlowInjectComponentsManager;

UCLASS(Hidden, NotBlueprintable)
class UFlowAgentToolkitSubGraphReuseTestComponent : public UActorComponent
{
	GENERATED_BODY()
};

UCLASS(Hidden, NotBlueprintable, meta = (ExcludeFromFlowCatalog))
class UFlowAgentToolkitSubGraphReusePolicyOverrideAsset : public UFlowAsset
{
	GENERATED_BODY()

public:
	virtual ESubGraphFinishPolicy GetSubGraphFinishPolicy() const override
	{
		return ESubGraphFinishPolicy::Deinitialize;
	}
};

UCLASS(Hidden, NotBlueprintable, NotPlaceable, meta = (ExcludeFromFlowCatalog))
class UFlowAgentToolkitSubGraphReuseTestStartNode : public UFlowNode_Start
{
	GENERATED_BODY()

public:
	virtual void TriggerFirstOutput(const bool bFinish) override;

	bool bAllNodesNeverActivatedBeforeStart = false;
	bool bNoPreviousRecordedNodesBeforeStart = false;
	FString OtherNodesWithPreviousActivation;
};

UCLASS(Hidden, NotBlueprintable, NotPlaceable, meta = (ExcludeFromFlowCatalog))
class UFlowAgentToolkitSubGraphReuseTestFinishNode : public UFlowNode_Finish
{
	GENERATED_BODY()

public:
	virtual void ExecuteInput(const FName& PinName) override;
	void FinishGraph();
	virtual void DeinitializeInstance() override;

	UPROPERTY(Transient)
	int32 ActivationCount = 0;

	UPROPERTY()
	bool bInjectComponentOnActivation = false;

	UPROPERTY(Transient)
	TObjectPtr<UFlowAgentToolkitSubGraphReuseTestComponent> InjectedComponent;

	UPROPERTY(Transient)
	TObjectPtr<UFlowInjectComponentsManager> InjectedComponentsManager;
};
