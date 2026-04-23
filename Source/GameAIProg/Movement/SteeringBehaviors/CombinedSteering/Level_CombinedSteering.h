// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <vector>
#include <memory>
#include <string>

#include "CoreMinimal.h"
#include "CombinedSteeringBehaviors.h"
#include "GameAIProg/Shared/Level_Base.h"
#include "GameAIProg/Movement/SteeringBehaviors/Steering/SteeringBehaviors.h"
#include "GameAIProg/Movement/SteeringBehaviors/SteeringAgent.h"
#include "Level_CombinedSteering.generated.h"

UCLASS()
class GAMEAIPROG_API ALevel_CombinedSteering : public ALevel_Base
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALevel_CombinedSteering();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void BeginDestroy() override;

private:
	//Data members
	bool UseMouseTarget = false;
	bool CanDebugRender = false;
	
	//Steering's
	ISteeringBehavior* pEvadeBehavior{ new Evade() };
	ISteeringBehavior* pWanderBehavior{ new Wander() };
	ISteeringBehavior* pSeekBehavior{ new Seek() };
    
	//Combined steering's
	BlendedSteering* pBlendedSteering{ nullptr };
	PrioritySteering* pPrioritySteering{ nullptr };
    
    
	//Agents
	ASteeringAgent* pBlendedAgent{ nullptr };
	ASteeringAgent* pPriorityAgent{ nullptr };
	
	enum class BehaviorTypes
	{
		Seek,
		Wander,
		Flee,
		Arrive,
		Evade,
		Pursuit,
		Face,

		// @ End
		Count
	};
	
	struct ImGui_Agent final
	{
		ASteeringAgent* Agent{nullptr};
		std::unique_ptr<ISteeringBehavior> Behavior{nullptr};
		int SelectedBehavior{static_cast<int>(BehaviorTypes::Seek)};
		int SelectedTarget = -1;
	};
	
	std::vector<ImGui_Agent> CombinedSteeringAgents{};
	std::vector<std::string> TargetLabels{};
	
	void RefreshTargetLabels();
	void UpdateTarget(ImGui_Agent& Agent);
	void RefreshAgentTargets(unsigned int IndexRemoved);
};
