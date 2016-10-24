#include "GL/glut.h"

#include "bsp.h"
#include "vtf.h"

#include <list>

/* void DrawBSP()
{
    BSP_H BSP = BSP_H("/home/nkarpey/.steam/steam/steamapps/common/Half-Life 2/hl2/maps/background01.bsp");

    list <Vector3> lVertices;

    int EdgeIndex = BSP.Faces[1].Firstedge + BSP.Faces[1].Numedges - 1;

    for (int i = 0; i < BSP.Faces[1].Numedges; i++)
    {
        int CSurfedge = BSP.Surfedges[EdgeIndex];
        dedge_t CEdge = BSP.Edges[abs(CSurfedge)];

        Vector3 CVertex = CSurfedge < 0 ? BSP.Vertices[CEdge.V[1]] : BSP.Vertices[CEdge.V[0]];
        lVertices.push_front(CVertex);

        EdgeIndex--;
    }

    list <unsigned int> lIndices;

    for (int i = 1; i < lVertices.size() - 1; i++)
    {
        lIndices.push_front(0);
        lIndices.push_front(i);
        lIndices.push_front(i + 1);
    }

    Vector3 *Vertices = new Vector3[lVertices.size()];
    copy(lVertices.begin(), lVertices.end(), Vertices);

    unsigned int *Indices = new unsigned int[lIndices.size()];
    copy(lIndices.begin(), lIndices.end(), Indices);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, sizeof(Vector3), Vertices);
        glDrawElements(GL_TRIANGLES, 6 , GL_UNSIGNED_INT, Indices);
    glDisableClientState(GL_VERTEX_ARRAY);

    glFlush();
} */

void DrawVTF()
{
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 0.0f); glVertex2f(-1.0f, -1.0f);
            glTexCoord2f(1.0f, 0.0f); glVertex2f(1.0f, -1.0f);
            glTexCoord2f(1.0f, -1.0f); glVertex2f(1.0f, 1.0f);
            glTexCoord2f(0.0f, -1.0f); glVertex2f(-1.0f, 1.0f);
        glEnd();

        glFlush();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(640, 480);
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - 640) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - 480) / 2);
    glutCreateWindow("SourceCpp - OpenGL");

    //BSP_H BSP = BSP_H("/home/nkarpey/.steam/steam/steamapps/common/Half-Life 2/hl2/maps/background01.bsp");
    //glutDisplayFunc(DrawBSP);
    //glutMainLoop();

    VTF_H VTF = VTF_H("/home/nkarpey/.steam/steam/steamapps/common/Half-Life 2/hl2/materials/vehicle/metaltrain001a.vtf");
    VTF.OGL_CreateImage();

    glutDisplayFunc(DrawVTF);
    glutMainLoop();

    return 0;
}
