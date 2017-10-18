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
	if (objectCounter < MAX_OBJECTS_COUNT) {
		objectCounter++;
	}
}

void SceneMgr::DeleteObject(int index) 
{
	delete m_gameObject[index];
}

void SceneMgr::GetObjectStats(int index)
{
	int posX    = m_gameObject[index]->posX;
	int posY	  = m_gameObject[index]->posY ;
	int posZ	  = m_gameObject[index]->posZ ;
	float speedX  = m_gameObject[index]->speedX ;
	float speedY  = m_gameObject[index]->speedY;
	float speedZ  = m_gameObject[index]->speedZ;
	float size	  = m_gameObject[index]->size;
	float colorR  = m_gameObject[index]->colorR;
	float colorG  = m_gameObject[index]->colorG;
	float colorB  = m_gameObject[index]->colorB;
	float colorA  = m_gameObject[index]->colorA;
}

void SceneMgr::Update()
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; i++) {
		m_gameObject[i]->Update();
	}
}

int SceneMgr::CountObject() 
{
	return objectCounter;
}