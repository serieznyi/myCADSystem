#include "cube.h"
#include "QDebug"

Cube::Cube(GLfloat a=1.0f):Primitive()
{
    this->a = a;
}

void Cube::Apply(bool mode)
{
    int *color = 0;
    if(mode)
    color = getColor();
            else
    color = getIDColor();
    //glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);

    const GLfloat vertices[] = {
            -a,-a,-a,
            a,-a,-a,
            a,a,-a,
            -a,a,-a,
            -a,-a,a,
            a,-a,a,
            a,a,a,
            -a,a,a};

    glColor3ub(color[0],color[1],color[2]);

    glVertexPointer(3,GL_FLOAT,0,vertices);
    //glColorPointer(3,GL_INT,0,colors);

    GLubyte cubeIndex[24]={
        0,3,2,1,
        2,3,7,6,
        0,4,7,3,
        1,2,6,5,
        4,5,6,7,
        0,1,5,4
    };

    for(int i=0; i<6; i++)
        glDrawElements(GL_POLYGON, 4,
                       GL_UNSIGNED_BYTE, &cubeIndex[4*i]);

}
