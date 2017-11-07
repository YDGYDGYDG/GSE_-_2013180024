#pragma once

class GameObject
{
public:
	GameObject();
	~GameObject();
	void SettingPos(float x, float y, float z);
	void Update(float elapsedTime);
	void SettingType(int objectType);
	int GetType();

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
	float lifePower;
	float lifeTime;
	float lifeCount;

	float fireBulletCool;

	typedef struct _boundingBox {
		float leftBottom[2];
		float rightTop[2];
	}boundingBox;

	boundingBox bb;
	bool collisionCounter = false;
	bool collisionCheck = false;

private:

};



