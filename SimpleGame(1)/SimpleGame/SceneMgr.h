#pragma once

#include "GameObject.h"

#define MAX_OBJECTS_COUNT 50

class SceneMgr
{
public:
	SceneMgr();
	~SceneMgr();

	GameObject *m_gameObject[MAX_OBJECTS_COUNT];

	void AddObject(int x, int y, int z);
	void DeleteObject(int index);
	void GetObjectStats(int index);
	int CountObject();
	void Update();

protected:
	int objectCounter = 0;
};

