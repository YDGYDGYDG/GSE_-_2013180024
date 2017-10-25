#pragma once

#include "GameObject.h"

#define MAX_OBJECTS_COUNT 50 //여기에 적힌 수보다 1 적은 개수가 나타남

class SceneMgr
{
public:
	SceneMgr();
	~SceneMgr();

	GameObject* m_gameObject[MAX_OBJECTS_COUNT];
	int objectCounter = 0;

	void AddObject(int x, int y, int z);
	void DeleteObject(int index);
	GameObject* GetObjectStats(int index);
	GameObject** GetObjectStats();
	int CountObject();
	void Update(float elapsedTime);
	bool Collision(GameObject a, GameObject b);

};

