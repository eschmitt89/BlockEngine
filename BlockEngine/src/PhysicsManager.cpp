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
		HandleGridCollisions(physicsObjects[i], PhysicsObject::ResolveBlockCollisionXFunction);

		physicsObjects[i]->UpdateY(dt);
		HandleGridCollisions(physicsObjects[i], PhysicsObject::ResolveBlockCollisionYFunction);

		HandlePhysicsObjectCollisions(i, &collisionMap);
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

void PhysicsManager::HandleGridCollisions(PhysicsObject * physicsObject, PhysicsObject::ResolveBlockCollision resolveBlockCollsion)
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
					resolveBlockCollsion(physicsObject, block);
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

						if (physicsObject->GetGlobalBounds().intersects(otherPhysicsObject->GetGlobalBounds()))
						{
							physicsObject->ResolvePhysicsObjectCollision(otherPhysicsObject);
							otherPhysicsObject->ResolvePhysicsObjectCollision(physicsObject);

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

void PhysicsManager::ResolvePhysicsObjectsCollision(PhysicsObject * physicsObject1, PhysicsObject * physicsObject2)
{

}

////////////////////////////////////////////////////////////////////////

int PhysicsManager::GetCollisionPairKey(int physicsObjectIndex1, int physicsObjectIndex2)
{
	return (physicsObjectIndex1 < physicsObjectIndex2) 
		? physicsObjectIndex1 + (physicsObjectIndex2 * physicsObjects.size()) 
		: physicsObjectIndex2 + (physicsObjectIndex1 * physicsObjects.size());
}

