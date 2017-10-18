#include "stdafx.h"
#include "SceneMgr.h"


SceneMgr::SceneMgr()
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; i++) {
		m_gameObject[i] = NULL;
	}
}


SceneMgr::~SceneMgr()
{
}

void SceneMgr::AddObject(int x, int y, int z)
{
	m_gameObject[objectCounter] = new GameObject();
	m_gameObject[objectCounter]->SettingPos(x, y, z);
	if (objectCounter < MAX_OBJECTS_COUNT-1) {
		objectCounter++;
	}
}

void SceneMgr::DeleteObject(int index) 
{
	delete m_gameObject[index];
}

GameObject* SceneMgr::GetObjectStats(int index)
{
	return m_gameObject[index];
}

GameObject** SceneMgr::GetObjectStats()
{
	return m_gameObject;
}

void SceneMgr::Update()
{
	for (int i = 0; i < objectCounter; i++) {
		m_gameObject[i]->Update();
	}
}

int SceneMgr::CountObject() 
{
	return objectCounter;
}