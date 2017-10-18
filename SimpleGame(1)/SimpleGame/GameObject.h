#pragma once

class GameObject
{
public:
	GameObject();
	~GameObject();
	void SettingPos(float x, float y, float z);
	void Update();
	void Collision();

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
	typedef struct _boundingSphere {
		float radious;

	}boundingBox;
	boundingBox bb;

};



