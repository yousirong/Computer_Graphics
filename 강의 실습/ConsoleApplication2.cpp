#include "gl/glut.h"
//실행 오류 뜰경우(코드수정바람)
// int argc, char** argv을 int main()에 인수로 추가
//glutInit(&argc, argv);
void display() {



    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0f, 0.0f, 1.0f);

    glBegin



    (GL_POLYGON);

    glVertex2f(-0.2f, -0.2f);

    glVertex2f(0.4f, -0.4f);

    glVertex2f(0.4f, 0.4f);

    glVertex2f(-0.2f, 0.2f);



    glEnd();

    glFinish();

}

int main(int argc, char** argv)

{

    glutInit(&argc, argv);

    glutCreateWindow

    ("OpenGL");

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;

}


