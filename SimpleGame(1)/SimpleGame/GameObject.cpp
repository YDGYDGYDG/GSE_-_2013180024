#include "stdafx.h"
#include "GameObject.h"


GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}

void GameObject::SettingPos(float x, float y, float z)
{
	pos_x = x;
	pos_y = y;
	pos_z = z;
}

float GameObject::GetPosx()
{
	return pos_x;
}
