/*
�� ������Ʈ�� kim.cpp ������ ������ �����ϴ�.
�׷��� ���� ����� ������ c:\ ��ο� ���������� �ʿ��ϴ�.

�� ������Ʈ�� �ȵ���̵� �κ��� ���ͼ� 4���� ������ �Ѵ�.
�������� ������ ���콺�� Ŭ���ϸ� 5���� �޴��� ���´�.
ù��°�� �κ��� �޸��� �������μ� �޴����� '�ϴ�~' �� ǥ�õȴ�.
�ι�°�� �κ��� ���� ������ �������μ� �޴����� '����~'�̶� ǥ�õȴ�.
����°�� �κ��� ���� ��ġ�� ������ �������μ� �޴����� '�л�~'�̶� ǥ�õȴ�.
�׹�°�� �κ��� �ǰܽ������� �������μ� �޴����� '����~'��� ǥ�õȴ�.
�ټ���°�� '����' �޴��μ� ���������� ���� ����ÿ� �޴����� �ٸ� ������ 
������ �ϱ� ���ؼ� �� �޴��� �̿��Ͽ� ���� ������ ���ǰ� �ൿ�� ������ų �� �ִ�.

Ű������ 'q'��ư�� ������ ���� �̹����� ���´�.
Ű������ 'w'��ư�� ������ wire �̹����� ��ȯ��Ű��,
Ű������ 's'��ư�� ������ solid �̹����� ��ȯ��Ų��.
*/

/*
�ʼ����� ��� ���ϵ�
*/

#include<windows.h>
#include<MMSystem.h>
#include<GL/glut.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<math.h>

static double time=0;  // Run_time ����
static double time2=0; // Jap_time ����
static double time3=0; // Rocket_time ����
static double time4=0; // ground_time ����
static double time6=0; // exit_time ����

GLfloat R_Arm_x=0; // ������ ���
GLfloat R_Arm_y=0; // ������ ��
GLfloat L_Arm_x=0; // ���� ���
GLfloat L_Arm_y=0; // ���� ��
GLfloat R_Leg_x=0; // ���� �����
GLfloat R_Leg_y=0; // ���� ���Ƹ�
GLfloat L_Leg_x=0; // �� �����
GLfloat L_Leg_y=0; // �� ���Ƹ�
GLfloat R=0; // ���� ���� ��ġ ������ ����
GLfloat R2=0;// ������ ���� ��ġ ������ ����

GLUquadricObj* cyl;// �Ǹ��� ��ü ����

int a=0; // x�� ����(���� 1�� �� x���� �������� ȸ��)
int b=0; // y�� ����(���� 1�� �� y���� �������� ȸ��)
int c=0; // z�� ����(���� 1�� �� z���� �������� ȸ��)

static int flag=0; // wireframe ���� solid rendering ��� ���� ����
static int key=0;  // ���� ���� ���� ���� ����

#define RUN		1					
#define JAP		2							
#define ROCKET	3	
#define YUNA	4	
#define EXIT	6	

void glInit(void){ // ���� �ʱ�ȭ �Լ� 
	glEnable(GL_DEPTH_TEST); // ���� �׽��� ���
	glEnable(GL_NORMALIZE);  // ����ȭ
	glEnable(GL_SMOOTH);     // �� ������ ������ �ε巴�� �����Ͽ� ĥ��������  �ϹǷ�, �������� ����� ������ ȥ�յǾ� ����ȴ�. 
	glEnable(GL_LIGHTING);   // ���� ����. ���� �޴� ������ ���� �κ� ������ ��ȭ

	/* ���� �޴� ������ ���� �κ� ������ ��ȭ�� ���� ���� */
	GLfloat ambientLight[]={0.3f,0.3f,0.3f,1.0f};
	GLfloat diffuseLight[]={0.7f,0.7f,0.7f,1.0f};
	GLfloat specular[]={1.0f,1.0f,1.0f,1.0f};
	GLfloat specref[]={1.0f,1.0f,1.0f,1.0f};
	GLfloat position[]={400.0,300.0,-700.0,1.0};
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMateriali(GL_FRONT, GL_SHININESS, 128);

	glClearColor(1.0,1.0,1.0,1.0); // ��� ������
	glMatrixMode(GL_PROJECTION);   // ��� ����
	glLoadIdentity();              // CTM �� �ʱ�ȭ 
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); // ���� ���� ����
}

void Draw_Color(int i){ // ������ �׸��� �Լ�
	if(i==RUN){
		glColor3f(0.0,1.0,0.0);
	}else if(i==JAP){
		glColor3f(1.0,1.0,0.0);
	}else if(i==ROCKET){
		glColor3f(0.0,1.0,1.0);
	}else if(i==YUNA){	
		glColor3f(1.0,0.0,1.0);
	}else if(i==EXIT){
		glColor3f(0.2,0.2,0.2);
	}
}

void Change_Wire_Or_Solid(int i){          // �ָ���, ���̾� ����
	if(flag==1)				
		gluQuadricDrawStyle(cyl,GLU_LINE); // ��Ÿ���� ���̾�� ����
}
/*
�κ� ������ �׸��� �Լ�
*/
void DrawL_Arm(int x,int a,int b,int c){
	glPushMatrix();
	Draw_Color(key);       // �� ����
	cyl=gluNewQuadric();   // �Ǹ��� ��ü ����
	glRotatef(x,a, b, c);  // �Ķ���� ����ŭ ȸ��
	glRotatef(90.0,1.0, 0.0, 0.0); // �Ǹ����� x�� �������� 90�� ȸ��(�Ǹ��� ���� �� ���� ������ ����)
	glTranslatef(0.25,0.0,0.0);    // ���� ��� ���������� �̵�
	glRotatef(15.0,0.0, 1.0, 0.0); // ���� ����� y���� �������� 15�� ȸ��
	Change_Wire_Or_Solid(flag);
	gluCylinder(cyl,0.05,0.05,0.2,50,1); // �Ǹ����� �׸�
}

/*
�κ� ���� ���� �׸��� �Լ�
*/
void DrawL_Hand(int y,int a,int b, int c){
	glPushMatrix();
	Draw_Color(key);       // �� ����
	cyl=gluNewQuadric();   // �Ǹ��� ��ü ����
	glTranslatef(0.0,0.0,0.22); // �޼� ������
	glRotatef(y,a,b, c);        // �Ķ���� ����ŭ ȸ��
	Change_Wire_Or_Solid(flag);
	if(key ==YUNA) gluCylinder(cyl,0.05,0.02,0.2,15,1); // �򶧱� ��� �Ǹ����� �׸�
	else gluCylinder(cyl,0.05,0.05,0.2,15,1);           // �Ǹ����� �׸�
	glPopMatrix();
}
/*
�κ� ���� �ָ�
*/
void DrawL_HandRocket(){
	glPushMatrix();
	Draw_Color(key);     // �� ����
	cyl=gluNewQuadric(); // �Ǹ��� ��ü ����
	glTranslatef(0,0,R); // ���� �ָ� ��ġ�� �Ķ���͸�ŭ �̵�
	Change_Wire_Or_Solid(flag);
	gluCylinder(cyl,0.05,0.05,0.2,50,1); // �Ǹ����� �׸�
	glPopMatrix();
}
/*
�κ� �������� �׸��� �Լ�
*/
void DrawR_Arm(int x,int a,int b,int c){
	glPushMatrix();
	Draw_Color(key);     // �� ����
	cyl=gluNewQuadric(); // �Ǹ��� ��ü ����
	glRotatef(x,a,b,c);  // �Ķ���� ����ŭ ȸ��
	glRotatef(90.0,1.0, 0.0, 0.0); // �Ǹ����� x���� �������� 90�� ȸ��(�Ǹ��� ���� �� ���� ������ ����)
	glTranslatef(-0.25,0.0,0.0); //���� ��� ���������� �̵�
	glRotatef(-15.0,0.0, 1.0, 0.0); //���� ��� -15�� y����� ȸ��
	Change_Wire_Or_Solid(flag);
	gluCylinder(cyl,0.05,0.05,0.2,50,1);// �Ǹ��� �׸�

}
/*
�κ� ������ ���� �׸��� �Լ�
*/
void DrawR_Hand(int y,int a,int b, int c){
	glPushMatrix();
	Draw_Color(key); // �� ����
	cyl=gluNewQuadric();//�Ǹ��� ��ü ����
	glTranslatef(0.0,0.0,0.22);//������ �� ������
	glRotatef(y, a , b, c);// �Ķ���Ͱ� ��ŭ ȸ��
	Change_Wire_Or_Solid(flag);
	if(key ==YUNA) gluCylinder(cyl,0.05,0.02,0.2,50,1);// �򶧱� ��� �Ǹ��� �׸�
	else gluCylinder(cyl,0.05,0.05,0.2,50,1);// �Ǹ��� �׸�
	glPopMatrix();
}

/*
�κ� ������ ����Ʈ �Լ�
*/

void DrawR_HandRocket(){
	glPushMatrix();
	Draw_Color(key);
	cyl=gluNewQuadric(); //�Ǹ��� ��ü ����
	glTranslatef(0,0,R2);//�����ָ� ��ġ �Ķ���͸�ŭ �̵�
	Change_Wire_Or_Solid(flag);
	gluCylinder(cyl,0.05,0.05,0.2,50,1);// �Ǹ��� �׸�
	glPopMatrix();
}
/*
�κ� ��ü�� �׸��� �Լ�
*/
void DrawBody(int x,int a,int b,int c){
	glPushMatrix();
	Draw_Color(key);
	cyl=gluNewQuadric();//�Ǹ��� ��ü ����
	glRotatef(90.0, 1.0, 0.0, 0.0);//�Ǹ��� 90�� x����� ȸ�� (�Ǹ��� ������ ���� ������ ���Ͽ�)
	glRotatef(x, a , b, c);//�Ķ���Ͱ� ��ŭ ȸ��
	Change_Wire_Or_Solid(flag);
	gluCylinder(cyl,0.2,0.2,0.45,50,1);// �Ǹ��� �׸�
	glPopMatrix();
}
/*
�κ� ���� ������� �׸��� �Լ�
*/
void DrawL_Legs(int x, int a,int b,int c){
	glPushMatrix();
	Draw_Color(key);
	cyl=gluNewQuadric();//�Ǹ��� ��ü ����
	glRotatef(90.0, 1.0, 0.0, 0.0);//�Ǹ��� 90�� x����� ȸ�� (�Ǹ��� ������ ���� ������ ���Ͽ�)
	glTranslatef(0.1,0.0,0.42);//���� ����� ������
	glRotatef(x,a, b, c);//�Ķ���͸�ŭ ȸ��
	Change_Wire_Or_Solid(flag);
	gluCylinder(cyl,0.05,0.05,0.15,50,1);// �Ǹ��� �׸�

}
/*
�κ� ���� ���Ƹ��� �׸��� �Լ�
*/
void DrawL_foot(int y,int a,int b,int c){
	glPushMatrix();
	Draw_Color(key);
	cyl=gluNewQuadric();//�Ǹ��� ��ü ����
	glTranslatef(0.0,0.0,0.18);//���� ���Ƹ� ������
	glRotatef(y,a, b, c);//�Ķ���͸�ŭ ȸ��
	Change_Wire_Or_Solid(flag);
	if(key ==YUNA) gluCylinder(cyl,0.05,0.03,0.2,50,1);// �򶧱� ��� �Ǹ��� �׸�
	else gluCylinder(cyl,0.05,0.05,0.2,50,1);// �Ǹ��� �׸�
	glPopMatrix();
}
/*
�κ� ������ ������� �׸��� �Լ�
*/
void DrawR_Legs(int x,int a,int b,int c){
	glPushMatrix();
	Draw_Color(key);
	cyl=gluNewQuadric();//�Ǹ��� ��ü ����
	glRotatef(90.0, 1.0, 0.0, 0.0);//�Ǹ��� 90�� x����� ȸ�� (�Ǹ��� ������ ���� ������ ���Ͽ�)
	glTranslatef(-0.1,0.0,0.42);//������ ����� ������
	glRotatef(x,a,b,c);//�Ķ���͸�ŭ ȸ��
	Change_Wire_Or_Solid(flag);
	gluCylinder(cyl,0.05,0.05,0.15,50,1);// �Ǹ��� �׸�

}
/*
�κ� ������ ���Ƹ��� �׸��� �Լ�
*/
void DrawR_foot(int y,int a,int b,int c){
	glPushMatrix();
	Draw_Color(key);
	cyl=gluNewQuadric();//�Ǹ��� ��ü ����

	glTranslatef(0.0,0.0,0.18);//������ ���Ƹ� ������
	glRotatef(y,a, b, c);//�Ķ���͸�ŭ ȸ��

	Change_Wire_Or_Solid(flag);
	if(key ==YUNA) gluCylinder(cyl,0.05,0.03,0.2,15,1);// �򶧱� ��� �Ǹ��� �׸�
	else gluCylinder(cyl,0.05,0.05,0.2,15,1);// �Ǹ��� �׸�
	glPopMatrix();
}
/*
�κ� ���� �׸��� �Լ�
*/
void Drawneck(){
	glPushMatrix();
	glColor3f(1.0,1.0,1.0);//�� ����(���)
	cyl=gluNewQuadric();//�Ǹ��� ��ü ����
	glRotatef(90.0, 1.0, 0.0, 0.0);//�Ǹ��� 90�� x����� ȸ�� (�Ǹ��� ������ ���� ������ ���Ͽ�)
	glTranslatef(0.0,0.0,-0.045); // �� ������
	Change_Wire_Or_Solid(flag);
	gluCylinder(cyl,0.2,0.2,0.025,100,1);// �Ǹ��� �׸�
	glPopMatrix();
}
/*
���� �׸��� �Լ�
���� Ŀ�ٶ� ���� �����Ͽ���.
���� �ð��� ���� ȸ���Ͽ��� ��ġ �κ��� 
������ �پ�� ������ �鵵�� �����Ͽ���.
*/
void DrawGround(){
	Draw_Color(flag);//���� ����
	glTranslatef(0.0,-2.73,0.0);//�� ������
	glRotatef(45.0,0,1,0);//45����ŭ y�� �������� ȸ��
	glRotatef(0.0+time4-15,0.0, 0.0, 1);// z�� �������� time4��ŭ ���� ȸ�� 
	Change_Wire_Or_Solid(flag);
	gluSphere(cyl, 2.5, 30, 90);	
}
/*
�κ� �Ӹ��� �׸��� �Լ�
�κ��� �Ӹ��� �޷��ִ� �԰�
�κ��� ���� �����Ͽ���.
*/
void DrawHead(){
	glTranslatef(0.0,0.02,0.0);//�Ӹ� ������
	glPushMatrix();// ó�� ���� ��ǥ �ٽ� ����
	cyl=gluNewQuadric();
	Change_Wire_Or_Solid(flag);
	Draw_Color(key);//���� ����
	gluSphere(cyl, 0.20, 30, 10);//�Ӹ� �׸���
	/*���� �� �׸���*/
	glRotatef(90.0, 1.0, 0.0, 0.0);//�Ǹ��� 90�� x����� ȸ�� (�Ǹ��� ������ ���� ������ ���Ͽ�)
	glTranslatef(-0.16,0.0,-0.22);//���� �� ������
	glRotatef(35.0, 0.0, 1.0, 0.0);//35�� y�� ���� ȸ��
	gluCylinder(cyl,0.005,0.008,0.1,3,1);//�Ǹ��� �׸�
	glPopMatrix( ); // ó�� ���� ��ǥ�� ���� ����.
	glPushMatrix( );// ó�� ���� ��ǥ �ٽ� ����

	/*������ �� �׸���*/
	glRotatef(90.0, 1.0, 0.0, 0.0);//�Ǹ��� 90�� x����� ȸ�� (�Ǹ��� ������ ���� ������ ���Ͽ�)
	glTranslatef(0.16,0.0,-0.22);//������ �� ������
	glRotatef(-35.0, 0.0, 1.0, 0.0);//-35�� y�� ���� ȸ��
	gluCylinder(cyl,0.005,0.008,0.1,3,1);//�Ǹ��� �׸�
	glPopMatrix( ); // ó�� ���� ��ǥ�� ���� ����.	
	glPushMatrix( );// ó�� ���� ��ǥ �ٽ� ����

	/*���� �� �׸���*/
	glTranslatef(-0.1,0.1,0.13);//���� �� ������
	glColor3f(0.0,0.0,0.0);// �� �÷� ����(���)
	gluSphere(cyl, 0.03, 10, 10);

	glPopMatrix(); // ó�� ���� ��ǥ�� ���� ����.
	glPushMatrix();// ó�� ���� ��ǥ �ٽ� ����

	/*������ �� �׸���*/
	glTranslatef(0.1,0.1,0.13);//������ �� ������
	gluSphere(cyl, 0.03, 10, 10);
	glPopMatrix();// ó�� ���� ��ǥ �ٽ� ����
}
/*
�ȵ���̵� ��ü ����� �׸��� �Լ�
*/
void DrawAndroid(){
	DrawBody(0,0,0,0); // ���� �Լ� ȣ��
	Drawneck(); // ���Լ� ȣ��
	DrawHead(); // �Ӹ� ȣ��
	DrawR_Arm(R_Arm_x,1,0,0);//�����ȶ�
	if(key==ROCKET) DrawR_HandRocket(); // ���ϸ���϶� ��������ȣ��
	else DrawR_Hand(R_Arm_y,1,0,0);  //������ȣ��
	DrawL_Arm(L_Arm_x,1,0,0);   //�����ȶ�
	if(key==ROCKET) DrawL_HandRocket(); // ���ϸ���϶� ��������ȣ��
 	else DrawL_Hand(L_Arm_y,1,0,0);//������ȣ��
	DrawL_Legs(L_Leg_x,1,0,0);  //�����ٸ�
	DrawL_foot(L_Leg_y,1,0,0);  //������		 
	DrawR_Legs(R_Leg_x,1,0,0);  //�����ٸ�
	DrawR_foot(R_Leg_y,1,0,0);  //������	
}
/*
�κ��� �޸��� ���� ǥ���� �Լ�.
�κ��� ������ �����̴� ���� ǥ���߰�,
�κ��� �޸��鼭 ��,��,��,��� �����̴� ����� ǥ���ߴ�.
*/
void Run(){
	sndPlaySound(TEXT("C:\\sample1.wav"),SND_ASYNC|SND_NOSTOP); 
	glLoadIdentity();//CTM �ʱ�ȭ
	/*
	�⺻���� �κ��� �������� ���ӵ��� sin() �Լ��� ���� ǥ���Ͽ���
	���� ������ ���ѹ����� �����Ͽ� abs() �Լ��� ���� ������ �������� �����Ͽ���.
	*/
	L_Arm_x=sin(time)*80;           //������ 80�� �������� �����̵� sin()�Լ��� ����Ͽ� �ֱ����� ������ ����
	R_Arm_x=-L_Arm_x;               //�������� ���ȹݴ�� 80���������� �����̵� sin()�Լ��� ����Ͽ� �ֱ����� ������ ����.
	R_Arm_y=-abs(sin(time)*60+50);  //�����ȶ� ��������(abs���밪�� �����ν� �ȶ��� �ڷβ����� �ʴ� �Ѱ����� ����) 
	L_Arm_y=-abs(-sin(time)*60+50); //�����ȶ� ��������(abs���밪�� �����ν� �ȶ��� �ڷβ����� �ʴ� �Ѱ����� ����) 

	R_Leg_y=abs(-sin(time)*30-30);  //�������Ƹ� ��������(abs���밪�� �����ν� ���Ƹ��� ������ ������ �ʴ� �Ѱ����� ����)
	L_Leg_y=abs(sin(time)*30-30);   //�������Ƹ� ��������(abs���밪�� �����ν� ���Ƹ��� ������ ������ �ʴ� �Ѱ����� ����)
	R_Leg_x=sin(time)*60;          //�����ٸ��� 60�� �������� �����̵� sin()�Լ��� ����Ͽ� �ֱ����� ������ ����
	L_Leg_x=-R_Leg_x;              //�����ٸ��� �����ٸ��ݴ�� 60�� �������� �����̵� sin()�Լ��� ����Ͽ� �ֱ����� ������ ����

	////////////////display////////////////

	cyl=gluNewQuadric(); //�Ǹ��� ��ü ����
	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT); //�ʱ�ȭ
	glMatrixMode(GL_MODELVIEW); //��� ����

	DrawGround();    //���� ȣ��
	glLoadIdentity();//CTM �ʱ�ȭ

	/*
	�κ��� �޸��鼭 ��,�ڷ� �ڶװŸ��� ���� Ʋ������ ���� ǥ�� 
	*/
	glRotatef(-230.0,0,1,0);//y������ �����
	glRotatef(abs(sin(time)*16),1,0,0);//x������ 16�� ���� ����Ʋ����(abs���밪�� �����ν� ��ü�� �ڷ� ������ �ʴ� �Ѱ����� ����)
	glRotatef(sin(time)*16,0,1,0); //y������ 16�� ���� ����Ʋ����, sin()�Լ��� ����Ͽ� �ֱ����� ������ ����

	/*
	�κ��� �޸��鼭 ��,�Ϸ� �����̴� ���� ǥ��
	*/
	float i=0;
	i=abs(sin(time)*0.08); //i������ ����
	glPushMatrix();// ó�� ���� ��ǥ �ٽ� ����
	glTranslatef(0.0,i,0); //���� i��ŭ �κ��� ��ü�� Y��������� ������.

	glTranslatef(0.0,0.5,0.0);//���� �κ��� ��ġ 
	DrawAndroid();
	glutSwapBuffers();
}

/*
�κ��� ���� ������ ���� ǥ���� �Լ�
*/
void Jap(){
	sndPlaySound(TEXT("C:\\sample3.wav"),SND_ASYNC|SND_NOSTOP);
	glLoadIdentity();//CTM �ʱ�ȭ
	/*
	�κ��� �⺻���� ������ ������ ������ �����ϴ� ��
	*/
	L_Arm_x=(-40)+sin(time2)*60;//���� ����� ���������� -40���¿��� sin()�Լ��� ����Ͽ� �ֱ����� ������ ����
 	R_Arm_x=(-80)-L_Arm_x;      //���� ����� ���������� -80���¿��� ���ʾ�� �������� �ݴ�� ����
	R_Arm_y=-abs(cos(time2)*80);  //�����ȶ� ��������(���� ���� ������ǥ�������Ͽ� ����� sin()�Լ��� �ݴ��� cos()�Լ� ���)
	L_Arm_y=-abs(-cos(time2)*80); //�����ȶ� ��������(���� ���� ������ǥ�������Ͽ� ����� sin()�Լ��� �ݴ��� cos()�Լ� ���)

	R_Leg_y=abs(-sin(time)*30-20);  //�������Ƹ� ��������(abs���밪�� �����ν� ���Ƹ��� ������ ������ �ʴ� �Ѱ����� ����)
	L_Leg_y=abs(sin(time)*30-20);   //�������Ƹ� ��������(abs���밪�� �����ν� ���Ƹ��� ������ ������ �ʴ� �Ѱ����� ����)
	R_Leg_x=sin(time)*30;          //�����ٸ��� 30�� �������� �����̵� sin()�Լ��� ����Ͽ� �ֱ����� ������ ����
	L_Leg_x=-R_Leg_x;              //�����ٸ��� �����ٸ��ݴ�� 30�� �������� �����̵� sin()�Լ��� ����Ͽ� �ֱ����� ������ ����

	////////////////display////////////////

	cyl=gluNewQuadric(); //�Ǹ��� ��ü ����
	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT); //�ʱ�ȭ
	glMatrixMode(GL_MODELVIEW); //��� ����

	DrawGround(); //���� ȣ��
	glLoadIdentity(); //CTM �ʱ�ȭ

	glRotatef(-230.0,0,1,0); //y��������� ȸ��

	glRotatef(sin(time)*10,0,0,1);//�κ��� ��,�� �ݵ� ǥ��(�¿�� 10�� ��ŭ �ֱ����� ������ ����)

	/*
	�κ��� ���� �����鼭 ��,�Ϸ� �����̴� ���� ǥ��
	*/
	float j=0;    
	j=abs(sin(time2)*0.085);// j�� ����
	glPushMatrix();// ó�� ���� ��ǥ �ٽ� ����
	glTranslatef(0.0,j,0); //���� j��ŭ �κ��� ��ü�� Y��������� ������.
	glTranslatef(0.0,0.5,0.0);//���� ��ġ 
	DrawAndroid();	
	glutSwapBuffers();
}

/*
�κ��� �����Ҷ� ũ�� ��ȯ�� ǥ���� �Լ�
*/
void ex()
{
	sndPlaySound(TEXT("C:\\sample5.wav"),SND_ASYNC|SND_NOSTOP);
	glLoadIdentity(); //CTM �ʱ�ȭ
	/*
	�κ��� �⺻���� ������ ������ ������ �����ϴ� ��
	*/
	L_Arm_x=(-40)+sin(time2)*60;//���� ����� ���������� -40���¿��� sin()�Լ��� ����Ͽ� �ֱ����� ������ ����
 	R_Arm_x=(-80)-L_Arm_x;      //���� ����� ���������� -80���¿��� ���ʾ�� �������� �ݴ�� ����
	R_Arm_y=-abs(cos(time2)*10);  //�����ȶ� ��������(���� ���� ������ǥ�������Ͽ� ����� sin()�Լ��� �ݴ��� cos()�Լ� ���)
	L_Arm_y=-abs(-cos(time2)*10);  //�����ȶ� ��������(���� ���� ������ǥ�������Ͽ� ����� sin()�Լ��� �ݴ��� cos()�Լ� ���)

	R_Leg_y=abs(-sin(time)*30-30);  //�������Ƹ� ��������(abs���밪�� �����ν� ���Ƹ��� ������ ������ �ʴ� �Ѱ����� ����)
	L_Leg_y=abs(sin(time)*30-30);  //�������Ƹ� ��������(abs���밪�� �����ν� ���Ƹ��� ������ ������ �ʴ� �Ѱ����� ����)
	R_Leg_x=sin(time)*60;           //�����ٸ��� 60�� �������� �����̵� sin()�Լ��� ����Ͽ� �ֱ����� ������ ����
	L_Leg_x=-R_Leg_x;              //�����ٸ��� �����ٸ��ݴ�� 60�� �������� �����̵� sin()�Լ��� ����Ͽ� �ֱ����� ������ ����

	////////////////display////////////////

	cyl=gluNewQuadric(); //�Ǹ��� ��ü ����
	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT); //�ʱ�ȭ
	glMatrixMode(GL_MODELVIEW); //��� ����

	glLoadIdentity(); //CTM �ʱ�ȭ
	glRotatef(-180,0,1,0); //y�� �������� ȸ��
	glRotatef(time6,0,0,1); //time6 ������ŭ z��������� ȸ��

	glScalef(0.4/(sin(time3)),0.4/(sin(time3)),0.4/(sin(time3))); //0.4�� ũ�⿡�� sin()�� ���� ũ�������� �ֱ������� ���Կ����� 
	
	glPushMatrix();// ó�� ���� ��ǥ �ٽ� ����															  //�־����� ��������µ��� ������ ǥ��
	glTranslatef(0.0,0.5,0.0);//���� ��ġ 
	DrawAndroid();	
	glutSwapBuffers();
}
/*
�迬�� ������ ����� ���ϴ� �Լ�
*/
void Show()
{
	sndPlaySound(TEXT("C:\\sample4.wav"),SND_ASYNC|SND_NOSTOP);
	glLoadIdentity(); //CTM �ʱ�ȭ

	/*
	�κ��� �⺻���� ������ ������ ������ �����ϴ� ��
	*/
	L_Arm_x=(-40)+sin(time2)*60;//���� ����� ���������� -40���¿��� sin()�Լ��� ����Ͽ� �ֱ����� ������ ����
	R_Arm_x=(-80)-L_Arm_x;       //���� ����� ���������� -80���¿��� ���ʾ�� �������� �ݴ�� ����
	R_Arm_y=-abs(cos(time2)*10);  //�����ȶ� ��������(���� ���� ������ǥ�������Ͽ� ����� sin()�Լ��� �ݴ��� cos()�Լ� ���)
	L_Arm_y=-abs(-cos(time2)*10); //�����ȶ� ��������(���� ���� ������ǥ�������Ͽ� ����� sin()�Լ��� �ݴ��� cos()�Լ� ���)

	R_Leg_y=abs(-sin(time)*30-30); //�������Ƹ� ��������(abs���밪�� �����ν� ���Ƹ��� ������ ������ �ʴ� �Ѱ����� ����)
	L_Leg_y=abs(sin(time)*30-30);  //�������Ƹ� ��������(abs���밪�� �����ν� ���Ƹ��� ������ ������ �ʴ� �Ѱ����� ����)
	R_Leg_x=sin(time)*60;          //�����ٸ��� 60�� �������� �����̵� sin()�Լ��� ����Ͽ� �ֱ����� ������ ����
	L_Leg_x=-R_Leg_x;             //�����ٸ��� �����ٸ��ݴ�� 60�� �������� �����̵� sin()�Լ��� ����Ͽ� �ֱ����� ������ ����

	////////////////display////////////////

	cyl=gluNewQuadric(); //�Ǹ��� ��ü ����
	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT); //�ʱ�ȭ
	glMatrixMode(GL_MODELVIEW); //��� ����

	DrawGround(); //���� ȣ��
	glLoadIdentity(); //CTM �ʱ�ȭ
	glRotatef(-230.0,0,1,0); //y��������� ȸ��

	/*
	�κ��� �ǰܵ��۽� ���� Ʋ������ ���� ǥ�� 
	*/
	glRotatef(sin(time)*7,0,0,1); //z��������� 7�� ���� ����Ʋ���� (sin()�Լ��� ����Ͽ� �ֱ����� ������ ����)
	glRotatef(sin(time)*7,0,1,0); //y������ 7�� ���� ����Ʋ���� (sin()�Լ��� ����Ͽ� �ֱ����� ������ ����)

	//�κ� ��ü ���� ����
	glTranslatef(0.0,0.18,0.0); //y������ �̵�
	glRotatef(80,1,0,0);        //x�� �������� ȸ��

	glTranslatef(0.0,0.5,0.0);//���� ��ġ 

	glPushMatrix( ); // ó�� ���� ��ġ

	DrawBody(0,0,0,0); // ���� �Լ� ȣ��

	glPopMatrix( ); // ó�� ���� ��ǥ�� ���� ����.
	glPushMatrix( );// ó�� ���� ��ǥ �ٽ� ����

	Drawneck(); // ���Լ� ȣ��

	glPopMatrix( ); // ó�� ���� ��ǥ�� ���� ����.
	glPushMatrix( );// ó�� ���� ��ǥ �ٽ� ����

	//�Ӹ� ��ġ ����
	glRotatef(-75,1,0,0); //x��������� ȸ��(�Ӹ��� �������� ������)
	glTranslatef(0.0,-0.02,0.0); //y������ �̵� (�Ӹ� ������)
	
	DrawHead(); // �Ӹ� ȣ��

	glPopMatrix( ); // ó�� ���� ��ǥ�� ���� ����.
	glPushMatrix( );// ó�� ���� ��ǥ �ٽ� ����

	//������ü�� ��ġ ����


	DrawR_Arm((R_Arm_y +30),1,0,0);  //������ȣ��
	DrawR_Hand(-(R_Arm_y  - 15),1,0,0); //�����ȶ�

	glPopMatrix( ); // ó�� ���� ��ǥ�� ���� ����.
	glPushMatrix( );// ó�� ���� ��ǥ �ٽ� ����

	//������ü�� ��ġ ����
	glTranslatef(0.0,-0.16,-0.04);//y��,z������ �̵�(������ ������)
	glRotatef(40,0,0,1);     //z�� �������� ȸ��

	DrawL_Arm((L_Arm_y +30),1,0,0);   //������ȣ��	
	DrawL_Hand( -(L_Arm_y  - 15),1,0,0);  //�����ȶ�

	glPopMatrix( ); // ó�� ���� ��ǥ�� ���� ����.
	glPushMatrix( );// ó�� ���� ��ǥ �ٽ� ����

	//������ü �ٸ� ��ġ ����
	glTranslatef(0.0,-0.45,-0.25);//y��,z������ �̵�(�����ٸ� ������)
	glRotatef(-90,1,0,0);  //x�� �������� ȸ��

	DrawL_Legs(-30,1,0,0);  //�����ٸ�
	DrawL_foot(10,1,0,0);  //�������Ƹ�		 

	glPopMatrix( ); // ó�� ���� ��ǥ�� ���� ����.
	glPushMatrix( );// ó�� ���� ��ǥ �ٽ� ����

	//������ü �ٸ� ��ġ ����
	glTranslatef(0.0,-0.5,-0.5);//y��,z������ �̵�(�����ٸ� ������)
	glRotatef(-90,1,0,0); //x�� �������� ȸ��

	DrawR_Legs(160,1,0,0);  //�����ٸ�
	DrawR_foot(R_Leg_y,1,0,0);  //�������Ƹ�		

	glPopMatrix( ); // ó�� ���� ��ǥ�� ���� ����.
	
	glutSwapBuffers( );
}
/*
�κ��� ������ ������ ����� ǥ���� �Լ�
*/
void Rocket(){
	sndPlaySound(TEXT("C:\\sample2.wav"),SND_ASYNC|SND_NOSTOP);
	glLoadIdentity(); //CTM �ʱ�ȭ

	/*90�� ������ ���� ������ ���δ�*/
	L_Arm_x=-90; 
	R_Arm_x=-90;

	R=2*abs(-sin(time2)*0.2-0.2)+0.2;//���� ���� ������ ����
	                                 //abs���밪���� ������ �������� ������ ����.
	                                 //+0.2�� ���� ������ ó����ġ ����. 2*�� ���� ������ ������ �Ÿ�����.
	                                 //sin()�Լ��� ���� �ֱ����� ������ ����.
	                                                        
	R2=2*abs(sin(time2)*0.2-0.2)+0.2;//���� ���� ������ ���� 
	                                 //abs���밪���� ������ �������� ������ ����.
	                                 //+0.2�� ���� ������ ó����ġ ����. 2*�� ���� ������ ������ �Ÿ�����.
                                     //sin()�Լ��� ���� �ֱ����� ������ ����.

	R_Leg_y=abs(-sin(time)*30-30);  //�������Ƹ� ��������(abs���밪�� �����ν� ���Ƹ��� ������ ������ �ʴ� �Ѱ����� ����)
	L_Leg_y=abs(sin(time)*30-30);   //�������Ƹ� ��������(abs���밪�� �����ν� ���Ƹ��� ������ ������ �ʴ� �Ѱ����� ����)
	R_Leg_x=sin(time)*60;          //�����ٸ��� 60�� �������� �����̵� sin()�Լ��� ����Ͽ� �ֱ����� ������ ����
	L_Leg_x=-R_Leg_x;              //�����ٸ��� �����ٸ��ݴ�� 60�� �������� �����̵� sin()�Լ��� ����Ͽ� �ֱ����� ������ ����

	////////////////display////////////////

	cyl=gluNewQuadric(); //�Ǹ��� ��ü ����
	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT); //�ʱ�ȭ
	glMatrixMode(GL_MODELVIEW); //��� ����

	DrawGround(); //���� ȣ��

	glLoadIdentity(); //CTM �ʱ�ȭ
	glPushMatrix();// ó�� ���� ��ǥ �ٽ� ����
	glRotatef(-230.0,0,1,0); //y�� �������� ȸ��

	/*
	�κ��� ������ �� �� ��,��,��,��� ���� Ʈ�� ����� ����
	*/
	glRotatef(-abs(sin(time)*8),1,0,0); //x������ 8�� ���� ����Ʋ����(abs���밪�� �����ν� ��ü�� �ڷ� ������ �ʴ� �Ѱ����� ����)
	glRotatef(sin(time)*7,0,0,1);       //z������ 7�� ���� ����Ʋ����, sin()�Լ��� ����Ͽ� �ֱ����� ������ ����

	/*
	�κ��� ������ ������ ���� ƨ��� ����� ǥ��
	*/
	float i=0;    
	i=abs(sin(time)*0.08); //i�� ���� 
	glTranslatef(0.0,i,0); //���� i��ŭ �̵�
	glTranslatef(0.0,0.5,0.0);//���� ��ġ 
	DrawAndroid();		
	glutSwapBuffers();
}

/*
Ű���� �ݹ� ���� �Լ�
w�� ������ wire ����, s�� ������ solid ����, q�� ������ ���Ḧ ǥ��
*/
void MyKeyboard(unsigned char KeyPressed,int x,int y){
	switch (KeyPressed){
		case 'w':
			flag=1; 
			break;
		case 's':
			flag=0;	
			break;
		case 'q':
			key=6;
			break;
	}
}

/*
key ���� ���� �뷡�� �귯���´�.
�뷡 ����� sndPlaySound �Լ��� �귯������ �����Ͽ���.
�� key ���� ���� �� ����� ���Ѵ�.
������ ���������� �ʿ��ϸ� ��μ�����
sndPlaySound(TEXT("�������ϰ��") �� �Է��ϸ� �ȴ�.
*/
void MyDisplay(){
	if(key==RUN){//�κ��� �޸���		
		Run();
		glPopMatrix( );
	}
	else if(key==JAP){//�κ��� ���� ���� ��
		Jap();
		glPopMatrix( );		
	}
	else if(key==ROCKET){//�κ��� ������ �߻��Ҷ�
		Rocket();
		glPopMatrix( );
	}
	else if(key==YUNA){//�κ��� �迬�� ������ ����� ���� ��
		Show();
		glPopMatrix( );
	}
	else if(key==5){//������ ���õ��� ��
		sndPlaySound(NULL,SND_ASYNC);
	}
	else if(key==EXIT){//���ᰡ ���õ��� ��
		ex();
		glPopMatrix( );
	}
}
/*
Ÿ�̸� �Լ�
�� ��鸶�� ���� ǥ���� �ٸ��� �α� ���� ����� �ð� �������� ������.
*/
void MyTimer(int Value){
	time=time+0.1;//�޸��� ���� Ÿ�̸� ����
	time2=time2+0.5;//���� ������ ���� Ÿ�̸� ����
	time3=time3+0.01;//������ ������ ���� Ÿ�̸� ����, ����� �κ��� ��۹�� ���ư��� �ϱ� ���� ���� Ÿ�̸� ����
	time4=time4+1.0;//�迬�� ���� ����� ���Ҷ� ���� Ÿ�̸� ����
	glutPostRedisplay();
	glutTimerFunc(40,MyTimer,1);
}
/*
���콺 ������ Ŭ���� �ؼ� �޴��� �����ϸ� ����Ǵ� �Լ�.
�⺻������ ����� ��ȯ�Ҷ� ���콺 �ݹ��� �̿��Ͽ� ��ȯ�ϵ��� �����Ͽ���.
*/
void MyMainMenu(int entryID){ //�޴�
	key=entryID;
}

int main(int argc, char** argv){
	glutInit(&argc, argv);//�ʱ�ȭ
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE | GLUT_DEPTH);//���÷��� ��� ����
	glutInitWindowSize(800,800);//������ ũ�� ����
	glutInitWindowPosition(0,0);//������ �ʱ� ��ġ ����
	glutCreateWindow("2�� ����");//������ ����
	glInit(); // ���� �ʱ�ȭ
	GLint MyMainMenuID = glutCreateMenu(MyMainMenu);//�޴��߰�
	glutAddMenuEntry("�ϴ�~",1);//�κ��� �޸��� ��� �޴� �߰�
	glutAddMenuEntry("����~",2);//�κ��� �쳯���� ��� �޴� �߰�
	glutAddMenuEntry("�л�~",3);//�κ��� ������ġ�� ������ ��� �޴� �߰�
	glutAddMenuEntry("����~",4);//�κ��� �ǰܽ��������ϴ� ��� �޴� �߰�
	glutAddMenuEntry("����",5);//�κ��� �ϴ� ���� ���߰� �ϴ� �޴� �߰�
	glutAttachMenu(GLUT_RIGHT_BUTTON);//�����ʸ��콺Ŭ���ø޴��˾�
	glutKeyboardFunc(MyKeyboard); //Ű���� �ݹ�
	glutTimerFunc(40,MyTimer,1); //Ÿ�̸� �Լ�
	glutDisplayFunc(MyDisplay); //���÷���
	glutMainLoop( );
	return 0;
}