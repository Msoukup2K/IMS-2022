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


CA *ANIMATION_MODEL = nullptr;
int ANIMATION_FREQUENCY = 1000;


/*
*   START
*   drawing functions
*/

void square(GLfloat x, GLfloat y, GLfloat size, GLfloat gray)
{
    glBegin(GL_POLYGON);
        glColor3f(gray, gray, gray);
        glVertex2f(x, y);
        glVertex2f(x+size, y);
        glVertex2f(x+size, y+size);
        glVertex2f(x, y+size);
    glEnd();
}

void grid()
{
    GLfloat sqr_size = 2.0f / ANIMATION_MODEL->size();

    GLfloat x = 0;
    GLfloat y = 0;
#if 0
    bool sw = true;
    for (unsigned int yi = 0; yi < ANIMATION_MODEL->size(); ++yi)
    {
        for (unsigned int xi = 0; xi < ANIMATION_MODEL->size(); ++xi)
        {
            if (sw)
            {
                square(x, y, sqr_size, 0.7f);
            }

            x += sqr_size;
            sw = !sw;
        }
        y += sqr_size;
        x = 0;
        if (ANIMATION_MODEL->size() % 2 == 0)
        {
            sw = !sw;
        }
    }
#else
    for (unsigned int yi = 0; yi < ANIMATION_MODEL->size(); ++yi)
    {
        for (unsigned int xi = 0; xi < ANIMATION_MODEL->size(); ++xi)
        {
            if (ANIMATION_MODEL->get(xi, yi))
            {
                square(x, y, sqr_size, ANIMATION_MODEL->getColor(xi, yi));
            }

            x += sqr_size;
        }
        y += sqr_size;
        x = 0;
    }
#endif
}

/*
*   END
*   drawing functions
*/

/*
*    START
*    GLUT -- functions for animation
*/

void defaultResize(int w, int h)
{
    if (w > h)
    {
        w = h;
    }
    else
    {
        h = w;
    }

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glTranslatef(-1.0f, -1.0f, 0);
}

void defaultRender(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    grid();

    int elapsed = glutGet(GLUT_ELAPSED_TIME);
    static int timepoint = elapsed;
    if (elapsed - timepoint > ANIMATION_FREQUENCY)
    {
        ANIMATION_MODEL->step();
        timepoint = elapsed;
    }

    glutSwapBuffers();
}

/*
*    END
*    GLUT -- functions for animation
*/

Animation::Animation(int argc, char **argv, const char *title, CA *model)
{
    ANIMATION_MODEL = model;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

    int window_width = glutGet(GLUT_SCREEN_HEIGHT) - 100;

    glutInitWindowPosition(
        glutGet(GLUT_SCREEN_WIDTH)/2 - window_width/2,
        glutGet(GLUT_SCREEN_HEIGHT)/2 - window_width/2
    );
    glutInitWindowSize(window_width, window_width);
    glutCreateWindow(title);

    setDisplayFunc(defaultRender);
    setReshapeFunc(defaultResize);
    setIdleFunc(defaultRender);
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

