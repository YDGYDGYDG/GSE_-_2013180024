#pragma once

#define RED_TEAM 0
#define BLUE_TEAM 1
#define BUILDING_LIFE 1000
#define CHARACTER_ARCHER_LIFE 50
#define CHARACTER_KNIGHT_LIFE 150
#define BULLET_LIFE 1
#define ARROW_LIFE 1

//캐릭터 타입
#define CHARACTER_KNIGHT 0
#define CHARACTER_ARCHER 1
//캐릭터 태세
#define RUN_STATE 0
#define ATTACK_STATE 1

class GameObject
{
public:
	GameObject();
	~GameObject();
	void SettingPos(float x, float y, float z);
	void Update(float elapsedTime);
	void SettingType(int objectType, int whatButton);
	void SettingTeam(int objectTeam);
	//그림여부
	bool objectDrawFlag;
	//타입
	int type;
	int charClass;
	int team;
	//태세
	int state;
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
	//총 사거리
	float attackRange;
	//충돌박스
	typedef struct _boundingBox {
		float leftBottom[2];
		float rightTop[2];
	}boundingBox;
	boundingBox bb;
	//충돌체크
	bool collisionCheck;
	bool damageCheck;
	//충돌주인
	int master;
	//파티클
	double arrowParticleTime;
private:

};



