#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <iostream>
#include <math.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
using namespace std;
int first = 1;
GLfloat angle1 = 160.0;
GLfloat angle2 = 200.0;
GLfloat angle3 = 200.0;
float current_angle = 0.0f;
float step_angle = 0.2f;
float center_x = 168.0f;
float center_y = 440.0f;
float m = 0;
float mount = 0;
float mm = 500;
float flag = 0;
float flag2 = 500;
int F = 0;
float b2_speed = 5;
float ba_posion = 0;
int counter = 0;
float scale_cloud;
void sceenario(void);
void girl();
void hare_walking();
void cloud();
void circle(GLdouble rad);
void hare();
void hare_sleep();
#define PI 3.1416
unsigned int bg2;
void loadBackground(void)
{
    glGenTextures(1, &bg2);
    glBindTexture(GL_TEXTURE_2D, bg2);
    // set the bg1 wrapping/filtering options (on the currently bound bg1 object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load and generate the bg1
    int width, height, nrChannels;
    unsigned char *data = stbi_load("E:\\6\\CGVLAB\\CGV PROJECT\\tor\\hi.png", &width, &height, &nrChannels, STBI_rgb_alpha);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        //glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        cout << stbi_failure_reason()
             << endl;
    }
    stbi_image_free(data);
}

void frontscene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glColor3f(1, 1, 1);

    //  glVertex2i(0, 20);
    //     glVertex2i(700, 20);
    //     glVertex2i(700, 300);
    //     glVertex2i(0, 300);
    glBindTexture(GL_TEXTURE_2D, bg2);

    // drawOneLine(-5.95, -1.70, 5.50, -1.70);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);

    glVertex2i(0, 0);
    glTexCoord2f(0, 1);

    glVertex2i(650, 0);
    glTexCoord2f(1, 1);

    glVertex2i(650, 500);
    glTexCoord2f(1, 0);

    glVertex2i(0, 500);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);
    glFlush();
}
void drawLeftCircle() // the filled one
{
    /**-----------Head------------**/
    glPushMatrix();
    glColor3f(0, .5, 0);
    glScalef(.5, .7, .5);
    glTranslatef(110 + 350, 245, 1);
    circle(20);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0, 0, 0);
    glScalef(.5, .7, .5);
    glTranslatef(110 + 350, 245, 1);
    circle(5);
    glPopMatrix();
    /**-----------Neck-----------**/
    glPushMatrix();
    glColor3f(0, .5, 0);
    glScalef(.5, .7, .5);
    glTranslatef(210 + 350, 180, 1);
    glRotatef(20, 0, 0, 1);
    glBegin(GL_POLYGON);
    glVertex3f(-70, 90, 1);
    glVertex3f(-70, 50, 1);
    glVertex3f(-50, 50, 1);
    glVertex3f(-50, 90, 1);
    glEnd();
    glPopMatrix();
    /**-----------Leg1-----------**/
    glPushMatrix();
    glColor3f(0, .7, 0);
    glScalef(.5, .7, .5);
    glTranslatef(230 + 350, 110, 1);

    glBegin(GL_POLYGON);
    glVertex3f(-80, 90, 1);
    glVertex3f(-85, 70, 1);
    glVertex3f(-45, 70, 1);
    glVertex3f(-50, 90, 1);
    glEnd();
    glPopMatrix();
    /**-----------LEg2-----------**/
    glPushMatrix();
    glColor3f(0, .7, 0);
    glScalef(.5, .7, .5);
    glTranslatef(300 + 350, 110, 1);
    //glRotatef(20,0,0,1);
    glBegin(GL_POLYGON);
    glVertex3f(-80, 90, 1);
    glVertex3f(-85, 70, 1);
    glVertex3f(-45, 70, 1);
    glVertex3f(-50, 90, 1);
    glEnd();
    glPopMatrix();
    /**-----------Body-----------------**/
    glPushMatrix();
    float radius = 70;
    float twoPI = 2 * PI;

    glColor3f(0, .5, 0);
    glScalef(.5, 0.7, .5);
    glTranslatef(200 + 350, 200, 1);
    //glTranslatef(550,150,1);
    glRotatef(-90, 0, 0, 1);
    glBegin(GL_TRIANGLE_FAN);

    for (float i = PI; i <= twoPI; i += 0.001)
        glVertex2f((sin(i) * radius), (cos(i) * radius));

    glEnd();
    glPopMatrix();
}

void drawstring(float x, float y, float z, char *string)
{
    char *ct;
    glRasterPos3f(x, y, z);

    for (ct = string; *ct != '\0'; ct++)
    {
        glColor3f(0.0, 0.0, 0.0);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *ct);
    }
}

void myInit(void)
{
    glColor3f(1.0f, 0.0f, 0.0f);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

void sleeping_body2()
{
    glColor3f(0.0, 0.5, 0.1);
    glLineWidth(4.0);
    glPushMatrix();
    glScalef(.15, .15, .15);
    glTranslatef(200 - m * 6.68, 2050, 0);
    glRotatef(70, 0, 0, 1);

    glBegin(GL_LINE_LOOP);
    glVertex2i(40, 10);
    glVertex2i(0, 0);
    glVertex2i(-40, 10);
    glVertex2i(-40, 160);
    glVertex2i(-10, 180);
    glVertex2i(60, 180);
    glVertex2i(20, 100);
    glVertex2i(60, 60);
    glEnd();
    glPopMatrix();

    /**------------------------------Body Starts---------------------------**/

    //glViewport(1000,100,500,500);
    glColor3f(0.7, .2, 0);
    glPushMatrix();
    glScalef(.15, .15, .15);
    glTranslatef(120 - m * 6.68, 2400, 0);
    glRotatef(70 + 190, 0, 0, 1);

    //glTranslatef(1000, 500, 0);
    glBegin(GL_POLYGON);
    glVertex2i(400, 300);
    glVertex2i(310, 370);
    glVertex2i(280, 400); //(x,y) First point
    glVertex2i(180, 400);
    glVertex2i(130, 370);
    glVertex2i(130, 340);
    glVertex2i(155, 330);
    glVertex2i(130, 310);
    glVertex2i(130, 290);
    glVertex2i(180, 270);
    glVertex2i(180, 150);
    glVertex2i(250, 150);
    glVertex2i(300, 80);
    glVertex2i(390, 80);
    glVertex2i(430, 120);
    glEnd();
    glPopMatrix();
    /**-------------------------------------Body Ends----------------------------**/

    /**....................................Leg1 starts........................**/

    glClearColor(1.0, 1.0, 1.0, 1.0);

    // Leg

    glColor3f(0.0, 0.6, 0.0);
    glLineWidth(4.0);
    glPushMatrix();
    glScalef(.15, .15, .15);
    glTranslatef(220 - m * 6.68, 2005, 0);
    glRotatef(70, 0, 0, 1);
    glBegin(GL_LINE_LOOP);
    glVertex2i(40, 10);
    glVertex2i(0, 0);
    glVertex2i(-40, 10);
    glVertex2i(-40, 160);
    glVertex2i(-10, 180);
    glVertex2i(60, 180);
    glVertex2i(20, 100);
    glVertex2i(60, 60);
    glEnd();
    glPopMatrix();

    /**....................................Leg1 ends............................................**/

    /**.................................Arm starts........................................**/
    glColor3f(.0, 0.9, 0);
    glPushMatrix();
    glScalef(.15, .15, .15);
    glTranslatef(0 - m * 6.68, 2100, 0);
    glRotatef(-50, 0, 0, 1);

    glBegin(GL_POLYGON);
    glVertex2i(220, 270);
    glVertex2i(200, 250);
    glVertex2i(250, 250);
    glVertex2i(130 + angle3 * .5, 200 - angle3 * .5);
    glVertex2i(130 + angle3 * .5, 180 - angle3 * .5);
    glVertex2i(120 + angle3 * .5, 180 - angle3 * .5);
    glEnd();

    glColor3f(0, 0, 0);
    drawstring(300, 550, 0.0, "Z Z");
    drawstring(250, 450, 0.0, "Z Z");
    drawstring(200, 500, 0.0, "Z Z");
    glPopMatrix();
    glutPostRedisplay();
    /**....................................ARM END............................................**/
}
void body2()
{
    //glClear(GL_COLOR_BUFFER_BIT);

    //sceenario();
    /**------------------- Second Leg    angle2----------------------**/

    glColor3f(0.0, 0.6, 0.9);
    glLineWidth(4.0);
    glPushMatrix();
    glScalef(.2, .2, .2);
    glTranslatef(1250 + b2_speed * m + ba_posion, 1150, 0);
    glRotatef(-angle2, 0, 0, 1);
    glBegin(GL_LINE_LOOP);
    glVertex2i(30, 10);
    glVertex2i(0, 0);
    glVertex2i(-30, 10);
    glVertex2i(-30, 160);
    glVertex2i(-10, 180);
    glVertex2i(40, 180);
    glVertex2i(10, 100);
    glVertex2i(40, 50);
    glEnd();
    glPopMatrix();

    /**------------------------------Body Starts---------------------------**/

    glColor3f(0.7, .2, 0);
    glPushMatrix();
    glScalef(.2, .2, .2);
    glTranslatef(1000 + b2_speed * m + ba_posion, 950, 0);
    glBegin(GL_POLYGON);
    glVertex2i(400, 300);
    glVertex2i(310, 370);
    glVertex2i(280, 400); //(x,y) First point
    glVertex2i(180, 400);
    glVertex2i(130, 370);
    glVertex2i(130, 340);
    glVertex2i(155, 330);
    glVertex2i(130, 310);
    glVertex2i(130, 290);
    glVertex2i(180, 270);
    glVertex2i(180, 150);
    glVertex2i(250, 150);
    glVertex2i(300, 80);
    glVertex2i(390, 80);
    glVertex2i(430, 120);
    glEnd();
    glPopMatrix();
    /**-------------------------------------Body Ends----------------------------**/

    /**-------------------------------------Eye starts---------------------------**/
    glColor3f(.5, .5, .1);
    glPushMatrix();
    glScalef(.2, 0.2, 0.2);
    glTranslatef(1000 + b2_speed * m + ba_posion, 950, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2i(200, 350);
    glVertex2i(220, 345);
    glVertex2i(230, 360);
    glEnd();
    glPopMatrix();
    /**-------------------------------------Eye ends---------------------------**/

    /**....................................Leng1 starts........................**/

    glClearColor(1.0, 1.0, 1.0, 1.0);

    // Leg

    glColor3f(0.0, 0.6, 0.0);
    glLineWidth(4.0);
    glPushMatrix();
    glScalef(.2, .2, .2);
    glTranslatef(1250 + m * b2_speed + ba_posion, 1150, 0);
    glRotatef(-angle1, 0, 0, 1);
    glBegin(GL_LINE_LOOP);
    glVertex2i(30, 10);
    glVertex2i(0, 0);
    glVertex2i(-30, 10);
    glVertex2i(-30, 160);
    glVertex2i(-10, 180);
    glVertex2i(40, 180);
    glVertex2i(10, 100);
    glVertex2i(40, 50);
    glEnd();
    glPopMatrix();

    /**....................................Leg1 ends............................................**/

    /**.................................Arm starts........................................**/
    glColor3f(.0, 0.9, 0);
    glPushMatrix();
    glScalef(.2, .2, .2);
    //glTranslatef(0, 0, 0);
    glTranslatef(1000 + b2_speed * m + ba_posion, 950, 0);
    //glRotatef( 1, 0, 0, -angle3);

    glBegin(GL_POLYGON);
    glVertex2i(220, 270);
    glVertex2i(200, 250);
    glVertex2i(250, 250);
    glVertex2i(130 + angle3 * .5, 200 - angle3 * .5);
    glVertex2i(130 + angle3 * .5, 180 - angle3 * .5);
    glVertex2i(120 + angle3 * .5, 180 - angle3 * .5);
    glEnd();
    glPopMatrix();
    glutPostRedisplay();
    /**....................................ARM END............................................**/
}

void sceenario()
{

    /**Road------------------**/
    glColor3f(.7, 0.7, 0.7);
    glPushMatrix();
    glTranslatef(0, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2i(0, 20);
    glVertex2i(700, 20);
    glVertex2i(700, 300);
    glVertex2i(0, 300);
    glEnd();
    glPopMatrix();

    /**--------grass2----------**/
    glColor3f(.5, 1, 0.5);
    glPushMatrix();
    glTranslatef(0, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2i(0, 20);
    glVertex2i(700, 20);
    glVertex2i(700, 0);
    glVertex2i(0, 0);
    glEnd();
    glPopMatrix();

    /**-----------Border road--------**/
    glColor3f(1, 1, 0.5);
    glPushMatrix();
    glTranslatef(0, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2i(0, 160);
    glVertex2i(700, 160);
    glVertex2i(700, 155);
    glVertex2i(0, 155);
    glEnd();
    glPopMatrix();

    /**-------------tree---------------**/
    glColor3f(.1, 0.2, 0.1);
    glPushMatrix();
    glTranslatef(-m, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2i(72, 300);
    glVertex2i(78, 300);
    glVertex2i(78, 405);
    glVertex2i(72, 405);
    glEnd();

    glColor3f(.1, 0.5, 0.1);
    glBegin(GL_TRIANGLES);
    glVertex2i(75, 450);
    glVertex2i(100, 390);
    glVertex2i(50, 390);

    glVertex2i(75, 420);
    glVertex2i(100, 360);
    glVertex2i(50, 360);

    glVertex2i(75, 400);
    glVertex2i(100, 340);
    glVertex2i(50, 340);

    glEnd();
    glPopMatrix();

    /**-------------tree2---------------**/

    glPushMatrix();
    glTranslatef(-m, 0, 0);
    glColor3f(.1, 0.2, 0.1);
    glTranslatef(250, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2i(72, 300);
    glVertex2i(78, 300);
    glVertex2i(78, 405);
    glVertex2i(72, 405);
    glEnd();

    glColor3f(.1, 0.5, 0.1);
    glBegin(GL_POLYGON);
    glVertex2i(75, 450);
    glVertex2i(100, 390);
    glVertex2i(50, 390);

    glEnd();
    glBegin(GL_POLYGON);
    glVertex2i(75, 420);
    glVertex2i(100, 360);
    glVertex2i(50, 360);

    glEnd();
    glBegin(GL_POLYGON);
    glVertex2i(75, 400);
    glVertex2i(100, 340);
    glVertex2i(50, 340);

    glEnd();
    glPopMatrix();

    /**-------------windmill---------------**/
    glPushMatrix();
    glTranslatef(-mm + 800, 0, 0);
    // draw the tower
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(160, 300);
    glVertex2f(163, 440);
    //glVertex2f(160, 300);
    glVertex2f(175, 300);
    glVertex2f(175, 300);
    glVertex2f(172, 440);
    glEnd();
    // Rotate object

    glTranslatef(center_x, center_y, 0.0f);
    glRotatef(current_angle, 0, 0, 1);
    current_angle += step_angle;
    glTranslatef(-center_x, -center_y, 0.0f);

    // draw first rotor blade
    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(173, 440);
    glVertex2f(163, 440);
    glVertex2f(168, 530);
    glEnd();
    // draw second rotor blade
    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(170, 434);
    glVertex2f(175, 440);
    glVertex2f(247, 400);
    glEnd();
    // draw third rotor blade
    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(162, 440);
    glVertex2f(167, 434);
    glVertex2f(88, 400);
    glEnd();
    // circle in the middle
    float theta;
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    for (int i = 0; i <= 360; i++)
    {
        theta = i * 3.142 / 180;
        glVertex2f(168 + 7 * cos(theta), 440 + 6.5 * sin(theta));
    }
    glEnd();
    glPopMatrix();
}
void mountain()
{
    /**----------Sky----**/

    glPushMatrix();
    glTranslatef(0, 0, 0);
    glBegin(GL_POLYGON);
    glColor3f(.8, .89, 1);
    glVertex2i(0, 350);

    glColor3f(.8, .89, 1);
    glVertex2i(700, 350);

    glColor3f(.2, .58, 1);
    glVertex2i(700, 500);

    glColor3f(.2, .58, 1);
    glVertex2i(0, 500);
    glEnd();
    glPopMatrix();

    /**----------Grass----**/
    glColor3f(.5, 1, 0.5);
    glPushMatrix();
    glTranslatef(0, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2i(0, 350);
    glVertex2i(700, 350);
    glVertex2i(700, 300);
    glVertex2i(0, 300);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    int k = 1, i;
    for (i = 0; i < 10; i++)
    {
        glTranslatef(+mount * k - 600 * i * .5, -10, 0);
        k = k * .05;
        cloud();
        glColor3f(.2, .8, .2);
        glBegin(GL_TRIANGLES);
        glVertex2i(0, 360);
        glVertex2i(50, 400);
        glVertex2i(100, 360);

        glVertex2i(80, 350);
        glVertex2i(200, 450);
        glVertex2i(300, 350);

        glVertex2i(280, 360);
        glVertex2i(360, 430);
        glVertex2i(450, 360);

        glVertex2i(480, 340);
        glVertex2i(560, 430);
        glVertex2i(640, 340);
        glEnd();
    }

    glPopMatrix();
}
void sceenario2()
{

    /**-------------tree---------------**/
    glColor3f(.1, 0.2, 0.1);
    glPushMatrix();
    glTranslatef(-mm, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2i(72, 300);
    glVertex2i(78, 300);
    glVertex2i(78, 405);
    glVertex2i(72, 405);
    glEnd();

    glColor3f(.1, 0.5, .1);
    glBegin(GL_POLYGON);
    glVertex2i(75, 450);
    glVertex2i(100, 390);
    glVertex2i(50, 390);

    glEnd();
    glBegin(GL_POLYGON);
    glVertex2i(75, 420);
    glVertex2i(100, 360);
    glVertex2i(50, 360);

    glEnd();
    glBegin(GL_POLYGON);
    glVertex2i(75, 400);
    glVertex2i(100, 340);
    glVertex2i(50, 340);

    glEnd();
    glPopMatrix();

    /**-------------tree2---------------**/

    glPushMatrix();
    glTranslatef(-mm, 0, 0);
    glColor3f(.1, 0.2, .1);
    glTranslatef(250, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2i(72, 300);
    glVertex2i(78, 300);
    glVertex2i(78, 405);
    glVertex2i(72, 405);
    glEnd();

    glColor3f(.1, 0.5, .1);
    glBegin(GL_POLYGON);
    glVertex2i(75, 450);
    glVertex2i(100, 390);
    glVertex2i(50, 390);

    glEnd();
    glBegin(GL_POLYGON);
    glVertex2i(75, 420);
    glVertex2i(100, 360);
    glVertex2i(50, 360);

    glEnd();
    glBegin(GL_POLYGON);
    glVertex2i(75, 400);
    glVertex2i(100, 340);
    glVertex2i(50, 340);

    glEnd();
    glPopMatrix();
}

void my_control_func()
{
    counter++;
    if (counter > 16800 || counter < 3800)
    {
        m = m;
        mm = mm;
        mount = mount;
        //hare();
    }
    else
    {
        mount += .2;
        if (flag > -800)
        {
            m -= .2;
            flag -= .2;
        }
        else
        {
            m = 350;
            flag = 700;

            F++;
        }
        if (flag2 > -1200)
        {
            mm -= .2;
            flag2 -= .2;
        }
        else
        {
            mm = 350;
            flag2 = 700;
        }
        if (F == 2)
        {
            b2_speed = 10;
        }
    }
}

void starting()
{
    /**sinboard**/
    glColor3f(.7, 0.1, 0.7);
    glPushMatrix();
    glTranslatef(200 - m, 00, 0);
    glBegin(GL_POLYGON);
    glVertex2i(10, 20);
    glVertex2i(40, 20);
    glVertex2i(40, 300);
    glVertex2i(10, 300);
    glEnd();
    glPopMatrix();
}
void victory2()
{
    /*--------pole 1------------*/
    glColor3f(0.396, 0.263, 0.129);
    glPushMatrix();
    glTranslatef(300 - m, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2i(20, 300);
    glVertex2i(25, 300);
    glVertex2i(25, 350);
    glVertex2i(20, 350);
    glEnd();
    glPopMatrix();
    /*----------Rope1-----------------*/
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(300 - m, 0, 0);
    glBegin(GL_LINES);
    glVertex2f(22.5, 350);
    glVertex2f(12.5, 70);
    glEnd();
    glPopMatrix();
    /*-----------Pole 2-----------*/
    glColor3f(0.396, 0.263, 0.129);
    glPushMatrix();
    glTranslatef(300 - m - 10, -280, 0);
    glBegin(GL_POLYGON);
    glVertex2i(20, 300);
    glVertex2i(25, 300);
    glVertex2i(25, 350);
    glVertex2i(20, 350);
    glEnd();
    glPopMatrix();
}

void texts()
{
    glColor3f(1.0, 1.0, 1.0);
    //glScalef(2,2,2);
    if (counter > 400 && counter < 800)
        drawstring(160, 250, 0.0, "Hi tortoise..");
    if (counter > 800 && counter < 1200)
        drawstring(100, 250, 0.0, "You are such a slowCoach");

    if (counter > 2400 && counter < 2800)
        drawstring(180, 250, 0.0, "Ha ha ha");
    if (counter > 3600 && counter < 4000)
        drawstring(160, 150, 0.0, "Ok, i will try!");
    if (counter > 3200 && counter < 3600)
        drawstring(150, 270, 0.0, "Prove me wrong by winning this race");

    if (counter > 1200 && counter < 1600)
        drawstring(150, 165, 0.0, "My dear friend! ");
    if (counter > 1600 && counter < 2000)
        drawstring(140, 165, 0.0, "You are so proud ");
    glColor3f(1.0, 1.0, 1.0);
    if (counter > 2000 && counter < 2400)
        drawstring(160, 150, 0.0, "of your speed");
    if (counter > 2800 && counter < 3200)
        drawstring(150, 250, 0.0, "Let's have a race");

    if (counter > 17300)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(.8, 0.9, 1);
        glPushMatrix();
        glTranslatef(0, 0, 0);
        glBegin(GL_POLYGON);
        glVertex2i(0, 0);
        glVertex2i(700, 0);
        glVertex2i(700, 1350);
        glVertex2i(0, 1350);
        glEnd();
        glPopMatrix();
        glColor3f(0.0, 0.0, 1);

        drawstring(240, 335, 0.0, "++++++++++++++++");
        glColor3f(0.0, 0.0, 1);
        drawstring(240, 350, 0.0, "+  Moral of this story +");
        glColor3f(0.0, 0.0, 1);
        drawstring(240, 365, 0.0, "++++++++++++++++");
        glColor3f(0.0, 0.0, 1);
        drawstring(215, 315, 0.0, "++++++++++++++++++++++++");
        glColor3f(0.0, 0.0, 1);
        drawstring(215, 300, 0.0, "+ Slow and steady wins the race +");
        glColor3f(0.0, 0.0, 1);
        drawstring(215, 285, 0.0, "++++++++++++++++++++++++");
    }
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    if (first)
    {
        frontscene();
    }
    else
    {

        mountain();
        sceenario();
        sceenario2();
        if (F == 0)
        {
            starting();
            //body2();
            hare();
        }
        //body1();
        if (F == 1)
        {
            // sleeping_body2();

            hare_sleep();
        }
        drawLeftCircle();

        if (F == 2)
        {
            // body2();
            hare();
            victory2();
            ba_posion = 1500;
        }
        texts();
        glFlush();
        glutPostRedisplay();
        my_control_func();
    }
}
void keys(unsigned char key, int x, int y)
{
    if (key == ' ')
    {
        first = 0;
    }
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1350, 700);
    glutInitWindowPosition(100, 50);
    glutCreateWindow("Slow and Steady wins the race");
    glutKeyboardFunc(keys);
    glutDisplayFunc(display);
    loadBackground();
    myInit();
    glutMainLoop();
}
void cloud()
{

    float scale_cloud = .3;
    int trns_x = -1000;
    int trns_y = 1150;

    glColor3f(0.8, .9, 1);

    /**-----------------Cloud 1---------------**/
    glPushMatrix(); // tree leaves
    //glColor3f(0,.5,0);
    glScalef(scale_cloud, scale_cloud, scale_cloud);
    glTranslatef(250 + trns_x, 360 + trns_y, 0);
    circle(60);
    glPopMatrix();

    glPushMatrix();
    //glColor3f(0,.5,0);
    glScalef(scale_cloud, scale_cloud, scale_cloud);
    glTranslatef(260 + trns_x, 400 + trns_y, 0);
    circle(60);
    glPopMatrix();

    glPushMatrix();
    glScalef(scale_cloud, scale_cloud, scale_cloud);

    glTranslatef(300 + trns_x, 370 + trns_y, 0);
    circle(50);
    glPopMatrix();

    glPushMatrix();
    glScalef(scale_cloud, scale_cloud, scale_cloud);
    //glColor3f(0,.5,0);
    glTranslatef(330 + trns_x, 450 + trns_y, 0);
    circle(50);
    glPopMatrix();

    glPushMatrix();
    glScalef(scale_cloud, scale_cloud, scale_cloud);
    //glColor3f(0,.5,0);
    glTranslatef(350 + trns_x, 350 + trns_y, 0);
    circle(40);
    glPopMatrix();

    glPushMatrix();
    glScalef(scale_cloud, scale_cloud, scale_cloud);
    //glColor3f(0,.5,0);
    glTranslatef(365 + trns_x, 400 + trns_y, 0);
    circle(40);
    glPopMatrix();

    glPushMatrix();
    glScalef(scale_cloud, scale_cloud, scale_cloud);
    //glColor3f(0,.5,0);
    glTranslatef(370 + trns_x, 430 + trns_y, 0);
    circle(40);
    glPopMatrix();

    glPushMatrix();
    glScalef(scale_cloud, scale_cloud, scale_cloud);
    //glColor3f(0,.5,0);
    glTranslatef(390 + trns_x, 350 + trns_y, 0);
    circle(40);
    glPopMatrix();

    glPushMatrix();
    glScalef(scale_cloud, scale_cloud, scale_cloud);
    //glColor3f(0,.5,0);
    glTranslatef(390 + trns_x, 400 + trns_y, 0);
    circle(40);
    glPopMatrix();

    /**-----------------Cloud 2---------------**/
    trns_x = -500;

    glPushMatrix(); // tree leaves
    //glColor3f(0,.5,0);
    glScalef(scale_cloud, scale_cloud, scale_cloud);
    glTranslatef(250 + trns_x, 360 + trns_y, 0);
    circle(60);
    glPopMatrix();

    glPushMatrix();
    //glColor3f(0,.5,0);
    glScalef(scale_cloud, scale_cloud, scale_cloud);
    glTranslatef(260 + trns_x, 400 + trns_y, 0);
    circle(60);
    glPopMatrix();

    glPushMatrix();
    glScalef(scale_cloud, scale_cloud, scale_cloud);

    glTranslatef(300 + trns_x, 370 + trns_y, 0);
    circle(50);
    glPopMatrix();

    glPushMatrix();
    glScalef(scale_cloud, scale_cloud, scale_cloud);
    //glColor3f(0,.5,0);
    glTranslatef(330 + trns_x, 450 + trns_y, 0);
    circle(50);
    glPopMatrix();

    glPushMatrix();
    glScalef(scale_cloud, scale_cloud, scale_cloud);
    //glColor3f(0,.5,0);
    glTranslatef(350 + trns_x, 350 + trns_y, 0);
    circle(40);
    glPopMatrix();

    glPushMatrix();
    glScalef(scale_cloud, scale_cloud, scale_cloud);
    //glColor3f(0,.5,0);
    glTranslatef(365 + trns_x, 400 + trns_y, 0);
    circle(40);
    glPopMatrix();

    glPushMatrix();
    glScalef(scale_cloud, scale_cloud, scale_cloud);
    //glColor3f(0,.5,0);
    glTranslatef(370 + trns_x, 430 + trns_y, 0);
    circle(40);
    glPopMatrix();

    glPushMatrix();
    glScalef(scale_cloud, scale_cloud, scale_cloud);
    //glColor3f(0,.5,0);
    glTranslatef(390 + trns_x, 350 + trns_y, 0);
    circle(40);
    glPopMatrix();

    glPushMatrix();
    glScalef(scale_cloud, scale_cloud, scale_cloud);
    //glColor3f(0,.5,0);
    glTranslatef(390 + trns_x, 400 + trns_y, 0);
    circle(40);
    glPopMatrix();

    /**-----------------Cloud 3---------------**/

    trns_x = -1200;

    glPushMatrix(); // tree leaves
    //glColor3f(0,.5,0);
    glScalef(scale_cloud, scale_cloud, scale_cloud);
    glTranslatef(250 + trns_x, 360 + trns_y, 0);
    circle(60);
    glPopMatrix();

    glPushMatrix();
    //glColor3f(0,.5,0);
    glScalef(scale_cloud, scale_cloud, scale_cloud);
    glTranslatef(260 + trns_x, 400 + trns_y, 0);
    circle(60);
    glPopMatrix();

    glPushMatrix();
    glScalef(scale_cloud, scale_cloud, scale_cloud);

    glTranslatef(300 + trns_x, 370 + trns_y, 0);
    circle(50);
    glPopMatrix();

    glPushMatrix();
    glScalef(scale_cloud, scale_cloud, scale_cloud);
    //glColor3f(0,.5,0);
    glTranslatef(330 + trns_x, 450 + trns_y, 0);
    circle(50);
    glPopMatrix();

    glPushMatrix();
    glScalef(scale_cloud, scale_cloud, scale_cloud);
    //glColor3f(0,.5,0);
    glTranslatef(350 + trns_x, 350 + trns_y, 0);
    circle(40);
    glPopMatrix();

    glPushMatrix();
    glScalef(scale_cloud, scale_cloud, scale_cloud);
    //glColor3f(0,.5,0);
    glTranslatef(365 + trns_x, 400 + trns_y, 0);
    circle(40);
    glPopMatrix();

    glPushMatrix();
    glScalef(scale_cloud, scale_cloud, scale_cloud);
    //glColor3f(0,.5,0);
    glTranslatef(370 + trns_x, 430 + trns_y, 0);
    circle(40);
    glPopMatrix();

    glPushMatrix();
    glScalef(scale_cloud, scale_cloud, scale_cloud);
    //glColor3f(0,.5,0);
    glTranslatef(390 + trns_x, 350 + trns_y, 0);
    circle(40);
    glPopMatrix();

    glPushMatrix();
    glScalef(scale_cloud, scale_cloud, scale_cloud);
    //glColor3f(0,.5,0);
    glTranslatef(390 + trns_x, 400 + trns_y, 0);
    circle(40);
    glPopMatrix();
}

int i;
void circle(GLdouble rad)
{
    GLint points = 50;
    GLdouble delTheta = (2.0 * PI) / (GLdouble)points;
    GLdouble theta = 0.0;

    glBegin(GL_POLYGON);
    {
        for (i = 0; i <= 50; i++, theta += delTheta)
        {
            glVertex2f(rad * cos(theta), rad * sin(theta));
        }
    }
    glEnd();
}
void hare()
{
    /**-----------Head------------**/
    glPushMatrix();
    glColor3f(1, 1, 1);
    glScalef(.5, .7, .5);
    glTranslatef(110 + 360 + 2 * m, 245 + 100, 1);
    circle(20);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.5, 0.5, 0.5);
    glScalef(.5, .7, .5);
    glTranslatef(110 + 350 + 2 * m, 245 + 100, 1);
    circle(5);
    glPopMatrix();
    /**-----------Neck-----------**/
    glPushMatrix();
    glColor3f(1, 1, 1);
    glScalef(.5, .7, .5);
    glTranslatef(210 + 360 + 2 * m, 180 + 100, 1);
    glRotatef(20, 0, 0, 1);
    glBegin(GL_POLYGON);
    glVertex3f(-70, 90, 1);
    glVertex3f(-70, 50, 1);
    glVertex3f(-50, 50, 1);
    glVertex3f(-50, 90, 1);
    glEnd();
    glPopMatrix();
    /**-----------Leg1-----------**/
    glPushMatrix();
    glColor3f(1, 1, 1);
    glScalef(.5, .7, .5);
    glTranslatef(230 + 350 + 2 * m, 110 + 100, 1);

    glBegin(GL_POLYGON);
    glVertex3f(-80, 90, 1);
    glVertex3f(-85, 70, 1);
    glVertex3f(-45, 70, 1);
    glVertex3f(-50, 90, 1);
    glEnd();
    glPopMatrix();
    /**-----------LEg2-----------**/
    glPushMatrix();
    glColor3f(1, 1, 1);
    glScalef(.5, .7, .5);
    glTranslatef(300 + 345 + 2 * m, 110 + 100, 1);
    //glRotatef(20,0,0,1);
    glBegin(GL_POLYGON);
    glVertex3f(-80, 90, 1);
    glVertex3f(-85, 70, 1);
    glVertex3f(-45, 70, 1);
    glVertex3f(-50, 90, 1);
    glEnd();
    glPopMatrix();

    /**-----------Body-----------------**/
    glPushMatrix();
    glColor3f(1, 1, 1);
    glScalef(.5, .7, .5);
    glTranslatef(300 + 200 + 2 * m, 120 + 200, 1);
    circle(20);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1, 1, 1);
    glScalef(.5, .7, .5);
    glTranslatef(300 + 270 + 2 * m, 110 + 215, 1);
    circle(35);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1, 1, 1);
    glScalef(.5, .7, .5);
    glTranslatef(300 + 350 + 2 * m, 110 + 100, 1);
    //glRotatef(20,0,0,1);
    glBegin(GL_POLYGON);
    glVertex3f(-80, 150, 1);
    glVertex3f(-85, 80, 1);
    glVertex3f(-145, 80, 1);
    glVertex3f(-150, 130, 1);
    glEnd();
    glPopMatrix();
    /**tail**/
    glPushMatrix();
    glColor3f(1, 1, 1);
    glScalef(.5, .7, .5);
    glTranslatef(300 + 350 + 2 * m, 110 + 100, 1);
    glBegin(GL_TRIANGLES);
    glVertex2i(-55, 110);
    glVertex2i(-30, 120);
    glVertex2i(-55, 90);
    glEnd();
    glPopMatrix();
    /**ear**/
    glPushMatrix();
    glColor3f(1, 1, 1);
    glScalef(.5, .7, .5);
    glTranslatef(300 + 235 + 2 * m, 110 + 145, 1);
    glBegin(GL_TRIANGLES);
    glVertex2i(-55, 110);
    glVertex2i(-25, 120);
    glVertex2i(-55, 90);

    glVertex2i(-55, 110);
    glVertex2i(-25, 135);
    glVertex2i(-55, 90);
    glEnd();
    glPopMatrix();
}

void hare_sleep()
{
    /**-----------Head------------**/
    glPushMatrix();
    glColor3f(1, 1, 1);
    glScalef(.5, .5, 1);
    glTranslatef(110 + 60 - 2 * m, 640, 1);
    circle(20);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.5, 0.5, 0.5);
    glScalef(.5, .5, 1);
    glTranslatef(110 + 50 - 2 * m, 640, 1);
    circle(2);
    glPopMatrix();
    /**-----------Body-----------------**/
    glPushMatrix();
    glColor3f(1, 1, 1);
    glScalef(.5, .5, 1);
    glTranslatef(200 - 2 * m, 620, 1);
    circle(20);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1, 1, 1);
    glScalef(.5, .5, 1);
    glTranslatef(260 - 2 * m, 630, 1);
    circle(30);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1, 1, 1);
    //glScalef(.5,.5,1);

    glBegin(GL_POLYGON);
    glVertex3f(100 - m, 320, 1);
    glVertex3f(100 - m, 300, 1);
    glVertex3f(130 - m, 300, 1);
    glVertex3f(130 - m, 330, 1);
    glEnd();
    glPopMatrix();
    /**tail**/
    glPushMatrix();
    glColor3f(1, 1, 1);
    glScalef(.5, .5, 1);
    glTranslatef(340 - 2 * m, 220 + 300, 1);
    glBegin(GL_TRIANGLES);
    glVertex2i(-55, 110);
    glVertex2i(-30, 120);
    glVertex2i(-55, 90);
    glEnd();
    glPopMatrix();
    /**ear**/
    glPushMatrix();
    glColor3f(1, 1, 1);
    glScalef(.5, .5, 1);
    glTranslatef(235 - 2 * m, 400 + 145, 1);
    glBegin(GL_TRIANGLES);
    glVertex2i(-55, 110);
    glVertex2i(-25, 120);
    glVertex2i(-55, 90);

    glVertex2i(-55, 110);
    glVertex2i(-25, 135);
    glVertex2i(-55, 90);
    glEnd();
    glPopMatrix();
    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslatef(-m, 0, 1);
    drawstring(55, 320, 0.0, "Z Z");
    drawstring(45, 340, 0.0, "Z Z");
    drawstring(35, 360, 0.0, "Z Z");
    glPopMatrix();
}