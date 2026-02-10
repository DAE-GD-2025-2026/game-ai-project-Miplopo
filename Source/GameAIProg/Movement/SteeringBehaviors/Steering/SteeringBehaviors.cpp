#include "SteeringBehaviors.h"
#include "GameAIProg/Movement/SteeringBehaviors/SteeringAgent.h"

//SEEK
//*******
// TODO: Do the Week01 assignment :^)

SteeringOutput  Seek::CalculateSteering(float DeltaT, ASteeringAgent& Agent)
{
	// Steering
	SteeringOutput Steering{};
	
	//Agent.SetMaxLinearSpeed(300.0f);
	
	Steering.LinearVelocity = Target.Position - Agent.GetPosition();
	Steering.LinearVelocity.Normalize();
	
	// Debug lines
	FVector AgentLocation = FVector(
		Agent.GetPosition().X,
		Agent.GetPosition().Y,
		0.0f);
	
	FVector AgentLinearVelocity = FVector(
		Agent.GetPosition().X + Steering.LinearVelocity.X * Agent.GetMaxLinearSpeed(),
		Agent.GetPosition().Y + Steering.LinearVelocity.Y * Agent.GetMaxLinearSpeed(),
		0.0f);
	
	FVector AgentForwardVelocity = FVector(
		Agent.GetPosition().X + Agent.GetActorForwardVector().X,
		Agent.GetPosition().Y + Agent.GetActorForwardVector().Y,
		0.0f);
	
	FVector AgentRotationalVelocity = FVector();
	
	DrawDebugLine(Agent.GetWorld(),
	AgentLocation,
	AgentLinearVelocity,
	FColor::Green);
	
	DrawDebugLine(Agent.GetWorld(),
	AgentLocation,
	AgentForwardVelocity,
	FColor::Magenta);
	
	/*DrawDebugLine(Agent.GetWorld(),
	AgentLocation,
	AgentRotationalVelocity * Agent.GetAngularVelocity(),
	FColor::Cyan);*/
	
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