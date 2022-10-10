#include <GL/glut.h>
 
GLfloat rotateAll = 0.1f; 
int refreshMills = 15;  
float x;
float y;
float z;
float rx = 0.0f;
float ry = 0.0f;

void initGL() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   glClearDepth(1.0f);                   // Set background depth to farthest
   glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
   glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
   glShadeModel(GL_SMOOTH);   // Enable smooth shading
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}

void renderScene(void)
{
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glTranslatef(-60.5f + x, -35.0f + y, -80.0f + z);
glScalef(.4,.4f,1.0f);
glRotatef(rx, 0.5f, 0.0f, 0.0f);
glRotatef(ry, 0.0f, 0.5f, 0.0f);






glBegin(GL_QUADS);
//background
glColor3f(.80f,.78f, .74f);
glVertex3f(22.0f,180.0f, 0.0f);
glVertex3f(278.0f,180.0f, 0.0f);
glVertex3f(277.0f,2.0f, 0.0f);
glVertex3f(22.0f,1.0f, 0.0f);


//Window Wall
//grey
glColor3f(.73f,.72f, .70f);
	//top left
	glVertex3f(173.0f,168.0f, 0.0f);
	//bottom left
	glVertex3f(173.0f,68.0f, 0.0f);
	//bottom right
	glVertex3f(255.0f,38.0f, 0.0f);
	//top right
	glVertex3f(255.0f,168.0f, 0.0f);
      //Window Pane
      //blue
      glColor3f(.4f,.77f, 1.0f);
      
            //top left
            glVertex3f(180.0f,121.0f, 0.0f);
            //bottm left
            glVertex3f(180.0f,70.0f, 0.0f);
            //bottom right
            glVertex3f(209.0f,60.0f, 0.0f);
            //top right
            glVertex3f(209.0f,116.0f, 0.0f);

            glVertex3f(180.0f,167.0f, 0.0f);
            glVertex3f(180.0f,129.0f, 0.0f);
            glVertex3f(209.0f,124.0f, 0.0f);
            glVertex3f(209.0f,167.0f, 0.0f);

            //top left
            glVertex3f(215.0f,167.0f, 0.0f);
            //bottom left
            glVertex3f(215.0f,124.0f, 0.0f);
            //bottom right
            glVertex3f(251.0f,118.0f, 0.0f);
            //top right
            glVertex3f(251.0f,167.0f, 0.0f);

            glVertex3f(215.0f,116.0f, 0.0f);
            glVertex3f(215.0f,60.0f, 0.0f);
            glVertex3f(251.0f,47.0f, 0.0f);
            glVertex3f(251.0f,111.0f, 0.0f);

//CHAIR
//BROWN
glColor3f(0.61f,0.44f,0.32f);

      glVertex3f(190.0f,92.0f, 0.0f);
      glVertex3f(202.0f,90.0f, 0.0f);
      //bottom Right
      glVertex3f(201.0f,69.0f, 0.0f);
      //Top right
      glVertex3f(189.0f,69.0f, 0.0f);
      
      //base
      glVertex3f(190.0f,75.0f, 0.0f);
      glVertex3f(172.0f,70.0f, 0.0f);
      glVertex3f(184.0f,63.0f, 0.0f);
      glVertex3f(201.0f,69.0f, 0.0f);
      
      //LEG CHAIR
            //top right
            glVertex3f(202.0f,90.0f, 0.0f);
            glVertex3f(202.0f,51.0f, 0.0f);
            glVertex3f(201.0f,51.0f, 0.0f);
            glVertex3f(201.0f,90.0f, 0.0f);
            //bottom right
            glVertex3f(184.0f,65.0f, 0.0f);
            glVertex3f(184.0f,45.0f, 0.0f);
            glVertex3f(185.0f,45.0f, 0.0f);
            glVertex3f(185.0f,65.0f, 0.0f);
            //bottom left
            glVertex3f(173.0f,70.0f, 0.0f);
            glVertex3f(173.0f,51.0f, 0.0f);
            glVertex3f(172.0f,51.0f, 0.0f);
            glVertex3f(172.0f,70.0f, 0.0f);


//Lamp
glColor3f(0.84,0.84,0.84);
glVertex3f(40.0f,129.0f, 0.0f);
glVertex3f(33.0f,108.0f, 0.0f);
glVertex3f(70.0f,109.0f, 0.0f);
glVertex3f(52.0f,130.0f, 0.0f);
//Lamp stand
glColor3f(0.15,0.15,0.15);
glVertex3f(52.0f,107.0f, 0.0f);
glVertex3f(52.0f,50.0f, 0.0f);
glVertex3f(50.0f,50.0f, 0.0f);
glVertex3f(50.0f,107.0f, 0.0f);

// glVertex3f(101.0f,54.0f, 0.0f);
// glVertex3f(97.0f,51.0f, 0.0f);
// glVertex3f(98.0f,46.0f, 0.0f);
// glVertex3f(102.0f,43.0f, 0.0f);
// glVertex3f(109.0f,43.0f, 0.0f);
// glVertex3f(112.0f,45.0f, 0.0f);
// glVertex3f(113.0f,50.0f, 0.0f);
// glVertex3f(112.0f,53.0f, 0.0f);
// glVertex3f(105.0f,55.0f, 0.0f);



   glEnd();   // Done drawing the pyramid
 



    //rotateAll*=1.01;

    glutSwapBuffers();
}

void timer(int value) {
   glutPostRedisplay();      // Post re-paint request to activate display()
   glutTimerFunc(refreshMills, timer, 0); // next timer call milliseconds later
}

void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
   // Compute aspect ratio of the new window
   if (height == 0) height = 1;                // To prevent divide by 0
   GLfloat aspect = (GLfloat)width / (GLfloat)height;
 
   // Set the viewport to cover the new window
   glViewport(0, 0, width, height);
 
   // Set the aspect ratio of the clipping volume to match the viewport
   glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
   glLoadIdentity();             // Reset
   // Enable perspective projection with fovy, aspect, zNear and zFar
   gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}
 
void processSpecialKeys(int key, int xx, int yy) {

	float fraction = 0.5f;

	switch (key) {
		case GLUT_KEY_LEFT :
            x -= fraction;
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

void processNormalKeys(unsigned char key, int x, int y) {

   float fraction = 0.5f;
	/*if (key == 27)
		exit(0);
	else*/ if (key=='q') {
      z -= fraction;
	}else if (key=='e') {
      z += fraction;
	}else if (key=='a') {
      rx -= 1.0f;
	}else if (key=='d') {
      rx += 1.0f;
	}
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(1000, 600);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Talbert Herndon - Study Room");
    glutDisplayFunc(renderScene);
   glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);
    glutReshapeFunc(reshape);
    initGL();
    glutTimerFunc(0, timer, 0); 
    glutMainLoop();
    return 0;
}
    