#ifndef EnemyManager_hpp
#define EnemyManager_hpp

#include "Enemy.hpp"

using namespace std;

class EnemyManager
{
public:
	EnemyManager();
	~EnemyManager();
    
	void AddEnemy(Enemy* enemy);
	void Update(float dt);

private:
	vector<Enemy*> enemies;

};

#endif /* EnemyManager_hpp */
