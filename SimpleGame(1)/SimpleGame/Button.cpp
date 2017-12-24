#include "stdafx.h"
#include "Button.h"


Button::Button()
{
	//À§Ä¡
	 posX = 0;
	 posY = 0;
	 size = 50;
	
	 colorR = 1;
	 colorG = 1;
	 colorB = 1;
	 colorA = 1;

	 pushed = false;

	bb.leftBottom[0] = posX - (size / 2);
	bb.leftBottom[1] = posY - (size / 2);
	bb.rightTop[0] = posX + (size / 2);
	bb.rightTop[1] = posY + (size / 2);

}

Button::~Button()
{
}

void Button::SettingPos(float x, float y){
	posX = x;
	posY = y;
}

void Button::Update() {
	bb.leftBottom[0] = posX - (size / 2);
	bb.leftBottom[1] = posY - (size / 2);
	bb.rightTop[0] = posX + (size / 2);
	bb.rightTop[1] = posY + (size / 2);

	if (pushed == true) {
		colorA = BTcool;
	}
	else {
		colorA = 0.3;
	}
}