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
	lifeTime = 0;
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
		lifeTime = 0;
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
		lifeTime = 100;
		lifeCount = BUILDING_LIFE;
		attackPower = 0;
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
		lifeTime = 100;
		lifeCount = CHARACTER_LIFE;
		if (team == RED_TEAM) {
			charClass = rand() % 2;
		}
		attackPower = 10;
		if (charClass == CHARACTER_ARCHER) {
			size = 50;
			attackRange = 200;
			speed = 20; 
		}
		else if (charClass == CHARACTER_KNIGHT) {
			size = 50;
			attackRange = 40;
			speed = 50; 
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
		lifeTime = 100;
		lifeCount = BULLET_LIFE;
		attackPower = 10;

		break;
	case 4: //건물의 총알
		collisionCheck = false;
		damageCheck = false;
		speed = 100;
		dirX = rand() % 3 - 1;
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
		lifeTime = 100;
		lifeCount = ARROW_LIFE;
		attackPower = 10;
		arrowParticleTime = 0;
		break;
	}
}

