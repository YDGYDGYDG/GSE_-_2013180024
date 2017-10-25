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

void SceneMgr::Update(float elapsedTime)
{
	bool collisionCounter[MAX_OBJECTS_COUNT];
	for (int i = 0; i < MAX_OBJECTS_COUNT; i++) {
		collisionCounter[i] = false;
	}
	for (int i = 0; i < objectCounter; i++) {
		m_gameObject[i]->Update(elapsedTime);
	}

	for (int i = 0; i < objectCounter; i++) {
		for (int j = i; j < objectCounter-1; j++) {
			if (Collision(*m_gameObject[i], *m_gameObject[j+1]) == true) {
				collisionCounter[i] = true;
				collisionCounter[j + 1] = true;
			}
		}
		if (collisionCounter[i] == true) {
			m_gameObject[i]->colorG = 0;
			m_gameObject[i]->colorB = 0;
		}
		else {
			m_gameObject[i]->colorR = 1;
			m_gameObject[i]->colorG = 1;
			m_gameObject[i]->colorB = 1;
		}
	}
}

int SceneMgr::CountObject() 
{
	return objectCounter;
}

bool SceneMgr::Collision(GameObject a, GameObject b) {
	if (a.bb.leftBottom[0] <= b.bb.rightTop[0] && a.bb.leftBottom[1] <= b.bb.rightTop[1]
		&& a.bb.rightTop[0]>b.bb.leftBottom[0] && a.bb.rightTop[1]>b.bb.leftBottom[1]) 
	{ return true; }
	else 
	{ return false; }
}
