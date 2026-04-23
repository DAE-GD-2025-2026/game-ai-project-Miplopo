#include "Level_CombinedSteering.h"

#include <format>
#include <string>
#include "imgui.h"

// Sets default values
ALevel_CombinedSteering::ALevel_CombinedSteering()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ALevel_CombinedSteering::BeginPlay()
{
	
	std::vector<BlendedSteering::WeightedBehavior> WeightedBehaviors;
	ISteeringBehavior* pBeh{};
	BlendedSteering::WeightedBehavior firstBeh{pBeh, 0.0f};
	BlendedSteering::WeightedBehavior secondBeh{pBeh, 0.0f};
	WeightedBehaviors.push_back(firstBeh);
	WeightedBehaviors.push_back(secondBeh);
	
	pBlendedSteering = new BlendedSteering{WeightedBehaviors};
	
	pBlendedAgent = GetWorld()->SpawnActor<ASteeringAgent>(SteeringAgentClass, FVector{0,0,90}, FRotator::ZeroRotator);
	pBlendedAgent->SetSteeringBehavior(pBlendedSteering);
	
	Super::BeginPlay();
}

void ALevel_CombinedSteering::BeginDestroy()
{
	Super::BeginDestroy();

}

// Called every frame
void ALevel_CombinedSteering::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

#pragma region UI
	//UI
	{
		//Setup
		bool windowActive = true;
		ImGui::SetNextWindowPos(WindowPos);
		ImGui::SetNextWindowSize(WindowSize);
		ImGui::Begin("Game AI", &windowActive, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
	
		//Elements
		ImGui::Text("CONTROLS");
		ImGui::Indent();
		ImGui::Text("LMB: place target");
		ImGui::Text("RMB: move cam.");
		ImGui::Text("Scrollwheel: zoom cam.");
		ImGui::Unindent();
	
		ImGui::Spacing();
		ImGui::Separator();
		ImGui::Spacing();
		ImGui::Spacing();
	
		ImGui::Text("STATS");
		ImGui::Indent();
		ImGui::Text("%.3f ms/frame", 1000.0f / ImGui::GetIO().Framerate);
		ImGui::Text("%.1f FPS", ImGui::GetIO().Framerate);
		ImGui::Unindent();
	
		ImGui::Spacing();
		ImGui::Separator();
		ImGui::Spacing();
		ImGui::Spacing();
	
		ImGui::Text("Flocking");
		ImGui::Spacing();
		ImGui::Spacing();
	
		if (ImGui::Checkbox("Debug Rendering", &CanDebugRender))
		{
			// TODO: Handle the debug rendering of your agents here :)
		}
		ImGui::Checkbox("Trim World", &TrimWorld->bShouldTrimWorld);
		if (TrimWorld->bShouldTrimWorld)
		{
			ImGuiHelpers::ImGuiSliderFloatWithSetter("Trim Size",
				TrimWorld->GetTrimWorldSize(), 1000.f, 3000.f,
				[this](float InVal) { TrimWorld->SetTrimWorldSize(InVal); });
		}
		
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
	
		ImGui::Text("Behavior Weights");
		ImGui::Spacing();


		ImGuiHelpers::ImGuiSliderFloatWithSetter("Seek",
			pBlendedSteering->GetWeightedBehaviorsRef()[0].Weight, 0.f, 1.f,
			[this](float InVal) { pBlendedSteering->GetWeightedBehaviorsRef()[0].Weight = InVal; }, "%.2f");
		
		ImGuiHelpers::ImGuiSliderFloatWithSetter("Wander",
		pBlendedSteering->GetWeightedBehaviorsRef()[1].Weight, 0.f, 1.f,
		[this](float InVal) { pBlendedSteering->GetWeightedBehaviorsRef()[1].Weight = InVal; }, "%.2f");
	
		//End
		ImGui::End();
	}
#pragma endregion
	
	for (ImGui_Agent& a : CombinedSteeringAgents)
	{
		if (a.Agent)
		{
			UpdateTarget(a);
		}
	}
}

	// Combined Steering Update
	// TODO: implement handling mouse click input for seek
	// TODO: implement Make sure to also evade the wanderer

void ALevel_CombinedSteering::RefreshTargetLabels()
{
	TargetLabels.clear();
	
	TargetLabels.push_back("Mouse");
	for (int i{0}; i < CombinedSteeringAgents.size(); ++i)
	{
		TargetLabels.push_back(std::format("Agent {}", i));
	}
}

void ALevel_CombinedSteering::UpdateTarget(ImGui_Agent& Agent)
{
	// Note: MouseTarget position is updated via Level BP every click
	
	bool const bUseMouseAsTarget = Agent.SelectedTarget < 0;
	if (!bUseMouseAsTarget)
	{
		ASteeringAgent* const TargetAgent = CombinedSteeringAgents[Agent.SelectedTarget].Agent;

		FTargetData Target;
		Target.Position = TargetAgent->GetPosition();
		Target.Orientation = TargetAgent->GetRotation();
		Target.LinearVelocity = TargetAgent->GetLinearVelocity();
		Target.AngularVelocity = TargetAgent->GetAngularVelocity();

		Agent.Behavior->SetTarget(Target);
	}
	else
	{
		Agent.Behavior->SetTarget(MouseTarget);
	}
}

void ALevel_CombinedSteering::RefreshAgentTargets(unsigned int IndexRemoved)
{
	for (UINT i = 0; i < CombinedSteeringAgents.size(); ++i)
	{
		if (i >= IndexRemoved)
		{
			auto& Agent = CombinedSteeringAgents[i];
			if (Agent.SelectedTarget == IndexRemoved || i  == Agent.SelectedTarget)
			{
				--Agent.SelectedTarget;
			}
		}
	}
}
	