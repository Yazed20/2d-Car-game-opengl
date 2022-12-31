#include<windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>

//Game Speed
int FPS=50 ;

//Game Track
int start = 0;
int gameover = 0;
int level = 0;

//Track Score
int score = 0;

//For move track
//Road Lines
int roadDivTopMost = 0;
int roadDivTop = 0;
int roadDivMdl = 0;
int roadDivBtm = 0;

//For Card Left / RIGHT
//left right indx
int lrIndex = 5;


//Car Coming
int car1 = 0;
int lrIndex1 = 5;
int car2 = +35;
int lrIndex2 = 6;
int car3 = +70;
int lrIndex3 = 9;


//For Display TEXT
const int font1 = (int)GLUT_BITMAP_TIMES_ROMAN_24;
const int font2 = (int)GLUT_BITMAP_HELVETICA_18;
const int font3 = (int)GLUT_BITMAP_8_BY_13;


void renderBitmapString(float x, float y, void* font, const char* string) {
    const char* c;
    glRasterPos2f(x, y);
    for (c = string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}


void tree(int x, int y) {//drawing tree 
    int newx = x;
    int newy = y;
    //Tree Left
            //Bottom
    glColor3f(0, 0, 0);
    glBegin(GL_TRIANGLES);
    glVertex2f(newx + 11, newy + 55);
    glVertex2f(newx + 12, newy + 55 - 10);
    glVertex2f(newx + 10, newy + 55 - 10);
    glEnd();

    //Up 
    glColor3f(0.133, 0.245, 0.133);
    glBegin(GL_TRIANGLES);
    glVertex2f(newx + 11, newy + 55 + 3);
    glVertex2f(newx + 12 + 3, newy + 55 - 5);
    glVertex2f(newx + 10 - 3, newy + 55 - 5);
    glEnd();
}


void startGame() {
    //Road 
    glColor3f(0.212, 0.220, 0.212);
    glBegin(GL_POLYGON);
    glVertex2f(20, 0);
    glVertex2f(20, 100);
    glVertex2f(80, 100);
    glVertex2f(80, 0);
    glEnd();

    //Road Left Border 
    glColor3f(0.500, 0.500, 0.500);
    glBegin(GL_POLYGON);
    glVertex2f(20, 0);
    glVertex2f(20, 100);
    glVertex2f(23, 100);
    glVertex2f(23, 0);
    glEnd();

    //Road Right Border
    glColor3f(0.500, 0.500, 0.500);
    glBegin(GL_POLYGON);
    glVertex2f(77, 0);
    glVertex2f(77, 100);
    glVertex2f(80, 100);
    glVertex2f(80, 0);
    glEnd();

    //Road Middel Border
      //TOP
    glBegin(GL_POLYGON);
    glColor3f(0.400, 0.400, 0.000);
    glVertex2f(48, roadDivMdl + 40);
    glVertex2f(48, roadDivMdl + 60);
    glVertex2f(52, roadDivMdl + 60);
    glVertex2f(52, roadDivMdl + 40);
    glEnd();

    roadDivTop--;
    if (roadDivTop < -100) {
        roadDivTop = 20;
        score++;
    }
    //Midle
    glColor3f(0.300, 0.300, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(48, roadDivMdl + 40);
    glVertex2f(48, roadDivMdl + 60);
    glVertex2f(52, roadDivMdl + 60);
    glVertex2f(52, roadDivMdl + 40);
    glEnd();


    roadDivMdl--;
    if (roadDivMdl < -60) {
        roadDivMdl = 60;
        score++;
    }

    //Bottom street Line
    glColor3f(0.300, 0.300, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(48, roadDivBtm + 0);
    glVertex2f(48, roadDivBtm + 20);
    glVertex2f(52, roadDivBtm + 20);
    glVertex2f(52, roadDivBtm + 0);
    glEnd();

    roadDivBtm--;
    if (roadDivBtm < -20) {
        roadDivBtm = 100;
        score++;
    }

    //Score Board
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(80, 97);
    glVertex2f(100, 97);
    glVertex2f(100, 98 - 8);
    glVertex2f(80, 98 - 8);
    glEnd();

    //Print Score
    char buffer[50];
    sprintf_s(buffer, "SCORE: %d", score);
    glColor3f(0.000, 1.000, 0.000);
    renderBitmapString(80.5, 95, (void*)font3, buffer);


    //Speed Print
    char buffer1[50];
    sprintf_s(buffer1, "SPEED:%dKm/h", FPS);
    glColor3f(0.000, 1.000, 0.000);
    renderBitmapString(80.5, 95 - 2, (void*)font3, buffer1);
    if (score >= FPS) {
        FPS + 5;
    }

    //level Print
    if (score % 20 == 0) {
        int last = score / 20;
        if (last != level) {
            level = score / 20;
            FPS = FPS + 20;
        }
    }
    char level_buffer[50];
    sprintf_s(level_buffer, "LEVEL: %d", level);
    glColor3f(0.000, 1.000, 0.000);
    renderBitmapString(80.5, 95 - 4, (void*)font3, level_buffer);

    //Increse Speed With level

    //MAIN car
        //Front Tire
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex + 26 - 2, 5);
    glVertex2f(lrIndex + 26 - 2, 7);
    glVertex2f(lrIndex + 30 + 2, 7);
    glVertex2f(lrIndex + 30 + 2, 5);
    glEnd();

    //Back Tire player
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex + 26 - 2, 1);
    glVertex2f(lrIndex + 26 - 2, 3);
    glVertex2f(lrIndex + 30 + 2, 3);
    glVertex2f(lrIndex + 30 + 2, 1);
    glEnd();

    //Car Body plyer
    glColor3f(0.678, 0.000, 0.184);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex + 26, 1);
    glVertex2f(lrIndex + 26, 8);
    glColor3f(0.000, 0.545, 0.545);

    glVertex2f(lrIndex + 28, 10);
    glVertex2f(lrIndex + 30, 8);
    glVertex2f(lrIndex + 30, 1);
    glEnd();


    //Opposite car 1
    glColor3f(0.000, 0.000, 0.000); //car 1 tiers color

    glBegin(GL_POLYGON); //car 1 tiers
    glVertex2f(lrIndex1 + 26 - 2, car1 + 100 - 4);
    glVertex2f(lrIndex1 + 26 - 2, car1 + 100 - 6);
    glVertex2f(lrIndex1 + 30 + 2, car1 + 100 - 6);
    glVertex2f(lrIndex1 + 30 + 2, car1 + 100 - 4);
    glEnd();

    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON); //car 1 tiers
    glVertex2f(lrIndex1 + 26 - 2, car1 + 100);
    glVertex2f(lrIndex1 + 26 - 2, car1 + 100 - 2);
    glVertex2f(lrIndex1 + 30 + 2, car1 + 100 - 2);
    glVertex2f(lrIndex1 + 30 + 2, car1 + 100);
    glEnd();

    glColor3f(0.000, 1.000, 0.000); //car 1 tiers
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex1 + 26, car1 + 100);
    glVertex2f(lrIndex1 + 26, car1 + 100 - 7);
    glVertex2f(lrIndex1 + 28, car1 + 100 - 9);
    glVertex2f(lrIndex1 + 30, car1 + 100 - 7);
    glVertex2f(lrIndex1 + 30, car1 + 100);
    glEnd();

    car1--; 
    if (car1 < -100) {
        car1 = 0;
        lrIndex1 = lrIndex;
    }
    //KIll check car1
    if ((abs(lrIndex - lrIndex1) < 8) && (car1 + 100 < 10)) {
        start = 0;
        gameover = 1;

    }

    //Opposite car 2
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex2 + 26 - 2, car2 + 100 - 4);
    glVertex2f(lrIndex2 + 26 - 2, car2 + 100 - 6);
    glVertex2f(lrIndex2 + 30 + 2, car2 + 100 - 6);
    glVertex2f(lrIndex2 + 30 + 2, car2 + 100 - 4);
    glEnd();
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex2 + 26 - 2, car2 + 100);
    glVertex2f(lrIndex2 + 26 - 2, car2 + 100 - 2);
    glVertex2f(lrIndex2 + 30 + 2, car2 + 100 - 2);
    glVertex2f(lrIndex2 + 30 + 2, car2 + 100);
    glEnd();
    glColor3f(0.294, 0.000, 0.510);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex2 + 26, car2 + 100);
    glVertex2f(lrIndex2 + 26, car2 + 100 - 7);
    glVertex2f(lrIndex2 + 28, car2 + 100 - 9);
    glVertex2f(lrIndex2 + 30, car2 + 100 - 7);
    glVertex2f(lrIndex2 + 30, car2 + 100);
    glEnd();
    car2--;
    if (car2 < -100) {
        car2 = 0;
        lrIndex2 = lrIndex;
    }
    

    //KIll check car2
    if ((abs(lrIndex - lrIndex2) < 8) && (car2 + 100 < 10)) {
        start = 0;
        gameover = 1;
    }


    //Opposite car 3
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex3 + 26 - 2, car3 + 100 - 4);
    glVertex2f(lrIndex3 + 26 - 2, car3 + 100 - 6);
    glVertex2f(lrIndex3 + 30 + 2, car3 + 100 - 6);
    glVertex2f(lrIndex3 + 30 + 2, car3 + 100 - 4);
    glEnd();
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex3 + 26 - 2, car3 + 100);
    glVertex2f(lrIndex3 + 26 - 2, car3 + 100 - 2);
    glVertex2f(lrIndex3 + 30 + 2, car3 + 100 - 2);
    glVertex2f(lrIndex3 + 30 + 2, car3 + 100);
    glEnd();
    glColor3f(1.000, 0.271, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex3 + 26, car3 + 100);
    glVertex2f(lrIndex3 + 26, car3 + 100 - 7);
    glVertex2f(lrIndex3 + 28, car3 + 100 - 9);
    glVertex2f(lrIndex3 + 30, car3 + 100 - 7);
    glVertex2f(lrIndex3 + 30, car3 + 100);
    glEnd();
    car3--;
    if (car3 < -100) {
        car3 = 0;
        lrIndex3 = lrIndex;
    }

    //KIll check car3
    if ((abs(lrIndex - lrIndex3) < 8) && (car3 + 100 < 10)) {
        start = 0;
        gameover = 1;

    }

}
void fristDesign() {

    //Road Backgound
    glColor3f(0.000, 0.392, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(0, 55);
    glVertex2f(100, 55);
    glColor3f(0.604, 0.804, 0.196);
    glVertex2f(100, 50 - 50);
    glVertex2f(0, 50 - 50);
    glEnd();

    //Road Main Menu Design In Front Page
    glColor3f(0, 0, 0);
    glBegin(GL_TRIANGLES);
    glVertex2f(32 - 2 + 21, 55);
    glVertex2f(32 + 58, 50 - 50);
    glVertex2f(32 - 22, 50 - 50);
    glEnd();

    //Road Midle
    glColor3f(1, 1, 1);
    glBegin(GL_TRIANGLES);
    glVertex2f(32 - 2 + 21, 55);
    glVertex2f(50 + 2, 50 - 50);
    glVertex2f(50 - 2, 50 - 50);
    glEnd();

    //Hill 1
    glColor3f(0.235, 0.702, 0.443);
    glBegin(GL_TRIANGLES);
    glVertex2f(20, 55 + 10);
    glVertex2f(20 + 7, 55);
    glVertex2f(0, 55);
    glEnd();

    //Hill 2
    glColor3f(0.000, 0.502, 0.000);
    glBegin(GL_TRIANGLES);
    glVertex2f(20 + 15, 55 + 12);
    glVertex2f(20 + 20 + 10, 55);
    glVertex2f(0 + 10, 55);
    glEnd();

    //Hill 4
    glColor3f(0.235, 0.702, 0.443);
    glBegin(GL_TRIANGLES);
    glVertex2f(87, 55 + 10);
    glVertex2f(100, 55);
    glVertex2f(60, 55);
    glEnd();

    //Hill 3
    glColor3f(0.000, 0.502, 0.000);
    glBegin(GL_TRIANGLES);
    glVertex2f(70, 70);
    glVertex2f(90, 55);
    glVertex2f(50, 55);
    glEnd();

    //Trees Pos
    //Tree Left
        //Bottom
    tree(5, -15);
    tree(9, 5);
    tree(85, 9);
    tree(75, -5);

    //Menu Place Holder
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(32 - 4, 50 + 5 + 10);
    glVertex2f(32 + 46, 50 + 5 + 10);
    glVertex2f(32 + 46, 50 - 15 + 10);
    glVertex2f(32 - 4, 50 - 15 + 10);
    glEnd();

    //The 2D border
    glColor3f(1, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2f(32 - 4, 50 + 5 + 10);
    glVertex2f(32 + 46, 50 + 5 + 10);
    glVertex2f(32 + 46, 50 + 4 + 10);
    glVertex2f(32 - 4, 50 + 4 + 10);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(32 + 45, 50 + 5 + 10);
    glVertex2f(32 + 46, 50 + 5 + 10);
    glVertex2f(32 + 46, 50 - 15 + 10);
    glVertex2f(32 + 45, 50 - 15 + 10);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(32 - 4, 50 - 14 + 10);
    glVertex2f(32 + 46, 50 - 14 + 10);
    glVertex2f(32 + 46, 50 - 15 + 10);
    glVertex2f(32 - 4, 50 - 15 + 10);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(32 - 4, 50 + 5 + 10);
    glVertex2f(32 - 5, 50 + 5 + 10);
    glVertex2f(32 - 5, 50 - 15 + 10);
    glVertex2f(32 - 4, 50 - 15 + 10);
    glEnd();


    //Text Information in Frist Page
    if (gameover == 1) {
        glColor3f(1.000, 0.000, 0.000);
        renderBitmapString(35, 60 + 10, (void*)font1, "GAME OVER");
        glColor3f(1.000, 0.000, 0.000);
        char buffer2[50];
        sprintf_s(buffer2, "Your Score is : %d", score);
        renderBitmapString(33, 60 - 4 + 10, (void*)font1, buffer2);

    }

    glColor3f(1.000, 1.000, 1.000);
    renderBitmapString(30, 80, (void*)font1, "Project 2D Car Racing Game ");


    glColor3f(0.000, 1.000, 0.000);
    renderBitmapString(30, 50 + 10, (void*)font2, "Press SPACE to START");
    renderBitmapString(30, 50 - 3 + 10, (void*)font2, "Press ESC to Exit");


    glColor3f(1.000, 1.000, 1.000);
    renderBitmapString(30, 50 - 6 + 10, (void*)font3, "Press RIGHT to turn Right");
    renderBitmapString(30, 50 - 8 + 10, (void*)font3, "Press LEFT to turn Left");
    renderBitmapString(30, 50 - 12 + 10, (void*)font3, "BY its Yazed;/ & Triq;/ ");

    glColor3f(1.000, 1.000, 1.000);

}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    if (start == 1) {
        // glClearColor(0.627, 0.322, 0.176,1);

        glClearColor(0.000, 0.392, 0.000, 1);
        startGame();
    }

    else {
        fristDesign();
        //glClearColor(0.184, 0.310, 0.310,1);

    }
    glFlush();
    glutSwapBuffers();
}

void spe_key(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_LEFT:
        if (lrIndex >= 0) {
            lrIndex = lrIndex - (FPS / 10);
            if (lrIndex < 0) {
                lrIndex = -1;
            }
        }
        break;


    case GLUT_KEY_RIGHT:
        if (lrIndex <= 44) {
            lrIndex = lrIndex + (FPS / 10);
            if (lrIndex > 44) {
                lrIndex = 45;
            }
        }
        break;

    default:
        break;
    }

}

void processKeys(unsigned char key, int x, int y) {

    switch (key)
    {
    case ' ':
        if (start == 0) {
            start = 1;
            gameover = 0;
            FPS = 50;
            roadDivTopMost = 0;
            roadDivTop = 0;
            roadDivMdl = 0;
            roadDivBtm = 0;
            lrIndex = 0;
            car1 = 0;
            lrIndex1 = 0;
            car2 = +35;
            lrIndex2 = 0;
            car3 = +70;
            lrIndex3 = 0;
            score = 0;
            level = 20;
        }
        break;

    case 27:
        exit(0);
        break;
    default:
        break;
    }
}

void timer(int) {
    glutPostRedisplay();
    glutTimerFunc(1000 / FPS , timer,0);
}


int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(500, 650);
    glutInitWindowPosition(200, 20);
    int i = glutCreateWindow("Car Game by yazed && tariq");

    glutDisplayFunc(display);
    glutSpecialFunc(spe_key);
    glutKeyboardFunc(processKeys);

    glOrtho(0, 100, 0, 100, -1, 1);
    glClearColor(0.184, 0.310, 0.310, 1);

    glutTimerFunc(1000, timer, 0);
    glutMainLoop();

    return 0;
}