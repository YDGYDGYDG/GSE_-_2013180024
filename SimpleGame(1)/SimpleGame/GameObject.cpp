#include "stdafx.h"
#include "GameObject.h"


GameObject::GameObject()
{
	objectDrawFlag = false;
	collisionCheck = false;
	damageCheck = false;
	state = 2;
	speed = 0;
	dirX = 0;
	dirY = 0;
	size = 0;
	colorR = 0;
	colorG = 0;
	colorB = 0;
	colorA = 0;
	bb.leftBottom[0] = 0;
	bb.leftBottom[1] = 0;
	bb.rightTop[0] = 0;
	bb.rightTop[1] = 0;
	Life = false;
	lifeCount = 0;
	attackPower = 0;
	fireBulletCool = 0;
	master = -1;
	arrowParticleTime = 0;
	attackRange = 0;
}


GameObject::~GameObject()
{
}

void GameObject::SettingPos(float x, float y, float z)
{
	posX = x;
	posY = y;
	posZ = z;
}

void GameObject::Update(float elapsedTime) {

	float elapsedTimeInSecond = elapsedTime / 1000.f;

	posX = posX + (speed * dirX) * elapsedTimeInSecond;
	posY = posY + (speed * dirY) * elapsedTimeInSecond;

	bb.leftBottom[0] = posX - (size / 2);
	bb.leftBottom[1] = posY - (size / 2);
	bb.rightTop[0] = posX + (size / 2);
	bb.rightTop[1] = posY + (size / 2);

	//상태변화
	if (type == 2) {
		if (state == ATTACK_STATE) { speed = 0; }
		else if (state == RUN_STATE && charClass == CHARACTER_ARCHER) { speed = 20; }
		else if (state == RUN_STATE && charClass == CHARACTER_KNIGHT) { speed = 50; }
	}
	if (lifeTime <= 0) {
		Life = false;
	}
	if (lifeCount <= 0) {
		Life = false;
	}
}

void GameObject::SettingTeam(int objectTeam) { //SettingType보다 먼저 해야함
	team = objectTeam;
}

void GameObject::SettingType(int objectType, int whatButton) {
	type = objectType;
	charClass = whatButton;
	switch (objectType) {
	case 0:
		collisionCheck = false;
		damageCheck = false;
		state = 2;
		speed = 0;
		dirX = 0;
		dirY = 0;
		size = 0;
		colorR = 0;
		colorG = 0;
		colorB = 0;
		colorA = 0;
		bb.leftBottom[0] = 0;
		bb.leftBottom[1] = 0;
		bb.rightTop[0] =   0;
		bb.rightTop[1] =   0;
		Life = false;
		lifeCount = 0;
		attackPower = 0;
		fireBulletCool = 0;
		master = -1;
		arrowParticleTime = 0;
		attackRange = 0;
		break;
	case 1: //건물
		collisionCheck = false;
		damageCheck = false;
		state = 0;
		speed = 0;
		size = 100;
		colorR = 1;
		colorG = 1;
		colorB = 1;
		colorA = 1;
		bb.leftBottom[0] = posX - (size / 2);
		bb.leftBottom[1] = posY - (size / 2);
		bb.rightTop[0] = posX + (size / 2);
		bb.rightTop[1] = posY + (size / 2);
		Life = true;
		lifeCount = BUILDING_LIFE;
		attackPower = 1;
		attackRange = 0;
		break;
	case 2: //캐릭터
		collisionCheck = false;
		damageCheck = false;
		state = 0;
		dirX = 0;
		if (team == RED_TEAM) {
			dirY = -1;
		}
		if(team==BLUE_TEAM){
			dirY = 1;
		}
		colorR = 1;
		colorG = 1;
		colorB = 1;
		colorA = 1;
		bb.leftBottom[0] = posX - (size / 2);
		bb.leftBottom[1] = posY - (size / 2);
		bb.rightTop[0] = posX + (size / 2);
		bb.rightTop[1] = posY + (size / 2);
		Life = true;
		if (team == RED_TEAM) {
			charClass = rand() % 2;
		}
		attackPower = 10;
		if (charClass == CHARACTER_ARCHER) {
			lifeCount = CHARACTER_ARCHER_LIFE;
			size = 50;
			attackRange = 150;
			speed = 20; 
		}
		else if (charClass == CHARACTER_KNIGHT) {
			lifeCount = CHARACTER_KNIGHT_LIFE;
			size = 50;
			attackRange = 40;
			speed = 40; 
		}
		break;
	case 3: //캐릭터의 총알
		collisionCheck = false;
		damageCheck = false;
		speed = 600;
		dirX = 0;
		size = 10;
		if (team == RED_TEAM) {
			dirY = -1;
		}
		if (team == BLUE_TEAM) {
			dirY = 1;
		}
		if (team == RED_TEAM) {
			colorR = 1;
			colorG = 0;
			colorB = 0;
		}
		else if (team == BLUE_TEAM) {
			colorR = 0;
			colorG = 0;
			colorB = 1;
		}
		colorA = 1;
		bb.leftBottom[0] = posX - (size / 2);
		bb.leftBottom[1] = posY - (size / 2);
		bb.rightTop[0] = posX + (size / 2);
		bb.rightTop[1] = posY + (size / 2);
		Life = true;
		lifeCount = BULLET_LIFE;
		attackPower = 10;

		break;
	case 4: //건물의 총알
		collisionCheck = false;
		damageCheck = false;
		speed = 100;
		dirX = 0;
		if (team == RED_TEAM) {
			dirY = -1;
		}
		if (team == BLUE_TEAM) {
			dirY = 1;
		}
		size = 4;
		if (team == RED_TEAM) {
			colorR = 1;
			colorG = 0;
			colorB = 1;
		}
		else if (team == BLUE_TEAM) {
			colorR = 0;
			colorG = 1;
			colorB = 1;
		}
		colorA = 1;
		bb.leftBottom[0] = posX - (size / 2);
		bb.leftBottom[1] = posY - (size / 2);
		bb.rightTop[0] = posX + (size / 2);
		bb.rightTop[1] = posY + (size / 2);
		Life = true;
		lifeCount = ARROW_LIFE;
		attackPower = 10;
		arrowParticleTime = 0;
		break;
	}
}

