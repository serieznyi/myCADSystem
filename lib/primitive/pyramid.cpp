#include "pyramid.h"

Pyramid::Pyramid(GLfloat a):Cube(a)
{
    this->a = a;
}

void Pyramid::Apply(bool mode)
{
    int *color =0;
    if(mode)
    color = getColor();
            else
    color = getIDColor();
    GLdouble h = (sqrt(3)/2)*this->a;
        glPushMatrix();//основание
            glRotated(90, 1, 0, 0);
                glBegin(GL_TRIANGLES);
                    glColor3f(color[0], color[1], color[3]);
                    glVertex3d(0, h/2, 0);
                    glVertex3d(a/2, -h/2, 0);
                    glVertex3d(-a/2, -h/2, 0);

                    glVertex3d(0, 0, -h);
                    glVertex3d(0, h/2, 0);
                    glVertex3d(a/2, -h/2, 0);

                    glVertex3d(0, 0, -h);
                    glVertex3d(0, h/2, 0);
                    glVertex3d(-a/2, -h/2, 0);

                    glVertex3d(0, 0, -h);
                    glVertex3d(a/2, -h/2, 0);
                    glVertex3d(-a/2, -h/2, 0);
                glEnd();
        glPopMatrix();
}
