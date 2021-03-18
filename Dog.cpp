#include <windows.h>
#include <GL/gl.h>
#include <glut.h>
#include <GL/glu.h>
#include <math.h>       
#define PI 3.14159265

// Global variables for each angle
 
 float angleT = 0.0;

 //legB
 float LB1 = 0.0;
 float LB2 = 0.0;
 float LB3 = 0.0;
 //legA
 float LA1 = 0.0;
 float LA2 = 0.0;
 float LA3 = 0.0;
 //Neck
 float N = 0.0;
 //head
 float H1 = 0.0;
 float H2 = 0.0;
 //Jaw
 float J = 45.0;


 //Globals 
 float LengthL1 = 4.0;
 float LengthL2 = 2.0;
 float LengthL3 = 1.0;

 float LengthCy = 4.0; // Cylinder 

 float spheLength = 6.0; // Sphere

 float cubeSize = 2.5;
 float cubeWidth = 1.0; //assuming always is 1.0

 //Init Axes
 void Axes();

// Set the increment
static float angleInc = 1.0;


typedef struct treenode
{
	//GLfloat m[16];
	void (*transform)();
	void (*draw)();
	struct treenode *sibling;
	struct treenode *child;
} treenode;

void traverse(treenode *root)
{
	// Check to see if this node is null (error checking)
	//if(root == NULL)
	//	return;

	// Apply transformation for current node and draw
	// Continue with depth-first search (go to children)
	glPushMatrix();

	root->transform();
	root->draw();

	// Check for children
	// NOTE that transformation is still applied
	if(root->child != NULL)
		traverse(root->child);
	
	glPopMatrix();
	
	// Check for siblings
	if(root->sibling != NULL)
		traverse(root->sibling);
}

// Alternate cylinder for drawing
void glutSolidCylinder (float r, float h, int n, int m)
{
    glPushMatrix ();
    glRotatef (90,1.0f, 0.0f, 0.0f);
    glTranslatef (0.0F, 0.0F,-h / 2);
    GLUquadricObj * qobj = gluNewQuadric ();
    gluQuadricDrawStyle (qobj, GLU_FILL);
    gluCylinder (qobj, r, r, h, n, m);
    gluDeleteQuadric (qobj);
    glPopMatrix ();
}

// Define transforms and render functions here
// -------------------------------------------
// treenode node
treenode root;
treenode body;
treenode legB1;
treenode legB2;
treenode legB3;
treenode legBB1;  //same B leg, but different starting point

treenode legA1;
treenode legA2;
treenode legA3;
treenode legAA1; //same A leg, but different starting point

treenode neck;
treenode head;
treenode jaw;



// methods
void EmptyTransform()
{
	
}

void EmptyRender()
{
	
}

//BODY
void BodyRender(){

	glColor4f(0.0, 0.0, 1.0, 0.2);
	glPushMatrix();
	//Axes();
	glScaled(spheLength/2,spheLength/2.5,spheLength); //spheLength=6.0
	glutSolidSphere(1.0, 10, 10);
	glPopMatrix();
	
}

void BodyTransform() {
	glRotated(angleT, 0.0, 1.0, 0.0);
}

//LEG

void LegRender1(){ 
	glPushMatrix();
		glRotated(45,1.0,0.0,0.0);
		glPushMatrix();
				glTranslated(0.0,-LengthL1/2,0.0); //my new rotation point
				glScaled(1.0, LengthL1, 1.0);
				glutSolidCube(1.0);
		glPopMatrix();
	glPopMatrix();
}

void LegTransformBL1() { //BACK LEFT
	glTranslated(spheLength/2.5,0.0,-spheLength/2.5);
	glRotated(LB1,1.0,0.0,0.0);
}



void LegTransformBR1() { //BACK RIGHT
	glTranslated(-spheLength / 2.5, 0.0, -spheLength / 2.5);
	glRotated(LA1, 1.0, 0.0, 0.0);
}

void LegTransformFL1() { //FRONT LEFT
	glTranslated(spheLength / 2.5, 0.0, spheLength / 1.4);
	glRotated(LA1, 1.0, 0.0, 0.0);
}

void LegTransformFR1() { //FRONT RIGHT
	glTranslated(-spheLength / 2.5, 0.0, spheLength / 1.4);
	glRotated(LB1, 1.0, 0.0, 0.0);
}


void LegRender2() { //base position
	glPushMatrix();
		glRotated(-45, 1.0, 0.0, 0.0);
		glPushMatrix();
			glTranslated(0.0, -(LengthL2 / 2), 0.0); //my new rotation point
			glScaled(1.0, LengthL2, 1.0);
			glutSolidCube(1.0);
		glPopMatrix();
	glPopMatrix();
}

//positioning

//por si escalo los rectángulos
//sin(45 * PI / 180.0)
//cos(45 * PI / 180.0)

void LegTransformB2() {
	glTranslated(0.0, -LengthL1 * sin(45 * PI / 180.0), - LengthL1 * cos(45 * PI / 180.0));   ///
	glRotated(LB2, 1.0, 0.0, 0.0);
}

void LegTransformA2() {
	glTranslated(0.0, -LengthL1 * sin(45 * PI / 180.0), -LengthL1 * cos(45 * PI / 180.0));
	glRotated(LA2, 1.0, 0.0, 0.0);
}


void LegRender3() { //base position
	glPushMatrix();
		glRotated(-90, 1.0, 0.0, 0.0);
		glPushMatrix();
			glTranslated(0.0, -LengthL3 / 2, 0.0); //my new rotation point
			glScaled(1.0, LengthL2, 1.0);
			glutSolidCube(1.0);
		glPopMatrix();
	glPopMatrix();
}

//positioning
void LegTransformB3() {
	glTranslated(0.0, -LengthL2 * sin(45 * PI / 180.0), LengthL2 * cos(45 * PI / 180.0));
	glRotated(LB3, 1.0, 0.0, 0.0);
}

void LegTransformA3() {
	glTranslated(0.0, -LengthL2 * sin(45 * PI / 180.0), LengthL2 * cos(45 * PI / 180.0));
	glRotated(LA3, 1.0, 0.0, 0.0);
}


void NeckRender(){ //base position
	glPushMatrix();
	glTranslated(0.0, LengthCy / 2, 0.0); //my new rotation point
	glutSolidCylinder(0.5,LengthCy,20,20);
	glPopMatrix();

}

//positioning
void NeckTransform()
{
	glTranslated(0.0, spheLength / 12, spheLength / 1.3);
	glRotated(N,1.0,0.0,0.0);
}


void HeadRender() { //base position
	//HEAD
	glPushMatrix();
		glPushMatrix();
			glScaled(cubeSize, cubeSize, cubeSize); //cubeSize=2.5
			glutSolidCube(1.0);
		glPopMatrix();
	//NOISE
		glPushMatrix();
		glTranslated(0.0,0.0, cubeSize/1.25);
			glScaled(cubeSize, cubeSize/2.0, cubeSize/1.25);
			glutSolidCube(1.0);
		glPopMatrix();
	glPopMatrix();
}

//positioning
void HeadTransform() {
	glTranslated(0.0,LengthCy,0.0);
	glRotated(H1,1.0,0.0,0.0);
	glRotated(H2, 0.0, 1.0, 0.0);
}

void JawRender() {//base position

	glPushMatrix();
		glTranslated(0.0,0.0, cubeSize/cubeSize);
		glScaled(cubeSize, cubeSize/3, cubeSize/1.25);
		glutSolidCube(1.0);
	glPopMatrix();
}

//positioning
void JawTransform() {
	glTranslated(0.0,-(cubeSize / 3), (cubeSize / 1.25)/2);
	glRotated(J,1.0,0.0,0.0);
}

// END define transforms and render functions
// -------------------------------------------

void Create()
{
	// Create tree structure here  

	root.draw = EmptyRender;
	root.transform = EmptyTransform;
	root.child = &body;
	root.sibling = NULL;

	body.draw = BodyRender;
	body.transform = BodyTransform;
	body.child = &legB1;
	body.sibling = NULL;

	legB1.draw = LegRender1;
	legB1.transform = LegTransformBL1;
	legB1.child = &legB2;
	legB1.sibling = &legBB1;

	//same leg as B1 but start in different point 
	legBB1.draw = LegRender1;
	legBB1.transform = LegTransformFR1;
	legBB1.child = &legB2;
	legBB1.sibling = &legA1;


	legB2.draw = LegRender2;
	legB2.transform = LegTransformB2;
	legB2.child = &legB3;
	legB2.sibling = NULL;

	legB3.draw = LegRender3;
	legB3.transform = LegTransformB3;
	legB3.child = NULL;
	legB3.sibling = NULL;


	legA1.draw = LegRender1;
	legA1.transform = LegTransformFL1;
	legA1.child = &legA2;
	legA1.sibling = &legAA1;

	//same leg as A1 but start in different point 
	legAA1.draw = LegRender1;
	legAA1.transform = LegTransformBR1;
	legAA1.child = &legA2;
	legAA1.sibling = &neck;

	legA2.draw = LegRender2;
	legA2.transform = LegTransformA2;
	legA2.child = &legA3;
	legA2.sibling = NULL;

	legA3.draw = LegRender3;
	legA3.transform = LegTransformA3;
	legA3.child = NULL;
	legA3.sibling = NULL;

	neck.draw = NeckRender;
	neck.transform =NeckTransform;
	neck.child = &head;
	neck.sibling = NULL;

	head.draw = HeadRender;
	head.transform = HeadTransform;
	head.child = &jaw;
	head.sibling = NULL;

	jaw.draw = JawRender;
	jaw.transform = JawTransform;
	jaw.child = NULL;
	jaw.sibling = NULL;

}

void init(void)
{
    // Set clear (background) color
	glClearColor(0.3, 0.32, 0.354, 0.0);

   // Set light properties...
   GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat light_position0[] = { 1.0, 1.0, 1.0, 0.0 };
   GLfloat light_position1[] = { -1.0, 1.0, 0.5, 0.0 };

   // Finish setting up the two lights (position, and component values (specular and diffuse))
   glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
   glLightfv(GL_LIGHT0, GL_AMBIENT_AND_DIFFUSE, white_light);
   glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);

   glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
   glLightfv(GL_LIGHT1, GL_AMBIENT_AND_DIFFUSE, white_light);
   glLightfv(GL_LIGHT1, GL_SPECULAR, white_light);

   // Define material properties
   GLfloat mat_specular[] = { 0.8, 0.9, 1.0, 1.0 };
   GLfloat mat_shininess[] = { 30.0 };
   GLfloat mat_surface[] = { 0.2, 0.2, 0.9, 1.0 };

   // Set material properties, as defined above
   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
   glMaterialfv(GL_FRONT, GL_AMBIENT, mat_surface);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_surface);

   // Set shading model to use
   glShadeModel (GL_SMOOTH);

   // Enable lighting
   glEnable(GL_LIGHTING);
   // Activate (enable) lights
   glEnable(GL_LIGHT0);
   glEnable(GL_LIGHT1);

   // Enable depth testing (for hidden surface removal)
   glEnable(GL_DEPTH_TEST);

   // Create tree structure
   Create();
}

void Axes(void)
{
glDisable(GL_LIGHTING);
   glLineWidth(2.0);
   glColor3f(1.0, 0.0, 0.0);
   glBegin(GL_LINES);
   glVertex3f(0.0,0.0,0.0);
   glVertex3f(10.0,0.0,0.0);
   glEnd();

   glColor3f(0.0, 1.0, 0.0);
   glBegin(GL_LINES);
   glVertex3f(0.0,0.0,0.0);
   glVertex3f(0.0,10.0,0.0);
   glEnd();

   glColor3f(0.0, 0.0, 1.0);
   glBegin(GL_LINES);
   glVertex3f(0.0,0.0,0.0);
   glVertex3f(0.0,0.0,10.0);
   glEnd();
   glEnable(GL_LIGHTING);
}

void display(void)
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Initial Push-Pop, so that each time display is called, the same image is drawn
	Axes();
	

		glPushMatrix();
		traverse( &root );
		glPopMatrix();


	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport( 0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 80.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(15.0, 15.0, 15.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {

	

			//to move body
		case 'a':
            angleT-=angleInc;
            break;
		case 'A':
			angleT+=angleInc;
			break;
		
		case 0x1B:
			break;

			//to move legs
		case 'p':
			if (LB1 <= -60)
				LB1 = -60;
			LB1 -= angleInc;
			break;
		case 'P':
			if (LB1 >= 0)
				LB1 = 0;
			LB1 += angleInc;
			break;

		case 'o':
			LB2 -= angleInc;
			break;
		case 'O':
			LB2 += angleInc;
			break;

		case 'i':
			if (LB3 <= -45)
				LB3 = -45;
			LB3 -= angleInc;
			break;
		case 'I':
			if (LB3 >= 0)
				LB3 = 0;
			LB3 += angleInc;
			break;


		case 'u':
			if (LA1 <= -60)
				LA1 = -60;
			LA1 -= angleInc;
			break;
		case 'U':
			if (LA1 >= 0)
				LA1 = 0;
			LA1 += angleInc;
			break;

		case 'y':
			LA2 -= angleInc;
			break;
		case 'Y':
			LA2 += angleInc;
			break;

		case 't':
			if (LA3 <= -45)
				LA3 = -45;
			LA3 -= angleInc;
			break;
		case 'T':
			if (LA3 >= 0)
				LA3 = 0;
			LA3 += angleInc;
			break;

			//to move neck
		case 'n':
			if (N <= 0)
				N = 0.0;
			N -= angleInc;
			break;
		case 'N':
			if (N >= 125)
				N = 125;
			N += angleInc;
			break;

			//to move head
		case 'H':
			if (H1 <= -45)
				H1 = -45;
			H1 -= angleInc;
			break;
		case 'h':
			if (H1 >= 25)
				H1 = 25;
			H1 += angleInc;
			break;

		case 'G':
			if (H2 <= -35)
				H2 = -35;
			H2 -= angleInc;
			break;
		case 'g':
			if (H2 >= 35)
				H2 = 35;
			H2 += angleInc;
			break;


			//to move jaw
		case 'J':
			if (J <= 0)
				J = 0.0;
			J -= angleInc;
			break;
		case 'j':
			if (J >= 45)
				J = 45;
			J += angleInc;
			break;

			//to exit
		case 'q':
		case 'Q':
			exit(0);
			break;
		default:
			break;
	}
}

void processSpecialKeys(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		glutPostRedisplay();
		break;

	case GLUT_KEY_DOWN:
		glutPostRedisplay();
		break;

	case GLUT_KEY_LEFT:
		glutPostRedisplay();
		break;

	case GLUT_KEY_RIGHT:
		glutPostRedisplay();
		break;
	}

}

int main (int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Empty Hierarchical Model using Nodes");
	init();

	glutKeyboardFunc(keyboard);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(display);
	glutSpecialFunc(processSpecialKeys);
	

	glutMainLoop();
	return 0;
}
