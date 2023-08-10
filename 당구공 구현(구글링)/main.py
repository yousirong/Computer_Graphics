from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *
import math
import numpy as np
import random
from PIL import Image

Window_Width = 800
Window_Height = 600

# Light Properties
Ld = [1, 1, 1, 0]
Ls = [1, 1, 1, 0]
La = [0.5, 0.5, 0.5, 0]
# Material Properties
Md = [1, 1, 0, 1]
Ms = [1, 1, 1, 1]
Ma = [0.5, 0.5, 0.5, 0]
shininess = [80]


isLightOn_0 = True
isRotateCamera = True
rotateSpeed = math.pi/500

ballMove = False
ballSpeed = 0
ballSpeedInit = 1700 / 10000
ballMoveAngle = 0
ballFriction = 3 / 10000

cameraPosX = 15
cameraPosY = 10
cameraPosZ = 25

pool_camera_dist = 40
pool_camera_y_angle = math.pi/6
pool_camera_x_angel = math.pi/6

Color_Wall = [0.4, 0.7, 0.9]
Color_Floor = [0.3, 0.3, 0.7]
Color_Box = [0.5, 0.9, 0.9]
Color_Ball_1 = [0.7, 0.3, 0.3]

poolwall = [
    [[-10, 1, -20], [10, 1, -20]]
    , [[10, 1, -20], [10, 1, 20]]
    , [[10, 1, 20], [-10, 1, 20]]
    , [[-10, 1, 20], [-10, 1, -20]]
]

ballPos_x = 0
ballPos_y = 1
ballPos_z = 0

def loadImage(imageName) :
    img = Image.open(imageName)
    img_data = np.array(list(img.getdata()), np.uint16)
    return img.size[0], img.size[1], img_data

wallix, walliy, wallimg = loadImage("wall2.jpg")
floorix, flooriy, floorimg = loadImage("floor.jpg")



def computeNormal(p1, p2, p3):
    u = np.array([p2[i] - p1[i] for i in range(0, 3)])
    v = np.array([p3[i] - p1[i] for i in range(0, 3)])
    N = np.cross(u, v)
    N = N / np.linalg.norm(N)
    return N


def drawVerts(v, f, color_vector):
    glColor3fv(color_vector)
    glBegin(GL_QUADS)
    for i in range(len(f)):
        p1, p2, p3, p4 = f[i][0], f[i][1], f[i][2], f[i][3]
        N = computeNormal(v[p1], v[p2], v[p3])
        glNormal3fv(N)
        glVertex3fv(v[p1])
        glVertex3fv(v[p2])
        glVertex3fv(v[p3])
        glVertex3fv(v[p4])
    glEnd()


def loadMesh(filename):
    print(filename)
    with open(filename, "rt") as mesh:
        nV = int(next(mesh))
        verts = [[0, 0, 0] for idx in range(nV)]
        for i in range(0, nV):
            verts[i][0], verts[i][1], verts[i][2] = [float(x) for x in next(mesh).split()]
        nF = int(next(mesh))
        faces = [[0, 0, 0, 0] for idx in range(nF)]
        for i in range(0, nF):
            faces[i][0], faces[i][1], faces[i][2], faces[i][3] = [int(x) for x in next(mesh).split()]
    return verts, faces


def drawPoolBox():
    drawVerts(PoolBox_V, PoolBox_F, Color_Box)


def drawWall():
    glColor3fv([1,1,1])
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, wallix, walliy, 0, GL_RGB, GL_UNSIGNED_BYTE, wallimg)

    glBegin(GL_QUADS)
    glTexCoord2fv([0, 1])
    glVertex3fv([-50, 50, 50])
    glTexCoord2fv([1, 1])
    glVertex3fv([-50, 50, -50])
    glTexCoord2fv([1, 0])
    glVertex3fv([-50, -50,-50])
    glTexCoord2fv([0, 0])
    glVertex3fv([-50, -50, 50])

    glTexCoord2fv([0, 1])
    glVertex3fv([50, 50, 50])
    glTexCoord2fv([1, 1])
    glVertex3fv([50, 50, -50])
    glTexCoord2fv([1, 0])
    glVertex3fv([50, -50,-50])
    glTexCoord2fv([0, 0])
    glVertex3fv([50, -50, 50])

    glTexCoord2fv([0, 1])
    glVertex3fv([-50, -50, -50])
    glTexCoord2fv([1, 1])
    glVertex3fv([50, -50, -50])
    glTexCoord2fv([1, 0])
    glVertex3fv([50, 50, -50])
    glTexCoord2fv([0, 0])
    glVertex3fv([-50, 50, -50])

    glTexCoord2fv([0, 1])
    glVertex3fv([-50, -50, 50])
    glTexCoord2fv([1, 1])
    glVertex3fv([50, -50, 50])
    glTexCoord2fv([1, 0])
    glVertex3fv([50, 50, 50])
    glTexCoord2fv([0, 0])
    glVertex3fv([-50, 50, 50])

    glEnd()



def drawFloor():
    glColor3fv([1,1,1])
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, floorix, flooriy, 0, GL_RGB, GL_UNSIGNED_BYTE, floorimg)

    glBegin(GL_QUADS)
    glTexCoord2fv([0, 1])
    glVertex3fv([-60, -5, -60])
    glTexCoord2fv([1, 1])
    glVertex3fv([60, -5, -60])
    glTexCoord2fv([1, 0])
    glVertex3fv([60, -5, 60])
    glTexCoord2fv([0, 0])
    glVertex3fv([-60, -5, 60])

    glEnd()

def drawPoolRoom():
    drawPoolBox()
    drawFloor()
    drawWall()

def CalcDistWallBall(wall, ball_x, ball_y, ball_z):
    if(wall[0][1] != ball_y) : return
    wall_dx = wall[0][0] - wall[1][0]
    wall_dz = wall[0][2] - wall[1][2]
    a = wall_dz
    b = wall_dx
    c = wall_dz * wall[0][0] - wall_dx * wall[0][2]
    dist = (a * ball_x + b * ball_z + c) / math.sqrt(a*a + b*b)
    return dist

def CalcBallPos():
    global ballPos_x, ballPos_y, ballPos_z, ballSpeed, ballMoveAngle, ballFriction, ballMove, poolwall
    if(ballMove):
        ballSpeed -= ballFriction
        if(ballSpeed <= 0):
            ballMove = False
            return
        ballPos_x += ballSpeed * math.cos(ballMoveAngle)
        ballPos_z += ballSpeed * math.sin(ballMoveAngle)
        for i in range(0, len(poolwall)) :
            dist = CalcDistWallBall(poolwall[i], ballPos_x, ballPos_y, ballPos_z)
            if(dist >= -1.05) :
                if(i == 0 or i == 2):
                    ballMoveAngle *= -1
                if(i == 1 or i == 3):
                    ballMoveAngle += math.pi
                    ballMoveAngle *= -1



def drawPoolBall():
    global ballPos_x, ballPos_y, ballPos_z
    glPushMatrix()
    glTranslatef(ballPos_x, ballPos_y, ballPos_z)
    glColor3fv(Color_Ball_1)
    glutSolidSphere(1, 10, 10)
    glPopMatrix()



# initialization
def GLinit():
    # 색상,z-buffer, 조명 설정
    glClearColor(0, 0, 0, 0)
    glEnable(GL_COLOR_MATERIAL)
    glEnable(GL_DEPTH_TEST)
    glEnable(GL_LIGHTING)
    glEnable(GL_LIGHT0)
    glLightfv(GL_LIGHT0, GL_DIFFUSE, Ld)
    glLightfv(GL_LIGHT0, GL_AMBIENT, La)
    glLightfv(GL_LIGHT0, GL_SPECULAR, Ls)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, Md)
    glMaterialfv(GL_FRONT, GL_SPECULAR, Ms)
    glMaterialfv(GL_FRONT, GL_AMBIENT, Ma)
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess)

    glEnable(GL_TEXTURE_2D)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR)



def keyboardEvent(key, x, y):
    global isRotateCamera, pool_camera_dist, ballMove, ballMoveAngle, ballSpeed, ballSpeedInit
    global isLightOn_0
    if (key == b'n' or key == b'N'):
        if(isLightOn_0 == False):
            glEnable(GL_LIGHT0)
            isLightOn_0 = True
    if(key == b'f' or key == b'F'):
        if (isLightOn_0):
            glDisable(GL_LIGHT0)
            isLightOn_0 = False

    if(key == b'i' or key == b'I'):
        if(pool_camera_dist >= 10):
            pool_camera_dist -= 1
    if(key == b'o' or key == b'O'):
        if(pool_camera_dist <= 50):
            pool_camera_dist += 1
    if(key == b'r' or key == b'R'):
        if(isRotateCamera):
            isRotateCamera = False
        else:
            isRotateCamera = True

    if(key == b'h' or key == b'H'):
        if(ballMove == False):
            ballMoveAngle = random.random() * 2 * math.pi
            ballSpeed = ballSpeedInit
            ballMove = True


def CalcCameraPos():
    global pool_camera_dist, pool_camera_x_angel, pool_camera_y_angle

    x = pool_camera_dist * math.cos(pool_camera_y_angle) *math.cos(pool_camera_x_angel)
    y = pool_camera_dist * math.sin(pool_camera_y_angle)
    z = pool_camera_dist * math.cos(pool_camera_y_angle) *math.sin(pool_camera_x_angel)

    return x, y, z



# display callback
def display():
    global cameraPosX, cameraPosY, cameraPosZ, pool_camera_x_angel, rotateSpeed
    if(isRotateCamera):
        pool_camera_x_angel += rotateSpeed
        if(rotateSpeed >= math.pi):
            rotateSpeed = 0
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    # CAMERA SETTING
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    gluPerspective(60.0, Window_Width / Window_Height, 0.1, 1000)
    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()

    cameraPosX, cameraPosY, cameraPosZ = CalcCameraPos()
    gluLookAt(cameraPosX, cameraPosY, cameraPosZ, 0, 0, 0, 0, 1, 0)

    glLightfv(GL_LIGHT0, GL_POSITION, [-30, +30, +30, 1])

    # draw vertices
    drawPoolRoom()
    CalcBallPos()
    drawPoolBall()

    glFlush()

#######################################################
PoolBox_V, PoolBox_F = loadMesh("PoolBox.txt")

# windowing
glutInit(sys.argv)
glutInitDisplayMode(GLUT_SINGLE | GLUT_DEPTH | GLUT_RGBA)
glutInitWindowSize(Window_Width, Window_Height)
glutInitWindowPosition(10, 10)
glutCreateWindow(b"Light on Mesh in file ")
GLinit()

# register callbacks
glutDisplayFunc(display)
glutIdleFunc(display)
glutKeyboardFunc(keyboardEvent)

# enter main-loop
glutMainLoop()
