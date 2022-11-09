#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cstdlib>

GLfloat angle = 45.0f;
int refreshmill = 1;
bool spin = true;
//void keyboard(unsigned char key, int x, int y);
float x;
float y;
float z;
float rx = 0.0f;
float ry = 0.0f;

void initGL(){

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

}

// Define a 2 x 2 red and yellow checkered pattern using RGB colors.
#define red {0xff, 0x00, 0x00}
#define yellow {0xff, 0xff, 0x00}
#define magenta {0xff, 0, 0xff}
GLubyte texture[][3] = {
    red, yellow,
    yellow, red,
};

void timer(int value){
    glutPostRedisplay();
    glutTimerFunc(refreshmill, timer, 0);
}
// Fixes up camera and remaps texture when window reshaped.
void reshape(int width, int height) {
  glViewport(0, 0, (GLsizei)width, (GLsizei)height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(80, (GLfloat)width/(GLfloat)height, 1, 40);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(2, -1, 5, 0, 0, 0, 0, 1, 0);
  glEnable(GL_TEXTURE_2D);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexImage2D(GL_TEXTURE_2D,
               0,                    // level 0
               3,                    // use only R, G, and B components
               2, 2,                 // texture has 2x2 texels
               0,                    // no border
               GL_RGB,               // texels are in RGB format
               GL_UNSIGNED_BYTE,     // color components are unsigned bytes
               texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

// Draws three textured triangles.  Each triangle uses the same texture,
// but the mappings of texture coordinates to vertex coordinates is
// different in each triangle.
void display() {
  glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    glRotatef(angle, 0.0f, 0.0f, -1.0f);
    glRotatef(angle, 0.0f, 0.0f, -1.0f);
    glTranslatef(x, y, z);
    glScalef(1.0f,1.0f,1.0f);
    glRotatef(rx, 0.5f, 0.0f, 0.0f);
    glRotatef(ry, 0.0f, 0.5f, 0.0f);
  glBegin(GL_TRIANGLES);
    glTexCoord2f(0.5, 1.0);    glVertex2f(-3, 3);
    glTexCoord2f(0.0, 0.0);    glVertex2f(-3, 0);
    glTexCoord2f(1.0, 0.0);    glVertex2f(0, 0);

    glTexCoord2f(4, 8);        glVertex2f(3, 3);
    glTexCoord2f(0.0, 0.0);    glVertex2f(0, 0);
    glTexCoord2f(8, 0.0);      glVertex2f(3, 0);

    glTexCoord2f(5, 5);        glVertex2f(0, 0);
    glTexCoord2f(0.0, 0.0);    glVertex2f(-1.5, -3);
    glTexCoord2f(4, 0.0);      glVertex2f(1.5, -3);
  glEnd();
    glPopMatrix();
    glutSwapBuffers();
    if(spin)
            angle += 2.0;
  //glFlush();
}

void processSpecialKeys(int key, int xx, int yy){
    float fraction = 0.7f;

    switch(key){
        case GLUT_KEY_LEFT :
            x-= fraction;
            break;
        case GLUT_KEY_RIGHT :
            x += fraction;
            break;
        case GLUT_KEY_UP :
            y += fraction;
            break;
        case GLUT_KEY_DOWN :
            y -= fraction;
            break;
    }
}

void keyPressed(unsigned char key, int xx, int yy){
    float fraction = 0.5f;
    if(key == 27)//escape
        exit(0);
    if(key == 112)//P
        spin = false;
    if(key == 99)//C
        spin = true;
    if(key == 117)//U
        y += fraction;
    if(key == 100)//D
        y -= fraction;
    if(key == 108)//L
        x-= fraction;
    if(key == 114)//R
        x += fraction;
    if(key == 61)//+
        z += fraction;
    if(key == 45)//-
        z -= fraction;
}

// Initializes GLUT and enters the main loop.
int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(520, 390);
  glutCreateWindow("Textured Triangles");
  glutDisplayFunc(display);
  glutKeyboardFunc(keyPressed);
  glutSpecialFunc(processSpecialKeys);
  glutReshapeFunc(reshape);
  initGL();
  glutTimerFunc(0, timer, 0);
  glutMainLoop();
}
