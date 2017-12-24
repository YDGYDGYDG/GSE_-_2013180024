#pragma once

#define RED_TEAM 0
#define BLUE_TEAM 1
#define BUILDING_LIFE 1000
#define CHARACTER_ARCHER_LIFE 50
#define CHARACTER_KNIGHT_LIFE 150
#define BULLET_LIFE 1
#define ARROW_LIFE 1

//ĳ���� Ÿ��
#define CHARACTER_KNIGHT 0
#define CHARACTER_ARCHER 1
//ĳ���� �¼�
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
	//�׸�����
	bool objectDrawFlag;
	//Ÿ��
	int type;
	int charClass;
	int team;
	//�¼�
	int state;
	//��ġ
	float posX;
	float posY;
	float posZ;
	//�ӵ�
	float speed;
	//����
	float dirX;
	float dirY;
	//ũ��
	float size;
	//��
	float colorR;
	float colorG;
	float colorB;
	float colorA;
	//�������
	bool Life;
	float attackPower;
	float lifeTime;
	float lifeCount;
	//�Ѿ��� �����ϴ� ��� ��Ÿ��
	float fireBulletCool;
	//�� ��Ÿ�
	float attackRange;
	//�浹�ڽ�
	typedef struct _boundingBox {
		float leftBottom[2];
		float rightTop[2];
	}boundingBox;
	boundingBox bb;
	//�浹üũ
	bool collisionCheck;
	bool damageCheck;
	//�浹����
	int master;
	//��ƼŬ
	double arrowParticleTime;
private:

};



