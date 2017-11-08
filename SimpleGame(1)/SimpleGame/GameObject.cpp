#include "stdafx.h"
#include "GameObject.h"


GameObject::GameObject()
{
	objectDrawFlag = false;
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
	collisionCounter = false;
	Life = false;
	lifeTime = 0;
	lifeCount = 0;
	attackPower = 0;
	fireBulletCool = 0;
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

	if (posX > 250.f) { dirX = -1; }
	if (posX < -250.f) { dirX = 1; }
	if (posY > 250.f) { dirY = -1; }
	if (posY < -250.f) { dirY = 1; }

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

void GameObject::SettingType(int objectType) {
	type = objectType;
	switch (objectType) {
	case 1: //건물
		speed = 0;
		dirX = 0;
		dirY = 0;
		size = 50;
		colorR = 1;
		colorG = 1;
		colorB = 0;
		colorA = 1;
		bb.leftBottom[0] = posX - (size / 2);
		bb.leftBottom[1] = posY - (size / 2);
		bb.rightTop[0] = posX + (size / 2);
		bb.rightTop[1] = posY + (size / 2);
		collisionCounter = false;
		Life = true;
		lifeTime = 100;
		lifeCount = 500;
		attackPower = 500;
		break;
	case 2: //캐릭터
		speed = 100;
		dirX = rand() % 3 - 1;
		dirY = rand() % 3 - 1;
		if (dirX == 0 && dirY == 0) {
			dirX++; dirY++;
		}
		size = 10;
		colorR = 1;
		colorG = 1;
		colorB = 1;
		colorA = 0.5;
		bb.leftBottom[0] = posX - (size / 2);
		bb.leftBottom[1] = posY - (size / 2);
		bb.rightTop[0] = posX + (size / 2);
		bb.rightTop[1] = posY + (size / 2);
		collisionCounter = false;
		Life = true;
		lifeTime = 100;
		lifeCount = 10;
		attackPower = 10;
		break;
	case 3: //캐릭터의 총알
		speed = 300;
		dirX = rand() % 3 - 1;
		dirY = rand() % 3 - 1;
		if (dirX == 0 && dirY == 0) {
			dirX++; dirY++;
		}
		size = 2;
		colorR = 1;
		colorG = 0;
		colorB = 0;
		colorA = 1;
		bb.leftBottom[0] = posX - (size / 2);
		bb.leftBottom[1] = posY - (size / 2);
		bb.rightTop[0] = posX + (size / 2);
		bb.rightTop[1] = posY + (size / 2);
		collisionCounter = false;
		Life = true;
		lifeTime = 100;
		lifeCount = 10;
		attackPower = 10;
		break;
	case 4: //건물의 총알
		speed = 100;
		dirX = rand() % 3 - 1;
		dirY = rand() % 3 - 1;
		if (dirX == 0 && dirY == 0) {
			dirX++; dirY++;
		}
		size = 2;
		colorR = 0;
		colorG = 1;
		colorB = 0;
		colorA = 1;
		bb.leftBottom[0] = posX - (size / 2);
		bb.leftBottom[1] = posY - (size / 2);
		bb.rightTop[0] = posX + (size / 2);
		bb.rightTop[1] = posY + (size / 2);
		collisionCounter = false;
		Life = true;
		lifeTime = 100;
		lifeCount = 10;
		attackPower = 10;
		break;
	}
}


int GameObject::GetType() {
	return type;
}

