//
//  PhysicsObject.cpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#include "PhysicsManager.hpp"

#define XAXIS 'x'
#define YAXIS 'y'

PhysicsManager::PhysicsManager(Grid* grid)
{
	this->grid = grid;
}

////////////////////////////////////////////////////////////////////////

PhysicsManager::~PhysicsManager()
{
	ClearPhyiscsObjects();
}

////////////////////////////////////////////////////////////////////////

void PhysicsManager::Update(float dt)
{
	CollisionMap collisionMap;

	for (int i = 0; i < physicsObjects.size(); i++)
	{
		physicsObjects[i]->Update(dt);

		physicsObjects[i]->UpdateX(dt);
		HandleGridCollisions(physicsObjects[i], PhysicsObject::ResolveBlockCollisionXFunction, dt);

		physicsObjects[i]->UpdateY(dt);
		HandleGridCollisions(physicsObjects[i], PhysicsObject::ResolveBlockCollisionYFunction, dt);

		HandlePhysicsObjectCollisions(i, &collisionMap);

		if (physicsObjects[i]->GetExpired())
		{
			delete physicsObjects[i];
			physicsObjects.erase(physicsObjects.begin() + i);
			i--;
		}
	}
}

////////////////////////////////////////////////////////////////////////

void PhysicsManager::Draw(sf::RenderWindow & window)
{
	for (int i = 0; i < physicsObjects.size(); i++)
	{
		physicsObjects[i]->Draw(window);
	}
}

////////////////////////////////////////////////////////////////////////

void PhysicsManager::AddPhysicsObject(PhysicsObject * physicsObject)
{
	physicsObjects.push_back(physicsObject);
}

////////////////////////////////////////////////////////////////////////

void PhysicsManager::ClearPhyiscsObjects()
{
	for (int i = 0; i < physicsObjects.size(); i++)
	{
		delete physicsObjects[i];
	}
	physicsObjects.clear();
}

////////////////////////////////////////////////////////////////////////

void PhysicsManager::HandleGridCollisions(PhysicsObject * physicsObject, PhysicsObject::ResolveBlockCollision resolveBlockCollsion, float dt)
{
	Vector4i collidedBlocks = grid->GetBlockIndicies(physicsObject->GetPosition(), physicsObject->GetSize());

	for (int column = collidedBlocks.x1; column <= collidedBlocks.x2; column++)
	{
		for (int row = collidedBlocks.y1; row <= collidedBlocks.y2; row++)
		{
			if (grid->IsValidNonEmptyBlockIndex(column, row))
			{
				Block block = grid->GetBlock(column, row);

				if (Intersect(physicsObject->GetPosition(), physicsObject->GetSize(), block.GetPosition(), block.GetSize()))
				{
					resolveBlockCollsion(physicsObject, block, dt);
				}
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////

void PhysicsManager::HandlePhysicsObjectCollisions(int physicsObjectIndex, CollisionMap* collisionMap)
{
	set<int> checkedCollisionPairs;

	PhysicsObject* physicsObject = physicsObjects[physicsObjectIndex];

	Vector4i collidedBlocks = grid->GetBlockIndicies(physicsObject->GetPosition(), physicsObject->GetSize());

	for (int column = collidedBlocks.x1; column <= collidedBlocks.x2; column++)
	{
		for (int row = collidedBlocks.y1; row <= collidedBlocks.y2; row++)
		{
			if (grid->IsValidBlockIndex(column, row))
			{
				int blockKey = grid->GetBlockKey(column, row);
				
				for (int i = 0; i < (*collisionMap)[blockKey].size(); i++)
				{
					int otherPhysicsObjectIndex = (*collisionMap)[blockKey][i];

					int collisionPairKey = GetCollisionPairKey(physicsObjectIndex, otherPhysicsObjectIndex);

					if (checkedCollisionPairs.find(collisionPairKey) == checkedCollisionPairs.end())
					{
						PhysicsObject* otherPhysicsObject = physicsObjects[(*collisionMap)[blockKey][i]];

						if (Intersect(physicsObject->GetPosition(), physicsObject->GetSize(), otherPhysicsObject->GetPosition(), otherPhysicsObject->GetSize()))
						{
							physicsObject->CollideWith(otherPhysicsObject);
							otherPhysicsObject->CollideWith(physicsObject);

							ResolvePhysicsObjectsCollision(physicsObject, otherPhysicsObject);
						}

						checkedCollisionPairs.insert(collisionPairKey);
					}
				}

				(*collisionMap)[blockKey].push_back(physicsObjectIndex);
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////

void PhysicsManager::ResolvePhysicsObjectsCollision(PhysicsObject * physicsObjectA, PhysicsObject * physicsObjectB)
{
	sf::Vector2f collisionNormal = NormalizeVector(physicsObjectB->GetCenter() - physicsObjectA->GetCenter());

	sf::Vector2f relativeVelocity = physicsObjectB->GetVelocity() - physicsObjectA->GetVelocity();

	float velocityMagnitude = DotProduct(relativeVelocity, collisionNormal);

	if (velocityMagnitude > 0) return;

	float collisionElasticity = min(physicsObjectA->GetElasticity(), physicsObjectB->GetElasticity());

	float impulseScalar = -(1 + collisionElasticity) * velocityMagnitude;
	impulseScalar /= (1 / physicsObjectA->GetMass()) + (1 / physicsObjectB->GetMass());

	sf::Vector2f impulse = impulseScalar * collisionNormal;

	physicsObjectA->Impulse(-(1 / physicsObjectA->GetMass()) * impulse);
	physicsObjectB->Impulse((1 / physicsObjectB->GetMass()) * impulse);
}

////////////////////////////////////////////////////////////////////////

int PhysicsManager::GetCollisionPairKey(int physicsObjectIndexA, int physicsObjectIndexB)
{
	return (physicsObjectIndexA < physicsObjectIndexB) 
		? physicsObjectIndexA + (physicsObjectIndexB * physicsObjects.size()) 
		: physicsObjectIndexB + (physicsObjectIndexA * physicsObjects.size());
}

