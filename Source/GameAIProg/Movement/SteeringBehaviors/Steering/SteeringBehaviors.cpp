#include "SteeringBehaviors.h"

#include <iostream>

#include "GameAIProg/Movement/SteeringBehaviors/SteeringAgent.h"

#include "VectorTypes.h"

//SEEK
//*******
// TODO: Do the Week01 assignment :^)

SteeringOutput  Seek::CalculateSteering(float DeltaT, ASteeringAgent& Agent)
{
	// Steering
	SteeringOutput Steering{};
	Agent.SetMaxLinearSpeed(600.0f);
	Steering.LinearVelocity = Target.Position - Agent.GetPosition();
	
	// Debug info
	FVector AgentLocation = FVector(
		Agent.GetPosition().X,
		Agent.GetPosition().Y,
		0.0f);
	
	FVector AgentDirection = FVector(
		Agent.GetPosition().X + Agent.GetLinearVelocity().X,
		Agent.GetPosition().Y + Agent.GetLinearVelocity().Y,
		0.0f);
	
	FVector AgentForwardVelocity = FVector(
		Agent.GetPosition().X + Agent.GetActorForwardVector().X * abs(Agent.GetLinearVelocity().Length()),
		Agent.GetPosition().Y + Agent.GetActorForwardVector().Y * abs(Agent.GetLinearVelocity().Length()),
		0.0f);
	
	if (Agent.GetDebugRenderingEnabled())
	{
		//LinearVelocity
		DrawDebugLine(Agent.GetWorld(),
		AgentLocation,
		AgentDirection,
		FColor::Green);
	
		//ForwardVelocity
		DrawDebugLine(Agent.GetWorld(),
		AgentLocation,
		AgentForwardVelocity,
		FColor::Magenta);
	
		//Target
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
	}
	
	return Steering;
}

SteeringOutput  Flee::CalculateSteering(float DeltaT, ASteeringAgent& Agent)
{
	SteeringOutput Steering{};
	Agent.SetMaxLinearSpeed(600.0f);
	Steering.LinearVelocity = -(Target.Position - Agent.GetPosition());
	
	// Debug info
    	FVector AgentLocation = FVector(
    		Agent.GetPosition().X,
    		Agent.GetPosition().Y,
    		0.0f);
    	
    	FVector AgentDirection = FVector(
    		Agent.GetPosition().X + Agent.GetLinearVelocity().X,
    		Agent.GetPosition().Y + Agent.GetLinearVelocity().Y,
    		0.0f);
    	
    	FVector AgentForwardVelocity = FVector(
    		Agent.GetPosition().X + Agent.GetActorForwardVector().X * abs(Agent.GetLinearVelocity().Length()),
    		Agent.GetPosition().Y + Agent.GetActorForwardVector().Y * abs(Agent.GetLinearVelocity().Length()),
    		0.0f);
    	
    	if (Agent.GetDebugRenderingEnabled())
    	{
    		//LinearVelocity
    		DrawDebugLine(Agent.GetWorld(),
    		AgentLocation,
    		AgentDirection,
    		FColor::Green);
    	
    		//ForwardVelocity
    		DrawDebugLine(Agent.GetWorld(),
    		AgentLocation,
    		AgentForwardVelocity,
    		FColor::Magenta);
    	
    		//Target
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
    	}
	
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
	
	// Debug info
	FVector AgentLocation = FVector(
		Agent.GetPosition().X,
		Agent.GetPosition().Y,
		0.0f);
    	
	FVector AgentDirection = FVector(
		Agent.GetPosition().X + Agent.GetLinearVelocity().X,
		Agent.GetPosition().Y + Agent.GetLinearVelocity().Y,
		0.0f);
    	
	FVector AgentForwardVelocity = FVector(
		Agent.GetPosition().X + Agent.GetActorForwardVector().X * abs(Agent.GetLinearVelocity().Length()),
		Agent.GetPosition().Y + Agent.GetActorForwardVector().Y * abs(Agent.GetLinearVelocity().Length()),
		0.0f);
    	
	if (Agent.GetDebugRenderingEnabled())
	{
		//LinearVelocity
		DrawDebugLine(Agent.GetWorld(),
		AgentLocation,
		AgentDirection,
		FColor::Green);
    	
		//ForwardVelocity
		DrawDebugLine(Agent.GetWorld(),
		AgentLocation,
		AgentForwardVelocity,
		FColor::Magenta);
		
		//SlowCircle
		DrawDebugCircle(Agent.GetWorld(),
			FVector(Agent.GetPosition().X, Agent.GetPosition().Y, 0.0f),
			SlowRadius,
			500,
			FColor::Blue,
			false,
			-1.0f,
			0,
			5.0f,
			FVector(1.0f, 0.0f, 0.0f),
			FVector(0.0f, 1.0f, 0.0f),
			false);
		
		//StopCircle
		DrawDebugCircle(Agent.GetWorld(),
			FVector(Agent.GetPosition().X, Agent.GetPosition().Y, 0.0f),
			StopRadius,
			500,
			FColor::Orange,
			false,
			-1.0f,
			0,
			5.0f,
			FVector(1.0f, 0.0f, 0.0f),
			FVector(0.0f, 1.0f, 0.0f),
			false);
		
		//Target
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
	}
	
	return Steering;
}

SteeringOutput  Face::CalculateSteering(float DeltaT, ASteeringAgent& Agent)
{
	SteeringOutput Steering{};
	
	Steering.LinearVelocity = Target.Position - Agent.GetPosition();
	Agent.SetMaxLinearSpeed(0.0f);
	
	// Debug info
	FVector AgentLocation = FVector(
		Agent.GetPosition().X,
		Agent.GetPosition().Y,
		0.0f);
	
	FVector AgentForwardVelocity = FVector(
		Agent.GetPosition().X + Agent.GetActorForwardVector().X * 300.0f,
		Agent.GetPosition().Y + Agent.GetActorForwardVector().Y * 300.0f,
		0.0f);
	
	if (Agent.GetDebugRenderingEnabled())
	{
		//ForwardVelocity
		DrawDebugLine(Agent.GetWorld(),
		AgentLocation,
		AgentForwardVelocity,
		FColor::Magenta);
		
		//Target
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
	}
	
	return Steering;
}

SteeringOutput  Pursuit::CalculateSteering(float DeltaT, ASteeringAgent& Agent)
{
	SteeringOutput Steering{};
	Agent.SetMaxLinearSpeed(600.0f);
	Steering.LinearVelocity = (Target.Position + Target.LinearVelocity - Agent.GetPosition())/DeltaT;
	
	// Debug info
	FVector AgentLocation = FVector(
		Agent.GetPosition().X,
		Agent.GetPosition().Y,
		0.0f);
	
	FVector AgentDirection = FVector(
		Agent.GetPosition().X + Agent.GetLinearVelocity().X,
		Agent.GetPosition().Y + Agent.GetLinearVelocity().Y,
		0.0f);
	
	FVector AgentForwardVelocity = FVector(
		Agent.GetPosition().X + Agent.GetActorForwardVector().X * abs(Agent.GetLinearVelocity().Length()),
		Agent.GetPosition().Y + Agent.GetActorForwardVector().Y * abs(Agent.GetLinearVelocity().Length()),
		0.0f);
	
	if (Agent.GetDebugRenderingEnabled())
	{
		//LinearVelocity
		DrawDebugLine(Agent.GetWorld(),
		AgentLocation,
		AgentDirection,
		FColor::Green);
	
		//ForwardVelocity
		DrawDebugLine(Agent.GetWorld(),
		AgentLocation,
		AgentForwardVelocity,
		FColor::Magenta);
	
		//Target
		DrawDebugCircle(Agent.GetWorld(),
			FVector(Target.Position + Target.LinearVelocity, 0.0f),
			20.0f,
			500,
			FColor::Magenta,
			false,
			-1.0f,
			0,
			5.0f,
			FVector(1.0f, 0.0f, 0.0f),
			FVector(0.0f, 1.0f, 0.0f),
			false);
	}
	
	return Steering;
}

SteeringOutput  Evade::CalculateSteering(float DeltaT, ASteeringAgent& Agent)
{
	SteeringOutput Steering{};
	Agent.SetMaxLinearSpeed(600.0f);
	float distance {};
	distance = (Target.Position - Agent.GetPosition()).Length();
	
	if (distance < 500.0f)
	{
		Steering.LinearVelocity = -((Target.Position + Target.LinearVelocity - Agent.GetPosition())/DeltaT);
	}
	
	// Debug info
	FVector AgentLocation = FVector(
		Agent.GetPosition().X,
		Agent.GetPosition().Y,
		0.0f);
	
	FVector AgentDirection = FVector(
		Agent.GetPosition().X + Agent.GetLinearVelocity().X,
		Agent.GetPosition().Y + Agent.GetLinearVelocity().Y,
		0.0f);
	
	FVector AgentForwardVelocity = FVector(
		Agent.GetPosition().X + Agent.GetActorForwardVector().X * abs(Agent.GetLinearVelocity().Length()),
		Agent.GetPosition().Y + Agent.GetActorForwardVector().Y * abs(Agent.GetLinearVelocity().Length()),
		0.0f);
	
	if (Agent.GetDebugRenderingEnabled())
	{
		//LinearVelocity
		DrawDebugLine(Agent.GetWorld(),
		AgentLocation,
		AgentDirection,
		FColor::Green);
	
		//ForwardVelocity
		DrawDebugLine(Agent.GetWorld(),
		AgentLocation,
		AgentForwardVelocity,
		FColor::Magenta);
	
		//Target
		DrawDebugCircle(Agent.GetWorld(),
			FVector(Target.Position + Target.LinearVelocity, 0.0f),
			20.0f,
			500,
			FColor::Magenta,
			false,
			-1.0f,
			0,
			5.0f,
			FVector(1.0f, 0.0f, 0.0f),
			FVector(0.0f, 1.0f, 0.0f),
			false);
	}
	
	return Steering;
}

SteeringOutput  Wander::CalculateSteering(float DeltaT, ASteeringAgent& Agent)
{
	SteeringOutput Steering{};
	Agent.SetMaxLinearSpeed(600.0f);
	m_WanderAngle += FMath::RandRange(-m_MaxAngleChange, m_MaxAngleChange);
	
	FVector2D circleCenter(Agent.GetPosition() + Agent.GetLinearVelocity() / Agent.GetMaxLinearSpeed() * m_OffsetDistance);
	FVector2D circleWanderTarget(circleCenter.X + cosf(m_WanderAngle) * m_Radius, circleCenter.Y - sinf(m_WanderAngle) * m_Radius);
	
	Steering.LinearVelocity = circleWanderTarget - Agent.GetPosition();
	
	// Debug info
	FVector AgentLocation = FVector(
		Agent.GetPosition().X,
		Agent.GetPosition().Y,
		0.0f);
    	
	FVector AgentDirection = FVector(
		Agent.GetPosition().X + Agent.GetLinearVelocity().X,
		Agent.GetPosition().Y + Agent.GetLinearVelocity().Y,
		0.0f);
    	
	FVector AgentForwardVelocity = FVector(
		Agent.GetPosition().X + Agent.GetActorForwardVector().X * abs(Agent.GetLinearVelocity().Length()),
		Agent.GetPosition().Y + Agent.GetActorForwardVector().Y * abs(Agent.GetLinearVelocity().Length()),
		0.0f);
    	
	if (Agent.GetDebugRenderingEnabled())
	{
		//LinearVelocity
		DrawDebugLine(Agent.GetWorld(),
		AgentLocation,
		AgentDirection,
		FColor::Green);
    	
		//ForwardVelocity
		DrawDebugLine(Agent.GetWorld(),
		AgentLocation,
		AgentForwardVelocity,
		FColor::Magenta);
		
		DrawDebugCircle(
			Agent.GetWorld(),
			FVector {circleCenter.X, circleCenter.Y,0},
			m_Radius,
			20,
			FColor::Blue,
			false,
			-1.f,
			0,
			0,
			FVector {0,1,0},
			FVector {1,0,0},
			false);
	}
	
	return Steering;
}

