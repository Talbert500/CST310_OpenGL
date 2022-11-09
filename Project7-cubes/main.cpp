// This program is a flyby around the RGB color cube.  One intersting note
// is that because the cube is a convex polyhedron and it is the only thing
// in the scene, we can render it using backface culling only. i.e., there
// is no need for a depth buffer.

#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cmath>

// The cube has opposite corners at (0,0,0) and (1,1,1), which are black and
// white respectively.  The x-axis is the red gradient, the y-axis is the
// green gradient, and the z-axis is the blue gradient.  The cube's position
// and colors are fixed.
float x;
float y;
float z;
float rx = 0.0f;
float ry = 0.0f;
bool move = true;
bool bounce = true;

double cube1 = 1;
double cube2 = -1;
double cube3 = 0;
double cube1Position = 0;
double cube2Position = 0;
double cube3Position = 0;

namespace Cube {

const int NUM_VERTICES = 8;
const int NUM_FACES = 6;

GLint vertices[NUM_VERTICES][3] = {
  {0, 0, 0}, {0, 0, 1}, {0, 1, 0}, {0, 1, 1},
  {1, 0, 0}, {1, 0, 1}, {1, 1, 0}, {1, 1, 1}};

GLint faces[NUM_FACES][4] = {
  {1, 5, 7, 3}, {5, 4, 6, 7}, {4, 0, 2, 6},
  {3, 7, 6, 2}, {0, 1, 3, 2}, {0, 4, 5, 1}};

GLfloat vertexColors[NUM_VERTICES][3] = {
  {0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 1.0, 0.0}, {0.0, 1.0, 1.0},
  {1.0, 0.0, 0.0}, {1.0, 0.0, 1.0}, {1.0, 1.0, 0.0}, {1.0, 1.0, 1.0}};

void draw(GLfloat x, double pos) {
    //below two lines
    glPushMatrix();
    glTranslatef(x, pos, 0);
    
  glBegin(GL_QUADS);
  for (int i = 0; i < NUM_FACES; i++) {
    for (int j = 0; j < 4; j++) {
      glColor3fv((GLfloat*)&vertexColors[faces[i][j]]);
      glVertex3iv((GLint*)&vertices[faces[i][j]]);
    }
  }
  glEnd();
  glPopMatrix();
}
}

// Display and Animation. To draw we just clear the window and draw the cube.
// Because our main window is double buffered we have to swap the buffers to
// make the drawing visible. Animation is achieved by successively moving our
// camera and drawing. The function nextAnimationFrame() moves the camera to
// the next point and draws. The way that we get animation in OpenGL is to
// register nextFrame as the idle function; this is done in main().
void display() {
  glClear(GL_COLOR_BUFFER_BIT);
    if (cube1Position > 10)
      cube1 = -0.1;
    else if (cube1Position < -10)
      cube1 = 0.1;
    if (cube2Position > 10)
      cube2 = -0.1;
    else if (cube2Position < -10)
      cube2 = 0.1;
    if (cube3Position > -10)
      cube3 = -0.1;
    else if (cube3Position < -10)
      cube3 = 0.1;

    if (bounce)
    {
      cube1Position += cube1;
      cube2Position += cube2;
      cube3Position += cube3;
    }
    
    glBegin(GL_QUADS);
    {
      glColor3f(1, 1, 1);

      glVertex3f(-5, 5, 5);
      glVertex3f(-5, 5, -5);
      glVertex3f(5, 5, -5);
      glVertex3f(5, 5, 5);

      glVertex3f(-5, -5, 5);
      glVertex3f(-5, -5, -5);
      glVertex3f(5, -5, -5);
      glVertex3f(5, -5, 5);
    }
    glEnd();
    
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(1.0f,1.0f,1.0f);
    glRotatef(rx, 0.5f, 0.0f, 0.0f);
    glRotatef(ry, 0.0f, 0.5f, 0.0f);
    Cube::draw(0, 0);
    Cube::draw(2, cube1Position);
    Cube::draw(-2, cube2Position);
    Cube::draw(1, cube3Position);
    glPopMatrix();
  glFlush();
  glutSwapBuffers();
}

// We'll be flying around the cube by moving the camera along the orbit of the
// curve u->(8*cos(u), 7*cos(u)-1, 4*cos(u/3)+2).  We keep the camera looking
// at the center of the cube (0.5, 0.5, 0.5) and vary the up vector to achieve
// a weird tumbling effect.
void timer(int v) {
  static GLfloat u = 0.0;
    if(move){
        u += 0.01;
    }
  glLoadIdentity();
  gluLookAt(8*cos(u), 7*cos(u)-1, 4*cos(u/3)+2, .5, .5, .5, cos(u), 1, 0);
  glutPostRedisplay();
  glutTimerFunc(1000/60.0, timer, v);
}

// When the window is reshaped we have to recompute the camera settings to
// match the new window shape.  Set the viewport to (0,0)-(w,h).  Set the
// camera to have a 60 degree vertical field of view, aspect ratio w/h, near
// clipping plane distance 0.5 and far clipping plane distance 40.
void reshape(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, GLfloat(w) / GLfloat(h), 0.5, 40.0);
  glMatrixMode(GL_MODELVIEW);
}

// Application specific initialization:  The only thing we really need to do
// is enable back face culling because the only thing in the scene is a cube
// which is a convex polyhedron.
void init() {
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
}

void keyPressed(unsigned char key, int xx, int yy){
    float fraction = 0.5f;
    if(key == 27)//escape
        exit(0);
    if(key == 115)//S
        move = false;
    if(key == 99)//C
        move = true;
    if(key == 117)//U
        y += fraction;
    if(key == 100)//D
        y -= fraction;
    if(key == 108)//L
        x-= fraction;
    if(key == 114)//R
        bounce = false;
    if(key == 61)//+
        z += fraction;
    if(key == 45)//-
        z -= fraction;
}

// The usual main for a GLUT application.
int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(500, 500);
  glutCreateWindow("The RGB Color Cube");
  glutReshapeFunc(reshape);
  glutTimerFunc(100, timer, 0);
  glutDisplayFunc(display);
  glutKeyboardFunc(keyPressed);
  init();
  glutMainLoop();
}

