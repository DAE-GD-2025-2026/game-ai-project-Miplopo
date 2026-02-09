#include "SteeringBehaviors.h"
#include "GameAIProg/Movement/SteeringBehaviors/SteeringAgent.h"

//SEEK
//*******
// TODO: Do the Week01 assignment :^)

SteeringOutput  Seek::CalculateSteering(float DeltaT, ASteeringAgent& Agent)
{
	SteeringOutput Steering{};
	
	Steering.LinearVelocity = Target.Position - Agent.GetPosition();
	
	FVector AgentLocation = FVector(Agent.GetPosition().X, Agent.GetPosition().Y, 0.0f);
	FVector AgentLinearVelocity = FVector(Agent.GetPosition().X + Agent.GetVelocity().X, Agent.GetPosition().Y + Agent.GetVelocity().Y, 0.0f);
	FVector AgentForwardVelocity = FVector(Agent.GetPosition().X + Agent.GetActorForwardVector().X, Agent.GetPosition().Y + Agent.GetActorForwardVector().Y, 0.0f);
	FVector AgentRotationalVelocity = FVector();
	
	DrawDebugLine(Agent.GetWorld(),
	AgentLocation,
	AgentLinearVelocity,
	FColor::Green);
	
	DrawDebugLine(Agent.GetWorld(),
	AgentLocation,
	AgentForwardVelocity * Agent.GetLinearVelocity().Length(),
	FColor::Magenta);
	
	DrawDebugLine(Agent.GetWorld(),
	AgentLocation,
	AgentRotationalVelocity * Agent.GetAngularVelocity(),
	FColor::Cyan);
	//Add debug rendering for grades!!!
	
	return Steering;
}

SteeringOutput  Flee::CalculateSteering(float DeltaT, ASteeringAgent& Agent)
{
	SteeringOutput Steering{};
	
	Steering.LinearVelocity = -(Target.Position - Agent.GetPosition());
	//Add debug rendering for grades!!!
	
	return Steering;
}

SteeringOutput  Arrive::CalculateSteering(float DeltaT, ASteeringAgent& Agent)
{
	SteeringOutput Steering{};
	
	Steering.LinearVelocity = Target.Position - Agent.GetPosition();
	//Add debug rendering for grades!!!
	
	return Steering;
}