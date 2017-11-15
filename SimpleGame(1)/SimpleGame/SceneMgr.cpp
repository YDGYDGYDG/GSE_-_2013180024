#include "stdafx.h"
#include "SceneMgr.h"



SceneMgr::SceneMgr()
{
	m_renderer = new Renderer(WINDOW_WIDTH, WINDOW_HEIGHT);
	m_texRedTeamBuilding = m_renderer->CreatePngTexture("../Resource/Bloodtrail.png");
	m_texBlueTeamBuilding = m_renderer->CreatePngTexture("../Resource/Bibblethump.png");
	for (int i = 0; i < MAX_OBJECTS_COUNT; i++) {
		m_gameObject[i] = new GameObject();
	}
}


SceneMgr::~SceneMgr()
{
	DeleteObject();
}

void SceneMgr::DrawObjects()
{

	m_renderer->DrawSolidRect(0, 0, 0, 0, 0, 0, 0, 1.0);

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
					m_texRedTeamBuilding
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
					m_texBlueTeamBuilding
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
					m_gameObject[i]->colorA
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
	for (int i = 0; i < MAX_OBJECTS_COUNT; i++) {
		m_gameObject[i]->Update(elapsedTime);
		if (m_gameObject[i]->objectDrawFlag == false) {
			m_gameObject[i]->SettingType(0);
		}
	}


	for (int i = 0; i < MAX_OBJECTS_COUNT; i++) {
		for (int j = i+1; j < MAX_OBJECTS_COUNT-1; j++) {
			if(m_gameObject[i]->team != m_gameObject[j]->team){ //���� �ٸ� ���� ��쿡�� �浹
				//�ǹ� - ĳ���Ͱ� �浹
				if ((m_gameObject[i]->type == OBJECT_BUILDING && m_gameObject[j]->type == OBJECT_CHARACTER) || (m_gameObject[i]->type == OBJECT_CHARACTER && m_gameObject[j]->type == OBJECT_BUILDING)) {
					if (Collision(*m_gameObject[i], *m_gameObject[j]) == true) {
						if (m_gameObject[i]->collisionCheck == false || m_gameObject[j]->collisionCheck == false) { // ����ģ �� �� �ϳ��� �浹 ���� �ƴϾ��ٸ�
							m_gameObject[i]->lifeCount -= m_gameObject[j]->attackPower; // ������ ���ݷ¸�ŭ ���� ����� ����
							m_gameObject[j]->lifeCount -= m_gameObject[i]->attackPower;
						}
						m_gameObject[i]->collisionCheck = true; //�浹���̿���~
						m_gameObject[j]->collisionCheck = true; //�����
					}
				}
				//ĳ���� - �ǹ��Ѿ˰� �浹
				if ((m_gameObject[i]->type == OBJECT_CHARACTER && m_gameObject[j]->type == OBJECT_ARROW) || (m_gameObject[i]->type == OBJECT_ARROW && m_gameObject[j]->type == OBJECT_CHARACTER)) {
					if (Collision(*m_gameObject[i], *m_gameObject[j]) == true) {
						if (m_gameObject[i]->collisionCheck == false || m_gameObject[j]->collisionCheck == false) { // ����ģ �� �� �ϳ��� �浹 ���� �ƴϾ��ٸ�
							m_gameObject[i]->lifeCount -= m_gameObject[j]->attackPower; // ������ ���ݷ¸�ŭ ���� ����� ����
							m_gameObject[j]->lifeCount -= m_gameObject[i]->attackPower;
						}
						m_gameObject[i]->collisionCheck = true; //�浹���̿���~
						m_gameObject[j]->collisionCheck = true; //�����
					}
				}
				//�ǹ� - ĳ�����Ѿ˰� �浹
				if ((m_gameObject[i]->type == OBJECT_BUILDING && m_gameObject[j]->type == OBJECT_BULLET) || (m_gameObject[i]->type == OBJECT_BULLET && m_gameObject[j]->type == OBJECT_BUILDING)) {
					if (Collision(*m_gameObject[i], *m_gameObject[j]) == true) {
						if (m_gameObject[i]->collisionCheck == false || m_gameObject[j]->collisionCheck == false) { // ����ģ �� �� �ϳ��� �浹 ���� �ƴϾ��ٸ�
							m_gameObject[i]->lifeCount -= m_gameObject[j]->attackPower; // ������ ���ݷ¸�ŭ ���� ����� ����
							m_gameObject[j]->lifeCount -= m_gameObject[i]->attackPower;
						}
						m_gameObject[i]->collisionCheck = true; //�浹���̿���~
						m_gameObject[j]->collisionCheck = true; //�����
					}
				}
				//ĳ���� - ĳ�����Ѿ˰� �浹 (�ڱ� ���̸� ������ �� �´�)
				if ((m_gameObject[i]->type == OBJECT_CHARACTER && m_gameObject[j]->type == OBJECT_BULLET) || (m_gameObject[i]->type == OBJECT_BULLET && m_gameObject[j]->type == OBJECT_CHARACTER)) {
					if (Collision(*m_gameObject[i], *m_gameObject[j]) == true && i != m_gameObject[j]->master && j != m_gameObject[i]->master) { //�Ѿ��� ������ �ƴ� ��쿡�� �浹
						if (m_gameObject[i]->collisionCheck == false || m_gameObject[j]->collisionCheck == false) { // ����ģ �� �� �ϳ��� �浹 ���� �ƴϾ��ٸ�
							m_gameObject[i]->lifeCount -= m_gameObject[j]->attackPower; // ������ ���ݷ¸�ŭ ���� ����� ����
							m_gameObject[j]->lifeCount -= m_gameObject[i]->attackPower;
						}
						m_gameObject[i]->collisionCheck = true; //�浹���̿���~
						m_gameObject[j]->collisionCheck = true; //�����
					}
				}
			}
		}
	}

	DeleteDeadObject();

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
	if (enemyResenCool > 1.0) {
		AddObject(X, Y, 0, OBJECT_CHARACTER, -1, RED_TEAM);
		enemyResenCool = 0;
	}
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
