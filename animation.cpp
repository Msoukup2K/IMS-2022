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

void square(GLfloat x, GLfloat y, GLfloat size)
{
    glBegin(GL_POLYGON);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(x, y);
        glVertex2f(x+size, y);
        glVertex2f(x+size, y+size);
        glVertex2f(x, y+size);
    glEnd();
}

void grid()
{
    GLfloat sqr_size = 2.0f / ANIMATION_MODEL->width();

    GLfloat x = 0;
    GLfloat y = 0;
//bool sw = true;
    for (unsigned int yi = 0; yi < ANIMATION_MODEL->height(); ++yi)
    {
        for (unsigned int xi = 0; xi < ANIMATION_MODEL->width(); ++xi)
        {
            if (ANIMATION_MODEL->get(xi, yi))
            {
                square(x, y, sqr_size);
            }

            x += sqr_size;
            //sw = !sw;
        }
        y += sqr_size;
        x = 0;
        //if (ANIMATION_MODEL->width() % 2 == 0)
        //{
        //    sw = !sw;
        //}
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
    if (h == 0)
        h = 1;

    float ratio =  w * 1.0 / h;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glTranslatef(-1.0f, -1.0f, 0);
    glScalef(1.0f, ratio, 1.0f);
}

void defaultRender(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
    model->setHeight(model->width()/2);
    ANIMATION_MODEL = model;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

    glutInitWindowPosition(0, 0);
    glutInitWindowSize(glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT));
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

