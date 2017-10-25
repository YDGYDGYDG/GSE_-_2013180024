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

	for (int i = 0; i < objectCounter; i++) {
		m_gameObject[i]->Update(elapsedTime);
	}

	for (int i = 0; i < objectCounter; i++) {
		for (int j = 0; j < objectCounter; j++) {
			if (Collision(*m_gameObject[i], *m_gameObject[j]) == true) {
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

}

int SceneMgr::CountObject() 
{
	return objectCounter;
}

bool SceneMgr::Collision(GameObject a, GameObject b) {
	if (a.bb.leftBottom < b.bb.rightTop 
		&& a.bb.rightTop>b.bb.leftBottom) { return true; }
	else if (b.bb.leftBottom < a.bb.rightTop 
		&& b.bb.rightTop>a.bb.leftBottom) { return true; }
	else { return false; }
}
