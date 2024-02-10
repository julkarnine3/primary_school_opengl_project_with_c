// CGIPL Lab Assignment - 3 (2085)

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <windows.h>
#include <iostream>
#include "BmpLoader.h"

unsigned int ID;
GLboolean redFlag = true, switchOne = false, amb1=true, diff1=true, spec1=true, amb2=true, diff2=true, spec2=true, amb3=true, diff3=true, spec3=true;
double windowHeight=1000, windowWidth=800;
//double eyeX=70.0, eyeY=3.0, eyeZ=60.0, refX = -3, refY=0,refZ=0;
double eyeX=80.0, eyeY=20.0, eyeZ=140.0, refX = 0, refY=0,refZ=0;
double theta = 360.0, y = 1.36, z = 7.97888, a=2;
GLuint textureID = 7;
int wave_count = 0, on = 0, off = 0, p = 0;
double points[45][45][3], r = 1.85, s = 0.00681817;
double pi = acos(-1);

GLfloat hold;

bool isDay = true;

//z = 7.97888
static GLfloat v_cube[8][3] =
{
    {0.0, 0.0, 0.0}, //0
    {0.0, 0.0, 3.0}, //1
    {3.0, 0.0, 3.0}, //2
    {3.0, 0.0, 0.0}, //3
    {0.0, 3.0, 0.0}, //4
    {0.0, 3.0, 3.0}, //5
    {3.0, 3.0, 3.0}, //6
    {3.0, 3.0, 0.0}  //7
};

static GLubyte quadIndices[6][4] =
{
    {0, 1, 2, 3}, //bottom
    {4, 5, 6, 7}, //top
    {5, 1, 2, 6}, //front
    {0, 4, 7, 3}, // back is clockwise
    {2, 3, 7, 6}, //right
    {1, 5, 4, 0}  //left is clockwise
};


static GLfloat colors[6][3] =
{
    {0.4, 0.1, 0.0}, //bottom
    {0.6, 0.0, 0.7}, //top
    {0.0, 1.0, 0.0},
    {0.0, 1.0, 1.0},
    {0.8, 0.0, 0.0},
    {0.3, 0.6, 0.7}
};
static void getNormal3p
(GLfloat x1, GLfloat y1,GLfloat z1, GLfloat x2, GLfloat y2,GLfloat z2, GLfloat x3, GLfloat y3,GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2-x1;
    Uy = y2-y1;
    Uz = z2-z1;

    Vx = x3-x1;
    Vy = y3-y1;
    Vz = z3-z1;

    Nx = Uy*Vz - Uz*Vy;
    Ny = Uz*Vx - Ux*Vz;
    Nz = Ux*Vy - Uy*Vx;

    glNormal3f(Nx,Ny,Nz);
}


void drawCube()
{
    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        glVertex3fv(&v_cube[quadIndices[i][0]][0]);
        glVertex3fv(&v_cube[quadIndices[i][1]][0]);
        glVertex3fv(&v_cube[quadIndices[i][2]][0]);
        glVertex3fv(&v_cube[quadIndices[i][3]][0]);
    }
    glEnd();
}
void Cube()
{
    glEnable(GL_LIGHTING); // Enable lighting
    glEnable(GL_LIGHT0);   // Enable light 0

    // Material properties
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
    GLfloat mat_diffuse[] = {0.8, 0.8, 0.8, 1.0};
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_shininess[] = {50.0};

    // Set material properties
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);

    glBegin(GL_QUADS);
    for (GLint i = 0; i < 6; i++)
    {
        getNormal3p(v_cube[quadIndices[i][0]][0], v_cube[quadIndices[i][0]][1], v_cube[quadIndices[i][0]][2],
                    v_cube[quadIndices[i][1]][0], v_cube[quadIndices[i][1]][1], v_cube[quadIndices[i][1]][2],
                    v_cube[quadIndices[i][2]][0], v_cube[quadIndices[i][2]][1], v_cube[quadIndices[i][2]][2]);

        for (GLint j = 0; j < 4; j++)
        {
            glVertex3fv(&v_cube[quadIndices[i][0]][0]);
            glTexCoord2f(1, 1);
            glVertex3fv(&v_cube[quadIndices[i][1]][0]);
            glTexCoord2f(1, 0);
            glVertex3fv(&v_cube[quadIndices[i][2]][0]);
            glTexCoord2f(0, 0);
            glVertex3fv(&v_cube[quadIndices[i][3]][0]);
            glTexCoord2f(0, 1);
        }
    }
    glEnd();

    glDisable(GL_LIGHTING); // Disable lighting
}


void drawCube1(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX=0, GLfloat ambY=0, GLfloat ambZ=0, GLfloat shine=50)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { ambX, ambY, ambZ, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {shine};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        getNormal3p(v_cube[quadIndices[i][0]][0], v_cube[quadIndices[i][0]][1], v_cube[quadIndices[i][0]][2],
                    v_cube[quadIndices[i][1]][0], v_cube[quadIndices[i][1]][1], v_cube[quadIndices[i][1]][2],
                    v_cube[quadIndices[i][2]][0], v_cube[quadIndices[i][2]][1], v_cube[quadIndices[i][2]][2]);
        glVertex3fv(&v_cube[quadIndices[i][0]][0]);
        glVertex3fv(&v_cube[quadIndices[i][1]][0]);
        glVertex3fv(&v_cube[quadIndices[i][2]][0]);
        glVertex3fv(&v_cube[quadIndices[i][3]][0]);
    }
    glEnd();
}


static GLfloat v_pyramid[5][3] =
{
    {0.0, 0.0, 0.0},
    {0.0, 0.0, 2.0},
    {2.0, 0.0, 2.0},
    {2.0, 0.0, 0.0},
    {1.0, 4.0, 1.0}
};

static GLubyte p_Indices[4][3] =
{
    {4, 1, 2},
    {4, 2, 3},
    {4, 3, 0},
    {4, 0, 1}
};

static GLubyte PquadIndices[1][4] =
{
    {0, 3, 2, 1}
};

void drawpyramid()
{
    glBegin(GL_TRIANGLES);
    for (GLint i = 0; i <4; i++)
    {
        glVertex3fv(&v_pyramid[p_Indices[i][0]][0]);
        glVertex3fv(&v_pyramid[p_Indices[i][1]][0]);
        glVertex3fv(&v_pyramid[p_Indices[i][2]][0]);
    }
    glEnd();

    glBegin(GL_QUADS);
    for (GLint i = 0; i <1; i++)
    {
        glVertex3fv(&v_pyramid[PquadIndices[i][0]][0]);
        glVertex3fv(&v_pyramid[PquadIndices[i][1]][0]);
        glVertex3fv(&v_pyramid[PquadIndices[i][2]][0]);
        glVertex3fv(&v_pyramid[PquadIndices[i][3]][0]);
    }
    glEnd();

}


void base()
{
   ///Room1
    /// back wall
  // glColor3f(0.8, 0.9, 0.9);
    //glColor3f(1.0, 1.0, 1.0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,9);
    glPushMatrix();
    glTranslatef(-1.5,-1,-1.5);
    glScalef(19.6, 12, 0.5);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    /// left wall
    //glColor3f(0.5, 0.5, 0.6);
    //glColor3f(1.0, 1.0, 1.0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,9);
    glPushMatrix();
    glTranslatef(-2.3,-1,-0.4);
    glScalef(0.4,12, 9.7);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

 /// right wall
    //glColor3f(0.5, 0.5, 0.6);
    //glColor3f(1.0, 1.0, 1.0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,9);
    glPushMatrix();
    glTranslatef(18,-0.5,-0.4);
    glScalef(0.4,10, 8.5);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    ///right wall2
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,9);
    //glColor3f(0.5, 0.5, 0.6);
    //glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
    glTranslatef(38,-0.5,-0.4);
    glScalef(0.4,10, 8.5);
     Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
     ///right wall3
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,9);
    //glColor3f(0.5, 0.5, 0.6);
    //glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
    glTranslatef(55.9,-0.5,-0.4);
    glScalef(0.4,12, 9.7);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    ///ceiling
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,13);
    //glColor3f(0.8, 0.8, 0.9);
    //glColor3f(0.1f, 0.1f, 0.1f);//Dark grey
    glPushMatrix();
    //glScalef(5, 0.1, 7);
    glTranslatef(-1.1,14,0);
    glScalef(19, 0.4, 10.5);
     Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    ///
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,9);
    glTranslatef(-1.1,15,0);
    glScalef(19, 0.1, 10.5);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    ///
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,9);
    glTranslatef(-1.1,0.3,0);
    glScalef(19, 0.1, 10.5);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    ///Top_ceiling
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,9);
    glPushMatrix();
    glTranslatef(-1.1,29,0);
    glScalef(19, 0.4, 10.5);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // carpet
   // glColor3f(0.4, 0.1, 0.0);
    //glPushMatrix();
    //glScalef(5, 0.1, 7);
    //glTranslatef(3,-0.2,7);
    //glScalef(1.3, 0.01, 1.7);
    //drawCube();
    //glPopMatrix();

    ///school surface
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,14);
    glTranslatef(-1.1,-1,0);
    glScalef(19, 0.5, 10.5);
    Cube();
    glPopMatrix();
    //Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    /// left_piller
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,13);
    glTranslatef(7.7,-1,38);
    glScalef(0.4,12.3, 0.7);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    /// right_piller
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,13);
    glTranslatef(65.9,-1,38);
    glScalef(0.4,12.3, 0.7);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    ///ceiling front
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,13);
    glTranslatef(8.8,31,39);
    glScalef(19.2,1.7, 0.2);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
///room_front
void room_front(){
    ///room1
    //left
      glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(8.8,0,34);
    glScalef(4.5,5, 0.2);
     Cube();
    glPopMatrix();
    //right
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(27,0,34);
    glScalef(0.5,5, 0.2);
    Cube();
    glPopMatrix();
     //up
     glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(22,11.5,34);
    glScalef(1.8,1.2, 0.2);
     Cube();
    glPopMatrix();
}

///class_name_text
void text1(){
    //Class 1
    glPushMatrix();
    glTranslatef(22.8,11.6,34.4);
    glScalef(1.3,0.8, 0.1);
    Cube();
    glPopMatrix();
}
void text5(){
    //Teachers Room
    glPushMatrix();
    glTranslatef(42.4,11.6,34.4);
    glScalef(1.3,0.8, 0.1);
    Cube();
    glPopMatrix();
}
void text6(){
    //Store Room
    glPushMatrix();
    glTranslatef(61,11.6,34.4);
    glScalef(1.3,0.8, 0.1);
    Cube();
    glPopMatrix();
}

void text2(){
    //Class 2
    glPushMatrix();
    glTranslatef(22.8,26.6,34.4);
    glScalef(1.3,0.8, 0.1);
    Cube();
    glPopMatrix();
}
void text3(){
    //Class 3
    glPushMatrix();
    glTranslatef(42.4,26.6,34.4);
    glScalef(1.3,0.8, 0.1);
    Cube();
    glPopMatrix();
}
void text4(){
    //Class 4
    glPushMatrix();
    glTranslatef(61,26.6,34.4);
    glScalef(1.3,0.8, 0.1);
    Cube();
    glPopMatrix();
}

void sky(){
     ///left sky wall
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,7);
    glPushMatrix();
    glTranslatef(-110,-0.9,150);
    glRotatef(-90,1,0,0);
    glScalef(0.1,80,100 );
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    ///right sky wall
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,7);
    glPushMatrix();
    glTranslatef(200,-0.9,-40);
    glScalef(0.1,90,100);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    /// back sky wall
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,7);
    glPushMatrix();
    glTranslatef(-140,-0.9,-30);
    glScalef(113, 80, 0.1);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}
void area(){
    ///surface
    //glColor3f(1.0,1.0, 1.0);
   // Set mud color (dark brown)
    //glColor3f(0.4, 0.2, 0.0);
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,2);
    //glScalef(5, 0.1, 7);
    glTranslatef(-110,-1,-40);
    glScalef(120, 0.1, 100);
    //drawCube();
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);



    ///left outside wall
    //glColor3f(0.5, 0.5, 0.6);
    //glColor3f(1.0, 1.0, 1.0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 1);

    glPushMatrix();
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glScalef(12, 1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);

    glTranslatef(-2.1, -0.9, 0.8);
    glScalef(0.4, 3, 37);
    Cube();

    glPopMatrix();

    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);

    glDisable(GL_TEXTURE_2D);
    //
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,22);

    glTranslatef(-2.9,-0.9,0.8);
    glScalef(0.2,3,37 );
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    //
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,22);
    glTranslatef(-2.3,8,0.8);
    glScalef(0.45,0.1,37 );
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


     ///right outside wall
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 17);

    glPushMatrix();
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glScalef(1, 6, 1);
    glMatrixMode(GL_MODELVIEW);

    glTranslatef(75,-0.9,0.8);
    glScalef(0.4,3,37 );
    Cube();
    glPopMatrix();

    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);

    glDisable(GL_TEXTURE_2D);
    //
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,22);
    glTranslatef(75.8,-0.9,0.8);
    glScalef(0.2,3,37 );
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    //
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,22);
    glTranslatef(75,8,0.8);
    glScalef(0.45,0.1,37 );
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

     /// back outside wall
      glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
     glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,9);
    glTranslatef(-2.1,-0.9,-0.1);
    glScalef(26, 3, 0.3);
     Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    /// front_left outside wall
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,22);
    glTranslatef(-3.0,-0.9,111.5);
    glScalef(10.5, 3, 0.3);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    /// front_right outside wall
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,22);
    glTranslatef(46.3,-0.9,111.5);
    glScalef(10, 3, 0.3);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

   ///Gate....
   /// right gate piller
    //glColor3f(0.5, 0.5, 0.6);
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,13);
    glTranslatef(45,-0.9,111.5);
    glScalef(0.5, 8, 0.5);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    /// left gate piller
    //glColor3f(0.5, 0.5, 0.6);
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,13);
    glTranslatef(27.5,-0.9,111.5);
    glScalef(0.5, 8, 0.5);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    /// upper gate piller
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,9);
    glTranslatef(29,15,111.5);
    glScalef(5.3, 2, 0.5);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    /// upper_text gate
    glColor3f(1, 1, 1);
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,8);
    glTranslatef(29.5,15,112.9);
    glScalef(5, 2, 0.1);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    /// left_front_wall_text
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,11);
    glTranslatef(5,1.8,112.2);
    glScalef(5, 1.5, 0.1);
    Cube();
    glPopMatrix();
   glDisable(GL_TEXTURE_2D);

   /*/// right_front_wall_text
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,12);
    glTranslatef(35,2.5,112.2);
    glScalef(1, 2, 0.01);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);*/

}
void tree(){
    ///kando
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,23);
    glTranslatef(24,-0.9,114);
    glScalef(0.2, 2.5, 0.2);
    Cube();
    glPopMatrix();
   glDisable(GL_TEXTURE_2D);
     ///upper
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,16);
    glTranslatef(23,4,113);
    glScalef(1, 1, 1);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
     ///upper1
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,16);
    glTranslatef(23.8,7,113.8);
    glScalef(0.5,0.5, 0.5);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    ///upper2
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,16);
    glTranslatef(24,8.5,113.9);
    glScalef(0.3,0.3, 0.3);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}


void tree1(){
    ///kando
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,23);
    glTranslatef(24,-0.9,114);
    glScalef(0.2, 4, 0.2);
    Cube();
    glPopMatrix();
   glDisable(GL_TEXTURE_2D);
     ///upper
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,16);
    glTranslatef(23,10,113);
    glScalef(1, 1, 1);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
     ///upper1
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,16);
    glTranslatef(23.8,13,113.8);
    glScalef(0.5,0.5, 0.5);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    ///upper2
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,16);
    glTranslatef(24,14.5,113.9);
    glScalef(0.3,0.3, 0.3);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
void blackboard(){
   // Draw blackboard
	glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,20);
	glBegin(GL_QUADS);
	glVertex3f(-6.0f, 2.0f, -9.99f);
	glVertex3f(-6.0f, 5.5f, -9.99f);
	glVertex3f(6.0f, 5.5f, -9.99f);
	glVertex3f(6.0f, 2.0f, -9.99f);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,20);
	glBegin(GL_QUADS);
	glVertex3f(-5.8f, 2.2f, -9.98f);
	glVertex3f(-5.8f, 5.3f, -9.98f);
	glVertex3f(5.8f, 5.3f, -9.98f);
	glVertex3f(5.8f, 2.2f, -9.98f);
	glEnd();
	glDisable(GL_TEXTURE_2D);

}


//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// DEMO CODE FOR DRAW WARDROBE



//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// DEMO CODE FOR DRAW WINDOW
void window()
{
    //Window ********************************************

    //window white open
    glColor3f(1.0,1.0,1.0);
    glPushMatrix();
    glTranslatef(-0.9,1,8.9); //0.5,1,9.6
    //glRotatef(22, 0,0,1);
    glScalef(0.0001, .6, .3);
    Cube();
    glPopMatrix();

    //window side corner
    glColor3f(0.8,0.6,0.4);
    glPushMatrix();
    glTranslatef(-0.9,1,8.9);
    //glRotatef(22, 0,0,1);
    glScalef(0.04, 0.6, 0.0001);
    Cube();
    glPopMatrix();

    //window left side corner
    glColor3f(0.8,0.6,0.4);
    glPushMatrix();
    glTranslatef(-0.9,1,9.8);
    glScalef(0.04, 0.6, 0.0001);
    Cube();
    glPopMatrix();

    //window upper side corner
    glColor3f(0.7,0.6,0.5);
    glPushMatrix();
    glTranslatef(-0.8,2.7,8.9);
    //glRotatef(22, 0,0,1);
    glScalef(0.0001, 0.05, 0.4);
    Cube();
    glPopMatrix();


    //window lower side corner
    glColor3f(0.7,0.6,0.5);
    glPushMatrix();
    glTranslatef(-0.8,1.02,8.9);
    //glRotatef(22, 0,0,1);
    glScalef(0.0001, 0.02, 0.34);
    Cube();
    glPopMatrix();

    //window vertical bar 1
    glColor3f(0.0,0.0,0.0);
    glPushMatrix();
    glTranslatef(-0.87,2.1,8.9);
    //glRotatef(22, 0,0,1);
    glScalef(0.0001, 0.02, 0.3);
    Cube();
    glPopMatrix();

    //window vertical bar 2
    glColor3f(0.0,0.0,0.0);
    glPushMatrix();
    glTranslatef(-0.87,1.6,8.9);
    //glRotatef(22, 0,0,1);
    glScalef(0.0001, 0.02, 0.3);
    Cube();
    glPopMatrix();

    //window horizontal bar
    glColor3f(0.0,0.0,0.0);
    glPushMatrix();
    glTranslatef(-0.87,1,9.3);
    //glRotatef(22, 0,0,1);
    glScalef(0.0001, 0.6, 0.02);
    Cube();
    glPopMatrix();
}
void drawTable()
{
    // Table surface
    glPushMatrix();
    glTranslatef(1.4, 1.1, 3.5); // Adjust the y-translation to lift the table off the ground
    glScalef(0.6, -0.1, 0.6);
    Cube();
    glPopMatrix();

    // Table legs
    //glColor3f(0.6, 0.4, 0.2);
    for (int i = 0; i < 4; i++)
    {
        glPushMatrix();
        glTranslatef(1.5 + (i % 2) * 1.4, -0.3, 3.5 + (i / 2) * 1.6); // Adjust the y-translation to lift the legs off the ground
        glScalef(0.08, 0.42, 0.08);
        Cube();
        glPopMatrix();
    }

    // Chairs around the table
    //drawChair(2.1, 2.0);
    //drawChair(2.1, 5.5);
   // drawChair(0.6, 4.5);
    //drawChair(3.4, 4.5);
}
void table() {
  // Tabletop

   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D,23);
   glPushMatrix();
   glTranslatef(3, 1.01, 7);
   glScalef(0.5, 0.05, 0.4);
   Cube();
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);


  // Table leg 1
  glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D,21);
  glPushMatrix();
  glTranslatef(3, -0.5, 7); // Adjusted position for leg 1
  glScalef(0.02, 0.54, 0.02);
  Cube();
  glPopMatrix();

  // Table leg 2
  glPushMatrix();
  glTranslatef(4.4, -0.5, 7); // Adjusted position for leg 2
  glScalef(0.02, 0.54, 0.02);
  Cube();
  glPopMatrix();

  // Table leg 3
  glPushMatrix();
  glTranslatef(3, -0.5, 8); // Adjusted position for leg 3
  glScalef(0.02, 0.54, 0.02);
  Cube();
  glPopMatrix();

  // Table leg 4
  glPushMatrix();
  glTranslatef(4.35, -0.5, 8); // Adjusted position for leg 4
  glScalef(0.02, 0.54, 0.02);
  Cube();
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);
}
void table1() {
  // Tabletop

   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D,23);
   glPushMatrix();
   glTranslatef(3, 1.01, 7);
   glScalef(0.5, 0.05, 0.4);
   Cube();
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);

  // Table leg 1
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,21);
  glPushMatrix();
  glTranslatef(3, -0.5, 7); // Adjusted position for leg 1
  glScalef(0.02, 0.54, 0.02);
  Cube();
  glPopMatrix();

  // Table leg 2
  glPushMatrix();
  glTranslatef(4.4, -0.5, 7); // Adjusted position for leg 2
  glScalef(0.02, 0.54, 0.02);
  Cube();
  glPopMatrix();

  // Table leg 3
  glPushMatrix();
  glTranslatef(3, -0.5, 8); // Adjusted position for leg 3
  glScalef(0.02, 0.54, 0.02);
  Cube();
  glPopMatrix();

  // Table leg 4
  glPushMatrix();
  glTranslatef(4.35, -0.5, 8); // Adjusted position for leg 4
  glScalef(0.02, 0.54, 0.02);
  Cube();
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);
}


void chair() {
  // Seat
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,23);
  glPushMatrix();
  glTranslatef(3.05, 0.7, 6.8);
  glScalef(0.25, 0.025, 0.25);
  Cube();
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);

  // Backrest
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,21);
  glPushMatrix();
  glTranslatef(3, 1, 6.8); // Adjusted position for the backrest
  glScalef(0.26, 0.3, 0.02);
  Cube();
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);
  //inside backrest
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,23);
  glPushMatrix();
  glTranslatef(3.1, 1.15, 6.9); // Adjusted position for the backrest
  glScalef(0.2, 0.22, 0.001);
  Cube();
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);

  // Front leg 1
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,23);
  glPushMatrix();
  glTranslatef(3.05, -0.7, 7.5); // Adjusted position for leg 1
  glScalef(0.02, 0.5, 0.02);
  Cube();
  glPopMatrix();

  // Front leg 2
  glPushMatrix();
  glTranslatef(3.7, -0.7, 7.5); // Adjusted position for leg 2
  glScalef(0.02, 0.5, 0.02);
  Cube();
  glPopMatrix();

  // Back leg 1
  glPushMatrix();
  glTranslatef(3, -0.5, 6.8); // Adjusted position for leg 3
  glScalef(0.02, 0.5, 0.02);
  Cube();
  glPopMatrix();

  // Back leg 2
  glPushMatrix();
  glTranslatef(3.71, -0.4, 6.8); // Adjusted position for leg 4
  glScalef(0.02, 0.5, 0.02);
  Cube();
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);
}

void almari(){
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,28);
    glPushMatrix();
    glTranslatef(0,0,4);
    glScalef(0.12, 0.55, 0.4);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,28);
    glPushMatrix();
    glTranslatef(0,0,9);
    glScalef(0.12, 0.55, 0.4);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void element(){
    ///blackboard
    glPushMatrix();
    glTranslatef(18.5,1,10.3);
    glScalef(1.0, 2.2, 0.1);
    blackboard();
    glPopMatrix();
    //
    glPushMatrix();
    glTranslatef(38.5,1,10.3);
    glScalef(1.0, 2.2, 0.1);
    blackboard();
    glPopMatrix();
    //
    glPushMatrix();
    glTranslatef(57.3,1,10.3);
    glScalef(1.0, 2.2, 0.1);
    blackboard();
    glPopMatrix();
    //
    glPushMatrix();
    glTranslatef(18.5,-14,10.5);
    glScalef(1.0, 2.2, 0.1);
    blackboard();
    glPopMatrix();

   ///window
    glPushMatrix();
    glTranslatef(12.5,5,4.0);
    glScalef(4, 2, 2);
    window();
    glPopMatrix();
    ///window_opo
    glPushMatrix();
    glTranslatef(11,5,4.0);
    glScalef(4, 2, 2);
    window();
    glPopMatrix();
   ///chair
    glPushMatrix();
    glTranslatef(7,2.7,-10);
    glScalef(3, 2.7, 3);
    chair();
    glPopMatrix();

    ///big_table
    glPushMatrix();
    glTranslatef(4,2.7,-6);
    glScalef(3.5, 3.3, 2.5);
    table();
    glPopMatrix();

     ///High_bench1
    glPushMatrix();
    glTranslatef(-9,2.5,6);
    glScalef(7, 2.5, 1.5);
    table() ;
    glPopMatrix();

     ///low_bench1
    glPushMatrix();
    glTranslatef(-9,2.1,10.5);
    glScalef(7, 1.1, 1.2);
    table() ;
    glPopMatrix();

    ///High_bench2
    glPushMatrix();
    glTranslatef(-9,2.5,10);
    glScalef(7, 2.5, 1.5);
    table() ;
    glPopMatrix();

     ///low_bench2
    glPushMatrix();
    glTranslatef(-9,2.1,14.5);
    glScalef(7, 1.1, 1.2);
    table() ;
    glPopMatrix();

    ///High_bench3
    glPushMatrix();
    glTranslatef(-9,2.5,14);
    glScalef(7, 2.5, 1.5);
    table() ;
    glPopMatrix();

     ///low_bench3
    glPushMatrix();
    glTranslatef(-9,2.1,18.5);
    glScalef(7, 1.1, 1.2);
    table() ;
    glPopMatrix();

    ///High_bench4
    glPushMatrix();
    glTranslatef(-9,2.5,18);
    glScalef(7, 2.5, 1.5);
    table() ;
    glPopMatrix();

     ///low_bench4
    glPushMatrix();
    glTranslatef(-9,2.1,22.5);
    glScalef(7, 1.1, 1.2);
    table() ;
    glPopMatrix();

}
void element1(){
    ///chair
    glPushMatrix();
    glTranslatef(7,2.7,-10);
    glScalef(3, 2.7, 3);
    chair() ;
    glPopMatrix();
    ///big_table
    glPushMatrix();
    glTranslatef(4,2.7,-6);
    glScalef(3.5, 3.3, 2.5);
    table() ;
    glPopMatrix();
     ///High_bench1
    glPushMatrix();
    glTranslatef(-9,2.5,6);
    glScalef(7, 2.5, 1.5);
    table() ;
    glPopMatrix();
     ///low_bench1
    glPushMatrix();
    glTranslatef(-9,2.1,10.5);
    glScalef(7, 1.1, 1.2);
    table() ;
    glPopMatrix();
    ///High_bench2
    glPushMatrix();
    glTranslatef(-9,2.5,10);
    glScalef(7, 2.5, 1.5);
    table() ;
    glPopMatrix();

     ///low_bench2
    glPushMatrix();
    glTranslatef(-9,2.1,14.5);
    glScalef(7, 1.1, 1.2);
    table() ;
    glPopMatrix();
    ///High_bench3
    glPushMatrix();
    glTranslatef(-9,2.5,14);
    glScalef(7, 2.5, 1.5);
    table() ;
    glPopMatrix();
     ///low_bench3
    glPushMatrix();
    glTranslatef(-9,2.1,18.5);
    glScalef(7, 1.1, 1.2);
    table() ;
    glPopMatrix();
    ///High_bench4
    glPushMatrix();
    glTranslatef(-9,2.5,18);
    glScalef(7, 2.5, 1.5);
    table() ;
    glPopMatrix();
     ///low_bench4
    glPushMatrix();
    glTranslatef(-9,2.1,22.5);
    glScalef(7, 1.1, 1.2);
    table() ;
    glPopMatrix();

}
void element2(){
   ///chair
    glPushMatrix();
    glTranslatef(7,2.7,-10);
    glScalef(3, 2.7, 3);
    chair() ;
    glPopMatrix();
    ///chair1
    glPushMatrix();
    glRotatef(-90,0,1,0);
    glTranslatef(17,2.7,-44);
    glScalef(3, 2.7, 3);
    chair() ;
    glPopMatrix();
    ///chair2
    glPushMatrix();
    glRotatef(-90,0,1,0);
    glTranslatef(7,2.7,-45);
    glScalef(3, 2.7, 3);
    chair() ;
     glPopMatrix();
    ///chair3
    glPushMatrix();
    glRotatef(-90,0,1,0);
    glTranslatef(11,2.7,-45);
    glScalef(3, 2.7, 3);
    chair() ;
    glPopMatrix();
    ///big_table
    glPushMatrix();
    glTranslatef(4,2.7,-6);
    glScalef(3.5, 3.3, 2.5);
    table() ;
    glPopMatrix();
}
void siri(){
    ///siri_surface

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,16);
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(7,-1.3,40.8);
    glScalef(20,0.3, 23);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,12);
    ///siri_1
    glPushMatrix();
    //glColor3f(1.0, 1.0, 1.0);
    glTranslatef(58.5,0.8,54);
    glScalef(2.5,0.5, 1);
    Cube();
    glPopMatrix();
    ///siri_2
    glPushMatrix();
    //glColor3f(1.0, 1.0, 1.0);
    glTranslatef(58.5,2.5,52.5);
    glScalef(2.5,0.5, 1);
    Cube();
    glPopMatrix();
     ///siri_3
    glPushMatrix();
    //glColor3f(1.0, 1.0, 1.0);
    glTranslatef(58.5,3.5,51);
    glScalef(2.5,0.5, 1);
    Cube();
    glPopMatrix();
     ///siri_3
    glPushMatrix();
    //glColor3f(1.0, 1.0, 1.0);
    glTranslatef(58.5,4.5,49.5);
    glScalef(2.5,0.5, 1);
    Cube();
    glPopMatrix();
    ///siri_4
    glPushMatrix();
    //glColor3f(1.0, 1.0, 1.0);
    glTranslatef(58.5,5.5,48);
    glScalef(2.5,0.5, 1);
    Cube();
    glPopMatrix();
    ///siri_5
    glPushMatrix();
    //glColor3f(1.0, 1.0, 1.0);
    glTranslatef(58.5,6.5,46.5);
    glScalef(2.5,0.5, 1);
    Cube();
    glPopMatrix();
    ///siri_6
    glPushMatrix();
    //glColor3f(1.0, 1.0, 1.0);
    glTranslatef(58.5,7.5,45);
    glScalef(2.5,0.5, 1);
    Cube();
    glPopMatrix();
    ///siri_7
    glPushMatrix();
    //glColor3f(1.0, 1.0, 1.0);
    glTranslatef(58.5,8.5,43.5);
    glScalef(2.5,0.5, 1);
    Cube();
    glPopMatrix();
    ///siri_8
    glPushMatrix();
    //glColor3f(1.0, 1.0, 1.0);
    glTranslatef(58.5,9.5,42);
    glScalef(2.5,0.5, 1);
    Cube();
    glPopMatrix();
     ///siri_9
    glPushMatrix();
    //glColor3f(1.0, 1.0, 1.0);
    glTranslatef(58.5,10.5,40.5);
    glScalef(2.5,0.5, 1);
    Cube();
    glPopMatrix();
    ///siri_10
    glPushMatrix();
    //glColor3f(1.0, 1.0, 1.0);
    glTranslatef(58.5,11.9,39);
    glScalef(2.5,0.5, 1);
    Cube();
    glPopMatrix();
    ///siri_11
    glPushMatrix();
    //glColor3f(1.0, 1.0, 1.0);
    glTranslatef(58.5,13.5,37.5);
    glScalef(2.5,0.5, 1);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}

void office_tex(){
    ///mujib
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,4);
    glTranslatef(35,7,9.5);
    glScalef(1,2, 0.01);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    ///hasina
    glPushMatrix();
     glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,5);
     glColor3f(1.0, 1.0, 1.0);
    glTranslatef(39,7,9.5);
    glScalef(1,2, 0.01);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    //
    ///bishagor
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,30);
    glTranslatef(52,0.9,112.5);
    glScalef(1,2, 0.01);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    //
    ///kajinajrul
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,33);
    glTranslatef(58,0.9,112.5);
    glScalef(1,2, 0.01);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    ///robindronat
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,31);
    glTranslatef(64,0.9,112.5);
    glScalef(1,2, 0.01);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    ///begumrokiya
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,32);
    glTranslatef(70,0.9,112.5);
    glScalef(1,2, 0.01);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void road()
{
    ///road
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,34);
    glTranslatef(-120,-0.5,115.5);
    glRotatef(90,1,0,0);
    glScalef(150,6, 0.01);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    ///road_stripe 1
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(-70,-0.3,124);
    glRotatef(90,1,0,0);
    glScalef(2,0.5, 0.01);
    Cube();
    glPopMatrix();

    ///road_stripe 2
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(-30,-0.3,124);
    glRotatef(90,1,0,0);
    glScalef(7,0.5, 0.01);
    Cube();
    glPopMatrix();

    ///road_stripe 3
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(10,-0.3,124);
    glRotatef(90,1,0,0);
    glScalef(7,0.5, 0.01);
    Cube();
    glPopMatrix();
    ///road_stripe 4
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(50,-0.3,124);
    glRotatef(90,1,0,0);
    glScalef(7,0.5, 0.01);
    Cube();
    glPopMatrix();

    ///road_stripe 5
    glPushMatrix();

    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(90,-0.3,124);
    glRotatef(90,1,0,0);
    glScalef(7,0.5, 0.01);
    Cube();
    glPopMatrix();

    ///road_stripe 5
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(130,-0.3,124);
    glRotatef(90,1,0,0);
    glScalef(7,0.5, 0.01);
    Cube();
    glPopMatrix();

    ///road_stripe 4
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(170,-0.3,124);
    glRotatef(90,1,0,0);
    glScalef(7,0.5, 0.01);
    Cube();
    glPopMatrix();

    ///road_stripe 4
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(210,-0.3,124);
    glRotatef(90,1,0,0);
    glScalef(7,0.5, 0.01);
    Cube();
    glPopMatrix();
}

void office_tex2(){
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,9);
    glTranslatef(30.5,5,9.3);
    glScalef(5.2,4.5,0.01);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    //
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,35);
    glTranslatef(49,3,9.3);
    glScalef(5.6,4,0.01);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}


void box(){
    //
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,36);
    glTranslatef(49,0,15.3);
    glScalef(1.5,1.8,1);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    //
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,36);
    glTranslatef(49,0,18.3);
    glScalef(1.5,1.8,1);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    //
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,36);
    glTranslatef(49,5.5,16.3);
    glScalef(1.5,1.8,1);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}

//=================Flag====================

void flag(){
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,9);
    glTranslatef(12,0,45.5);
    glScalef(0.2,8.5,0.1);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void rectangle(void)
{
    int x, y;
    double double_x, double_y, double_xb, double_yb;

    double scale_x = 0.8;
    double scale_y = 1.0;

    glEnable(GL_LIGHTING);
    glTranslatef(0.0f, 0.0f, -12.0f);
    glScalef(scale_x, scale_y, 1.0f);

    glBegin(GL_QUADS);
    for (x = 0; x < 34; x++)
    {
        for (y = 0; y < 34; y++)
        {
            double_x = double(x) / 34.0f;
            double_y = double(y) / 34.0f;
            double_xb = double(x + 1) / 34.0f;
            double_yb = double(y + 1) / 34.0f;

            // Specify normals for each vertex
            glNormal3f(0.0f, 0.0f, 1.0f);

            glTexCoord2f(double_x, double_y);
            glVertex3f(points[x][y][0], points[x][y][1], points[x][y][2]);

            glTexCoord2f(double_x, double_yb);
            glVertex3f(points[x][y + 1][0], points[x][y + 1][1], points[x][y + 1][2]);

            glTexCoord2f(double_xb, double_yb);
            glVertex3f(points[x + 1][y + 1][0], points[x + 1][y + 1][1], points[x + 1][y + 1][2]);

            glTexCoord2f(double_xb, double_y);
            glVertex3f(points[x + 1][y][0], points[x + 1][y][1], points[x + 1][y][2]);
        }
    }
    glEnd();

    if (wave_count == 5)
    {
        for (y = 0; y < 35; y++)
        {
            hold = points[5][y][2];

            for (x = 5; x < 34; x++)
            {
                points[x][y][2] = points[x + 1][y][2];
            }

            points[34][y][2] = hold;
        }

        wave_count = 0;
    }

    wave_count++;
}
void bar(){
    ///back_bar
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,9);
    glTranslatef(12,0,50);
    glScalef(0.2,4.5,0.1);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    ///front bar
     glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,9);
    glTranslatef(12,0,60);
    glScalef(0.2,4.5,0.1);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    ///up bar
     glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,9);
    glTranslatef(12,13,50);
    glScalef(0.2,0.2,3.4);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}


//===========================================================

void light0()
{
    glPushMatrix();
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {0.3, 0.3, 0.3, 1.0};
    GLfloat light_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 8.0, 8.0, 8.0, 0.0 }; //5 5 10

    glEnable( GL_LIGHT0);

    if(amb1 == true){glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient);}
    else{glLightfv( GL_LIGHT0, GL_AMBIENT, no_light);}

    if(diff1 == true){glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse);}
    else{glLightfv( GL_LIGHT0, GL_DIFFUSE, no_light);}

    if(spec1 == true){glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular);}
    else{glLightfv( GL_LIGHT0, GL_SPECULAR, no_light);}

    glLightfv( GL_LIGHT0, GL_POSITION, light_position);
    glPopMatrix();
}

void light1()
{
    glPushMatrix();
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {0.1, 0.1, 0.1, 1.0};
    GLfloat light_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 8.0, 8.0, 8.0, 0.0 }; //5 5 10

    glEnable( GL_LIGHT1);

    if(amb1 == true){glLightfv( GL_LIGHT1, GL_AMBIENT, light_ambient);}
    else{glLightfv( GL_LIGHT0, GL_AMBIENT, no_light);}

    if(diff1 == true){glLightfv( GL_LIGHT1, GL_DIFFUSE, light_diffuse);}
    else{glLightfv( GL_LIGHT0, GL_DIFFUSE, no_light);}

    if(spec1 == true){glLightfv( GL_LIGHT1, GL_SPECULAR, light_specular);}
    else{glLightfv( GL_LIGHT0, GL_SPECULAR, no_light);}

    glLightfv( GL_LIGHT1, GL_POSITION, light_position);
    glPopMatrix();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective(100,1,1,1000);

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt(eyeX,eyeY,eyeZ,  refX,refY,refZ,  0,1,0); //7,2,15, 0,0,0, 0,1,0

    glViewport(0, 0, 1200, 800);

 if (isDay) {
    glEnable(GL_LIGHTING);
    light0();

    glPushMatrix();
     glTranslatef(10,1,9.3);
    base();  // DRAW THE BASE OF THE HOUSE
    glPopMatrix();

    ///room1_front
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,15);
    room_front();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    ///room2_front
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,15);
    glPushMatrix();
    glTranslatef(0,15,0);
    room_front();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    ///room3_front
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,15);
    glPushMatrix();
    glTranslatef(19.7,0,0);
    room_front();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    ///room4_front
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,15);
    glPushMatrix();
    glTranslatef(19.7,15,0);
    room_front();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    ///room5_front
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,15);
    glPushMatrix();
    glTranslatef(40,0,0);
    glScalef(0.93,1,1);
    room_front();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    ///room6_front
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,15);
    glPushMatrix();
    glTranslatef(40,15,0);
    glScalef(0.93,1,1);
    room_front();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    ///class name text
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glRotatef(-90, 0,0,1);
    glScalef(1.0, 1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 10);
    text1();
    glDisable(GL_TEXTURE_2D);
    //
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 24);
    text2();
    glDisable(GL_TEXTURE_2D);
    //
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 25);
    text3();
    glDisable(GL_TEXTURE_2D);
    //
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 26);
    text4();
    glDisable(GL_TEXTURE_2D);
    //
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 27);
    text5();
    glDisable(GL_TEXTURE_2D);
    //
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 37);
    text6();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    ///bar
   glPushMatrix();
   glTranslatef(0,0,25);
    bar();
    glPopMatrix();
    ///bar2
     glPushMatrix();
   glTranslatef(52,0,25);
    bar();
    glPopMatrix();



    area();
    ///for_room1
    element();
    ///for_room2
    glPushMatrix();
     glTranslatef(0,15,0);
     element();
     glPopMatrix();
     ///for_room3
     glPushMatrix();
     glTranslatef(20.5,15,0);
     element1();
     glPopMatrix();
      ///for_room4
     glPushMatrix();
     glTranslatef(38,15,0);
     element1();
     glPopMatrix();
    ///for_office_room
     glPushMatrix();
     glTranslatef(23,0,2);
     element2();
     glPopMatrix();
     ///almari
    glPushMatrix();
    glTranslatef(17.3,0,11.5);
    glRotatef(90,0,1,0);
    glScalef(5,7,3);
    almari();
    glPopMatrix();

    ///office table
    glPushMatrix();
    //glColor3f(0.2, 0.1, 0);
    glScalef(2,5.5,13);
    glTranslatef(18.5,0,-5.7);
    table1();
    glPopMatrix();
    ///siri
     glPushMatrix();

   // Cube();
    siri();
    glPopMatrix();

    office_tex();
    office_tex2();

    glPushMatrix();
    sky();
    glPopMatrix();
    ///tree_line1
     glPushMatrix();
      glTranslatef(0,0,0);
    tree();
    glPopMatrix();
    glPushMatrix();
      glTranslatef(24,0,0);
    tree();
    glPopMatrix();
 glPushMatrix();
      glTranslatef(-21,0,-10);
    tree();
    glPopMatrix();
     glPushMatrix();
glTranslatef(-21,0,-20);
    tree();
    glPopMatrix();
    glPushMatrix();
glTranslatef(-21,0,-30);
    tree();
    glPopMatrix();
    glPushMatrix();
glTranslatef(-21,0,-40);
    tree();
    glPopMatrix();
    glPushMatrix();
glTranslatef(-21,0,-50);
    tree();
    glPopMatrix();
    glPopMatrix();
    glPushMatrix();
glTranslatef(-21,0,-60);
    tree();
    glPopMatrix();
    glPopMatrix();
    glPushMatrix();
glTranslatef(-21,0,-70);
    tree();
    glPopMatrix();
    ///tree_line2

 glPushMatrix();
      glTranslatef(45,0,-10);
    tree();
    glPopMatrix();

     glPushMatrix();
glTranslatef(45,0,-20);
    tree();
    glPopMatrix();

    glPushMatrix();
glTranslatef(45,0,-30);
    tree();
    glPopMatrix();

    glPushMatrix();
glTranslatef(45,0,-40);
    tree();
    glPopMatrix();

    glPushMatrix();
glTranslatef(45,0,-50);
    tree();
    glPopMatrix();

    glPushMatrix();
glTranslatef(45,0,-60);
    tree();
    glPopMatrix();

    glPushMatrix();
glTranslatef(45,0,-70);
    tree();
    glPopMatrix();
    ///street tree
    //left
    glPushMatrix();
      glTranslatef(-25,0,0);
    tree1();
    glPopMatrix();

    glPushMatrix();
      glTranslatef(-25,0,0);
    tree1();
    glPopMatrix();

    glPushMatrix();
      glTranslatef(-35,0,0);
    tree1();
    glPopMatrix();

    glPushMatrix();
      glTranslatef(-45,0,0);
    tree1();
    glPopMatrix();
    glPushMatrix();
      glTranslatef(-55,0,0);
    tree1();
    glPopMatrix();
    glPushMatrix();
      glTranslatef(-65,0,0);
    tree1();
    glPopMatrix();
    glPushMatrix();
      glTranslatef(-75,0,0);
    tree1();
    glPopMatrix();
    glPushMatrix();
      glTranslatef(-85,0,0);
    tree1();
    glPopMatrix();
    glPushMatrix();
      glTranslatef(-95,0,0);
    tree1();
    glPopMatrix();
    glPushMatrix();
      glTranslatef(-105,0,0);
    tree1();
    glPopMatrix();
    //right
    glPushMatrix();
      glTranslatef(35,0,0);
    tree1();
    glPopMatrix();

    glPushMatrix();
      glTranslatef(45,0,0);
    tree1();
    glPopMatrix();

    glPushMatrix();
      glTranslatef(55,0,0);
    tree1();
    glPopMatrix();

    glPushMatrix();
      glTranslatef(65,0,0);
    tree1();
    glPopMatrix();
    glPushMatrix();
      glTranslatef(75,0,0);
    tree1();
    glPopMatrix();
    glPushMatrix();
      glTranslatef(85,0,0);
    tree1();
    glPopMatrix();
    glPushMatrix();
      glTranslatef(95,0,0);
    tree1();
    glPopMatrix();
    glPushMatrix();
      glTranslatef(105,0,0);
    tree1();
    glPopMatrix();
    glPushMatrix();
      glTranslatef(115,0,0);
    tree1();
    glPopMatrix();
    glPushMatrix();
      glTranslatef(125,0,0);
    tree1();
    glPopMatrix();

    ///other tree

    glPushMatrix();
    glTranslatef(-70,0,-70);
    tree1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-65,0,-60);
    tree1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-48,0,-30);
    tree1();
    glPopMatrix();


    flag();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,29);
    glPushMatrix();
    glTranslatef(17.8,23,57);
    rectangle();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    road();
    box();

    glDisable(GL_LIGHTING);
} else {
    glEnable(GL_LIGHTING);
    light0();

    glPushMatrix();
     glTranslatef(10,1,9.3);
    base();  // DRAW THE BASE OF THE HOUSE
    glPopMatrix();

    ///room1_front
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,15);
    room_front();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    ///room2_front
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,15);
    glPushMatrix();
    glTranslatef(0,15,0);
    room_front();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    ///room3_front
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,15);
    glPushMatrix();
    glTranslatef(19.7,0,0);
    room_front();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    ///room4_front
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,15);
    glPushMatrix();
    glTranslatef(19.7,15,0);
    room_front();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    ///room5_front
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,15);
    glPushMatrix();
    glTranslatef(40,0,0);
    glScalef(0.93,1,1);
    room_front();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    ///room6_front
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,15);
    glPushMatrix();
    glTranslatef(40,15,0);
    glScalef(0.93,1,1);
    room_front();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    ///class name text
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glRotatef(-90, 0,0,1);
    glScalef(1.0, 1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 10);
    text1();
    glDisable(GL_TEXTURE_2D);
    //
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 24);
    text2();
    glDisable(GL_TEXTURE_2D);
    //
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 25);
    text3();
    glDisable(GL_TEXTURE_2D);
    //
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 26);
    text4();
    glDisable(GL_TEXTURE_2D);
    //
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 27);
    text5();
    glDisable(GL_TEXTURE_2D);
    //
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 37);
    text6();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();



    area();
    ///for_room1
    element();
    ///for_room2
    glPushMatrix();
     glTranslatef(0,15,0);
     element();
     glPopMatrix();
     ///for_room3
     glPushMatrix();
     glTranslatef(20.5,15,0);
     element1();
     glPopMatrix();
      ///for_room4
     glPushMatrix();
     glTranslatef(38,15,0);
     element1();
     glPopMatrix();
    ///for_office_room
     glPushMatrix();
     glTranslatef(23,0,2);
     element2();
     glPopMatrix();
     ///almari
    glPushMatrix();
    glTranslatef(17.3,0,11.5);
    glRotatef(90,0,1,0);
    glScalef(5,7,3);
    almari();
    glPopMatrix();

    ///office table
    glPushMatrix();
    //glColor3f(0.2, 0.1, 0);
    glScalef(2,5.5,13);
    glTranslatef(18.5,0,-5.7);
    table1();
    glPopMatrix();
    ///siri
     glPushMatrix();

   // Cube();
    siri();
    glPopMatrix();

    office_tex();
    office_tex2();

    glPushMatrix();
    sky();
    glPopMatrix();

    flag();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,29);
    glPushMatrix();
    glTranslatef(17.8,23,57);
    rectangle();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    road();
    box();

    glDisable(GL_LIGHTING);
}

    glFlush();
    glutSwapBuffers();

}

void timer(int unused)
{
    if (on==1 && off==1) {
        glutPostRedisplay();
        glutTimerFunc(30, timer, 0);
    }
}

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//DO NOT TOUCH!!!!

void LoadTexture(const char*filename)
{
    glGenTextures(1, &ID);
     //glGenTextures(2, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    glPixelStorei(GL_UNPACK_ALIGNMENT, ID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    BmpLoader bl(filename);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bl.iWidth, bl.iHeight, GL_RGB, GL_UNSIGNED_BYTE, bl.textureData );
}

// CODE FOR KEYBOARD CONTROL
void myKeyboardFunc( unsigned char key, int x, int y )
{
    switch ( key )
    {
        case 'w': // move eye point upwards along Y axis
            eyeY+=1.0;
            refY+=1.0;
            break;
        case 's': // move eye point downwards along Y axis
            eyeY-=1.0;
            refY-=1.0;
            break;
        case 'a': // move eye point left along X axis
            eyeX-=1.0;
            refX-=1.0;
            break;
        case 'd': // move eye point right along X axis
            eyeX+=1.0;
            refX+=1.0;
            break;
        case 'o':  //zoom out
            eyeZ+=1;
            refZ+=1;
            break;
        case 'i': //zoom in
            eyeZ-=1;
            refZ-=1;
            break;
        case 'q': //back to default eye point and ref point
                eyeX=0.0; eyeY=2.0; eyeZ=40.0;
                refX=0.0; refY=0.0; refZ=0.0;
            break;
        case 'j': // move ref point upwards along Y axis
            refY+=1.0;
            break;
        case 'n': // move ref point downwards along Y axis
            refY-=1.0;
            break;
        case 'b': // move ref point left along X axis
            refX-=1.0;
            break;
        case 'm': // move eye point right along X axis
            refX+=1.0;
            break;
        case 'k':  //move ref point away from screen/ along z axis
            refZ+=1;
            break;
        case 'l': //move ref point towards screen/ along z axis
            refZ-=1;
            break;

    case '1':
    if (switchOne == false) {
        switchOne = true;
        amb1 = true;
        diff1 = true;
        spec1 = true;
        glEnable(GL_LIGHT0);
        if (textureID != 18) {
            glDeleteTextures(1, &textureID); // Delete the old texture
        }
        LoadTexture("C:\\Users\\asus\\Downloads\\assign2_cgipl\\sky.bmp");
    } else {
        switchOne = false;
        amb1 = false;
        diff1 = false;
        spec1 = false;
        glDisable(GL_LIGHT0);
        if (textureID != 18) {
            glDeleteTextures(1, &textureID); // Delete the old texture
        }
        LoadTexture("C:\\Users\\asus\\Downloads\\assign2_cgipl\\nightsky.bmp");
    }
    break;

        case 27:    // Escape key
            exit(1);
    }

    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
    if (on==0 && off==0) {
        on = 1;
    }
    else if (on==1 && off==0) {
        off = 1;
    }
    else if (on==1 && off==1) {
        on = 0;
    }
    else if (on==0 && off==1) {
        off = 0;
    }

    glutTimerFunc(30, timer, 0);
}

void init(void)
{
    for (int x=0; x<45; x++) {
        for (int y=0; y<45; y++) {
			points[x][y][0] = double((x / 3.0f) - 7.25f);
			points[x][y][1] = double((y / 5.0f) - 4.5f);
			points[x][y][2] = double(sin((((x / 5.0f) * 40.0f) / 360.0f) * pi * 2.0f));
		}
	}
}

int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    std::cout<<"To move Eye point:"<< std::endl;
    std::cout<<"w: up"<<std::endl;
    std::cout<<"s: down"<<std::endl;
    std::cout<<"a: left"<<std::endl;
    std::cout<<"d: right"<<std::endl;
    std::cout<<"i: zoom in"<<std::endl;
    std::cout<<"o: zoom out"<<std::endl;
    std::cout<<"      "<<std::endl;
    std::cout<<"To move Camera point:"<< std::endl;
    std::cout<<"j: up"<<std::endl;
    std::cout<<"n: down"<<std::endl;
    std::cout<<"b: left"<<std::endl;
    std::cout<<"m: right"<<std::endl;
    std::cout<<"l: move nearer"<<std::endl;
    std::cout<<"k: move far"<<std::endl;
    std::cout<<"      "<<std::endl;
    std::cout<<"Press q to move to default position"<<std::endl;
    std::cout<<"      "<<std::endl;


    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(300,100);
    glutInitWindowSize(windowHeight, windowWidth);
    glutCreateWindow("Primary School | CGIPL Final Project");

    init();

    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    LoadTexture("C:\\Users\\asus\\Downloads\\assign2_cgipl\\mina.bmp");//1
    LoadTexture("C:\\Users\\asus\\Downloads\\assign2_cgipl\\mud.bmp");//2
    LoadTexture("C:\\Users\\asus\\Downloads\\assign2_cgipl\\bamboo.bmp");//3
    LoadTexture("C:\\Users\\asus\\Downloads\\assign2_cgipl\\mujib.bmp");//4
    LoadTexture("C:\\Users\\asus\\Downloads\\assign2_cgipl\\hasina.bmp");//5
    LoadTexture("C:\\Users\\asus\\Downloads\\assign2_cgipl\\stair.bmp");//6
    LoadTexture("C:\\Users\\asus\\Downloads\\assign2_cgipl\\sky.bmp");//7
    LoadTexture("C:\\Users\\asus\\Downloads\\assign2_cgipl\\gate.bmp");//8
    LoadTexture("C:\\Users\\asus\\Downloads\\assign2_cgipl\\wall2.bmp");//9
    LoadTexture("C:\\Users\\asus\\Downloads\\assign2_cgipl\\cls1.bmp");//10
    LoadTexture("C:\\Users\\asus\\Downloads\\assign2_cgipl\\colo.bmp");//11
    LoadTexture("C:\\Users\\asus\\Downloads\\assign2_cgipl\\tile.bmp");//12
    LoadTexture("C:\\Users\\asus\\Downloads\\assign2_cgipl\\wall.bmp");//13
    LoadTexture("C:\\Users\\asus\\Downloads\\assign2_cgipl\\surface.bmp");//14
    LoadTexture("C:\\Users\\asus\\Downloads\\assign2_cgipl\\wall3.bmp");//15
    LoadTexture("C:\\Users\\asus\\Downloads\\assign2_cgipl\\grass1.bmp");//16
    LoadTexture("C:\\Users\\asus\\Downloads\\assign2_cgipl\\mina2.bmp");//17
    LoadTexture("C:\\Users\\asus\\Downloads\\assign2_cgipl\\nightsky.bmp");//18
    LoadTexture("C:\\Users\\asus\\Downloads\\assign2_cgipl\\sky2.bmp");//19
    LoadTexture("C:\\Users\\asus\\Downloads\\assign2_cgipl\\blackboard.bmp");//20
    LoadTexture("C:\\Users\\asus\\Downloads\\assign2_cgipl\\wood2.bmp");//21
    LoadTexture("C:\\Users\\asus\\Downloads\\assign2_cgipl\\wall6.bmp");//22
    LoadTexture("C:\\Users\\asus\\Downloads\\assign2_cgipl\\wood.bmp");//23
    LoadTexture("C:\\Users\\asus\\Downloads\\assign2_cgipl\\cls2.bmp");//24
    LoadTexture("C:\\Users\\asus\\Downloads\\assign2_cgipl\\cls3.bmp");//25
    LoadTexture("C:\\Users\\asus\\Downloads\\assign2_cgipl\\cls4.bmp");//26
    LoadTexture("C:\\Users\\asus\\Downloads\\assign2_cgipl\\tr.bmp");//27
    LoadTexture("C:\\Users\\asus\\Downloads\\assign2_cgipl\\almari.bmp");//28
    LoadTexture("C:\\Users\\asus\\Downloads\\assign2_cgipl\\bdflag.bmp");//29
    LoadTexture("C:\\Users\\asus\\Downloads\\assign2_cgipl\\bshagor.bmp");//30
    LoadTexture("C:\\Users\\asus\\Downloads\\assign2_cgipl\\rtagore.bmp");//31
    LoadTexture("C:\\Users\\asus\\Downloads\\assign2_cgipl\\begumr.bmp");//32
    LoadTexture("C:\\Users\\asus\\Downloads\\assign2_cgipl\\kaji.bmp");//33
    LoadTexture("C:\\Users\\asus\\Downloads\\assign2_cgipl\\road.bmp");//34
    LoadTexture("C:\\Users\\asus\\Downloads\\assign2_cgipl\\color.bmp");//35
    LoadTexture("C:\\Users\\asus\\Downloads\\assign2_cgipl\\box.bmp");//36
    LoadTexture("C:\\Users\\asus\\Downloads\\assign2_cgipl\\store.bmp");//37


    glutDisplayFunc(display);
    glutKeyboardFunc(myKeyboardFunc);
    glutMouseFunc(mouse);
    glutMainLoop();

    return 0;
}

