#include "EnemyManager.hpp"

EnemyManager::EnemyManager()
{
}

////////////////////////////////////////////////////////////////////////

EnemyManager::~EnemyManager()
{
}

////////////////////////////////////////////////////////////////////////

void EnemyManager::AddEnemy(Enemy * enemy)
{
	enemies.push_back(enemy);
}

////////////////////////////////////////////////////////////////////////

void EnemyManager::Update(float dt)
{
	for (int i = 0; i < enemies.size(); i++)
	{
		if (enemies[i]->GetExpired())
		{
			enemies.erase(enemies.begin() + i);
			i--;
		}
	}
}
