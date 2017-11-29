#include "stdafx.h"
#include "GameObject.h"


GameObject::GameObject()
{
	objectDrawFlag = false;
	collisionCheck = false;
	damageCheck = false;
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

	//lifeTime--;

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

void GameObject::SettingType(int objectType) {
	type = objectType;
	switch (objectType) {
	case 0:
		collisionCheck = false;
		damageCheck = false;
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
		break;
	case 1: //건물
		collisionCheck = false;
		damageCheck = false;
		speed = 0;
		dirX = 0;
		dirY = 0;
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
		lifeCount = 500;
		attackPower = 500;
		break;
	case 2: //캐릭터
		collisionCheck = false;
		damageCheck = false;
		speed = 300;
		dirX = rand() % 3 - 1;
		dirY = rand() % 3 - 1;
		if (dirX == 0 && dirY == 0) {
			dirX++; dirY++;
		}
		size = 30;
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
		lifeCount = 10;
		attackPower = 10;
		break;
	case 3: //캐릭터의 총알
		collisionCheck = false;
		damageCheck = false;
		speed = 600;
		dirX = rand() % 3 - 1;
		dirY = rand() % 3 - 1;
		if (dirX == 0 && dirY == 0) {
			dirX++; dirY++;
		}
		size = 4;
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
		lifeCount = 10;
		attackPower = 10;
		break;
	case 4: //건물의 총알
		collisionCheck = false;
		damageCheck = false;
		speed = 100;
		dirX = rand() % 3 - 1;
		dirY = rand() % 3 - 1;
		if (dirX == 0 && dirY == 0) {
			dirX++; dirY++;
		}
		size = 4;
		if (team == RED_TEAM) {
			colorR = 1;
			colorG = 0;
			colorB = 1;
		}
		else if (team == BLUE_TEAM) {
			colorR = 1;
			colorG = 1;
			colorB = 0;
		}
		colorA = 1;
		bb.leftBottom[0] = posX - (size / 2);
		bb.leftBottom[1] = posY - (size / 2);
		bb.rightTop[0] = posX + (size / 2);
		bb.rightTop[1] = posY + (size / 2);
		Life = true;
		lifeTime = 100;
		lifeCount = 10;
		attackPower = 10;
		break;
	}
}


