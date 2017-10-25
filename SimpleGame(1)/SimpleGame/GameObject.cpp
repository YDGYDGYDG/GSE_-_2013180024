#include "stdafx.h"
#include "GameObject.h"


GameObject::GameObject()
{
	posX = 0;
	posY = 0;
	posZ = 0;
	speedX = 20;
	speedY = 20;
	speedZ = 20;
	size = 10;
	colorR = 100;
	colorG = 100;
	colorB = 100;
	colorA = 100;
	bb.leftBottom[0] = posX - (size / 2);
	bb.leftBottom[1] = posY - (size / 2);
	bb.rightTop[0] = posX + (size / 2);
	bb.rightTop[1] = posY + (size / 2);
	Life = true;
	lifeTime = 100;
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
	posX = posX + speedX * elapsedTimeInSecond;
	posY = posY + speedY * elapsedTimeInSecond;
	if (posX > 250) { speedX = -speedX; }
	if (posX < -250) { speedX = -speedX; }
	if (posY > 250) { speedY = -speedY; }
	if (posY < -250) { speedY = -speedY; }
	//posZ = posZ + speedZ * time;

	lifeTime--;
	if (lifeTime <= 0) {
		Life = false;
	}
}

