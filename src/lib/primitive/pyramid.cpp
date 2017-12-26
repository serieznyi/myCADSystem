#include "pyramid.h"

Pyramid::Pyramid(GLfloat a):Primitive()
{
    this->a = a;
    this->setTypeName(MEL_PYRAMID);
}

void Pyramid::draw()
{
    MCOLOR *color = 0;
    if(getPaintMode())
    color = getColor();
            else
    color = getIDColor();

    glColor3ub(color->red,color->green,color->blue);

    GLdouble h = (sqrt(3)/2)*this->a;
       // glPushMatrix();//основание
            glRotated(90, 1, 0, 0);
                glBegin(GL_TRIANGLES);
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
   //             glPopMatrix();
}
