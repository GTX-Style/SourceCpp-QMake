#include "GL/glut.h"
#include "vtf.h"

void Draw()
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

    VTF_H VTF = VTF_H("/home/nkarpey/.steam/steam/steamapps/common/Half-Life 2/hl2/materials/vehicle/metaltrain001a.vtf");
    VTF.OGL_CreateImage();

    glutDisplayFunc(Draw);
    glutMainLoop();

    return 0;
}
