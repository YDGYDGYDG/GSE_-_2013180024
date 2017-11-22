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
	//�׸�����
	bool objectDrawFlag;
	//Ÿ��
	int type;
	int team;
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
	//�浹�ڽ�
	typedef struct _boundingBox {
		float leftBottom[2];
		float rightTop[2];
	}boundingBox;
	boundingBox bb;
	//�浹üũ
	bool collisionCheck;
	//�浹����
	int master;

private:

};



