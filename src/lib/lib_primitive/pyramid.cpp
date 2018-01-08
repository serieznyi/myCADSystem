#include "pyramid.h"

Pyramid::Pyramid(GLfloat a):Cube(a)
{
    this->a = a;
}

void Pyramid::Apply()
{
    GLdouble a = 0.5;
    GLdouble h = (sqrt(3)/2)*a;
        glPushMatrix();//основание
            glRotated(90, 1, 0, 0);
                glBegin(GL_TRIANGLES);
                    glColor3f(1.0, 0, 0);
                    glVertex3d(0, h/2, 0);
                    glVertex3d(a/2, -h/2, 0);
                    glVertex3d(-a/2, -h/2, 0);

                        glColor3d(0, 1, 0);
                    glVertex3d(0, 0, -h);
                    glVertex3d(0, h/2, 0);
                    glVertex3d(a/2, -h/2, 0);

                        glColor3d(0, 0, 1);
                    glVertex3d(0, 0, -h);
                    glVertex3d(0, h/2, 0);
                    glVertex3d(-a/2, -h/2, 0);

                        glColor3d(0, 0.5, 0.5);
                    glVertex3d(0, 0, -h);
                    glVertex3d(a/2, -h/2, 0);
                    glVertex3d(-a/2, -h/2, 0);
                glEnd();
        glPopMatrix();
}
