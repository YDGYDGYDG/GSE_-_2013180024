#include "stdafx.h"
#include "SceneMgr.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#define SOUND_BGM "..\\Resource\\Sounds\\Delirium.wav"
#define SOUND_BOSS_BGM "..\\Resource\\Sounds\\BOSS.wav"


SceneMgr::SceneMgr()
{
	PlaySound(TEXT(SOUND_BGM), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	m_renderer = new Renderer(WINDOW_WIDTH, WINDOW_HEIGHT);
	m_texBG = m_renderer->CreatePngTexture("../Resource/Images/land.png");
	m_texBGgrass = m_renderer->CreatePngTexture("../Resource/Images/grass.png");
	m_texBGland = m_renderer->CreatePngTexture("../Resource/Images/darkland.png");
	
	m_texBlueTeamBuilding = m_renderer->CreatePngTexture("../Resource/Images/Bibblethump.png");//
	m_texBlueTeamArcherRun = m_renderer->CreatePngTexture("../Resource/Images/BArunning.png");//
	m_texBlueTeamArcherAttack = m_renderer->CreatePngTexture("../Resource/Images/BAshooting.png");
	m_texBlueTeamArcherTip = m_renderer->CreatePngTexture("../Resource/Images/BAtipping.png");
	m_texBlueTeamKnightRun = m_renderer->CreatePngTexture("../Resource/Images/BKrunning.png");//
	m_texBlueTeamKnightAttack = m_renderer->CreatePngTexture("../Resource/Images/BKattack.png");
	m_texBlueTeamKnightTip = m_renderer->CreatePngTexture("../Resource/Images/BKtipping.png");

	m_texRedTeamBuilding = m_renderer->CreatePngTexture("../Resource/Images/Illuminati.png");//
	m_texRedTeamArcherRun = m_renderer->CreatePngTexture("../Resource/Images/RArunning.png");//
	m_texRedTeamArcherAttack = m_renderer->CreatePngTexture("../Resource/Images/RAshooting.png");
	m_texRedTeamArcherTip = m_renderer->CreatePngTexture("../Resource/Images/RAtipping.png");
	m_texRedTeamKnightRun = m_renderer->CreatePngTexture("../Resource/Images/RKrunning.png");//
	m_texRedTeamKnightAttack = m_renderer->CreatePngTexture("../Resource/Images/RKattack.png");
	m_texRedTeamKnightTip = m_renderer->CreatePngTexture("../Resource/Images/RKtipping.png");

	m_texArrow = m_renderer->CreatePngTexture("../Resource/Images/Voidball.png");

	m_texKnightBT = m_renderer->CreatePngTexture("../Resource/Images/Knight.png");
	m_texArcherBT = m_renderer->CreatePngTexture("../Resource/Images/Archer.png");

	REDbuildingCounter = 0;
	BLUEbuildingCounter = 0;
	REDcharacterCounter = 0;
	BLUEcharacterCounter = 0;
	REDarrowCounter = 0;
	BLUEarrowCounter= 0;
	REDbulletCounter= 0;
	BLUEbulletCounter = 0;
	enemyResenCool = 0;
	characterResenCool = 0;
	characterAnimationStack = 0;

	m_texClimateParticle = m_renderer->CreatePngTexture("../Resource/Images/Voidball.png");
	climateTime = 0;

	for (int i = 0; i < MAX_OBJECTS_COUNT; i++) {
		m_gameObject[i] = new GameObject();
	}
	m_knightBT = new Button();
	m_knightBT->pushed = true;
	m_archerBT = new Button();
	m_archerBT->pushed = false;
	whatButton = KNIGHT_PUSHED;

	m_Bang = new Sound();
	soundBang = m_Bang->CreateSound("../Resource/Sounds/Bang.wav");
	m_Hit = new Sound();
	soundHit = m_Hit->CreateSound("../Resource/Sounds/Damage.wav");
	m_BuildingHit = new Sound();
	soundBuildingHit = m_BuildingHit->CreateSound("../Resource/Sounds/Boxhit.wav");

}


SceneMgr::~SceneMgr()
{
	DeleteObject();
}

void SceneMgr::DrawObjects()
{

	//���
	m_renderer->DrawTexturedRect(0, 0, 0, WINDOW_HEIGHT, 1, 1, 1, 1, m_texBG, 0.9);
	for (int i = 0; i < 7; i++) {
		m_renderer->DrawTexturedRect(-WINDOW_WIDTH / 2, 150 * (i - 3), 0, 150, 1, 1, 1, 1, m_texBGgrass, 0.7);
		m_renderer->DrawTexturedRect(WINDOW_WIDTH / 2, 150 * (i - 3), 0, 150, 1, 1, 1, 1, m_texBGgrass, 0.7);
	}
	m_renderer->DrawTexturedRect(0, WINDOW_WIDTH / 2 + 170, 0, 400, 1, 1, 1, 1, m_texBGland, 0.8);
	m_renderer->DrawTexturedRect(0, -WINDOW_WIDTH / 2 - 150, 0, 400, 1, 1, 1, 1, m_texBGland, 0.8);

	//��ư
	m_knightBT->posX = WINDOW_WIDTH / 2 - m_knightBT->size * 2 / 3;
	m_knightBT->posY = m_knightBT->size;
	m_archerBT->posX = WINDOW_WIDTH / 2 - m_archerBT->size * 2 / 3;
	m_archerBT->posY = -m_archerBT->size;
	m_renderer->DrawTexturedRect(m_knightBT->posX, m_knightBT->posY, 0, m_knightBT->size, 1, 1, 1, m_knightBT->colorA, m_texKnightBT, 0.2);
	m_renderer->DrawTexturedRect(m_archerBT->posX, m_archerBT->posY, 0, m_archerBT->size, 1, 1, 1, m_archerBT->colorA, m_texArcherBT, 0.2);

	//�߾Ӽ�
	for (int i = 0; i < 50; i++) { 
		m_renderer->DrawSolidRect((i * 10)-WINDOW_WIDTH/2, 0, 0, 1, 1, 1, 1, 1.0, 0.1);
	}

	//����
	m_renderer->DrawParticleClimate(0, 0, 0, 1, 0.5, 1, 0.5, 1, -0.1, -0.1, m_texClimateParticle, climateTime, 0.01);

	//���ӿ�����Ʈ �׸��� (������Ʈ, ������Ʈü�°�����, ü�¼�ġ�ؽ�Ʈ)
	for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
	{
		if (m_gameObject[i] != NULL && m_gameObject[i]->objectDrawFlag == true)
		{
			// Renderer Test
			if (m_gameObject[i]->type == OBJECT_BUILDING && m_gameObject[i]->team == RED_TEAM) {
				m_renderer->DrawTexturedRect(
					m_gameObject[i]->posX,
					m_gameObject[i]->posY,
					m_gameObject[i]->posZ,
					m_gameObject[i]->size,
					m_gameObject[i]->colorR,
					m_gameObject[i]->colorG,
					m_gameObject[i]->colorB,
					m_gameObject[i]->colorA,
					m_texRedTeamBuilding, 
					0.5
				);
				m_renderer->DrawSolidRectGauge(
					m_gameObject[i]->posX,
					m_gameObject[i]->posY + m_gameObject[i]->size / 2 + 5,
					m_gameObject[i]->posZ,
					m_gameObject[i]->size,
					10,
					1, 0, 0, 1,
					m_gameObject[i]->lifeCount / BUILDING_LIFE,
					0.5
				);
			}
			else if (m_gameObject[i]->type == OBJECT_BUILDING && m_gameObject[i]->team == BLUE_TEAM) {
				m_renderer->DrawTexturedRect(
					m_gameObject[i]->posX,
					m_gameObject[i]->posY,
					m_gameObject[i]->posZ,
					m_gameObject[i]->size,
					m_gameObject[i]->colorR,
					m_gameObject[i]->colorG,
					m_gameObject[i]->colorB,
					m_gameObject[i]->colorA,
					m_texBlueTeamBuilding,
					0.5
				);
				m_renderer->DrawSolidRectGauge(
					m_gameObject[i]->posX,
					m_gameObject[i]->posY + m_gameObject[i]->size/2 + 5,
					m_gameObject[i]->posZ,
					m_gameObject[i]->size,
					10,
					0, 0, 1, 1,
					m_gameObject[i]->lifeCount / BUILDING_LIFE,
					0.5
				);
			}
			else if (m_gameObject[i]->type == OBJECT_CHARACTER && m_gameObject[i]->team == RED_TEAM) {
				if (m_gameObject[i]->charClass == CHARACTER_KNIGHT && m_gameObject[i]->state == RUN_STATE) {
					m_renderer->DrawTexturedRectSeq(
						m_gameObject[i]->posX,
						m_gameObject[i]->posY,
						m_gameObject[i]->posZ,
						m_gameObject[i]->size,
						m_gameObject[i]->colorR,
						m_gameObject[i]->colorG,
						m_gameObject[i]->colorB,
						m_gameObject[i]->colorA,
						m_texRedTeamKnightRun,
						(int)characterAnimationStack, 0, 8, 1,
						0.4
					);
					m_renderer->DrawSolidRectGauge(
						m_gameObject[i]->posX,
						m_gameObject[i]->posY + m_gameObject[i]->size / 2 + 5,
						m_gameObject[i]->posZ,
						m_gameObject[i]->size,
						5,
						1, 0, 0, 1,
						m_gameObject[i]->lifeCount / CHARACTER_KNIGHT_LIFE,
						0.4
					);
				}
				else if (m_gameObject[i]->charClass == CHARACTER_KNIGHT && m_gameObject[i]->state == ATTACK_STATE) {
					m_renderer->DrawTexturedRectSeq(
						m_gameObject[i]->posX,
						m_gameObject[i]->posY,
						m_gameObject[i]->posZ,
						m_gameObject[i]->size,
						m_gameObject[i]->colorR,
						m_gameObject[i]->colorG,
						m_gameObject[i]->colorB,
						m_gameObject[i]->colorA,
						m_texRedTeamKnightAttack,
						(int)characterAnimationStack, 0, 13, 1,
						0.4
					);
					m_renderer->DrawSolidRectGauge(
						m_gameObject[i]->posX,
						m_gameObject[i]->posY + m_gameObject[i]->size / 2 + 5,
						m_gameObject[i]->posZ,
						m_gameObject[i]->size,
						5,
						1, 0, 0, 1,
						m_gameObject[i]->lifeCount / CHARACTER_KNIGHT_LIFE,
						0.4
					);
				}
				else if (m_gameObject[i]->charClass == CHARACTER_ARCHER && m_gameObject[i]->state == RUN_STATE) {
					m_renderer->DrawTexturedRectSeq(
						m_gameObject[i]->posX,
						m_gameObject[i]->posY,
						m_gameObject[i]->posZ,
						m_gameObject[i]->size,
						m_gameObject[i]->colorR,
						m_gameObject[i]->colorG,
						m_gameObject[i]->colorB,
						m_gameObject[i]->colorA,
						m_texRedTeamArcherRun,
						(int)characterAnimationStack, 0, 8, 1,
						0.4
					);
					m_renderer->DrawSolidRectGauge(
						m_gameObject[i]->posX,
						m_gameObject[i]->posY + m_gameObject[i]->size / 2 + 5,
						m_gameObject[i]->posZ,
						m_gameObject[i]->size,
						5,
						1, 0, 0, 1,
						m_gameObject[i]->lifeCount / CHARACTER_ARCHER_LIFE,
						0.4
					);
				}
				else if (m_gameObject[i]->charClass == CHARACTER_ARCHER && m_gameObject[i]->state == ATTACK_STATE) {
					m_renderer->DrawTexturedRectSeq(
						m_gameObject[i]->posX,
						m_gameObject[i]->posY,
						m_gameObject[i]->posZ,
						m_gameObject[i]->size,
						m_gameObject[i]->colorR,
						m_gameObject[i]->colorG,
						m_gameObject[i]->colorB,
						m_gameObject[i]->colorA,
						m_texRedTeamArcherAttack,
						(int)characterAnimationStack, 0, 13, 1,
						0.4
					);
					m_renderer->DrawSolidRectGauge(
						m_gameObject[i]->posX,
						m_gameObject[i]->posY + m_gameObject[i]->size / 2 + 5,
						m_gameObject[i]->posZ,
						m_gameObject[i]->size,
						5,
						1, 0, 0, 1,
						m_gameObject[i]->lifeCount / CHARACTER_ARCHER_LIFE,
						0.4
					);
				}
			}
			else if (m_gameObject[i]->type == OBJECT_CHARACTER && m_gameObject[i]->team == BLUE_TEAM) {
				if (m_gameObject[i]->charClass == CHARACTER_KNIGHT && m_gameObject[i]->state == RUN_STATE) {
					m_renderer->DrawTexturedRectSeq(
						m_gameObject[i]->posX,
						m_gameObject[i]->posY,
						m_gameObject[i]->posZ,
						m_gameObject[i]->size,
						m_gameObject[i]->colorR,
						m_gameObject[i]->colorG,
						m_gameObject[i]->colorB,
						m_gameObject[i]->colorA,
						m_texBlueTeamKnightRun,
						(int)characterAnimationStack, 0, 8, 1,
						0.4
					);
					m_renderer->DrawSolidRectGauge(
						m_gameObject[i]->posX,
						m_gameObject[i]->posY + m_gameObject[i]->size / 2 + 5,
						m_gameObject[i]->posZ,
						m_gameObject[i]->size,
						5,
						0, 0, 1, 1,
						m_gameObject[i]->lifeCount / CHARACTER_KNIGHT_LIFE,
						0.4
					);
				}
				else if (m_gameObject[i]->charClass == CHARACTER_KNIGHT && m_gameObject[i]->state == ATTACK_STATE) {
					m_renderer->DrawTexturedRectSeq(
						m_gameObject[i]->posX,
						m_gameObject[i]->posY,
						m_gameObject[i]->posZ,
						m_gameObject[i]->size,
						m_gameObject[i]->colorR,
						m_gameObject[i]->colorG,
						m_gameObject[i]->colorB,
						m_gameObject[i]->colorA,
						m_texBlueTeamKnightAttack,
						(int)characterAnimationStack, 0, 13, 1,
						0.4
					);
					m_renderer->DrawSolidRectGauge(
						m_gameObject[i]->posX,
						m_gameObject[i]->posY + m_gameObject[i]->size / 2 + 5,
						m_gameObject[i]->posZ,
						m_gameObject[i]->size,
						5,
						0, 0, 1, 1,
						m_gameObject[i]->lifeCount / CHARACTER_KNIGHT_LIFE,
						0.4
					);
				}
				else if (m_gameObject[i]->charClass == CHARACTER_ARCHER && m_gameObject[i]->state == RUN_STATE) {
					m_renderer->DrawTexturedRectSeq(
						m_gameObject[i]->posX,
						m_gameObject[i]->posY,
						m_gameObject[i]->posZ,
						m_gameObject[i]->size,
						m_gameObject[i]->colorR,
						m_gameObject[i]->colorG,
						m_gameObject[i]->colorB,
						m_gameObject[i]->colorA,
						m_texBlueTeamArcherRun,
						(int)characterAnimationStack, 0, 8, 1,
						0.4
					);
					m_renderer->DrawSolidRectGauge(
						m_gameObject[i]->posX,
						m_gameObject[i]->posY + m_gameObject[i]->size / 2 + 5,
						m_gameObject[i]->posZ,
						m_gameObject[i]->size,
						5,
						0, 0, 1, 1,
						m_gameObject[i]->lifeCount / CHARACTER_ARCHER_LIFE,
						0.4
					);
				}
				else if (m_gameObject[i]->charClass == CHARACTER_ARCHER && m_gameObject[i]->state == ATTACK_STATE) {
					m_renderer->DrawTexturedRectSeq(
						m_gameObject[i]->posX,
						m_gameObject[i]->posY,
						m_gameObject[i]->posZ,
						m_gameObject[i]->size,
						m_gameObject[i]->colorR,
						m_gameObject[i]->colorG,
						m_gameObject[i]->colorB,
						m_gameObject[i]->colorA,
						m_texBlueTeamArcherAttack,
						(int)characterAnimationStack, 0, 13, 1,
						0.4
					);
					m_renderer->DrawSolidRectGauge(
						m_gameObject[i]->posX,
						m_gameObject[i]->posY + m_gameObject[i]->size / 2 + 5,
						m_gameObject[i]->posZ,
						m_gameObject[i]->size,
						5,
						0, 0, 1, 1,
						m_gameObject[i]->lifeCount / CHARACTER_ARCHER_LIFE,
						0.4
					);
				}
			}
			else if (m_gameObject[i]->type == OBJECT_ARROW && m_gameObject[i]->team == BLUE_TEAM) {
				m_renderer->DrawParticle(
					m_gameObject[i]->posX,
					m_gameObject[i]->posY,
					m_gameObject[i]->posZ,
					m_gameObject[i]->size,
					m_gameObject[i]->colorR,
					m_gameObject[i]->colorG,
					m_gameObject[i]->colorB,
					m_gameObject[i]->colorA,
					-m_gameObject[i]->dirX, -m_gameObject[i]->dirY,
					m_texArrow,
					m_gameObject[i]->arrowParticleTime,
					0.3
				);
			}
			else if (m_gameObject[i]->type == OBJECT_ARROW && m_gameObject[i]->team == RED_TEAM) {
				m_renderer->DrawParticle(
					m_gameObject[i]->posX,
					m_gameObject[i]->posY,
					m_gameObject[i]->posZ,
					m_gameObject[i]->size,
					m_gameObject[i]->colorR,
					m_gameObject[i]->colorG,
					m_gameObject[i]->colorB,
					m_gameObject[i]->colorA,
					-m_gameObject[i]->dirX, -m_gameObject[i]->dirY,
					m_texArrow,
					m_gameObject[i]->arrowParticleTime,
					0.3
				);
			}
			else {
				m_renderer->DrawSolidRect(
					m_gameObject[i]->posX,
					m_gameObject[i]->posY,
					m_gameObject[i]->posZ,
					m_gameObject[i]->size,
					m_gameObject[i]->colorR,
					m_gameObject[i]->colorG,
					m_gameObject[i]->colorB,
					m_gameObject[i]->colorA,
					0.1
				);
			}
		}
	}
}


void SceneMgr::AddObject(int x, int y, int z, int type, int master, int team)
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; i++) {
		if (m_gameObject[i]->objectDrawFlag == false) { //���� �Ⱥ��̰� �ִ� ������Ʈ ������ ã��
			m_gameObject[i]->SettingTeam(team);
			m_gameObject[i]->SettingType(type, whatButton);
			m_gameObject[i]->SettingPos(x, y, z);
			m_gameObject[i]->master = master;
			switch (m_gameObject[i]->type) //���� ����
			{
			case OBJECT_BUILDING:
				if (m_gameObject[i]->team == RED_TEAM && REDbuildingCounter < MAX_RED_BUILDINGS_COUNT) {
					REDbuildingCounter++;
					m_gameObject[i]->objectDrawFlag = true;
				}
				if (m_gameObject[i]->team == BLUE_TEAM && BLUEbuildingCounter < MAX_BLUE_BUILDINGS_COUNT) {
					BLUEbuildingCounter++;
					m_gameObject[i]->objectDrawFlag = true;
				}
				break;
			case OBJECT_CHARACTER:
				if (m_gameObject[i]->team == RED_TEAM && REDcharacterCounter < MAX_RED_CHARACTERS_COUNT) {
					REDcharacterCounter++;
					m_gameObject[i]->objectDrawFlag = true;
				}
				if (m_gameObject[i]->team == BLUE_TEAM && BLUEcharacterCounter < MAX_BLUE_CHARACTERS_COUNT) {
					BLUEcharacterCounter++;
					m_gameObject[i]->objectDrawFlag = true;
				}
				break;
			case OBJECT_ARROW:
				if (m_gameObject[i]->team == RED_TEAM && REDarrowCounter < MAX_RED_ARROWS_COUNT) {
					REDarrowCounter++;
					m_gameObject[i]->objectDrawFlag = true;
				}
				if (m_gameObject[i]->team == BLUE_TEAM && BLUEarrowCounter < MAX_BLUE_ARROWS_COUNT) {
					BLUEarrowCounter++;
					m_gameObject[i]->objectDrawFlag = true;
				}
				break;
			case OBJECT_BULLET:
				if (m_gameObject[i]->team == RED_TEAM && REDbulletCounter < MAX_RED_BULLETS_COUNT) {
					REDbulletCounter++;
					m_gameObject[i]->objectDrawFlag = true;
				}
				if (m_gameObject[i]->team == BLUE_TEAM && BLUEbulletCounter < MAX_BLUE_BULLETS_COUNT) {
					BLUEbulletCounter++;
					m_gameObject[i]->objectDrawFlag = true;
				}
				break;
			default:
				break;
			}
			break;
		}
	}
}

void SceneMgr::DeleteObject() 
{
	delete[] m_gameObject;
	delete[] m_renderer;
	delete[] m_Bang;
	m_Bang->DeleteSound(soundBang);
	delete[] m_Hit;
	m_Hit->DeleteSound(soundHit);
	delete[] m_BuildingHit;
	m_BuildingHit->DeleteSound(soundBuildingHit);
	delete[] m_knightBT;
	delete[] m_archerBT;
}

void SceneMgr::Update(float elapsedTime)
{
	
	//����
	climateTime += 0.01;
	if (climateTime > 1000) { climateTime = 0; }

	//��ư
	m_knightBT->Update();
	m_archerBT->Update();

	//ĳ���� �ִϸ��̼� ������ �����Ӵ� ������
	characterAnimationStack += 0.02;
	if (characterAnimationStack >= 9) { characterAnimationStack = 0; }

	//�ǹ��Ѿ� ��ƼŬ Ÿ��
	for (int i = 0; i < MAX_RED_ARROWS_COUNT + MAX_BLUE_ARROWS_COUNT; i++) {
		if (m_gameObject[i]->type == OBJECT_ARROW) {
			m_gameObject[i]->arrowParticleTime += 0.001;
			if (m_gameObject[i]->arrowParticleTime >= 1000) { m_gameObject[i]->arrowParticleTime = 0; }
		}
	}

	//�ð� �帧�� ���� ĳ����, �Ѿ� ����
	CreateEnemyCharacter(elapsedTime);
	CreateOurCharacter(elapsedTime);
	CreateBullet(elapsedTime);

	for (int i = 0; i < MAX_OBJECTS_COUNT; i++) { // �׸������ �ʱ�ȭ
		m_gameObject[i]->Update(elapsedTime);
		if (m_gameObject[i]->objectDrawFlag == false) {
			m_gameObject[i]->SettingType(0,2);
		}
		m_gameObject[i]->collisionCheck = false; //�浹 �ʱ�ȭ
	}

	for (int i = 0; i < MAX_OBJECTS_COUNT; i++) { // ȭ�� ���� ������Ʈ�� ü�� 0
		if (m_gameObject[i]->type == OBJECT_ARROW || m_gameObject[i]->type == OBJECT_BULLET || m_gameObject[i]->type == OBJECT_CHARACTER) {
			if (m_gameObject[i]->posX > WINDOW_WIDTH / 2 || m_gameObject[i]->posX < -WINDOW_WIDTH / 2 ||
				m_gameObject[i]->posY > WINDOW_HEIGHT / 2 || m_gameObject[i]->posY < -WINDOW_HEIGHT / 2) {
				m_gameObject[i]->lifeCount = 0;
			}
		}
	}

	DeleteDeadObject(); //������, ü�� �ٵ� �� ����

	//�浹 üũ // 
	for (int i = 0; i < MAX_OBJECTS_COUNT; i++) {
		for (int j = 0; j < MAX_OBJECTS_COUNT; j++) {
			if(m_gameObject[i]->team != m_gameObject[j]->team){ //���� �ٸ� ���� ��쿡�� �浹
				//ĳ���� - �ǹ��Ѿ˰� �浹
				if ((m_gameObject[i]->type == OBJECT_CHARACTER && m_gameObject[j]->type == OBJECT_ARROW) || (m_gameObject[i]->type == OBJECT_ARROW && m_gameObject[j]->type == OBJECT_CHARACTER)) {
					if (Collision(*m_gameObject[i], *m_gameObject[j]) == true) {
						m_gameObject[i]->collisionCheck = true; //�浹���̿���~
						m_gameObject[j]->collisionCheck = true; //�����
						if (m_gameObject[i]->damageCheck == false || m_gameObject[j]->damageCheck == false) { // ����ģ �� �� �ϳ��� �浹 ���� �ƴϾ��ٸ�
							m_Hit->PlaySound(soundHit, false, 1.0f);
							m_gameObject[i]->lifeCount -= m_gameObject[j]->attackPower; // ������ ���ݷ¸�ŭ ���� ����� ����
							m_gameObject[j]->lifeCount -= m_gameObject[i]->attackPower;
							m_gameObject[i]->damageCheck = true;
							m_gameObject[j]->damageCheck = true;
						}
					}
				}
				//�ǹ� - ĳ�����Ѿ˰� �浹
				else if ((m_gameObject[i]->type == OBJECT_BUILDING && m_gameObject[j]->type == OBJECT_BULLET) || (m_gameObject[i]->type == OBJECT_BULLET && m_gameObject[j]->type == OBJECT_BUILDING)) {
					if (Collision(*m_gameObject[i], *m_gameObject[j]) == true) {
						m_gameObject[i]->collisionCheck = true; //�浹���̿���~
						m_gameObject[j]->collisionCheck = true; //�����
						if (m_gameObject[i]->damageCheck == false || m_gameObject[j]->damageCheck == false) { // ����ģ �� �� �ϳ��� �浹 ���� �ƴϾ��ٸ�
							m_BuildingHit->PlaySound(soundBuildingHit, false, 1.0f);
							m_gameObject[i]->lifeCount -= m_gameObject[j]->attackPower; // ������ ���ݷ¸�ŭ ���� ����� ����
							m_gameObject[j]->lifeCount -= m_gameObject[i]->attackPower;
							m_gameObject[i]->damageCheck = true;
							m_gameObject[j]->damageCheck = true;
						}
					}
				}
				//ĳ���� - ĳ�����Ѿ˰� �浹 (�ڱ� ���̸� ������ �� �´�)
				else if ((m_gameObject[i]->type == OBJECT_CHARACTER && m_gameObject[j]->type == OBJECT_BULLET) || (m_gameObject[i]->type == OBJECT_BULLET && m_gameObject[j]->type == OBJECT_CHARACTER)) {
					if (Collision(*m_gameObject[i], *m_gameObject[j]) == true && i != m_gameObject[j]->master && j != m_gameObject[i]->master) { //�Ѿ��� ������ �ƴ� ��쿡�� �浹
						m_gameObject[i]->collisionCheck = true; //�浹���̿���~
						m_gameObject[j]->collisionCheck = true; //�����
						if (m_gameObject[i]->damageCheck == false || m_gameObject[j]->damageCheck == false) { // ����ģ �� �� �ϳ��� �浹 ���� �ƴϾ��ٸ�
							m_Hit->PlaySound(soundHit, false, 1.0f);
							m_gameObject[i]->lifeCount -= m_gameObject[j]->attackPower; // ������ ���ݷ¸�ŭ ���� ����� ����
							m_gameObject[j]->lifeCount -= m_gameObject[i]->attackPower;
							m_gameObject[i]->damageCheck = true;
							m_gameObject[j]->damageCheck = true;
						}
					}
				}
				//�ǹ� - �ǹ��Ѿ˰� �浹
				else if ((m_gameObject[i]->type == OBJECT_BUILDING && m_gameObject[j]->type == OBJECT_ARROW) || (m_gameObject[i]->type == OBJECT_ARROW && m_gameObject[j]->type == OBJECT_BUILDING)) {
					if (Collision(*m_gameObject[i], *m_gameObject[j]) == true) {
						m_gameObject[i]->collisionCheck = true; //�浹���̿���~
						m_gameObject[j]->collisionCheck = true; //�����
						if (m_gameObject[i]->damageCheck == false || m_gameObject[j]->damageCheck == false) { // ����ģ �� �� �ϳ��� �浹 ���� �ƴϾ��ٸ�
							m_BuildingHit->PlaySound(soundBuildingHit, false, 1.0f);
							m_gameObject[i]->lifeCount -= m_gameObject[j]->attackPower; // ������ ���ݷ¸�ŭ ���� ����� ����
							m_gameObject[j]->lifeCount -= m_gameObject[i]->attackPower;
							m_gameObject[i]->damageCheck = true;
							m_gameObject[j]->damageCheck = true;
						}
					}
				}
			}
		}
	}
	//��Ÿ�üũ ����
	for (int i = 0; i < MAX_OBJECTS_COUNT; i++) {
		m_gameObject[i]->state = RUN_STATE;
	}
	//��Ÿ� vs �Ÿ� üũ
	for (int i = 0; i < MAX_OBJECTS_COUNT; i++) {
		for (int j = 0; j < MAX_OBJECTS_COUNT; j++) {
			if (m_gameObject[i]->team != m_gameObject[j]->team) { //���� �ٸ� ���� ��쿡��
				//�ǹ� - ĳ���Ͱ� �Ÿ� üũ 
				if ((m_gameObject[i]->type == OBJECT_BUILDING && m_gameObject[j]->type == OBJECT_CHARACTER) || (m_gameObject[i]->type == OBJECT_CHARACTER && m_gameObject[j]->type == OBJECT_BUILDING)) {
					if (abs(m_gameObject[i]->posY - m_gameObject[j]->posY) < m_gameObject[i]->attackRange && //Y�Ÿ��� i�� ��Ÿ����� �۰ų�������
						abs(m_gameObject[i]->posX - m_gameObject[j]->posX) < m_gameObject[i]->size) { //X�Ÿ��� ĳ���� i�� ������� �۰ų�������
						m_gameObject[i]->state = ATTACK_STATE;	//i�� �����¼��� ��ȯ
					}
					if (abs(m_gameObject[i]->posY - m_gameObject[j]->posY) < m_gameObject[j]->attackRange && //Y�Ÿ��� j�� ��Ÿ����� �۰ų�������
						abs(m_gameObject[i]->posX - m_gameObject[j]->posX) < m_gameObject[j]->size) { //X�Ÿ��� ĳ���� j�� ������� �۰ų�������
						m_gameObject[j]->state = ATTACK_STATE;	//j�� �����¼��� ��ȯ
					}
				}
				//ĳ���� - ĳ���Ͱ� �Ÿ� üũ 
				if (m_gameObject[i]->type == OBJECT_CHARACTER &&  m_gameObject[j]->type == OBJECT_CHARACTER) {
					if (abs(m_gameObject[i]->posY - m_gameObject[j]->posY) < m_gameObject[i]->attackRange &&
						abs(m_gameObject[i]->posX - m_gameObject[j]->posX) < m_gameObject[i]->size/2) {
						m_gameObject[i]->state = ATTACK_STATE;	//i�� �����¼��� ��ȯ
					}
					if (abs(m_gameObject[i]->posY - m_gameObject[j]->posY) < m_gameObject[j]->attackRange &&
						abs(m_gameObject[i]->posX - m_gameObject[j]->posX) < m_gameObject[j]->size/2) {
						m_gameObject[j]->state = ATTACK_STATE;	//j�� �����¼��� ��ȯ
					}
				}
			}
		}
	}

	//�ƹ����� �浹������ ���� �ִ� ������üũ�� false�� �ȴ�
	for (int i = 0; i < MAX_OBJECTS_COUNT; i++) { 
		if(m_gameObject[i]->collisionCheck == false)
			m_gameObject[i]->damageCheck = false;
	}

}

bool SceneMgr::Collision(GameObject a, GameObject b) {
	if (a.bb.leftBottom[0] <= b.bb.rightTop[0] && a.bb.leftBottom[1] <= b.bb.rightTop[1]
		&& a.bb.rightTop[0]>b.bb.leftBottom[0] && a.bb.rightTop[1]>b.bb.leftBottom[1]) 
	{ return true; }
	else 
	{ return false; }
}

void SceneMgr::CreateBullet(float elapsedTime) {

	float coolTime = elapsedTime / 1000.f;

	//�Ѿ� ���� ��Ÿ�� �����ϱ�
	for (int i = 0; i < MAX_OBJECTS_COUNT; i++) {
		m_gameObject[i]->fireBulletCool += coolTime;
	}
	//�ǹ� �Ѿ� ����
	for (int i = 0; i < MAX_OBJECTS_COUNT; i++) {
		if (m_gameObject[i]->type == OBJECT_BUILDING) {
			if (m_gameObject[i]->fireBulletCool > 2.0f) {
				AddObject(m_gameObject[i]->posX, m_gameObject[i]->posY, m_gameObject[i]->posZ, OBJECT_ARROW, i, m_gameObject[i]->team);
				m_gameObject[i]->fireBulletCool = 0;
			}
		}
	}
	//ĳ���� �Ѿ� ����
	for (int i = 0; i < MAX_OBJECTS_COUNT; i++) {
		if (m_gameObject[i]->type == OBJECT_CHARACTER && m_gameObject[i]->state==ATTACK_STATE) {
			if (m_gameObject[i]->fireBulletCool > 1.3f) {
				AddObject(m_gameObject[i]->posX, m_gameObject[i]->posY, m_gameObject[i]->posZ, OBJECT_BULLET, i, m_gameObject[i]->team);
				m_gameObject[i]->fireBulletCool = 0;
			}
		}
	}

}

//�� ĳ���� ����
void SceneMgr::CreateEnemyCharacter(float elapsedTime) {
	float coolTime = elapsedTime / 1000.f;
	enemyResenCool += coolTime;
	int X, Y;
	X = rand() % (WINDOW_WIDTH-150) - ((WINDOW_WIDTH-150) / 2);
	Y = rand() % (WINDOW_HEIGHT / 2 - 200);
	if (enemyResenCool >= 2.0f) {
		AddObject(X, Y, 0, OBJECT_CHARACTER, -1, RED_TEAM);
		enemyResenCool = 0;
	}
}

//�츮 ĳ���� ������Ÿ��
void SceneMgr::CreateOurCharacter(float elapsedTime) {
	float coolTime = elapsedTime / 1000.f;
	characterResenCool += coolTime;
	m_knightBT->BTcool = characterResenCool;
	m_archerBT->BTcool = characterResenCool;
}

//������������ ����
void SceneMgr::DeleteDeadObject() {
	for (int i = 0; i < MAX_OBJECTS_COUNT; i++) {
		if (m_gameObject[i]->lifeCount <= 0) {
			m_gameObject[i]->objectDrawFlag = false;
			for (int j = 0; j < MAX_OBJECTS_COUNT; j++) {
				if (m_gameObject[j]->master == i) {
					//m_gameObject[j]->master = -1; //������ ������ �Ѿ��� ���ξ��� �Ѿ��� �ȴ� - ������ �޾Ƹ�
					m_gameObject[j]->objectDrawFlag = false; //������ ���� �� �Ѿ˵� ���� �״´�
					if (m_gameObject[j]->team == RED_TEAM) {
						REDbulletCounter--;
					}
					else if (m_gameObject[j]->team == BLUE_TEAM) {
						BLUEbulletCounter--;
					}
				}
			}
			switch (m_gameObject[i]->type)
			{
			case OBJECT_BUILDING:
				if (m_gameObject[i]->team == RED_TEAM) {
					m_Bang->PlaySound(soundBang, false, 1.0f);
					REDbuildingCounter--;
				}
				else if (m_gameObject[i]->team == BLUE_TEAM) {
					m_Bang->PlaySound(soundBang, false, 1.0f);
					BLUEbuildingCounter--;
					if (BLUEbuildingCounter < 2) {
						PlaySound(TEXT(SOUND_BOSS_BGM), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
					}
				}
				break;
			case OBJECT_CHARACTER:
				if (m_gameObject[i]->team == RED_TEAM) {
					REDcharacterCounter--;
				}
				else if (m_gameObject[i]->team == BLUE_TEAM) {
					BLUEcharacterCounter--;
				}
				break;
			case OBJECT_ARROW:
				if (m_gameObject[i]->team == RED_TEAM) {
					REDarrowCounter--;
				}
				else if (m_gameObject[i]->team == BLUE_TEAM) {
					BLUEarrowCounter--;
				}
				break;
			case OBJECT_BULLET:
				if (m_gameObject[i]->team == RED_TEAM) {
					REDbulletCounter--;
				}
				else if (m_gameObject[i]->team == BLUE_TEAM) {
					BLUEbulletCounter--;
				}
				break;
			default:
				break;
			}

		}
	}
}
