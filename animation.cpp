/******************************************
* FILE: animation.cpp
*
* IMS 2022/23 -- 11. Model pomocí celulárního automatu
*
* authors:   Vojtech Kucera (xkucer0h),
*            Martin Soukup (xsouku15)
*
* date:     2022-12-04
*
*******************************************/

#include "animation.h"


CA *ANIMATION_MODEL = nullptr;
double ANIMATION_FREQUENCY = 1000;


/*
*   START
*   drawing functions
*/

void square(GLfloat x, GLfloat y, GLfloat size, Cell::Type type)
{
    glBegin(GL_POLYGON);
        switch (type)
        {
        case Cell::PC:
            glColor3f(0, 0, 1.0f);
            break;

        case Cell::QC:
            glColor3f(1.0f, 0, 0);
            break;
        
        case Cell::NeC:
            glColor3f(139.0f/255, 0, 0);
            break;

        case Cell::IC:
            glColor3f(1.0f, 253.0f/255, 208.0f/255);
            break;

        case Cell::US:
            glColor3f(0, 1.0f, 0);
            break;

        case Cell::DC:
            glColor3f(0, 139.0f/255, 0);
            break;
        
        default:
            break;
        }
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

    for (int yi = 1; yi < ANIMATION_MODEL->size()-1; ++yi)
    {
        for (int xi = 1; xi < ANIMATION_MODEL->size()-1; ++xi)
        {
            if (ANIMATION_MODEL->get(xi, yi).type)
            {
                square(x, y, sqr_size, ANIMATION_MODEL->get(xi, yi).type);
            }

            x += sqr_size;
        }
        y += sqr_size;
        x = 0;
    }
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

