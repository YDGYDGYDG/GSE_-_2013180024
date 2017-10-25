#include "stdafx.h"
#include "GameObject.h"


GameObject::GameObject()
{
	srand(time(NULL));
	posX = 0;
	posY = 0;
	posZ = 0;
	speedX = rand() % 15 + 5;
	speedY = rand() % 15 + 5;
	speedZ = rand() % 15 + 5;
	size = 15;
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
	//float time = 1;
	//posX = posX + speedX * time;
	//posY = posY + speedY * time;
	if (posX > 250.f) { speedX = -speedX; }
	if (posX < -250.f) { speedX = -speedX; }
	if (posY > 250.f) { speedY = -speedY; }
	if (posY < -250.f) { speedY = -speedY; }

	bb.leftBottom[0] = posX - (size / 2);
	bb.leftBottom[1] = posY - (size / 2);
	bb.rightTop[0] = posX + (size / 2);
	bb.rightTop[1] = posY + (size / 2);

	std::cout << posX << ", " <<posY << std::endl;

	lifeTime--;
	if (lifeTime <= 0) {
		Life = false;
	}
}

