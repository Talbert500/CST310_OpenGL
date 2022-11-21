#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cmath>

//Variable declarations for cube
double cube = 0;
double cubePosition = 0;

//function for creating cubes
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

//draw cube
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
// everthing will be shown to us on the z-axis.  We do this by rotating 90
// degrees about the x-axis which brings (0,0,1) to (0,1,0).
void mySolidSphere(GLfloat radius, int slices, int stacks) {
  glPushMatrix();
  glRotatef(90.0, 1.0, 0.0, 0.0);
  glutSolidSphere(radius, slices, stacks);
  glPopMatrix();
}

// there will be two variables that we will be keep track of the current
// In our solar system simulation we keep track of the current "turn" and
// current "rotate" in global variables.  Actually we just make the planet go
// around the sun in increments of 5 degrees (the "turn") and rotate the
// planet on its own axis in increments of 10 degrees (the "rotate").
static int turn = 0, rotate = 0;

// As usual, the routine to display the current state of the system is
// bracketed with a clearing of the window and a glFlush call.  Immediately
// within those calls the drawing code itself is bracketed by pushing and
// popping the current transformation.  And also as usual, we are assuming the
// current matrix mode is GL_MODELVIEW.  We finish with a SwapBuffers call
// because we'll animate.
void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (cubePosition > 10)
      cube = -0.1;
    else if (cubePosition < -10)
  glPushMatrix();

  // Draw a red sphere
  glColor3f(1.0, 0.0, 0.0);
  mySolidSphere(5.0, 15, 15);

  // Draw a blue sphere
  glRotatef((GLfloat)turn, 0.0, 1.0, 0.0);
  glTranslatef (2.0, 0.0, 0.0);
  glRotatef((GLfloat)rotate, 0.0, 1.0, 0.0);
  glColor3f(0.0, 0.0, 1.0);
  mySolidSphere(5, 15, 15);
  glColor3f(1, 1, 1);
  glBegin(GL_LINES);
    glVertex3f(0, -0.3, 0);
    glVertex3f(0, 0.3, 0);
  glEnd();

  Cube::draw(2, cubePosition);
  glPopMatrix();
  glFlush();
  glutSwapBuffers();
}

/*The moving camera route, which with the "turn" . To animate we have function next AnimationFrame(), which as a idle function. It increments the value of u (to "move" the camera), ticks off another portion of the rotate and turn, then reorients the camera and refreshes the display.*/

static GLfloat u = 0.0;                 // curve parameter for cube position
static GLfloat du = 0.1;                // amt to increment u each frame

void timer(int v) {
  u += du;
  turn = (rotate + 1) % 500;
  rotate = (turn + 2) % 500;
  glLoadIdentity();
  gluLookAt(20*cos(u/8.0)+12,5*sin(u/8.0)+1,10*cos(u/8.0)+2, 0,0,0, 0,1,0);
  glutPostRedisplay();
  glutTimerFunc(1000/60, timer, v);
}

// Reset the projection transformation whenever the window is
// reshaped.  This is done (of course) by setting the current matrix mode
// to GL_PROJECTION and then setting the matrix.  It is easiest to use the
// perspective-projection-making matrix from the GL utiltiy library.  Here
// we set a perspective camera with a 30-degree vertical field of view,
// an aspect ratio to perfectly map into the system window, a near clipping
// plane distance of 5.0 and a far clipping distance of 90.0.  The last
// thing done is to reset the current matrix mode to GL_MODELVIEW, as
// that is expected in all the calls to display().
void reshape(GLint w, GLint h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(30.0, (GLfloat)w/(GLfloat)h, 5.0, 90.0);
  glMatrixMode(GL_MODELVIEW);
}

// The usual main() for a GLUT application.
int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(800, 600);
  glutCreateWindow("Two Balls");
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutTimerFunc(100, timer, 0);
  glEnable(GL_DEPTH_TEST);
  glutMainLoop();
}
