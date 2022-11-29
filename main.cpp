/******************************************
* FILE: main.cpp
*
* IMS 2022/23 -- 11. Model pomocí celulárního automatu
*
* author:   Vojtech Kucera (xkucer0h)
* date:     2022-11-16
*
*******************************************/

#include <iostream>
#include "animation.h"

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio =  w * 1.0 / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45,ratio,1,100);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

void renderScene(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBegin(GL_TRIANGLES);
		glVertex3f(-2,-2,-5.0);
		glVertex3f(2,0.0,-5.0);
		glVertex3f(0.0,2,-5.0);
	glEnd();

	glutSwapBuffers();
}

int main(int argc, char *argv[])
{
    Animation *animation = new Animation{argc, argv};

    animation->setDisplayFunc(renderScene);
    animation->setReshapeFunc(changeSize);
    animation->setIdleFunc(renderScene);

    animation->run();

	return EXIT_SUCCESS;
}

/******************************************
* END OF FILE: main.cpp
*******************************************/

