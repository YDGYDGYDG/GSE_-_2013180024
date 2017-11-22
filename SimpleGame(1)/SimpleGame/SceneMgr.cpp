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
	//중앙선
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
		if (m_gameObject[i]->objectDrawFlag == false) { //지금 안보이고 있는 오브젝트 공간을 찾아
			m_gameObject[i]->SettingTeam(team);
			m_gameObject[i]->SettingType(type);
			m_gameObject[i]->SettingPos(x, y, z);
			m_gameObject[i]->master = master;
			switch (m_gameObject[i]->type) //갯수 조절
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
	for (int i = 0; i < MAX_OBJECTS_COUNT; i++) { // 그리기셋팅 초기화
		m_gameObject[i]->Update(elapsedTime);
		if (m_gameObject[i]->objectDrawFlag == false) {
			m_gameObject[i]->SettingType(0);
		}
		m_gameObject[i]->collisionCheck = false; //충돌 초기화
	}
	for (int i = 0; i < MAX_OBJECTS_COUNT; i++) { // 화면 나간 총알은 체력 0
		if (m_gameObject[i]->type == OBJECT_ARROW || m_gameObject[i]->type == OBJECT_BULLET) {
			if (m_gameObject[i]->posX > WINDOW_WIDTH / 2 || m_gameObject[i]->posX < -WINDOW_WIDTH / 2 ||
				m_gameObject[i]->posY > WINDOW_HEIGHT / 2 || m_gameObject[i]->posY < -WINDOW_HEIGHT / 2) {
				m_gameObject[i]->lifeCount = 0;
			}
		}
	}

	for (int i = 0; i < MAX_OBJECTS_COUNT; i++) { // 캐릭터는 화면 안나감
		if (m_gameObject[i]->type == OBJECT_CHARACTER) {
			if (m_gameObject[i]->posX > WINDOW_WIDTH / 2) { m_gameObject[i]->dirX = -1; }
			if (m_gameObject[i]->posX < -WINDOW_WIDTH / 2) { m_gameObject[i]->dirX = 1; }
			if (m_gameObject[i]->posY > WINDOW_HEIGHT / 2) { m_gameObject[i]->dirY = -1; }
			if (m_gameObject[i]->posY < -WINDOW_HEIGHT / 2) { m_gameObject[i]->dirY = 1; }
		}
	}

	DeleteDeadObject(); //나간애, 체력 다된 애 삭제

	//충돌 체크 // 현재 충돌이 해체되었을 때 collisionCheck가 도로 false가 되어야 함
	for (int i = 0; i < MAX_OBJECTS_COUNT; i++) {
		for (int j = 0; j < MAX_OBJECTS_COUNT; j++) {
			if(m_gameObject[i]->team != m_gameObject[j]->team){ //서로 다른 팀인 경우에만 충돌
				//건물 - 캐릭터간 충돌 
				if ((m_gameObject[i]->type == OBJECT_BUILDING && m_gameObject[j]->type == OBJECT_CHARACTER) || (m_gameObject[i]->type == OBJECT_CHARACTER && m_gameObject[j]->type == OBJECT_BUILDING)) {
					if (Collision(*m_gameObject[i], *m_gameObject[j]) == true) {
						m_gameObject[i]->collisionCheck = true; //충돌중이에요~
						m_gameObject[j]->collisionCheck = true; //얘랑요
						if (m_gameObject[i]->damageCheck == false || m_gameObject[j]->damageCheck == false) { // 마주친 둘 중 하나라도 충돌 중이 아니었다면
							m_gameObject[i]->lifeCount -= m_gameObject[j]->attackPower; // 서로의 공격력만큼 각각 생명력 감소
							m_gameObject[j]->lifeCount -= m_gameObject[i]->attackPower;
							m_gameObject[i]->damageCheck = true;
							m_gameObject[j]->damageCheck = true;
							std::cout << m_gameObject[i]->lifeCount << std::endl;
							std::cout << m_gameObject[j]->lifeCount << std::endl;
							std::cout << "띠기" << std::endl;
						}
					}
				}
				//캐릭터 - 건물총알간 충돌
				else if ((m_gameObject[i]->type == OBJECT_CHARACTER && m_gameObject[j]->type == OBJECT_ARROW) || (m_gameObject[i]->type == OBJECT_ARROW && m_gameObject[j]->type == OBJECT_CHARACTER)) {
					if (Collision(*m_gameObject[i], *m_gameObject[j]) == true) {
						m_gameObject[i]->collisionCheck = true; //충돌중이에요~
						m_gameObject[j]->collisionCheck = true; //얘랑요
						if (m_gameObject[i]->damageCheck == false || m_gameObject[j]->damageCheck == false) { // 마주친 둘 중 하나라도 충돌 중이 아니었다면
							m_gameObject[i]->lifeCount -= m_gameObject[j]->attackPower; // 서로의 공격력만큼 각각 생명력 감소
							m_gameObject[j]->lifeCount -= m_gameObject[i]->attackPower;
							m_gameObject[i]->damageCheck = true;
							m_gameObject[j]->damageCheck = true;
						}
					}
				}
				//건물 - 캐릭터총알간 충돌
				else if ((m_gameObject[i]->type == OBJECT_BUILDING && m_gameObject[j]->type == OBJECT_BULLET) || (m_gameObject[i]->type == OBJECT_BULLET && m_gameObject[j]->type == OBJECT_BUILDING)) {
					if (Collision(*m_gameObject[i], *m_gameObject[j]) == true) {
						m_gameObject[i]->collisionCheck = true; //충돌중이에요~
						m_gameObject[j]->collisionCheck = true; //얘랑요
						if (m_gameObject[i]->damageCheck == false || m_gameObject[j]->damageCheck == false) { // 마주친 둘 중 하나라도 충돌 중이 아니었다면
							m_gameObject[i]->lifeCount -= m_gameObject[j]->attackPower; // 서로의 공격력만큼 각각 생명력 감소
							m_gameObject[j]->lifeCount -= m_gameObject[i]->attackPower;
							m_gameObject[i]->damageCheck = true;
							m_gameObject[j]->damageCheck = true;
						}
					}
				}
				//캐릭터 - 캐릭터총알간 충돌 (자기 것이면 맞으면 안 됀다)
				else if ((m_gameObject[i]->type == OBJECT_CHARACTER && m_gameObject[j]->type == OBJECT_BULLET) || (m_gameObject[i]->type == OBJECT_BULLET && m_gameObject[j]->type == OBJECT_CHARACTER)) {
					if (Collision(*m_gameObject[i], *m_gameObject[j]) == true && i != m_gameObject[j]->master && j != m_gameObject[i]->master) { //총알의 주인이 아닌 경우에만 충돌
						m_gameObject[i]->collisionCheck = true; //충돌중이에요~
						m_gameObject[j]->collisionCheck = true; //얘랑요
						if (m_gameObject[i]->damageCheck == false || m_gameObject[j]->damageCheck == false) { // 마주친 둘 중 하나라도 충돌 중이 아니었다면
							m_gameObject[i]->lifeCount -= m_gameObject[j]->attackPower; // 서로의 공격력만큼 각각 생명력 감소
							m_gameObject[j]->lifeCount -= m_gameObject[i]->attackPower;
							m_gameObject[i]->damageCheck = true;
							m_gameObject[j]->damageCheck = true;
						}
					}
				}
				//건물 - 건물총알간 충돌
				else if ((m_gameObject[i]->type == OBJECT_BUILDING && m_gameObject[j]->type == OBJECT_ARROW) || (m_gameObject[i]->type == OBJECT_ARROW && m_gameObject[j]->type == OBJECT_BUILDING)) {
					if (Collision(*m_gameObject[i], *m_gameObject[j]) == true) {
						m_gameObject[i]->collisionCheck = true; //충돌중이에요~
						m_gameObject[j]->collisionCheck = true; //얘랑요
						if (m_gameObject[i]->damageCheck == false || m_gameObject[j]->damageCheck == false) { // 마주친 둘 중 하나라도 충돌 중이 아니었다면
							m_gameObject[i]->lifeCount -= m_gameObject[j]->attackPower; // 서로의 공격력만큼 각각 생명력 감소
							m_gameObject[j]->lifeCount -= m_gameObject[i]->attackPower;
							m_gameObject[i]->damageCheck = true;
							m_gameObject[j]->damageCheck = true;
						}
					}
				}
			}
		}
	}

	for (int i = 0; i < MAX_OBJECTS_COUNT; i++) { //아무랑도 충돌중이지 않은 애는 데미지체크가 false가 된다
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
					m_gameObject[j]->master = -1; //주인이 죽으면 총알은 주인없는 총알이 된다 - 죽음의 메아리
					//m_gameObject[j]->objectDrawFlag = false; //이거로 하면 주인이 죽을 때 총알도 같이 죽음
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
