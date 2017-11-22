#pragma once

#define RED_TEAM 0
#define BLUE_TEAM 1

class GameObject
{
public:
	GameObject();
	~GameObject();
	void SettingPos(float x, float y, float z);
	void Update(float elapsedTime);
	void SettingType(int objectType);
	void SettingTeam(int objectTeam);
	//그림여부
	bool objectDrawFlag;
	//타입
	int type;
	int team;
	//위치
	float posX;
	float posY;
	float posZ;
	//속도
	float speed;
	//방향
	float dirX;
	float dirY;
	//크기
	float size;
	//색
	float colorR;
	float colorG;
	float colorB;
	float colorA;
	//생명관련
	bool Life;
	float attackPower;
	float lifeTime;
	float lifeCount;
	//총알을 생성하는 경우 쿨타임
	float fireBulletCool;
	//충돌박스
	typedef struct _boundingBox {
		float leftBottom[2];
		float rightTop[2];
	}boundingBox;
	boundingBox bb;
	//충돌체크
	bool collisionCheck;
	//충돌주인
	int master;

private:

};



