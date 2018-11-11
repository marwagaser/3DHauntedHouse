#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <glut.h>
#include<iostream>
#include <string.h>

#define GLUT_KEY_ESCAPE 27
#define DEG2RAD(a) (a * 0.0174532925)
float rotAng=0;
float rotAng2 = 0;
float rotAng3 = 0;
float transx = 0;
float _angle = -70.0f;
float photox=1;
float lampY = 0;
bool animateColors = false;
bool animateRoom1 = false;
bool animateRoom2 = false;
//ROOM 1 COLORS
float teapotColorG = 0.0; //change Tpot to 0.0 then incremented each time by 0.01;
float tableColorR = 0.2; //change till 1 then go back
float chairColorB = 0.0; // change till it hits one go back
float doorColorG = 0.2; // change till 1 then go back
float jackColorR = 0.1; // change till 1 then go back


float teapotColorGO = 0.0; //change Tpot to 0.0 then incremented each time by 0.01;
float tableColorRO = 0.2; //change till 1 then go back
float chairColorBO = 0.0; // change till it hits one go back
float doorColorGO = 0.2; // change till 1 then go back
float jackColorRO = 0.1; // change till 1 then go back


//ROOM 2 COLORS
float bedColorB = 0.0;
float comodoColorR = 0.1;
float closetColorR = 0.0;
float closetColorG = 0.0;
float photoFrameColorR = 0.0;
float lampBulbColorB = 0.0;


float bedColorBO = 0.0;
float comodoColorRO = 0.1;
float closetColorRO = 0.0;
float closetColorGO = 0.0;
float photoFrameColorRO = 0.0;
float lampBulbColorBO = 0.0;


bool isColorReset = false;
float butterflyX=0.6;


class Vector3f {
public:
	float x, y, z;

	Vector3f(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f) {
		x = _x;
		y = _y;
		z = _z;
	}

	Vector3f operator+(Vector3f &v) {
		return Vector3f(x + v.x, y + v.y, z + v.z);
	}

	Vector3f operator-(Vector3f &v) {
		return Vector3f(x - v.x, y - v.y, z - v.z);
	}

	Vector3f operator*(float n) {
		return Vector3f(x * n, y * n, z * n);
	}

	Vector3f operator/(float n) {
		return Vector3f(x / n, y / n, z / n);
	}

	Vector3f unit() {
		return *this / sqrt(x * x + y * y + z * z);
	}

	Vector3f cross(Vector3f v) {
		return Vector3f(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}
};

class Camera {
public:
	Vector3f eye, center, up;

	Camera(float eyeX = 1.0f, float eyeY = 1.0f, float eyeZ = 1.0f, float centerX = 0.0f, float centerY = 0.0f, float centerZ = 0.0f, float upX = 0.0f, float upY = 1.0f, float upZ = 0.0f) {
		eye = Vector3f(eyeX, eyeY, eyeZ);
		center = Vector3f(centerX, centerY, centerZ);
		up = Vector3f(upX, upY, upZ);
	}

	void moveX(float d) {
		Vector3f right = up.cross(center - eye).unit();
		eye = eye + right * d;
		center = center + right * d;
	}

	void moveY(float d) {
		eye = eye + up.unit() * d;
		center = center + up.unit() * d;
	}

	void moveZ(float d) {
		Vector3f view = (center - eye).unit();
		eye = eye + view * d;
		center = center + view * d;
	}

	void rotateX(float a) {
		Vector3f view = (center - eye).unit();
		Vector3f right = up.cross(view).unit();
		view = view * cos(DEG2RAD(a)) + up * sin(DEG2RAD(a));
		up = view.cross(right);
		center = eye + view;
	}

	void rotateY(float a) {
		Vector3f view = (center - eye).unit();
		Vector3f right = up.cross(view).unit();
		view = view * cos(DEG2RAD(a)) + right * sin(DEG2RAD(a));
		right = view.cross(up);
		center = eye + view;
	}

	void look() {
		gluLookAt(
			eye.x, eye.y, eye.z,
			center.x, center.y, center.z,
			up.x, up.y, up.z
		);
	}
};

Camera camera;

void drawWall(double thickness) {
	glPushMatrix();
	glTranslated(0.5, 0.5 * thickness, 0.5);
	glScaled(1.0, thickness, 1.0);
	glutSolidCube(1);
	glPopMatrix();
}
void drawTableLeg(double thick, double len) {
	glPushMatrix();
	glTranslated(0, len / 2, 0);
	glScaled(thick, len, thick);
	glutSolidCube(1.0);
	glPopMatrix();
}
void drawJackPart() {
	glPushMatrix();
	glScaled(0.2, 0.2, 1.0);
	glutSolidSphere(1, 15, 15);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0, 0, 1.2);
	glutSolidSphere(0.2, 15, 15);
	glTranslated(0, 0, -2.4);
	glutSolidSphere(0.2, 15, 15);
	glPopMatrix();
}


void drawJack() {
	glPushMatrix();
	drawJackPart();
	glRotated(90.0, 0, 1, 0);
	drawJackPart();
	glRotated(90.0, 1, 0, 0);
	drawJackPart();
	glPopMatrix();
}

void drawTV(){
	glPushMatrix();
	glTranslatef(0.5, 0.5, 0.2);
	glScalef(0.2, 0.2, 0.2);
	glutSolidCube(1);
	glPopMatrix();
}
void drawChair(double topWid, double topThick, double legThick, double legLen) {
	glPushMatrix();
	glTranslated(0, legLen, 0);
	glScaled(topWid, topThick, topWid);
	//glColor3f(0.3f, 0.0f, 0.4f);
	glutSolidCube(1.0);
	glPopMatrix();

	//back chair
	glPushMatrix();
	glRotated(90, 0.0f, 0.0f, 1);
	glTranslatef(0.6f ,0.32f,0.0f);
	glScaled(topWid, topThick, topWid);
	//glColor3f(0.3f, 0.0f, 0.4f);
	glutSolidCube(1.0);
	glPopMatrix();

	//left of chair
	glPushMatrix();
	glRotated(-90, 1.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, -0.31f, 0.6f); //ely fel nos byt3ml k2no z
	glScaled(topWid, topThick, topWid);
	//glColor3f(0.4f, 0.20f, 0.42f);
	glutSolidCube(1.0);
	glPopMatrix();

	//right of chair
	glPushMatrix();
	glRotated(-90, 1.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, 0.3f, 0.6f); //ely fel nos byt3ml k2no z kol ma increase yrg3 wara
	//float widthchair = topWid * 0.5;
	glScaled(topWid, topThick, topWid);
	//glColor3f(0.4f, 0.20f, 0.42f);
	glutSolidCube(1.0);
	glPopMatrix();
	/////

	double dist = 0.95*topWid / 2.0 - legThick / 2.0;
	glPushMatrix();
	glTranslated(dist, 0, dist);
	drawTableLeg(legThick, legLen); //front right
	glTranslated(0, 0, -2 * dist);
	drawTableLeg(legThick, legLen); //back right
	glTranslated(-2 * dist, 0, 2 * dist);
	drawTableLeg(legThick, legLen); //front left
	glTranslated(0, 0, -2 * dist);
	drawTableLeg(legThick, legLen); //back left
	glPopMatrix();
}


void drawTable(double topWid, double topThick, double legThick, double legLen) {
	glPushMatrix();
	glTranslated(0, legLen, 0);
	glScaled(topWid, topThick, topWid);
	glutSolidCube(1.0);
	glPopMatrix();

	double dist = 0.95*topWid / 2.0 - legThick / 2.0;
	glPushMatrix();
	glTranslated(dist, 0, dist);
	drawTableLeg(legThick, legLen); //front right
	glTranslated(0, 0, -2 * dist);
	drawTableLeg(legThick, legLen); //back right
	glTranslated(-2 * dist, 0, 2 * dist);
	drawTableLeg(legThick, legLen); //front left
	glTranslated(0, 0, -2 * dist);
	drawTableLeg(legThick, legLen); //back left
	glPopMatrix();
}


void drawCloset() {
	
	glPushMatrix();
	glTranslatef(0.2, 0.0f, 0.0f);
	//door 1
	glPushMatrix();
	glTranslatef(-0.3f, -1.2f, -0.3f);
	glScalef(1.0f, 3.0f, 1.0f);
	glColor3f(closetColorR, closetColorG, 0.0f);
	drawTV();
	glPopMatrix();

	//door 2
	glPushMatrix();
	glTranslatef(-0.3f, 0.0f, -0.29f);
	glColor3f(closetColorR, closetColorG, 0.0f);
	drawTV();
	glPopMatrix();

	//doorknob
	glPushMatrix();
	glTranslatef(0.28f, 0.3f, 0.01f);
	glScalef(0.05f, 0.05f, 0.05f);
	glColor3f(0.4f, 0.26f, 0.13f);
	glutSolidSphere(0.5, 25, 25);
	glPopMatrix();

	//door 3
	glPushMatrix();
	glTranslatef(-0.3f, -0.4f, -0.29f);
	glColor3f(0.0f, 0.0f, 0.0f);
	drawTV();
	glPopMatrix();
	glPopMatrix();



	//door 1.2
	glPushMatrix();
	glTranslatef(0.3, 0.0f, 0.0f);
	glPushMatrix();
	glTranslatef(-0.3f, -1.2f, -0.3f);
	glScalef(1.0f, 3.0f, 1.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	drawTV();
	glPopMatrix();

	//door 2.2
	glPushMatrix();
	glTranslatef(-0.3f, 0.0f, -0.29f);
	glColor3f(1.0f, 0.0f, 0.0f);
	drawTV();
	glPopMatrix();

	//doorknob 2
	glPushMatrix();
	glTranslatef(0.28f, 0.3f, 0.01f);
	glScalef(0.05f, 0.05f, 0.05f);
	glColor3f(0.4f, 0.26f, 0.13f);
	glutSolidSphere(0.5, 25, 25);
	glPopMatrix();

	//door 3.2
	glPushMatrix();
	glTranslatef(-0.3f, -0.4f, -0.29f);
	glColor3f(1.0f, 0.0f, 0.0f);
	drawTV();
	glPopMatrix();
	glPopMatrix();



}

void drawBed(double topWid, double topThick, double legThick, double legLen) {
	glPushMatrix();
	glTranslated(0, legLen, 0);
	glScaled(topWid, topThick, topWid);
	//glColor3f(0.0f, 0.0f, bedColorB);
	glutSolidCube(1.0);
	glPopMatrix();

	//back of bed
	glPushMatrix();
	glRotated(90, 0.0f, 0.0f, 1);
	glTranslatef(0.6f, 0.32f, 0.0f);
	glScaled(topWid, topThick, topWid);
	//glColor3f(0.0f, 0.0f, bedColorB);
	glutSolidCube(1.0);
	glPopMatrix();

	/////

	double dist = 0.95*topWid / 2.0 - legThick / 2.0;
	glPushMatrix();
	glTranslated(dist, 0, dist);
	drawTableLeg(legThick, legLen); //front right
	glTranslated(0, 0, -2 * dist);
	drawTableLeg(legThick, legLen); //back right
	glTranslated(-2 * dist, 0, 2 * dist);
	drawTableLeg(legThick, legLen); //front left
	glTranslated(0, 0, -2 * dist);
	drawTableLeg(legThick, legLen); //back left
	glPopMatrix();
}

void setupLights() {
	GLfloat ambient[] = { 0.7f, 0.7f, 0.7, 1.0f };
	GLfloat diffuse[] = { 0.6f, 0.6f, 0.6, 1.0f };
	GLfloat specular[] = { 1.0f, 1.0f, 1.0, 1.0f };
	GLfloat shininess[] = { 50 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

	GLfloat lightIntensity[] = { 0.7f, 0.7f, 1, 1.0f };
	GLfloat lightPosition[] = { -7.0f, 6.0f, 3.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightIntensity);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);
}
void setupCamera() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 640 / 480, 0.001, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	camera.look();
}
void drawDoor() {

	//door 1
	glPushMatrix();
	glPushMatrix();
	glTranslatef(-0.3f, -1.2f, -0.3f);
	glScalef(1.0f, 3.0f, 1.0f);
	glColor3f(0.2f, doorColorG, 0.2f);
	drawTV();
	glPopMatrix();

	//door 2
	glPushMatrix();
	glTranslatef(-0.3f, 0.0f, -0.29f);
	glColor3f(1.0f, 1.0f, 1.0f);
	drawTV();
	glPopMatrix();

	//doorknob
	glPushMatrix();
	glTranslatef(0.28f, 0.3f, 0.01f);
	glScalef(0.05f, 0.05f, 0.05f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glutSolidSphere(0.5, 25, 25);
	glPopMatrix();

	//door 3
	glPushMatrix();
	glTranslatef(-0.3f, -0.4f, -0.29f);
	glColor3f(1.0f, 1.0f, 1.0f);
	drawTV();
	glPopMatrix();
	glPopMatrix();
}

void DrawComdo() {

	
	glPushMatrix();
	glScalef(0.5,0.5,0.5);
	//door 1
	glPushMatrix();
	glTranslatef(-0.3f, -0.2f, -0.29f);
	glColor3f(comodoColorR, 0.9f, 1.0f);
	drawTV();
	glPopMatrix();

	//door 2
	glPushMatrix();
	glTranslatef(-0.3f, 0.0f, -0.29f);
	glColor3f(0.1f, 0.0f, 0.0f);
	drawTV();
	glPopMatrix();

	//doorknob
	glPushMatrix();
	glTranslatef(0.28f, 0.3f, 0.01f);
	glScalef(0.05f, 0.05f, 0.05f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glutSolidSphere(0.5, 25, 25);
	glPopMatrix();

	//door 3
	glPushMatrix();
	glTranslatef(-0.3f, -0.4f, -0.29f);
	glColor3f(0.1f, 0.0f, 0.0f);
	drawTV();
	glPopMatrix();
	glPopMatrix();


}

void drawStandingLamp() { 
	glPushMatrix();
	glScalef(0.9, 0.9, 0.9);
	//basic 
	glPushMatrix();
	glTranslatef(1.6, 0.0, 0.9);
	glScalef(0.1, 0.1, 0.1);
	glColor3f(0.1f, 1.0f, 0.0f);
	glutSolidCube(1.0);
	glPopMatrix();

	//basic 2 
	glPushMatrix();
	glTranslatef(1.6, 0.02, 0.9);
	glScalef(0.07, 0.1, 0.1);
	glColor3f(0.1f, 1.0f, 0.0f);
	glutSolidCube(1.0);
	glPopMatrix();

	//stand
	glPushMatrix();
	glTranslatef(1.6, 0.18, 0.9);
	glScalef(0.04, 0.6, 0.07);
	glColor3f(1.0f, 0.0f, 0.0f);
	glutSolidCube(1.0);
	glPopMatrix();

	//bulb
	glPushMatrix();
	glTranslatef(1.6, 0.50, 0.88);
	glScalef(0.23, 0.23, 0.23);
	glColor3f(1.0f, 1.0f, lampBulbColorB);
	glutSolidSphere(0.5, 25, 25);
	glPopMatrix();

	glPopMatrix();
}

void drawPhotoFrame() {
	glPushMatrix();

	//big frame
	glPushMatrix();
	glTranslatef(-0.3f, -0.1f, -0.29f);
	glScalef(1.0, 1.5, 1.0);
	glColor3f(photoFrameColorR, 0.0f, 1.0f);
	drawTV();
	glPopMatrix();

	//small frame
	glPushMatrix();
	glTranslatef(-0.3f, -0.1f, -0.29f);
	glColor3f(0.0f, 0.0f, 0.0f);
	drawTV();
	glPopMatrix();


	//flower stigma
	glPushMatrix();
	glTranslatef(0.20f, 0.53f, 0.02f);
	glScalef(0.03, 0.03, 0.03);
	glColor3f(1.0f,1.00,0.00);
	glutSolidSphere(0.5, 25, 25);
	glPopMatrix();

	//flower petals 1
	glPushMatrix();
	glTranslatef(0.20f, 0.55f, 0.0f);
	glScalef(0.06, 0.06, 0.06);
	glColor3f(1.0f, 0.00, 1.00);
	glutSolidSphere(0.5, 25, 25);
	glPopMatrix();

	//flower petals 2
	glPushMatrix();
	glTranslatef(0.20f, 0.51f, 0.0f);
	glScalef(0.06, 0.06, 0.06);
	glColor3f(1.0f, 0.00, 1.00);
	glutSolidSphere(0.5, 25, 25);
	glPopMatrix();

	//flower petals 3
	glPushMatrix();
	glTranslatef(0.18f, 0.51f, 0.0f);
	glScalef(0.06, 0.06, 0.06);
	glColor3f(1.0f, 0.00, 1.00);
	glutSolidSphere(0.5, 25, 25);
	glPopMatrix();



	//flower petals 4
	glPushMatrix();
	glTranslatef(0.22f, 0.51f, 0.0f);
	glScalef(0.06, 0.06, 0.06);
	glColor3f(1.0f, 0.00, 1.00);
	glutSolidSphere(0.5, 25, 25);
	glPopMatrix();


	glPopMatrix();

}

void drawButterfly() {

	glPushMatrix();

	//face
	glPushMatrix();
	glTranslatef(1.6, 1.0, 0.9);
	glScalef(0.1, 0.1, 0.1);
	glColor3f(0.1f,1.0f,0.0f);
	glutSolidCube(1.0);
	glPopMatrix();

	//body
	glPushMatrix();
	glTranslatef(1.6, 0.9, 0.9);
	glScalef(0.05, 0.1, 0.1);
	glColor3f(0.2, 0.1, 0.4);
	glutSolidCube(1.0);
	glPopMatrix();

	//bbody x2
	glPushMatrix();
	glTranslatef(1.6, 0.7, 0.9);
	glScalef(0.03, 0.2, 0.07);
	glColor3f(0.9, 0.1, 0.4);
	glutSolidCube(1.0);
	glPopMatrix();

	//wings
	glPushMatrix();
	glTranslatef(1.6, 0.9, 0.9);
	glScalef(0.5, 0.2, 0.07);
	glColor3f(0.9, 0.1, 0.4);
	glutSolidSphere(0.5,25,25);
	glPopMatrix();

	glPopMatrix();
}

void Display() {
	setupCamera();
	setupLights();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix(); //ROOM1
	glRotatef(rotAng, 0, 1, 0);// Rotate room1 
	//jack
	glPushMatrix();
	glTranslated(0.7, 0.4, 0.6);
	glRotatef(rotAng, 0, 1, 0);
	//glRotated(45, 0, 0, 1);
	glScalef(0.04, 0.04, 0.04);
	glColor3f(jackColorR, 0.5f, 0.5f);
	drawJack();
	glPopMatrix();

	//teapot
	glPushMatrix();
	glTranslated(0.78, 0.38, 0.5);
	glRotated(rotAng, 0, 1, 0);
	glScalef(0.4, 0.4, 0.4);
	glColor3f(0.5f,teapotColorG, 0.1f);
	glutSolidTeapot(0.08);
	glPopMatrix();

	//table
	glPushMatrix();
	glTranslated(0.6, 0.0, 0.4);
	glRotatef(-rotAng, 0, 1, 0);
	glScalef(0.5, 0.5, 0.5);
	glColor3f(tableColorR, 0.0f, 0.1f);
	drawTable(0.6, 0.02, 0.02, 0.3);
	glPopMatrix();


	//draw door
	glPushMatrix();
	glTranslatef(transx, 0, 0);
	drawDoor();
	glPopMatrix();

	//draw chair
	glPushMatrix();
	glTranslated(0.2, 0.0, 0.4);
	glRotated(rotAng, 0, 1, 0);
	glScalef(0.5, 0.5, 0.5);
	glColor3f(0.3f, 0.0f, chairColorB);
	drawChair(0.6, 0.02, 0.02, 0.3);
	glPopMatrix();
	
	//floor
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	drawWall(0.02);
	glPopMatrix();

	//leftwall
	glPushMatrix();
	glRotated(90, 0, 0, 1.0);
	glColor3f(1.0f, 1.0f, 1.0f);
	drawWall(0.02);
	glPopMatrix();

	//back wall
	glPushMatrix();
	glRotated(-90, 1.0, 0.0, 0.0);
	glColor3f(1.0f, 1.0f, 1.0f);
	drawWall(0.02);
	glPopMatrix();

	glPopMatrix(); //finish room 1


	////////////////////////////////////////////////////////

	//ROOM NUMBER 2 BELOW///
	//floor2
	glPushMatrix(); //start room 2
        glRotatef(rotAng2, 0, 1, 0);
	glPushMatrix();
	glTranslatef(1.0f, 0, 0);
	glColor3f(1.0f, 1.0f, 1.0f);
	drawWall(0.02);
	glPopMatrix();

	//leftwall2
	glPushMatrix();
	glTranslatef(1.0f, 0.0f, 0.0f);
	glRotated(90, 0, 0, 1.0);
	glColor3f(1.0f, 1.0f, 1.0f);
	drawWall(0.02);
	glPopMatrix();

	//back wall2
	glPushMatrix();
	glTranslatef(1.0f,0.0f,0.0f);
	glRotated(-90, 1.0, 0.0, 0.0);
	glColor3f(1.0f, 1.0f, 1.0f);
	drawWall(0.02);
	glPopMatrix();

	//draw the bed
	glPushMatrix();
	glTranslatef(1.25f, 0.2f, 0.5f);
	glRotatef(-rotAng2,0,1,0);
	glScalef(0.5,0.5,0.5);
	glColor3f(0.3, 0.2, bedColorB);
	drawBed(0.6, 0.02, 0.02, 0.3);
	glPopMatrix();

	//draw the closet
	glPushMatrix();
	glTranslatef(1.6f, 0.5f, 0.6f);
	glRotatef(-rotAng2, 1, 0, 0);
	glScalef(0.5f, 1.0f, 0.5f);
	drawCloset();
	glPopMatrix();


	//draw the photo frame
	glPushMatrix();
	glTranslatef(photox,0.0,0.0);
	drawPhotoFrame();
	glPopMatrix();

	//draw character (butterfly)
	glPushMatrix();
	glTranslatef(butterflyX, 0.1, 0.1);
	glRotatef(rotAng3, 1, 0, 0);
	glScalef(0.6, 0.6, 0.6);
	drawButterfly();
	glPopMatrix();


	//draw standing lamp

	glPushMatrix();
	glTranslatef(0, lampY, 0);
	drawStandingLamp();
	glPopMatrix();


	//draw Comdo
	glPushMatrix();
	glTranslatef(1.2f, 0.0f, 0.9f);
	glRotatef(rotAng2,0,1,0);
	DrawComdo();
	glPopMatrix();

	glPopMatrix(); // finish room 2

	glFlush();
}


void Timer(int value) {
	// set the enemy defender y loctation anywhere between 10 an 780
	if (butterflyX > -0.8) {
	
		butterflyX = butterflyX -= 0.4;
	}
	else {
		butterflyX = 0.2;
	}
	//P1X = rand() % 400 + 0;
	//P1Y = rand() % 300 + 0;
	// ask OpenGL to recall the display function to reflect the changes on the window
	glutPostRedisplay();

	// recall the Timer function after 5 seconds (5,000 milliseconds)
	glutTimerFunc(15 * 1000, Timer, 0);
}

void Anim() {
	if (animateRoom1 == true) {
		if (transx < 0.511873)
			transx += 0.0001;
		else transx = 0;
	rotAng += 0.1;
	}
	if (animateRoom2 == true) {
	rotAng2 += 0.08;
	if (lampY < 0.5) {
		lampY += 0.0001;
	}
	else {
		lampY = 0;
	}
	if (photox < 1.31575)
		photox += 0.0001;
	else
		photox = 1.0;
	}
	rotAng3 +=0.1;
	
	
	
	if (animateColors ==true) {
		if (isColorReset == false && tableColorR <1) {
			tableColorR += 0.001;
		}
		else if (isColorReset == false && tableColorR >1) {
			tableColorR = tableColorRO;
		}
		if (isColorReset == false && chairColorB <1) {
			chairColorB += 0.001;
		}
		else if (isColorReset == false && chairColorB >1) {
			chairColorB = chairColorBO;
		}
		if (isColorReset == false && teapotColorG <1) {
			teapotColorG += 0.001;
		}
		else if (isColorReset == false && teapotColorG >1) {
			teapotColorG = teapotColorGO;
		}

		if (isColorReset == false && doorColorG <1) {
			doorColorG += 0.001;
		}
		else if (isColorReset == false && doorColorG >1) {
			doorColorG = doorColorGO;
		}

		if (isColorReset == false && jackColorR <1) {
			jackColorR += 0.001;
		}
		else if (isColorReset == false && jackColorR >1) {
			jackColorR = jackColorRO;
		}

		if (isColorReset == false && bedColorB <1) {
			bedColorB += 0.001;
		}
		else if (isColorReset == false && bedColorB >1) {
			bedColorB = bedColorBO;
		}

		if (isColorReset == false && comodoColorR <1) {
			comodoColorR += 0.001;
		}
		else if (isColorReset == false && comodoColorR >1) {
			comodoColorR = comodoColorRO;
		}
		if (isColorReset == false && closetColorG <1) {
			closetColorG += 0.001;
		}
		else if (isColorReset == false && closetColorG >1) {
			closetColorG = closetColorGO;
		}

		if (isColorReset == false && closetColorR <1) {
			closetColorR += 0.001;
		}
		else if (isColorReset == false && closetColorR >1) {
			closetColorR = closetColorRO;
		}

		if (isColorReset == false && photoFrameColorR <1) {
			photoFrameColorR += 0.001;
		}
		else if (isColorReset == false && photoFrameColorR >1) {
			photoFrameColorR = photoFrameColorRO;
		}

		if (isColorReset == false && lampBulbColorB <1) {
			lampBulbColorB += 0.001;
		}
		else if (isColorReset == false && lampBulbColorB >1) {
			lampBulbColorB = lampBulbColorBO;
		}

	}



	else if (animateColors = false) {
		lampBulbColorB = lampBulbColorBO;
		photoFrameColorR = photoFrameColorRO;
		closetColorR = closetColorRO;
		comodoColorR = comodoColorRO;
		bedColorB = bedColorBO;
		jackColorR = jackColorRO;
		doorColorG = doorColorGO;
		tableColorR = tableColorRO;
		chairColorB = chairColorBO;
		teapotColorG = tableColorRO;

	}

	

	std::cout << photox;
	//std::cout << transx;
	glutPostRedisplay();
}

void Keyboard(unsigned char key, int x, int y) {
	float d = 0.01;

	switch (key) {
	case 'w':
		camera.moveY(d);
		break;
	case 's':
		camera.moveY(-d);
		break;
	case 'a':
		camera.moveX(d);
		break;
	case 'd':
		camera.moveX(-d);
		break;
	case 'q':
		camera.moveZ(d);
		break;
	case 'e':
		camera.moveZ(-d);
		break;
	case 'v' :
	{
	
		lampBulbColorB = lampBulbColorBO;
		photoFrameColorR = photoFrameColorRO;
		closetColorR = closetColorRO;
		comodoColorR = comodoColorRO;
		bedColorB = bedColorBO;
		jackColorR = jackColorRO;
		doorColorG = doorColorGO;
		tableColorR = tableColorRO;
		chairColorB = chairColorBO;
		teapotColorG = tableColorRO;
		break;
	}
	case 'n': {
		rotAng2 = 0;
		lampY = 0;
		photox = 1;
		break;
	}
	case 'k': {
		rotAng = 0;
		transx = 0;
		break;
	}
	
	case GLUT_KEY_ESCAPE:
		exit(EXIT_SUCCESS);
	}

	glutPostRedisplay();
}
void Special(int key, int x, int y) {
	float a = 1.0;

	switch (key) {
	case GLUT_KEY_UP:
		camera.rotateX(a);
		break;
	case GLUT_KEY_DOWN:
		camera.rotateX(-a);
		break;
	case GLUT_KEY_LEFT:
		camera.rotateY(a);
		break;
	case GLUT_KEY_RIGHT:
		camera.rotateY(-a);
		break;
	}

	glutPostRedisplay();
}


void KeyUp(unsigned char key, int x, int y) {
	// reset the selectedBar value to 0 to unselect the selected bar
	if (key == 'c')
		animateColors = true;
	if (key == 'v') {
		animateColors = false;
	}
	if (key == 'b') {
		animateRoom2 = true;
	}

	if (key == 'l') {
		animateRoom1 = true;
	}
	if (key == 'k') {
		animateRoom1 = false;
	}
	if (key == 'n') {
	
		animateRoom2 = false;
	}

	// ask OpenGL to recall the display function to reflect the changes on the window
	glutPostRedisplay();
}


void main(int argc, char** argv) {
	glutInit(&argc, argv);

	glutInitWindowSize(640, 480);
	glutInitWindowPosition(50, 50);

	glutCreateWindow("Haunted House");
	glutDisplayFunc(Display);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(Special);
	//glutKeyboardFunc(key);
	glutIdleFunc(Anim);
	glutKeyboardUpFunc(KeyUp);
	glutTimerFunc(0, Timer, 0);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	glShadeModel(GL_SMOOTH);

	//glutMainLoop();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, 300 / 300, 0.1f, 300.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0f, 2.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	glutMainLoop();
}
