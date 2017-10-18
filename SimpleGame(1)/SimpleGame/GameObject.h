#pragma once

class GameObject
{
public:
	GameObject();
	~GameObject();
	void SettingPos(int x, int y, int z);
	void Update();

protected:

public:
	int posX;
	int posY;
	int posZ;

	float speedX;
	float speedY;
	float speedZ;

	float size;
	
	float colorR;
	float colorG;
	float colorB;
	float colorA;

};



