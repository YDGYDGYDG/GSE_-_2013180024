#pragma once

#include "GameObject.h"
#include "Renderer.h"
#include "Sound.h"

//������Ʈ ����
#define MAX_RED_BUILDINGS_COUNT 3
#define MAX_BLUE_BUILDINGS_COUNT 3
#define MAX_RED_CHARACTERS_COUNT 10
#define MAX_BLUE_CHARACTERS_COUNT 10
#define MAX_RED_BULLETS_COUNT 100
#define MAX_BLUE_BULLETS_COUNT 100
#define MAX_RED_ARROWS_COUNT 101  // -1
#define MAX_BLUE_ARROWS_COUNT 101  // -1
#define MAX_OBJECTS_COUNT (MAX_RED_BUILDINGS_COUNT + MAX_RED_CHARACTERS_COUNT + MAX_RED_BULLETS_COUNT + MAX_RED_ARROWS_COUNT + MAX_BLUE_BUILDINGS_COUNT + MAX_BLUE_CHARACTERS_COUNT+MAX_BLUE_BULLETS_COUNT+MAX_BLUE_ARROWS_COUNT)
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
	int REDbuildingCounter;
	int BLUEbuildingCounter;
	int REDcharacterCounter;
	int BLUEcharacterCounter;
	int REDarrowCounter;
	int BLUEarrowCounter;
	int REDbulletCounter;
	int BLUEbulletCounter;

	bool Collision(GameObject a, GameObject b); //�浹
	GameObject* m_gameObject[MAX_OBJECTS_COUNT];
	Renderer *m_renderer;

	Sound *m_BGM;//�������
	int soundBG;
	Sound *m_Bang;//�ǹ� ������ �Ҹ�
	int soundBang;
	Sound *m_Hit;//�Ѿ� �´� �Ҹ�
	int soundHit;
	Sound *m_CriHit;//ĳ���Ͱ� �ǹ��� �����ϴ� �Ҹ�
	int soundCriHit;
	
	//�ؽ�ó
	GLuint m_texBG;
	GLuint m_texCharacter;
	int characterAnimationStack;
	GLuint m_texBlueTeamBuilding;
	GLuint m_texBlueTeamCharacter;
	GLuint m_texArrow;
	GLuint m_texRedTeamBuilding;
	GLuint m_texRedTeamCharacter;
	GLuint m_texClimateParticle; //����
	double climateTime;
};

