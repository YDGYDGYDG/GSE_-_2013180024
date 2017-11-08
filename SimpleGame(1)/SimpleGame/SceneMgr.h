#pragma once

#include "GameObject.h"
#include "Renderer.h"

#define MAX_BUILDINGS_COUNT 1
#define MAX_CHARACTERS_COUNT 10
#define MAX_BULLETS_COUNT 50
#define MAX_ARROWS_COUNT 50
#define MAX_OBJECTS_COUNT (MAX_BUILDINGS_COUNT + MAX_CHARACTERS_COUNT + MAX_BULLETS_COUNT + MAX_ARROWS_COUNT)
//오브젝트 타입
#define OBJECT_BUILDING 1
#define OBJECT_CHARACTER 2
#define OBJECT_BULLET 3
#define OBJECT_ARROW 4

class SceneMgr
{
public:
	SceneMgr();
	~SceneMgr();

	int buildingCounter = 0;
	int characterCounter = 0;
	int arrowCounter = 0;
	int bulletCounter = 0;


	void AddObject(int x, int y, int z, int type); //객체생성
	void DeleteObject(); //모든 객체 삭제
	GameObject* GetObjectStats(int index); //n번째 객체정보 리턴
	GameObject** GetObjectStats(); //모든 객체정보 리턴
	void Update(float elapsedTime); 
	void DeleteDeadObject(); //n번째 객체 삭제
	void DrawObjects();
	void CreateBullet(float elapsedTime);

private:
	bool Collision(GameObject a, GameObject b); //충돌
	GameObject* m_gameObject[MAX_OBJECTS_COUNT];
	Renderer *m_renderer;

	GLuint m_texCharacter;
};

