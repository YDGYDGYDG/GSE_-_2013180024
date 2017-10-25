#include "stdafx.h"
#include "GameObject.h"


GameObject::GameObject()
{
	srand(time(NULL));
	posX = 0;
	posY = 0;
	posZ = 0;
	speed = rand() % 15 + 15;
	dirX = 1;
	dirY = 1;	
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

	float elapsedTimeInSecond = elapsedTime / 10.f;
	std::cout << elapsedTimeInSecond << std::endl;
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


	lifeTime--;
	if (lifeTime <= 0) {
		Life = false;
	}
}

