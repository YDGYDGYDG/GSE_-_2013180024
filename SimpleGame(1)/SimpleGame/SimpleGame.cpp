/*
Copyright 2017 Lee Taek Hee (Korea Polytech University)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"
#include <iostream>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

#include "Renderer.h"
#include "GameObject.h"
#include "SceneMgr.h"


SceneMgr *g_SceneMgr = NULL;
float g_prevTime = 0;

void RenderScene(void)
{
	DWORD currentTime = timeGetTime();
	DWORD elapsedTime = currentTime - g_prevTime;
	g_prevTime = currentTime;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.1f, 0.1f, 1.0f);

	g_SceneMgr->Update((float)elapsedTime);
	g_SceneMgr->DrawObjects();

	//glColor3f(1.f, 1.f, 1.f);
	//glBegin(GL_LINE);
	//glVertex3f(-WINDOW_WIDTH / 2, 0, 0);
	//glVertex3f(WINDOW_WIDTH / 2, 0, 0);
	//glEnd();

	glutSwapBuffers();
}

void Idle(void)
{
	DWORD currentTime = timeGetTime();
	DWORD elapsedTime = currentTime - g_prevTime;
	g_prevTime = currentTime;
	RenderScene();
	g_SceneMgr->Update(elapsedTime);
	
}

void MouseInput(int button, int state, int x, int y)
{
	//RenderScene();
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		std::cout << x << ", " << y << std::endl;
		g_SceneMgr->AddObject(x - (WINDOW_WIDTH / 2), (WINDOW_HEIGHT / 2) - y, 0, OBJECT_CHARACTER, -1, BLUE_TEAM);
	}
}

void KeyInput(unsigned char key, int x, int y)
{
	RenderScene();
}

void SpecialKeyInput(int key, int x, int y)
{
	RenderScene();
}

int main(int argc, char **argv)
{
	// Initialize GL things
	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Game Software Engineering KPU");

	glewInit();
	if (glewIsSupported("GL_VERSION_3_0"))
	{
		std::cout << " GLEW Version is 3.0\n ";
	}
	else
	{
		std::cout << "GLEW 3.0 not supported\n ";
	}

	// Initialize Renderer

	g_SceneMgr = new SceneMgr();
	g_SceneMgr->AddObject(0, 350, 0, OBJECT_BUILDING, -1, RED_TEAM);
	g_SceneMgr->AddObject(-120, 300, 0, OBJECT_BUILDING, -1, RED_TEAM);
	g_SceneMgr->AddObject(120, 300, 0, OBJECT_BUILDING, -1, RED_TEAM);
	g_SceneMgr->AddObject(0, -350, 0, OBJECT_BUILDING, -1, BLUE_TEAM);
	g_SceneMgr->AddObject(-120, -300, 0, OBJECT_BUILDING, -1, BLUE_TEAM);
	g_SceneMgr->AddObject(120, -300, 0, OBJECT_BUILDING, -1, BLUE_TEAM);

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	glutMainLoop();

	delete g_SceneMgr;


    return 0;
}

