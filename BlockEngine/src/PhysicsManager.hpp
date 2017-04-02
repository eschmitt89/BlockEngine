//
//  PhysicsManager.hpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#ifndef PhysicsManager_hpp
#define PhysicsManager_hpp

#include "PhysicsObject.hpp"
#include "Grid.hpp"
#include <vector>
#include <map>
#include <set>

using namespace std;

class PhysicsManager 
{
public:
	PhysicsManager(Grid* grid);
    ~PhysicsManager();

	void Update(float dt);
	void Draw(sf::RenderWindow& window);

	void AddPhysicsObject(PhysicsObject* physicsObject);
	void ClearPhyiscsObjects();

	typedef void(*spawn)(PhysicsObject* p);
    
private:
	Grid* grid;
	vector<PhysicsObject*> physicsObjects;

	typedef map<int, vector<int>> CollisionMap;
	
	void HandleGridCollisions(PhysicsObject* physicsObject, PhysicsObject::ResolveBlockCollision resolveBlockCollsion, float dt);
	void HandlePhysicsObjectCollisions(int physicsObjectIndex, CollisionMap* collisionMap);
	void ResolvePhysicsObjectsCollision(PhysicsObject* physicsObjectA, PhysicsObject* physicsObjectB);

	int GetCollisionPairKey(int physicsObjectIndexA, int physicsObjectIndexB);
};

#endif /* PhysicsManager_hpp */
