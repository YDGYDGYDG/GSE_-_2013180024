#pragma once

#include "GameObject.h"

#define MAX_BUILDINGS_COUNT 1
#define MAX_CHARACTERS_COUNT 10
#define MAX_BULLETS_COUNT 50
#define MAX_ARROWS_COUNT 50
#define MAX_OBJECTS_COUNT (MAX_BUILDINGS_COUNT+MAX_CHARACTERS_COUNT+MAX_BULLETS_COUNT+MAX_ARROWS_COUNT +1)
//������Ʈ Ÿ��
#define OBJECT_BUILDING 0
#define OBJECT_CHARACTER 1
#define OBJECT_BULLET 2
#define OBJECT_ARROW 3

class SceneMgr
{
public:
	SceneMgr();
	~SceneMgr();

	GameObject* m_gameObject[MAX_OBJECTS_COUNT];
	int objectCounter = 0;

	void AddObject(int x, int y, int z, int type); //��ü����
	void DeleteObject(); //��� ��ü ����
	GameObject* GetObjectStats(int index); //n��° ��ü���� ����
	GameObject** GetObjectStats(); //��� ��ü���� ����
	int CountObject(); //��ü ���� ����
	void Update(float elapsedTime); 
	bool Collision(GameObject a, GameObject b); //�浹
	void DeleteDeadObject(); //n��° ��ü ����
};

