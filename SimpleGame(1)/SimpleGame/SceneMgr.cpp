#include "stdafx.h"
#include "SceneMgr.h"



SceneMgr::SceneMgr()
{
	m_renderer = new Renderer(WINDOW_WIDTH, WINDOW_HEIGHT);
	m_texBG = m_renderer->CreatePngTexture("../Resource/Images/IsaacStage.png");

	m_texBlueTeamBuilding = m_renderer->CreatePngTexture("../Resource/Images/Bibblethump.png");
	m_texBlueTeamCharacter = m_renderer->CreatePngTexture("../Resource/Images/SonicRun.png");
	m_texArrow = m_renderer->CreatePngTexture("../Resource/Images/Voidball.png");

	m_texRedTeamBuilding = m_renderer->CreatePngTexture("../Resource/Images/Bloodtrail.png");
	m_texRedTeamCharacter = m_renderer->CreatePngTexture("../Resource/Images/Butterfly.png");

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

	m_BGM = new Sound();
	soundBG = m_BGM->CreateSound("../Resource/Sounds/Delirium.mp3");
	m_BGM->PlaySound(soundBG, true, 1.0f);
	m_Bang = new Sound();
	soundBang = m_Bang->CreateSound("../Resource/Sounds/Bang.wav");
	m_Hit = new Sound();
	soundHit = m_Hit->CreateSound("../Resource/Sounds/Damage.wav");
	m_CriHit = new Sound();
	soundCriHit = m_CriHit->CreateSound("../Resource/Sounds/CriHit.wav");

}


SceneMgr::~SceneMgr()
{
	DeleteObject();
}

void SceneMgr::DrawObjects()
{

	//���
	m_renderer->DrawTexturedRect(0, 0, 0, WINDOW_HEIGHT, 1, 1, 1, 1, m_texBG, 0.9);

	//�߾Ӽ�
	for (int i = 0; i < 50; i++) { 
		m_renderer->DrawSolidRect((i * 10)-WINDOW_WIDTH/2, 0, 0, 1, 1, 1, 1, 1.0, 0.1);
	}

	//m_renderer->DrawText(0, 0, GLUT_BITMAP_TIMES_ROMAN_24, 1, 1, 1, "?");

	//����
	m_renderer->DrawParticleClimate(0, 0, 0, 1, 0.5, 1, 0.5, 1, -0.1, -0.1, m_texClimateParticle, climateTime, 0.01);

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
					0.1
				);
				m_renderer->DrawSolidRectGauge(
					m_gameObject[i]->posX,
					m_gameObject[i]->posY + m_gameObject[i]->size / 2 + 5,
					m_gameObject[i]->posZ,
					m_gameObject[i]->size,
					10,
					1, 0, 0, 1,
					m_gameObject[i]->lifeCount / BUILDING_LIFE,
					0.1
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
					0.1
				);
				m_renderer->DrawSolidRectGauge(
					m_gameObject[i]->posX,
					m_gameObject[i]->posY + m_gameObject[i]->size/2 + 5,
					m_gameObject[i]->posZ,
					m_gameObject[i]->size,
					10,
					0, 0, 1, 1,
					m_gameObject[i]->lifeCount / BUILDING_LIFE,
					0.1
				);
			}
			else if (m_gameObject[i]->type == OBJECT_CHARACTER && m_gameObject[i]->team == RED_TEAM) {
				m_renderer->DrawTexturedRect(
					m_gameObject[i]->posX,
					m_gameObject[i]->posY,
					m_gameObject[i]->posZ,
					m_gameObject[i]->size,
					m_gameObject[i]->colorR,
					m_gameObject[i]->colorG,
					m_gameObject[i]->colorB,
					m_gameObject[i]->colorA,
					m_texRedTeamCharacter,
					0.1
				);
				m_renderer->DrawSolidRectGauge(
					m_gameObject[i]->posX,
					m_gameObject[i]->posY + m_gameObject[i]->size / 2 + 5,
					m_gameObject[i]->posZ,
					m_gameObject[i]->size,
					5,
					1, 0, 0, 1,
					m_gameObject[i]->lifeCount/CHARACTER_LIFE,
					0.1
				);
			}
			else if (m_gameObject[i]->type == OBJECT_CHARACTER && m_gameObject[i]->team == BLUE_TEAM) {
				m_renderer->DrawTexturedRectSeq(
					m_gameObject[i]->posX,
					m_gameObject[i]->posY,
					m_gameObject[i]->posZ,
					m_gameObject[i]->size,
					m_gameObject[i]->colorR,
					m_gameObject[i]->colorG,
					m_gameObject[i]->colorB,
					m_gameObject[i]->colorA,
					m_texBlueTeamCharacter,
					characterAnimationStack,0,8,1,
					0.1
				);
				m_renderer->DrawSolidRectGauge(
					m_gameObject[i]->posX,
					m_gameObject[i]->posY + m_gameObject[i]->size / 2 + 5,
					m_gameObject[i]->posZ,
					m_gameObject[i]->size,
					5,
					0, 0, 1, 1,
					m_gameObject[i]->lifeCount / CHARACTER_LIFE,
					0.1
				);
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
					0.1
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
					0.1
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
			m_gameObject[i]->SettingType(type);
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
	delete[] m_BGM;
	m_BGM->DeleteSound(soundBG);
	delete[] m_Bang;
	m_Bang->DeleteSound(soundBang);
	delete[] m_Hit;
	m_Hit->DeleteSound(soundHit);
	delete[] m_CriHit;
	m_CriHit->DeleteSound(soundCriHit);

}

void SceneMgr::Update(float elapsedTime)
{
	std::cout << BLUEbuildingCounter << std::endl;
	climateTime += 0.01;
	if (climateTime > 1000) { climateTime = 0; }

	characterAnimationStack++;
	if (characterAnimationStack >= 9) { characterAnimationStack = 0; }
	characterAnimationStack = characterAnimationStack % 9;

	for (int i = 0; i < MAX_RED_ARROWS_COUNT + MAX_BLUE_ARROWS_COUNT; i++) {
		if (m_gameObject[i]->type == OBJECT_ARROW) {
			m_gameObject[i]->arrowParticleTime += 0.001;
			if (m_gameObject[i]->arrowParticleTime >= 1000) { m_gameObject[i]->arrowParticleTime = 0; }
		}
	}

	CreateBullet(elapsedTime);
	CreateEnemyCharacter(elapsedTime);
	CreateOurCharacter(elapsedTime);

	for (int i = 0; i < MAX_OBJECTS_COUNT; i++) { // �׸������ �ʱ�ȭ
		m_gameObject[i]->Update(elapsedTime);
		if (m_gameObject[i]->objectDrawFlag == false) {
			m_gameObject[i]->SettingType(0);
		}
		m_gameObject[i]->collisionCheck = false; //�浹 �ʱ�ȭ
	}

	for (int i = 0; i < MAX_OBJECTS_COUNT; i++) { // ȭ�� ���� �Ѿ��� ü�� 0
		if (m_gameObject[i]->type == OBJECT_ARROW || m_gameObject[i]->type == OBJECT_BULLET) {
			if (m_gameObject[i]->posX > WINDOW_WIDTH / 2 || m_gameObject[i]->posX < -WINDOW_WIDTH / 2 ||
				m_gameObject[i]->posY > WINDOW_HEIGHT / 2 || m_gameObject[i]->posY < -WINDOW_HEIGHT / 2) {
				m_gameObject[i]->lifeCount = 0;
			}
		}
	}

	for (int i = 0; i < MAX_OBJECTS_COUNT; i++) { // ĳ���ʹ� ȭ�� �ȳ���
		if (m_gameObject[i]->type == OBJECT_CHARACTER) {
			if (m_gameObject[i]->posX > WINDOW_WIDTH / 2) { m_gameObject[i]->dirX = -1; }
			if (m_gameObject[i]->posX < -WINDOW_WIDTH / 2) { m_gameObject[i]->dirX = 1; }
			if (m_gameObject[i]->posY > WINDOW_HEIGHT / 2) { m_gameObject[i]->dirY = -1; }
			if (m_gameObject[i]->posY < -WINDOW_HEIGHT / 2) { m_gameObject[i]->dirY = 1; }
		}
	}

	DeleteDeadObject(); //������, ü�� �ٵ� �� ����

	//�浹 üũ // 
	for (int i = 0; i < MAX_OBJECTS_COUNT; i++) {
		for (int j = 0; j < MAX_OBJECTS_COUNT; j++) {
			if(m_gameObject[i]->team != m_gameObject[j]->team){ //���� �ٸ� ���� ��쿡�� �浹
				//�ǹ� - ĳ���Ͱ� �浹 
				if ((m_gameObject[i]->type == OBJECT_BUILDING && m_gameObject[j]->type == OBJECT_CHARACTER) || (m_gameObject[i]->type == OBJECT_CHARACTER && m_gameObject[j]->type == OBJECT_BUILDING)) {
					if (Collision(*m_gameObject[i], *m_gameObject[j]) == true) {
						m_gameObject[i]->collisionCheck = true; //�浹���̿���~
						m_gameObject[j]->collisionCheck = true; //�����
						if (m_gameObject[i]->damageCheck == false || m_gameObject[j]->damageCheck == false) { // ����ģ �� �� �ϳ��� �浹 ���� �ƴϾ��ٸ�
							m_CriHit->PlaySound(soundCriHit, false, 1.0f);
							m_gameObject[i]->lifeCount -= m_gameObject[j]->attackPower; // ������ ���ݷ¸�ŭ ���� ����� ����
							m_gameObject[j]->lifeCount -= m_gameObject[i]->attackPower;
							m_gameObject[i]->damageCheck = true;
							m_gameObject[j]->damageCheck = true;
						}
					}
				}
				//ĳ���� - �ǹ��Ѿ˰� �浹
				else if ((m_gameObject[i]->type == OBJECT_CHARACTER && m_gameObject[j]->type == OBJECT_ARROW) || (m_gameObject[i]->type == OBJECT_ARROW && m_gameObject[j]->type == OBJECT_CHARACTER)) {
					if (Collision(*m_gameObject[i], *m_gameObject[j]) == true) {
						m_gameObject[i]->collisionCheck = true; //�浹���̿���~
						m_gameObject[j]->collisionCheck = true; //�����
						m_Hit->PlaySound(soundHit, false, 1.0f);
						if (m_gameObject[i]->damageCheck == false || m_gameObject[j]->damageCheck == false) { // ����ģ �� �� �ϳ��� �浹 ���� �ƴϾ��ٸ�
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
							m_Hit->PlaySound(soundHit, false, 1.0f);
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
							m_Hit->PlaySound(soundHit, false, 1.0f);
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

	for (int i = 0; i < MAX_OBJECTS_COUNT; i++) { //�ƹ����� �浹������ ���� �ִ� ������üũ�� false�� �ȴ�
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

	for (int i = 0; i < MAX_OBJECTS_COUNT; i++) {
		m_gameObject[i]->fireBulletCool += coolTime;
	}

	for (int i = 0; i < MAX_OBJECTS_COUNT; i++) {
		if (m_gameObject[i]->type == OBJECT_BUILDING) {
			if (m_gameObject[i]->fireBulletCool > 1.0) {
				AddObject(m_gameObject[i]->posX, m_gameObject[i]->posY, m_gameObject[i]->posZ, OBJECT_ARROW, i, m_gameObject[i]->team);
				m_gameObject[i]->fireBulletCool = 0;
			}
		}
	}
	for (int i = 0; i < MAX_OBJECTS_COUNT; i++) {
		if (m_gameObject[i]->type == OBJECT_CHARACTER) {
			if (m_gameObject[i]->fireBulletCool > 1.0) {
				AddObject(m_gameObject[i]->posX, m_gameObject[i]->posY, m_gameObject[i]->posZ, OBJECT_BULLET, i, m_gameObject[i]->team);
				m_gameObject[i]->fireBulletCool = 0;
			}
		}
	}

}

void SceneMgr::CreateEnemyCharacter(float elapsedTime) {
	float coolTime = elapsedTime / 1000.f;
	enemyResenCool += coolTime;
	int X, Y;
	X = rand() % WINDOW_WIDTH - (WINDOW_WIDTH / 2);
	Y = rand() % (WINDOW_HEIGHT / 2);
	if (enemyResenCool >= 1.0f) {
		AddObject(X, Y, 0, OBJECT_CHARACTER, -1, RED_TEAM);
		enemyResenCool = 0;
	}
}

void SceneMgr::CreateOurCharacter(float elapsedTime) {
	float coolTime = elapsedTime / 1000.f;
	characterResenCool += coolTime;
}

void SceneMgr::DeleteDeadObject() {

	for (int i = 0; i < MAX_OBJECTS_COUNT; i++) {
		if (m_gameObject[i]->lifeCount <= 0) {
			m_gameObject[i]->objectDrawFlag = false;
			for (int j = 0; j < MAX_OBJECTS_COUNT; j++) {
				if (m_gameObject[j]->master == i) {
					m_gameObject[j]->master = -1; //������ ������ �Ѿ��� ���ξ��� �Ѿ��� �ȴ� - ������ �޾Ƹ�
					//m_gameObject[j]->objectDrawFlag = false; //�̰ŷ� �ϸ� ������ ���� �� �Ѿ˵� ���� ����
					//bulletCounter--;
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
