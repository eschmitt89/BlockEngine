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
    
private:
	Grid* grid;
	vector<PhysicsObject*> physicsObjects;

	typedef map<int, vector<int>> CollisionMap;
	typedef void (*ResolveBlockCollision)(PhysicsObject* physicsObject, Block block);
	
	void HandleGridCollisions(PhysicsObject* physicsObject, ResolveBlockCollision resolveBlockCollision);
	static void ResolveBlockCollisionX(PhysicsObject* physicsObject, Block block);
	static void ResolveBlockCollisionY(PhysicsObject* physicsObject, Block block);

	void HandlePhysicsObjectCollisions(int physicsObjectIndex, CollisionMap* collisionMap);
	void ResolvePhysicsObjectsCollision(PhysicsObject* physicsObject1, PhysicsObject* physicsObject2);

	int GetCollisionPairKey(int physicsObjectIndex1, int physicsObjectIndex2);

};

#endif /* PhysicsManager_hpp */
