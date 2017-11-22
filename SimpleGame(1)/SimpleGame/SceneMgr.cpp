#include "stdafx.h"
#include "SceneMgr.h"



SceneMgr::SceneMgr()
{
	m_renderer = new Renderer(WINDOW_WIDTH, WINDOW_HEIGHT);
	m_texRedTeamBuilding = m_renderer->CreatePngTexture("../Resource/Bloodtrail.png");
	m_texBlueTeamBuilding = m_renderer->CreatePngTexture("../Resource/Bibblethump.png");
	m_texBlueTeamCharacter = m_renderer->CreatePngTexture("../Resource/Illuminati.png");
	m_texRedTeamCharacter = m_renderer->CreatePngTexture("../Resource/Butterfly.png");

	for (int i = 0; i < MAX_OBJECTS_COUNT; i++) {
		m_gameObject[i] = new GameObject();
	}
	buildingCounter = 0;
	characterCounter = 0;
	arrowCounter = 0;
	bulletCounter = 0;
	enemyResenCool = 0;
	characterResenCool = 0;
}


SceneMgr::~SceneMgr()
{
	DeleteObject();
}

void SceneMgr::DrawObjects()
{
	//�߾Ӽ�
	for (int i = 0; i < 10; i++) { 
		m_renderer->DrawSolidRect(i * 10, WINDOW_HEIGHT / 2, 0, 0, 1, 1, 1, 1.0, 0);
	}

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
					0
				);
				m_renderer->DrawSolidRectGauge(
					m_gameObject[i]->posX,
					m_gameObject[i]->posY + m_gameObject[i]->size / 2 + 5,
					m_gameObject[i]->posZ,
					m_gameObject[i]->size,
					10,
					1, 0, 0, 1,
					1,
					0
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
					0
				);
				m_renderer->DrawSolidRectGauge(
					m_gameObject[i]->posX,
					m_gameObject[i]->posY + m_gameObject[i]->size/2 + 5,
					m_gameObject[i]->posZ,
					m_gameObject[i]->size,
					10,
					0, 0, 1, 1,
					1,
					0
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
					0
				);
				m_renderer->DrawSolidRectGauge(
					m_gameObject[i]->posX,
					m_gameObject[i]->posY + m_gameObject[i]->size / 2 + 5,
					m_gameObject[i]->posZ,
					m_gameObject[i]->size,
					5,
					1, 0, 0, 1,
					1,
					0
				);
			}
			else if (m_gameObject[i]->type == OBJECT_CHARACTER && m_gameObject[i]->team == BLUE_TEAM) {
				m_renderer->DrawTexturedRect(
					m_gameObject[i]->posX,
					m_gameObject[i]->posY,
					m_gameObject[i]->posZ,
					m_gameObject[i]->size,
					m_gameObject[i]->colorR,
					m_gameObject[i]->colorG,
					m_gameObject[i]->colorB,
					m_gameObject[i]->colorA,
					m_texBlueTeamCharacter,
					0
				);
				m_renderer->DrawSolidRectGauge(
					m_gameObject[i]->posX,
					m_gameObject[i]->posY + m_gameObject[i]->size / 2 + 5,
					m_gameObject[i]->posZ,
					m_gameObject[i]->size,
					5,
					0, 0, 1, 1,
					1,
					0
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
					0
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
				if (buildingCounter < MAX_BUILDINGS_COUNT) {
					buildingCounter++;
					m_gameObject[i]->objectDrawFlag = true;
				}
				break;
			case OBJECT_CHARACTER:
				if (characterCounter < MAX_CHARACTERS_COUNT) {
					characterCounter++;
					m_gameObject[i]->objectDrawFlag = true;
				}
				break;
			case OBJECT_ARROW:
				if (arrowCounter < MAX_ARROWS_COUNT) {
					arrowCounter++;
					m_gameObject[i]->objectDrawFlag = true;
				}
				break;
			case OBJECT_BULLET:
				if (bulletCounter < MAX_BULLETS_COUNT) {
					bulletCounter++;
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

	//�浹 üũ // ���� �浹�� ��ü�Ǿ��� �� collisionCheck�� ���� false�� �Ǿ�� ��
	for (int i = 0; i < MAX_OBJECTS_COUNT; i++) {
		for (int j = 0; j < MAX_OBJECTS_COUNT; j++) {
			if(m_gameObject[i]->team != m_gameObject[j]->team){ //���� �ٸ� ���� ��쿡�� �浹
				//�ǹ� - ĳ���Ͱ� �浹 
				if ((m_gameObject[i]->type == OBJECT_BUILDING && m_gameObject[j]->type == OBJECT_CHARACTER) || (m_gameObject[i]->type == OBJECT_CHARACTER && m_gameObject[j]->type == OBJECT_BUILDING)) {
					if (Collision(*m_gameObject[i], *m_gameObject[j]) == true) {
						m_gameObject[i]->collisionCheck = true; //�浹���̿���~
						m_gameObject[j]->collisionCheck = true; //�����
						if (m_gameObject[i]->damageCheck == false || m_gameObject[j]->damageCheck == false) { // ����ģ �� �� �ϳ��� �浹 ���� �ƴϾ��ٸ�
							m_gameObject[i]->lifeCount -= m_gameObject[j]->attackPower; // ������ ���ݷ¸�ŭ ���� ����� ����
							m_gameObject[j]->lifeCount -= m_gameObject[i]->attackPower;
							m_gameObject[i]->damageCheck = true;
							m_gameObject[j]->damageCheck = true;
							std::cout << m_gameObject[i]->lifeCount << std::endl;
							std::cout << m_gameObject[j]->lifeCount << std::endl;
							std::cout << "���" << std::endl;
						}
					}
				}
				//ĳ���� - �ǹ��Ѿ˰� �浹
				else if ((m_gameObject[i]->type == OBJECT_CHARACTER && m_gameObject[j]->type == OBJECT_ARROW) || (m_gameObject[i]->type == OBJECT_ARROW && m_gameObject[j]->type == OBJECT_CHARACTER)) {
					if (Collision(*m_gameObject[i], *m_gameObject[j]) == true) {
						m_gameObject[i]->collisionCheck = true; //�浹���̿���~
						m_gameObject[j]->collisionCheck = true; //�����
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
				buildingCounter--;
				break;
			case OBJECT_CHARACTER:
				characterCounter--;
				break;
			case OBJECT_ARROW:
				arrowCounter--;
				break;
			case OBJECT_BULLET:
				bulletCounter--;
				break;
			default:
				break;
			}

		}
	}
}
