/*         ����   : �ѱ��ܴ� ��ǻ�� �׷��Ƚ� ����
		 ���α׷� : �κ��� ������ ����
		  ��  ��  : ��ǻ�� ���ڽý��� ����
		  ��  ��  : 201904458
		  ��  ��  : ���ؿ�
*/
#include <windows.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>


int shoulderleft = 0, elbowleft = 0, body = 0, legleft = 0, footleft = 0, head = 0, neck = 0;
int shoulderright = 0, elbowright = 0, legright = 0, footright = 0;
int flagshoulderleft = 0, flagelbowleft = 0, flagshoulderright = 0, flagelbowright = 0;
int stop_elbowleft = 0, stop_elbowright = 0;
float x_Translation = 0.0, y_Translation = 0.0, z_move = 0.0;
float x_Rotation = 0.0, y_Rotation = 0.0;


bool mouse_Lbutton_pressed = false;
bool mouse_Rbutton_pressed = false;
bool mouse_Mbutton_pressed = false;

float  Rmouse_downx = 0;
float  Rmouse_downy = 0;
float  Lmouse_downx = 0;
float  Lmouse_downy = 0;
float  mouse_Mdownx = 0;
float  mouse_Mdowny = 0;
/*opengl 277p ������ �Ŵޱ� ���α׷�(��� ���� Ȱ�� �κ�) ������ */
void drawhead()
{
	glPushMatrix();//���� ���� ����� ���ÿ� �ֽ��ϴ�. ��, ���� ����� �����մϴ�.
	glTranslatef(-1.0, 0.0, 0.0);//��ǥ���̵� ���� ����� Tt1
	glRotatef((GLfloat)head, 0.0, 0.0, 1.0);//��ǥ�� ȸ�� Tr��� ����� 
	glTranslatef(1.0, 0.0, 0.0);//��ǥ�� �̵� ���� ����� Tt2

	glPushMatrix();//���� ����� �������� �ٽ� push
	glScalef(1.2, 1.2, 1.2);//��ǥ�� ũ�� Ȯ���� Ts ��� �����
	glutWireCube(1.0);//�Ӹ� �׸���(������ü ���и� �׸���)
	glColor3f(1.0f, 0.0f, 0.0f);
	glPopMatrix();//������ ȿ���� ����ϱ� ���� ��Ʈ������ ��Ÿ���ϴ�.

	glPopMatrix();//ó���� push�ߴ� ������ķ� �ٽ� ��ġ��ŵ�ϴ�.
}

void drawbody()
{
	glPushMatrix();//���� ���� ����� ���ÿ� �ֽ��ϴ�. ��, ���� ����� �����մϴ�.

	glTranslatef(-1.0, 0.0, 0.0);//��ǥ���̵� ���� ����� Tt1
	glRotatef((GLfloat)body, 0.0, 0.0, 1.0);//��ǥ�� ȸ�� Tr��� ����� 
	glTranslatef(1.0, 0.0, 0.0);//��ǥ�� �̵� ���� ����� Tt2

	glPushMatrix();//���� ����� �������� �ٽ� Ǫ��
	glScalef(3.7, 1.2, 2);//��ǥ�� ũ�� Ȯ���� Ts ��� �����
	glutWireCube(1.0);//��ü �׸���(������ü ���и� �׸���) 
	glColor3f(1.0f, 0.0f, 0.0f);
	glPopMatrix();//������ ȿ���� ����ϱ� ���� ����� ��Ÿ���ϴ�.

	glPopMatrix();//ó���� push�ߴ� ������ķ� �ٽ� ��ġ��ŵ�ϴ�.
}



void drawneck()
{
	glPushMatrix();//���� ���� ����� ���ÿ� �ֽ��ϴ�. ��, ���� ����� �����մϴ�.

	glTranslatef(-1.0, 0.0, 0.0);//��ǥ���̵� ���� ����� Tt1
	glRotatef((GLfloat)head, 0.0, 0.0, 1.0);//��ǥ�� ȸ�� Tr��� ����� 
	glTranslatef(1.0, 0.0, 0.0);//��ǥ�� �̵� ���� ����� Tt2

	glPushMatrix();//���� ����� �������� �ٽ� push
	glScalef(0.4, 0.7, 0.6);//��ǥ�� ũ�� Ȯ���� Ts ��� �����
	glutWireCube(1.0);//�� �׸���(������ü ���и� �׸���)
	glColor3f(1.0f, 0.0f, 0.0f);
	glPopMatrix();//������ ȿ���� ����ϱ� ���� ��Ʈ������ ��Ÿ���ϴ�.

	glPopMatrix();//ó���� push�ߴ� ������ķ� �ٽ� ��ġ��ŵ�ϴ�.
}

void drawlimbright()
{
	glPushMatrix();//���� ���� ����� ���ÿ� �ֽ��ϴ�. ��, ���� ����� �����մϴ�.

	glTranslatef(-1.0, 0.0, 0.0);//��ǥ���̵� ���� ����� Tt1
	glRotatef((GLfloat)shoulderright, 0.0, 0.0, 1.0);//��ǥ�� ȸ�� Tr��� ����� 
	glTranslatef(1.0, 0.0, 0.0);//��ǥ�� �̵� ���� ����� Tt2 

	glPushMatrix();//���� ����� �������� �ٽ� Ǫ��
	glScalef(1.8, 0.4, 0.4);//��ǥ�� ũ�� Ȯ���� Ts ��� �����
	glutWireCube(1.0);//���� ���� �׸��ϴ�. (������)
	glPopMatrix();// ������ glPushMatrix()���� ������ ��ǥ�踦 pop�ؼ� scale������ ��ǥ�踦 �ٽ� ������.

	glTranslatef(0.75, 0.0, 0.0); //Tt1 �̵�
	glRotatef((GLfloat)elbowright, 0.0, 0.0, 1.0); //Tr��� �����
	glTranslatef(1.0, 0.0, 0.0); //Tt2 �̵� 

	glPushMatrix();//���� ����� �������� �ٽ� Ǫ��
	glScalef(1.7, 0.4, 0.4);
	glutWireCube(1.0);//���� �ȶ� �׸���(������ü ���и� �׸���) 
	glColor3f(1.0f, 0.0f, 0.0f);
	glPopMatrix();//psuh�ߴ� ��� pop 

	glPopMatrix();//ó���� push�ߴ� ������ķ� �ٽ� ��ġ��ŵ�ϴ�. 
}

void drawlimbleft()
{
	glPushMatrix();//���� ���� ����� ���ÿ� �ֽ��ϴ�. ��, ���� ����� �����մϴ�.

	glTranslatef(-1.0, 0.0, 0.0);//��ǥ���̵� ���� ����� Tt1
	glRotatef((GLfloat)shoulderleft, 0.0, 0.0, 1.0);//��ǥ�� ȸ�� Tr��� ����� 
	glTranslatef(1.0, 0.0, 0.0);//��ǥ�� �̵� ���� ����� Tt2

	glPushMatrix();//���� ����� �������� �ٽ� push
	glScalef(1.8, 0.4, 0.4);//��ǥ�� ũ�� Ȯ���� Ts ��� �����
	glutWireCube(1.0);//���� ���� �׸��ϴ�. (����)
	glPopMatrix();//������ glPushMatrix()���� ������ ��ǥ�踦 pop�ؼ� scale������ ��ǥ�踦 �ٽ� ������.

	glTranslatef(0.75, 0.0, 0.0); //Tt1 �̵�
	glRotatef((GLfloat)elbowleft, 0.0, 0.0, 1.0); //Tr��� �����
	glTranslatef(1.0, 0.0, 0.0); //Tt2 �̵�

	glPushMatrix();//���� ����� �������� �ٽ� Ǫ��
	glScalef(1.7, 0.4, 0.4);
	glutWireCube(1.0);//���� �ȶ� �׸���(������ü ���и� �׸���) 
	glColor3f(1.0f, 0.0f, 0.0f);
	glPopMatrix();//psuh�ߴ� ��� pop 

	glPopMatrix();//ó���� push�ߴ� ������ķ� �ٽ� ��ġ��ŵ�ϴ�. 
}

void drawlegleft()
{
	glPushMatrix();//���� ���� ����� ���ÿ� �ֽ��ϴ�. ��, ���� ����� �����մϴ�.

	glTranslatef(-0.7, 0.0, 0.0);//��ǥ���̵� ���� ����� Tt1
	glRotatef((GLfloat)legleft, 0.0, 0.0, 1.0);//��ǥ�� ȸ�� Tr��� �����
	glTranslatef(1.0, 0.0, 0.0);//��ǥ�� �̵� ���� ����� Tt2

	glPushMatrix();//���� ����� �������� �ٽ� push
	glScalef(2.0, 0.6, 0.6);//��ǥ�� ũ�� Ȯ���� Ts ��� �����
	glutWireCube(1.0);//���� �ٸ� �׸���(������ü ���и� �׸���)
	glPopMatrix();//������ glPushMatrix()���� ������ ��ǥ�踦 pop�ؼ� scale������ ��ǥ�踦 �ٽ� ������.

	glTranslatef(1.0, 0.0, 0.0); //Tt1 �̵�
	glRotatef((GLfloat)footleft, 0.0, 0.0, 1.0); //Tr��� �����
	glTranslatef(1.0, 0.0, 0.0); //Tt2 �̵�

	glPushMatrix();//���� ����� �������� �ٽ� Ǫ��
	glScalef(2.0, 0.6, 0.6);
	glutWireCube(1.0);//���� �ٸ� �׸���(������ü ���и� �׸���) 
	glColor3f(1.0f, 0.0f, 0.0f);
	glPopMatrix();//psuh�ߴ� ��� pop 

	glPopMatrix();//ó���� push�ߴ� ������ķ� �ٽ� ��ġ��ŵ�ϴ�.
}

void drawlegright()
{
	glPushMatrix();//���� ���� ����� ���ÿ� �ֽ��ϴ�. ��, ���� ����� �����մϴ�.

	glTranslatef(-0.7, 0.0, 0.0);//��ǥ���̵� ���� ����� Tt1
	glRotatef((GLfloat)legright, 0.0, 0.0, 1.0);//��ǥ�� ȸ�� Tr��� �����
	glTranslatef(1.0, 0.0, 0.0);//��ǥ�� �̵� ���� ����� Tt2

	glPushMatrix();//���� ����� �������� �ٽ� push
	glScalef(2.0, 0.6, 0.6);//��ǥ�� ũ�� Ȯ���� Ts ��� �����
	glutWireCube(1.0);//������ �ٸ� �׸���(������ü ���и� �׸���)
	glPopMatrix();//������ glPushMatrix()���� ������ ��ǥ�踦 pop�ؼ� scale������ ��ǥ�踦 �ٽ� ������.

	glTranslatef(1.0, 0.0, 0.0);//Tt1 �̵�
	glRotatef((GLfloat)footright, 0.0, 0.0, 1.0);//Tr��� �����
	glTranslatef(1.0, 0.0, 0.0);//Tt2 �̵�

	glPushMatrix();//���� ����� �������� �ٽ� Ǫ��
	glScalef(2.0, 0.6, 0.6);
	glutWireCube(1.0);//������ �ٸ� �׸���(������ü ���и� �׸���) 
	glColor3f(1.0f, 0.0f, 0.0f);
	glPopMatrix();//psuh�ߴ� ��� pop 

	glPopMatrix();//ó���� push�ߴ� ������ķ� �ٽ� ��ġ��ŵ�ϴ�.
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();
	// ó���� �κ��� ���� ������ ����
	gluLookAt(10.0 + x_Translation, y_Translation, z_move, x_Translation, y_Translation, z_move, 0.0, 1.0, 0.0);

	glRotatef(x_Rotation, 1.0, 0.0, 0.0);
	glRotatef(y_Rotation, 0.0, 1.0, 0.0);


	//���� �� �׸���
	glPushMatrix();//���� ����� �������� Ǫ���մϴ�. ��, ���� ����� �����մϴ�.
	glTranslatef(-1.0, 0.5, -1.3);
	glRotatef(-90.0, 0.0, 0.0, 1.0);
	glColor3f(0.0f, 1.0f, 1.0f);
	drawlimbleft();
	glPopMatrix();//����� ���� ��ǥ�� ��� pop

	//������ �� �׸���
	glPushMatrix();//���� ����� �������� Ǫ���մϴ�. ��, ���� ����� �����մϴ�.
	glTranslatef(-1.0, 0.5, 1.3);
	glRotatef(-90.0, 0.0, 0.0, 1.0);
	glColor3f(0.0f, 1.0f, 1.0f);
	drawlimbright();
	glPopMatrix();

	//�� �׸���
	glPushMatrix();
	glTranslatef(-1.0, 0.0, 0.0);
	glRotatef(90.0, 0.0, 0.0, 1.0);
	drawbody();
	glPopMatrix();

	//�Ӹ� �׸���
	glPushMatrix();
	glTranslatef(-1.0, 2.8, 0.0);
	glRotatef(90.0, 0.0, 0.0, 1.0);
	drawhead();
	glPopMatrix();

	//�� �׸���
	glPushMatrix();
	glTranslatef(-1.0, 2.0, 0.0);
	glRotatef(90.0, 0.0, 0.0, 1.0);
	drawneck();
	glPopMatrix();

	//���� �ٸ� �׸���
	glPushMatrix();
	glTranslatef(-1.0, -2.5, -0.5);
	glRotatef(-90.0, 0.0, 0.0, 1.0);
	drawlegleft();
	glPopMatrix();

	//������ �ٸ� �׸���
	glPushMatrix();
	glTranslatef(-1.0, -2.5, 0.5);
	glRotatef(-90.0, 0.0, 0.0, 1.0);
	drawlegright();
	glPopMatrix();


	glutSwapBuffers();
}

void reshape(int w, int h)
{   // gluLoadIdentity() gluPerspective()
	/*���� �� matrix�� ��� �� �� glMultMatrix �� ȣ���� �� ó��
	gluPerspective �� ���� ���� �� ��Ŀ� ���� ����� �������ϴ�.
	��� ���� matrix ���ÿ� ť�� �� ��Ʈ������ �ε� �Ϸ���
	glLoadIdentity�� �� �� ȣ���� ��� �� �� gluPerspective �� �� �� ȣ�� �տ� �ɴϴ�.*/
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 1.0, 200.0);
	//1.y������ ���Ⱒ�� 65�� 
	//2. X ������ �� �ʵ带 ���� �ϴ� ���� ���� �����Դϴ�. ���� ���� ������ x (�ʺ�)�� y (����)�� �����Դϴ�
	//3. ���� ����� Ŭ���� ��� ������ �Ÿ� (�׻� ���)�Դϴ�.
	//4.���� �� Ŭ���� ��� ������ �Ÿ� (�׻� ���)�Դϴ�.
	glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'q':   // ���� ��� �ø��� (360ȸ��, z ��������� �����ϴ°��� ���)
		shoulderleft = (shoulderleft + 3) % 360;
		shoulderright = (shoulderright + 3) % 360;
		glutPostRedisplay();
		break;
	case 'a':   // ���� ��ü ������ (360ȸ��, z ���������� �����ϴ°��� ����)
		shoulderleft = (shoulderleft - 3) % 360;
		shoulderright = (shoulderright - 3) % 360;
		glutPostRedisplay();
		break;
	case 'p':  // ���� �ȶҺκ� ��ü �ø���( ������ 0���� 165������ �ø��� 165�Ǹ� �ȿø��� ����)
		if (stop_elbowleft) {
			elbowleft = (elbowleft + 3) % 360;
			if (elbowleft >= 165 || elbowleft >= -165)
				stop_elbowleft = 0;
		}
		else {
			if (elbowleft <= 165 || elbowleft <= -165)
				stop_elbowleft = 1;
		}
		if (stop_elbowright) {
			elbowright = (elbowright + 3) % 360;
			if (elbowright >= 165 || elbowright >= -165)
				stop_elbowright = 0;
		}
		else {
			if (elbowright <= 165 || elbowright <= -165)
				stop_elbowright = 1;
		}
		glutPostRedisplay();
		break;
	case 'l':  // ���� �ȶ� �κ� ��ü ������ ( ������ 0�� �ɰ��� ���� ���ڷ� ������ �����. ������ 0�� �Ǹ� ����)
		if (stop_elbowleft) {
			elbowleft = (elbowleft - 3) % 360;
			if (elbowleft == 0)
				stop_elbowleft = 0;
		}
		else {
			if (elbowleft > 0 && elbowleft <= 170)
				stop_elbowleft = 1;
		}
		if (stop_elbowright) {
			elbowright = (elbowright - 3) % 360;
			if (elbowright == 0)
				stop_elbowright = 0;
		}
		else {
			if (elbowright > 0 && elbowright <= 170)
				stop_elbowright = 1;
		}
		glutPostRedisplay();
		break;

	case'w':   //  �ڿ������� �ȱ�
		//���� �� �յڷ� ����
		if (flagshoulderleft)
		{
			shoulderleft = (shoulderleft - 3) % 360;
			if (shoulderleft <= -40)flagshoulderleft = 0;
		}
		else
		{
			shoulderleft = (shoulderleft + 3) % 360;
			if (shoulderleft >= 40)flagshoulderleft = 1;
		}

		if (flagelbowleft)
		{
			elbowleft = (elbowleft - 3) % 360;
			if (elbowleft <= -5)flagelbowleft = 0;
		}
		else
		{
			elbowleft = (elbowleft + 3) % 360;
			if (elbowleft >= 40)flagelbowleft = 1;
		}

		//������ �� �յڷ� ����
		if (flagshoulderright)
		{
			shoulderright = (shoulderright + 3) % 360;
			if (shoulderright >= 40)flagshoulderright = 0;
		}
		else
		{
			shoulderright = (shoulderright - 3) % 360;
			if (shoulderright <= -40)flagshoulderright = 1;
		}

		if (flagelbowright)
		{
			elbowright = (elbowright + 3) % 360;
			if (elbowright >= 40)flagelbowright = 0;
		}
		else
		{
			elbowright = (elbowright - 3) % 360;
			if (elbowright <= -5)flagelbowright = 1;
		}
		glutPostRedisplay();
		break;
	case 27:
		exit(0);
		break;
	default:
		break;
	}
}

void mouse(int   button, int   state, int   x, int   y)
{
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN)//���콺 ���� ��ư�� ������ mouse_Lbutton_pressed�� �����ǰ� Ŀ�� ��ġ�� ��ϵ˴ϴ�.
		{
			mouse_Lbutton_pressed = true;
			Lmouse_downx = x;
			Lmouse_downy = y;
		}
		else {
			mouse_Lbutton_pressed = false;
		}
	}
	if (button == GLUT_RIGHT_BUTTON) {
		if (state == GLUT_DOWN)//���콺 ������ ��ư�� ������ mouse_Rbutton_pressed�� �����ǰ� Ŀ�� ��ġ�� ��ϵ˴ϴ�.
		{
			mouse_Rbutton_pressed = true;
			Rmouse_downx = x;
			Rmouse_downy = y;
		}
		else {
			mouse_Rbutton_pressed = false;
		}
	}
	if (button == GLUT_MIDDLE_BUTTON) {
		if (state == GLUT_DOWN)//���콺 ���� ������ mouse_Mbutton_pressed�� �����ǰ� Ŀ�� ��ġ�� ��ϵ˴ϴ�.
		{
			mouse_Mbutton_pressed = true;
			mouse_Mdownx = x;
			mouse_Mdowny = y;
		}
		else {
			mouse_Mbutton_pressed = false;  // ���콺 ������ ��ư�� ��� x
		}
	}
}

void mouseMove(int x, int y)
{
	if (mouse_Lbutton_pressed) {     // ���콺 ��Ŭ�� ��ä�� 
		x_Translation += (Lmouse_downx - x) / 50.0f;  // +x������ ���콺 �̵��� �κ� ���������� ȸ�� 
		y_Translation -= (Lmouse_downy - y) / 50.0f;  // -x���� ���콺 �̵��� �κ� �������� ȸ�� 
		Lmouse_downx = x;  // -y������ ���콺 �̵��� �κ� �ݽð� ���� ȸ�� 
		Lmouse_downy = y;  // +y������ ������ �̵��� �κ� �ð� ���� ȸ�� 
		glutPostRedisplay();
	}
	if (mouse_Rbutton_pressed) {  // ���콺 ��Ŭ�� ��ä��
		x_Rotation -= (Rmouse_downy - y) / 3.0f;
		y_Rotation -= (Rmouse_downx - x) / 3.0f;
		Rmouse_downx = x;
		Rmouse_downy = y;
		glutPostRedisplay();
	}
}

void specialKeyFunc(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_DOWN:    // �Ʒ�Ű �������� ��ĭ �̵� 
		z_move--;
		glutPostRedisplay();
		break;
	case GLUT_KEY_UP:     // ��Ű ���������� ��ĭ �̵�
		z_move++;
		glutPostRedisplay();
		break;
	case GLUT_KEY_LEFT:   // ����Ű �κ� �ݽð� �������� ȸ�� 
		x_Rotation++;
		glutPostRedisplay();
		break;
	case GLUT_KEY_RIGHT:  // ������Ű �κ� �ݽð� �������� ȸ�� 
		x_Rotation--;
		glutPostRedisplay();
		break;

	default:
		break;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);       // �ִϸ��̼��� ��� �Ҷ� ���� ���۸��� ����ϴ°� ����. ������۸� ���ϸ� ( �����̴����� �߻�)
													//���� ���۸� ȭ�鿡 �Ѹ���, �ִϸ��̼���
													// ������ �Ѹ��� ���� 
	glutInitWindowSize(800, 1000);       // �������� ����� 800, 1000���� ����
	glutInitWindowPosition(400, 0);      // ���α׷� ���� ��ų ��� ��Ÿ���� ȭ���� ����� ��ġ��Ŵ.
	glutCreateWindow("OpenGl_����2 drawArm �κ��� �����ӱ���_201904458_���ؿ�");  //���ο� ������ ��ܿ� title �ٿ� ��Ÿ��
	glClearColor(1.0, 1.0, 1.0, 1.0);          //float�� ���� ���� �� ���ڴ� ������� RGB ������ ���ڴ� ����(����)  (1.0,1.0,1.0,1.0)���� �ٲٸ� ���ȭ���� ������� �ٲ�
											 // glClearColor �Լ��� ���ȭ�� �����ϴ� �Լ���.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();


	glutDisplayFunc(display);  // ȭ�鿡 ��� 

	glutReshapeFunc(reshape);

	glutKeyboardFunc(keyboard);  // Ű���� �Է�

	glutMouseFunc(mouse);  // ���콺 �Է� 
	glutMotionFunc(mouseMove); // ���콺�� ȭ�� ȸ�� �̵�
	glutSpecialFunc(specialKeyFunc); // ���Ʒ��¿�Ű�� ȭ�� �̵� 

	glutMainLoop();
	return 0;
}
