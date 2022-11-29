/******************************************
* FILE: animation.cpp
*
* IMS 2022/23 -- 11. Model pomocí celulárního automatu
*
* author:   Vojtech Kucera (xkucer0h)
* date:     2022-11-29
*
*******************************************/

#include "animation.h"

Animation::Animation(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(320,320);
	glutCreateWindow("Lighthouse3D- GLUT Tutorial");
}

void Animation::setDisplayFunc(void (*f)(void))
{
	glutDisplayFunc(f);
}

void Animation::setReshapeFunc(void (*f)(int, int))
{
    glutReshapeFunc(f);
}

void Animation::setIdleFunc(void (*f)(void))
{
    glutIdleFunc(f);
}

void Animation::run()
{
    glutMainLoop();
}

/******************************************
* END OF FILE: animation.cpp
*******************************************/

