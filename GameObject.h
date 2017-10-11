#pragma once

class GameObject
{
public:
	GameObject();
	~GameObject();
	void SettingPos(float x, float y, float z);
	void Update();

protected:

public:
	float posX;
	float posY;
	float posZ;

	float speedX;
	float speedY;
	float speedZ;

	float size;
	
	float colorR;
	float colorG;
	float colorB;
	float colorA;

};



