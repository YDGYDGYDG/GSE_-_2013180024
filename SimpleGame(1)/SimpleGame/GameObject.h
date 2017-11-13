#pragma once

class GameObject
{
public:
	GameObject();
	~GameObject();
	void SettingPos(float x, float y, float z);
	void Update(float elapsedTime);
	void SettingType(int objectType);

	bool objectDrawFlag;

	int type;

	float posX;
	float posY;
	float posZ;

	float speed;

	float dirX;
	float dirY;

	float size;
	
	float colorR;
	float colorG;
	float colorB;
	float colorA;

	bool Life;
	float attackPower;
	float lifeTime;
	float lifeCount;

	float fireBulletCool;

	typedef struct _boundingBox {
		float leftBottom[2];
		float rightTop[2];
	}boundingBox;

	boundingBox bb;
	bool collisionCheck = false;

private:

};



