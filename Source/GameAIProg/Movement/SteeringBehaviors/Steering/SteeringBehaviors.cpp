#include "SteeringBehaviors.h"
#include "GameAIProg/Movement/SteeringBehaviors/SteeringAgent.h"

#include "VectorTypes.h"

//SEEK
//*******
// TODO: Do the Week01 assignment :^)

SteeringOutput  Seek::CalculateSteering(float DeltaT, ASteeringAgent& Agent)
{
	// Steering
	SteeringOutput Steering{};
	
	Steering.LinearVelocity = Target.Position - Agent.GetPosition();
	Steering.LinearVelocity.Normalize();
	
	/*// Debug info
	FVector AgentLocation = FVector(
		Agent.GetPosition().X,
		Agent.GetPosition().Y,
		0.0f);
	
	FVector AgentDirection = FVector(
		Agent.GetPosition().X + Steering.LinearVelocity.X * Agent.GetMaxLinearSpeed(),
		Agent.GetPosition().Y + Steering.LinearVelocity.Y * Agent.GetMaxLinearSpeed(),
		0.0f);
	
	FVector AgentForwardVelocity = FVector(
		Agent.GetPosition().X + Agent.GetActorForwardVector().X * abs(Agent.GetLinearVelocity().Length()),
		Agent.GetPosition().Y + Agent.GetActorForwardVector().Y * abs(Agent.GetLinearVelocity().Length()),
		0.0f);
	
	FVector AgentRotationalVelocity = FVector(
		Agent.GetPosition().X,
		Agent.GetPosition().X,
		0.0f);
	
	DrawDebugLine(Agent.GetWorld(),
	AgentLocation,
	AgentDirection,
	FColor::Green);
	
	DrawDebugLine(Agent.GetWorld(),
	AgentLocation,
	AgentForwardVelocity,
	FColor::Magenta);
	
	DrawDebugCircle(Agent.GetWorld(),
		FVector(Target.Position.X,Target.Position.Y, 0.0f),
		20.0f,
		500,
		FColor::Red,
		false,
		-1.0f,
		0,
		5.0f,
		FVector(1.0f, 0.0f, 0.0f),
		FVector(0.0f, 1.0f, 0.0f),
		false);
	
	/*DrawDebugLine(Agent.GetWorld(),
	AgentLocation,
	AgentRotationalVelocity * Agent.GetAngularVelocity(),
	FColor::Cyan);#1#
	
	//Add debug rendering for grades!!!*/
	
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
	
	float distance {};
	distance = (Target.Position - Agent.GetPosition()).Length();
	
	if (startMaxSpeed < Agent.GetMaxLinearSpeed())
	{
		startMaxSpeed = Agent.GetMaxLinearSpeed();
	}
	if (startDistance < distance)
	{
		startDistance = distance;
	}
	
	if (distance < SlowRadius && distance > StopRadius)
	{
		Agent.SetMaxLinearSpeed(startMaxSpeed * (distance/startDistance));
	}
	else if (distance <= StopRadius)
	{
		Agent.SetMaxLinearSpeed(0.0f);
	}
	else
	{
		Agent.SetMaxLinearSpeed(startMaxSpeed);
	}
	//Add debug rendering for grades!!!
	
	return Steering;
}

SteeringOutput  Face::CalculateSteering(float DeltaT, ASteeringAgent& Agent)
{
	SteeringOutput Steering{};
	
	Steering.LinearVelocity = Target.Position - Agent.GetPosition();
	Agent.SetMaxLinearSpeed(0.0f);
	//Add debug rendering for grades!!!
	
	return Steering;
}