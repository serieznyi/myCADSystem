#include "cube.h"
#include "QDebug"

Cube::Cube(GLfloat a):Primitive()
{
    this->setTypeName(MEL_CUBE);
    this->a = a;
}

void Cube::draw()
{
    MCOLOR *color = getPaintMode() ? getColor() : getIDColor();

    glColor3ub(color->red,color->green,color->blue);

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

    glVertexPointer(3,GL_FLOAT,0,vertices);

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

QDataStream& operator<<(QDataStream &out, const Primitive *painting)
{

}
