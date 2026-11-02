// Copyright https://github.com/MothCocoon/FlowGraph/graphs/contributors
#include "FlowAgentToolkitSubGraphReuseTestTypes.h"

#include "FlowAsset.h"
#include "GameFramework/Actor.h"
#include "Types/FlowInjectComponentsManager.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(FlowAgentToolkitSubGraphReuseTestTypes)

void UFlowAgentToolkitSubGraphReuseTestStartNode::TriggerFirstOutput(const bool bFinish)
{
	bAllNodesNeverActivatedBeforeStart = true;

	if (const UFlowAsset* FlowAsset = GetFlowAsset())
	{
		const TArray<UFlowNode*>& RecordedNodes = FlowAsset->GetRecordedNodes();
		bNoPreviousRecordedNodesBeforeStart = RecordedNodes.Num() == 1 && RecordedNodes.Contains(this);
		OtherNodesWithPreviousActivation.Reset();

		for (const TPair<FGuid, UFlowNode*>& Node : FlowAsset->GetNodes())
		{
			if (Node.Value->GetActivationState() != EFlowNodeState::NeverActivated)
			{
				bAllNodesNeverActivatedBeforeStart = false;
				OtherNodesWithPreviousActivation += FString::Printf(TEXT("%s=%d; "),
					*Node.Value->GetName(), static_cast<int32>(Node.Value->GetActivationState()));
			}
		}
	}

	Super::TriggerFirstOutput(bFinish);
}

void UFlowAgentToolkitSubGraphReuseTestFinishNode::ExecuteInput(const FName& /*PinName*/)
{
	++ActivationCount;

	if (bInjectComponentOnActivation && !IsValid(InjectedComponent))
	{
		if (AActor* ActorOwner = GetFlowAsset()->TryFindActorOwner())
		{
			InjectedComponent = NewObject<UFlowAgentToolkitSubGraphReuseTestComponent>(ActorOwner);
			InjectedComponentsManager = NewObject<UFlowInjectComponentsManager>(this);
			InjectedComponentsManager->InitializeRuntime();
			InjectedComponentsManager->InjectComponentOnActor(*ActorOwner, *InjectedComponent);
		}
	}
}

void UFlowAgentToolkitSubGraphReuseTestFinishNode::FinishGraph()
{
	UFlowNode_Finish::ExecuteInput(UFlowNode::DefaultInputPin.PinName);
}

void UFlowAgentToolkitSubGraphReuseTestFinishNode::DeinitializeInstance()
{
	if (IsValid(InjectedComponentsManager))
	{
		InjectedComponentsManager->ShutdownRuntime();
		InjectedComponentsManager = nullptr;
	}

	Super::DeinitializeInstance();
}
