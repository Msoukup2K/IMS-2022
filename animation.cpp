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

/*
*    START
*    GLUT -- functions for animation
*/

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

/*
*    END
*    GLUT -- functions for animation
*/

Animation::Animation(int argc, char **argv, const char *title)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(
        glutGet(GLUT_SCREEN_WIDTH),
        glutGet(GLUT_SCREEN_HEIGHT)
    );
    glutCreateWindow(title);

    setDisplayFunc(renderScene);
    setReshapeFunc(changeSize);
    setIdleFunc(renderScene);
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

