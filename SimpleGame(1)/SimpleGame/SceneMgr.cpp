#include "stdafx.h"
#include "SceneMgr.h"



SceneMgr::SceneMgr()
{
	m_renderer = new Renderer(500,500);

	for (int i = 0; i < MAX_OBJECTS_COUNT; i++) {
		m_gameObject[i] = new GameObject();
	}
}


SceneMgr::~SceneMgr()
{
	DeleteObject();
}

void SceneMgr::DrawObjects()
{
	m_renderer->DrawSolidRect(0, 0, 0, 0, 0, 0, 0, 1.0);

	for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
	{
		if (m_gameObject[i] != NULL && m_gameObject[i]->objectDrawFlag == true)
		{
			// Renderer Test
			m_renderer->DrawSolidRect(
				m_gameObject[i]->posX,
				m_gameObject[i]->posY,
				m_gameObject[i]->posZ,
				m_gameObject[i]->size,
				m_gameObject[i]->colorR, 
				m_gameObject[i]->colorG, 
				m_gameObject[i]->colorB, 
				m_gameObject[i]->colorA
			);
		}
	}
}


void SceneMgr::AddObject(int x, int y, int z, int type)
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; i++) {
		if (m_gameObject[i]->objectDrawFlag == false) {
			m_gameObject[i]->objectDrawFlag = true;
			m_gameObject[i]->SettingType(type);
			m_gameObject[i]->SettingPos(x, y, z);
			objectCounter++;
			break;
		}
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

	for (int i = 0; i < MAX_OBJECTS_COUNT; i++) {
		m_gameObject[i]->collisionCounter = false;
	}

	for (int i = 0; i < MAX_OBJECTS_COUNT; i++) {
		m_gameObject[i]->Update(elapsedTime);
		if (m_gameObject[i]->GetType() == OBJECT_BUILDING) {
			if (m_gameObject[i]->fireBulletCool > 0.5f) {
				AddObject(m_gameObject[i]->posX, m_gameObject[i]->posY, m_gameObject[i]->posZ, OBJECT_ARROW);
				m_gameObject[i]->fireBulletCool = 0;
			}
		}
	}

	for (int i = 0; i < MAX_OBJECTS_COUNT; i++) {
		for (int j = i+1; j < MAX_OBJECTS_COUNT-1; j++) {
			if (m_gameObject[i]->type == OBJECT_BUILDING && m_gameObject[j]->type == OBJECT_CHARACTER) {
				if (Collision(*m_gameObject[i], *m_gameObject[j]) == true) {
					m_gameObject[i]->collisionCounter = true;
					m_gameObject[j]->collisionCounter = true;
					if (m_gameObject[i]->collisionCheck == false || m_gameObject[j]->collisionCheck == false) { // 마주친 둘 중 하나라도 충돌 중이 아니었다면
						m_gameObject[i]->lifeCount -= m_gameObject[j]->lifePower; // 서로의 생명력만큼 각각 생명력 감소
						m_gameObject[j]->lifeCount -= m_gameObject[i]->lifePower;
						std::cout << m_gameObject[i]->lifeCount;
					}
					m_gameObject[i]->collisionCheck = true; //충돌중이에요~
					m_gameObject[j]->collisionCheck = true; //얘랑요
				}
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

	DeleteDeadObject();

}

bool SceneMgr::Collision(GameObject a, GameObject b) {
	if (a.bb.leftBottom[0] <= b.bb.rightTop[0] && a.bb.leftBottom[1] <= b.bb.rightTop[1]
		&& a.bb.rightTop[0]>b.bb.leftBottom[0] && a.bb.rightTop[1]>b.bb.leftBottom[1]) 
	{ return true; }
	else 
	{ return false; }
}

void SceneMgr::DeleteDeadObject() {
	for (int i = 0; i < MAX_OBJECTS_COUNT; i++) {
		if (m_gameObject[i]->lifeCount <= 0) {
			m_gameObject[i]->objectDrawFlag = false;
			objectCounter--;
		}
	}
}
