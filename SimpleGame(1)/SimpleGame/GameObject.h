#pragma once

class GameObject
{
public:
	GameObject();
	~GameObject();

protected:
//public:
	float pos_x;
	float pos_y;
	float pos_z;

	float size;
	
	float r;
	float g;
	float b;
	float a;

public:
	void SettingPos(float x, float y, float z);
	float GetPosx();
};



