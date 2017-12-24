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

	//위치
	float posX;
	float posY;
	float size;
	//색
	float colorR;
	float colorG;
	float colorB;
	float colorA;
	//쿨타임
	float BTcool;

	typedef struct _boundingBox {
		float leftBottom[2];
		float rightTop[2];
	}boundingBox;
	boundingBox bb;

	bool pushed;
};

