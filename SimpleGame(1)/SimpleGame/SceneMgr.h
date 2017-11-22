#pragma once

#include "GameObject.h"
#include "Renderer.h"

#define MAX_BUILDINGS_COUNT 6
#define MAX_CHARACTERS_COUNT 10
#define MAX_BULLETS_COUNT 200
#define MAX_ARROWS_COUNT 201  // -1
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

	int buildingCounter;
	int characterCounter;
	int arrowCounter;
	int bulletCounter;
	float enemyResenCool;
	float characterResenCool;

	void AddObject(int x, int y, int z, int type, int master, int team); //객체생성
	void DeleteObject(); //모든 객체 삭제
	GameObject* GetObjectStats(int index); //n번째 객체정보 리턴
	GameObject** GetObjectStats(); //모든 객체정보 리턴
	void Update(float elapsedTime); 
	void DeleteDeadObject(); //n번째 객체 삭제
	void DrawObjects();
	void CreateBullet(float elapsedTime);
	void CreateEnemyCharacter(float elapsedTime);
	void CreateOurCharacter(float elapsedTime);

private:
	bool Collision(GameObject a, GameObject b); //충돌
	GameObject* m_gameObject[MAX_OBJECTS_COUNT];
	Renderer *m_renderer;

	GLuint m_texCharacter;
	GLuint m_texRedTeamBuilding;
	GLuint m_texBlueTeamBuilding;
	GLuint m_texBlueTeamCharacter;
	GLuint m_texRedTeamCharacter;
};

