#pragma once

#include "GameObject.h"
#include "Renderer.h"
#include "Sound.h"

//������Ʈ ����
#define MAX_BUILDINGS_COUNT 6
#define MAX_CHARACTERS_COUNT 10
#define MAX_BULLETS_COUNT 200
#define MAX_ARROWS_COUNT 201  // -1
#define MAX_OBJECTS_COUNT (MAX_BUILDINGS_COUNT + MAX_CHARACTERS_COUNT + MAX_BULLETS_COUNT + MAX_ARROWS_COUNT)
//������Ʈ Ÿ��
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

	void AddObject(int x, int y, int z, int type, int master, int team); //��ü����
	void DeleteObject(); //��� ��ü ����
	void Update(float elapsedTime); 
	void DeleteDeadObject(); //n��° ��ü ����
	void DrawObjects();
	void CreateBullet(float elapsedTime);
	void CreateEnemyCharacter(float elapsedTime);
	void CreateOurCharacter(float elapsedTime);

private:
	bool Collision(GameObject a, GameObject b); //�浹
	GameObject* m_gameObject[MAX_OBJECTS_COUNT];
	Renderer *m_renderer;
	Sound *m_sound;
	int soundBG;

	GLuint m_texBG;
	GLuint m_texCharacter;
	int characterAnimationStack;
	GLuint m_texRedTeamBuilding;
	GLuint m_texBlueTeamBuilding;
	int BuildingAnimationStack;
	GLuint m_texBlueTeamCharacter;
	GLuint m_texBlueTeamArrow;
	float BlueTeamArrowParticleTime;
	GLuint m_texRedTeamCharacter;
	GLuint m_texRedTeamBullet;
};

