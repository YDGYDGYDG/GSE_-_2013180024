#pragma once

#include <string>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Renderer.h"

class GameObject
{
public:
	GameObject();
	~GameObject();

private:
	float pos_x;
	float pos_y;
	float pos_z;

	float size;
	
	float r;
	float g;
	float b;
	float a;

	
};

