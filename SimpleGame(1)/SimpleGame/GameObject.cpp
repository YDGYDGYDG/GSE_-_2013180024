#include "stdafx.h"
#include "GameObject.h"


GameObject::GameObject()
{
	posX = 0;
	posY = 0;
	posZ = 0;
	speedX = 1;
	speedY = 1;
	speedZ = 1;
	size = 10;
	colorR = 100;
	colorG = 100;
	colorB = 100;
	colorA = 100;
}


GameObject::~GameObject()
{
}

void GameObject::SettingPos(int x, int y, int z)
{
	posX = x;
	posY = y;
	posZ = z;
}

void GameObject::Update() {
	float time = 1.0;
	posX = posX + speedX * time;
	posY = posY + speedY * time;
	if (posX > 250) { speedX = -speedX; }
	if (posX < -250) { speedX = -speedX; }
	if (posY > 250) { speedY = -speedY; }
	if (posY < -250) { speedY = -speedY; }
	//posZ = posZ + speedZ * time;
}
