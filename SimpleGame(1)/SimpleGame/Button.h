#pragma once

#define KNIGHT_PUSHED 0
#define ARCHER_PUSHED 1


class Button
{
public:
	Button();
	~Button();

	void SettingPos(float x, float y);
	void Update();

	//��ġ
	float posX;
	float posY;
	float size;
	//��
	float colorR;
	float colorG;
	float colorB;
	float colorA;
	//��Ÿ��
	float BTcool;

	typedef struct _boundingBox {
		float leftBottom[2];
		float rightTop[2];
	}boundingBox;
	boundingBox bb;

	bool pushed;
};

