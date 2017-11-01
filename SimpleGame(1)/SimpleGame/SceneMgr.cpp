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
	DeleteObject();
}

void SceneMgr::AddObject(int x, int y, int z, int type)
{
	m_gameObject[objectCounter] = new GameObject();
	m_gameObject[objectCounter]->SettingPos(x, y, z);
	m_gameObject[objectCounter]->SettingType(type);
	if (objectCounter < MAX_OBJECTS_COUNT-1) {
		objectCounter++;
	}
}

void SceneMgr::DeleteObject() 
{
	delete [] m_gameObject;
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
		m_gameObject[i]->collisionCounter = false;
	}

	for (int i = 0; i < objectCounter; i++) {
		m_gameObject[i]->Update(elapsedTime);
		if (m_gameObject[i]->GetType() == OBJECT_BUILDING) {
			if (m_gameObject[i]->fireBulletCool > 1.0f) {
				AddObject(m_gameObject[i]->posX, m_gameObject[i]->posY, m_gameObject[i]->posZ, OBJECT_ARROW);
				m_gameObject[i]->fireBulletCool = 0;
			}
		}
	}

	for (int i = 0; i < objectCounter; i++) {
		for (int j = i; j < objectCounter-1; j++) {
			if(m_gameObject[i]->GetType()== OBJECT_BUILDING && m_gameObject[j + 1]-> GetType() == OBJECT_CHARACTER)
			if (Collision(*m_gameObject[i], *m_gameObject[j+1]) == true) {
				m_gameObject[i]->collisionCounter = true;
				m_gameObject[j+1]->collisionCounter = true;
				if (m_gameObject[i]->collisionCheck == false || m_gameObject[j + 1]->collisionCheck == false) {
					m_gameObject[i]->lifeCount -= m_gameObject[j + 1]->lifeCount;
					std::cout << m_gameObject[i]->lifeCount;
				}
				m_gameObject[i]->collisionCheck = true;
				m_gameObject[j + 1]->collisionCheck = true;
			}
		}
		if (m_gameObject[i]->collisionCounter == true) {
			//m_gameObject[i]->colorG = 0;
			//m_gameObject[i]->colorB = 0;
		}
		else {
			//m_gameObject[i]->colorR = 1;
			//m_gameObject[i]->colorG = 1;
			//m_gameObject[i]->colorB = 1;
			m_gameObject[i]->collisionCheck = false;
		}
	}

	//DeleteDeadObject();

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

void SceneMgr::DeleteDeadObject() {
	for (int i = 0; i < objectCounter; i++) {
		if (m_gameObject[i]->lifeCount <= 0) {
			delete m_gameObject[i];
			for (int j = i; j < objectCounter; j++) {
				m_gameObject[i] = m_gameObject[j];
			}
		}
	}
}
