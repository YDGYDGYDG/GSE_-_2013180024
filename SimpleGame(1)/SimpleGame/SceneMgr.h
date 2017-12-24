#pragma once

#include "GameObject.h"
#include "Renderer.h"
#include "Sound.h"
#include "Button.h"

//오브젝트 갯수
#define MAX_RED_BUILDINGS_COUNT 3
#define MAX_BLUE_BUILDINGS_COUNT 3
#define MAX_RED_CHARACTERS_COUNT 10
#define MAX_BLUE_CHARACTERS_COUNT 10
#define MAX_RED_BULLETS_COUNT 100
#define MAX_BLUE_BULLETS_COUNT 100
#define MAX_RED_ARROWS_COUNT 101  // -1
#define MAX_BLUE_ARROWS_COUNT 101  // -1
#define MAX_OBJECTS_COUNT (MAX_RED_BUILDINGS_COUNT + MAX_RED_CHARACTERS_COUNT + MAX_RED_BULLETS_COUNT + MAX_RED_ARROWS_COUNT + MAX_BLUE_BUILDINGS_COUNT + MAX_BLUE_CHARACTERS_COUNT+MAX_BLUE_BULLETS_COUNT+MAX_BLUE_ARROWS_COUNT)
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

	float enemyResenCool;
	float characterResenCool;

	//버튼
	Button *m_knightBT;
	Button *m_archerBT;
	//버튼상태
	int whatButton;

	void AddObject(int x, int y, int z, int type, int master, int team); //객체생성
	void DeleteObject(); //모든 객체 삭제
	void Update(float elapsedTime); 
	void DeleteDeadObject(); //n번째 객체 삭제
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

	bool Collision(GameObject a, GameObject b); //충돌
	GameObject* m_gameObject[MAX_OBJECTS_COUNT];
	Renderer *m_renderer;


	Sound *m_BGM;//배경음악
	int soundBG;
	Sound *m_Bang;//건물 터지는 소리
	int soundBang;
	Sound *m_Hit;//총알 맞는 소리
	int soundHit;
	Sound *m_CriHit;//캐릭터가 건물에 자폭하는 소리
	int soundCriHit;
	

	//텍스처
	GLuint m_texBG;
	GLuint m_texBGgrass;
	GLuint m_texBGland;
	GLuint m_texKnightBT;
	GLuint m_texArcherBT;
	GLuint m_texCharacter;
	float characterAnimationStack;
	GLuint m_texBlueTeamBuilding;
	GLuint m_texBlueTeamArcherRun;
	GLuint m_texBlueTeamArcherAttack;
	GLuint m_texBlueTeamArcherTip;
	GLuint m_texBlueTeamKnightRun;
	GLuint m_texBlueTeamKnightAttack;
	GLuint m_texBlueTeamKnightTip;
	GLuint m_texArrow;
	GLuint m_texRedTeamBuilding;
	GLuint m_texRedTeamArcherRun;
	GLuint m_texRedTeamArcherAttack;
	GLuint m_texRedTeamArcherTip;
	GLuint m_texRedTeamKnightRun;
	GLuint m_texRedTeamKnightAttack;
	GLuint m_texRedTeamKnightTip;
	GLuint m_texClimateParticle; //날씨
	double climateTime;

};

