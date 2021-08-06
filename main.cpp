#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>




void resetCoordinates(void);

void drawLine(int x, int y);
void drawSquare(int x, int y);
void drawTriangle(int x, int y);
void drawCircle(int x, int y);
void drawPoint(int x, int y);

void mouse(int button, int state, int x, int y);

void key(unsigned char key, int x, int y);

void init(void);
void display(void);
void clearScreen(void);
void eraser(int x,int y);
void eraser_select(int x,int y);
void action_menu(int id);
void color_menu(int id);
void brush_menu(void);
void line_menu(void);

void defineMenus(void);


#ifndef PI
#define PI 3.1415926f
#endif

struct Coordinate {
    float x;
    float y;
};



GLsizei windowHeight = 500, windowWidth = 500;



GLfloat red = 0.0, green = 0.0, blue = 0.0;

int selected_shape = 0,flag=1;
float size=4.0,line_size=4.0;




int draw_count = 0;
struct Coordinate draw_Coordinates[3];


void resetCoordinates(void) {
    int i;
    for (i = 0; i < 3; ++i) {
        draw_Coordinates[i].x = 0.0;
        draw_Coordinates[i].y = 0.0;
    }
}


void drawLine(int x, int y) {
    draw_Coordinates[draw_count].x = x;
    draw_Coordinates[draw_count].y = windowHeight - y;

    draw_count++;

    glColor3f(red, green, blue);
    glLineWidth(line_size);
    if (draw_count == 2) {
        glBegin(GL_LINES);
        glVertex2f(draw_Coordinates[0].x, draw_Coordinates[0].y);
        glVertex2f(draw_Coordinates[1].x, draw_Coordinates[1].y);
        glEnd();
        draw_count = 0;
    }
    glutPostRedisplay();
}


void drawSquare(int x, int y) {
    glColor3f(red, green, blue);

    draw_Coordinates[draw_count].x = x;
    draw_Coordinates[draw_count].y = windowHeight - y;
    draw_count++;
    if (draw_count == 2) {
        glRectf(draw_Coordinates[0].x, draw_Coordinates[0].y,
                draw_Coordinates[1].x, draw_Coordinates[1].y);
        draw_count = 0;
    }
    glutPostRedisplay();
}

void eraser_select(int x, int y) {
    glColor3f(flag, flag, flag);

    draw_Coordinates[draw_count].x = x;
    draw_Coordinates[draw_count].y = windowHeight - y;
    draw_count++;
    if (draw_count == 2) {
        glRectf(draw_Coordinates[0].x, draw_Coordinates[0].y,
                draw_Coordinates[1].x, draw_Coordinates[1].y);
        draw_count = 0;
    }
    glutPostRedisplay();
}
void eraser(int x, int y) {

    glColor3f(flag, flag, flag);
    x = x;
    y = windowHeight - y;
    glPointSize(30);
    glBegin(GL_POINTS);
    glVertex2f(x ,y);
    glEnd();
    glutPostRedisplay();
}



void drawTriangle(int x, int y) {
    glColor3f(red, green, blue);
    draw_Coordinates[draw_count].x = x;
    draw_Coordinates[draw_count].y = windowHeight - y;
    draw_count++;

    if (draw_count == 3) {
        glColor3f(red, green, blue);
        glBegin(GL_TRIANGLES);
        glVertex2f(draw_Coordinates[0].x, draw_Coordinates[0].y);
        glVertex2f(draw_Coordinates[1].x, draw_Coordinates[1].y);
        glVertex2f(draw_Coordinates[2].x, draw_Coordinates[2].y);
        glEnd();
        draw_count = 0;
    }
    glutPostRedisplay();
}


void drawCircle(int x, int y) {
    glColor3f(red, green, blue);
    draw_Coordinates[draw_count].x = x;
    draw_Coordinates[draw_count].y = windowHeight - y;
    draw_count++;

    if (draw_count == 2) {
        int clarity = 25;
        float x = (draw_Coordinates[0].x - draw_Coordinates[1].x);
        float y = (draw_Coordinates[0].y - draw_Coordinates[1].y);
        /* Using the distance formula. */
        float radius = sqrt((x * x) + (y * y));
        glLineWidth(line_size);
        glBegin(GL_LINE_LOOP);
        int i;
        for(i = 0; i < clarity; i++) {

            float theta = 2.0f * PI * (float) i / (float) clarity;
            float x = radius * cosf(theta);
            float y = radius * sinf(theta);
            glVertex2f(x + draw_Coordinates[0].x, y + draw_Coordinates[0].y);
        }
        glEnd();
        draw_count = 0;
        glutPostRedisplay();
    }
}





void drawPoint(int x, int y) {

    glColor3f(red, green, blue);
    x = x;
    y = windowHeight - y;
    glPointSize(size);
    glBegin(GL_POINTS);
    glVertex2f(x ,y);
    glEnd();
    glutPostRedisplay();
}




void mouse(int button, int state, int x, int y) {
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        switch(selected_shape) {
        case 1  :
            drawLine(x,y);
            break;
        case 2  :
            drawSquare(x,y);
            break;
        case 3  :
            drawTriangle(x,y);
            break;
        case 4  :
            drawPoint(x,y);
            break;
        case 5:
            drawCircle(x,y);
            break;
        case 6:
            eraser(x,y);
            break;
        case 7:
            eraser_select(x,y);
            break;




        default:
            break;

        }
        glFlush();
    }
}

void display(void) {
    /* All display functions are called from mouse callback functions. */
}


void key(unsigned char key, int x, int y) {
    if (key == 'Q' || key == 'q') {
        exit(-1);
    }
    if (key == 'c' || key == 'C') {
    glClearColor(flag, flag, flag, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    glFlush();

    }
    if(key == 'b' || key == 'B') {
         glClearColor(0, 0, 0, 1);
         glClear(GL_COLOR_BUFFER_BIT);
         flag=0;
         glFlush();
    }
    if(key == 'w' || key == 'W') {
     glClearColor(1, 1, 1, 1);
     glClear(GL_COLOR_BUFFER_BIT);
     flag=1;
     glFlush();}
    return;
}


void init(void) {

    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, windowWidth, windowHeight);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, windowWidth, 0.0, windowHeight,  -1.0, 1.0);

    clearScreen();
}

void clearScreen(void) {
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}



void action_menu(int id) {
    if (id == 1) {
        clearScreen();
    } else {
        exit(1);
    }
}



void color_menu(int id) {
    if(id == 1) { // Red.
        red = 1.0;
        green = 0.0;
        blue = 0.0;
    } else if(id == 2) { // Green.
        red = 0.0;
        green = 1.0;
        blue = 0.0;
    } else if(id == 3) { // Blue.
        red = 0.0;
        green = 0.0;
        blue = 1.0;
    }
    else if(id == 4) { // Yellow.
        red = 1.0;
        green = 1.0;
        blue = 0.0;
    }
    else if(id == 5) { // Black.
        red = 0.0;
        green = 0.0;
        blue = 0.0;
    }
    else if(id == 6) { // Orange.
        red = 1.0;
        green = 0.64;
        blue = 0.0;
    }
     else if(id == 7) { // White.
        red = 1.0;
        green = 1;
        blue = 1;
    }
}

void brush_menu(int id){
    size=id;
}

void line_menu(int id){
    line_size=id;
}

void shape_menu(int id) {
    selected_shape = id;
}




void defineMenus(void) {

    int color_menu_handle, shape_menu_handle,brush_menu_handle,line_menu_handle;

    shape_menu_handle = glutCreateMenu(shape_menu);
    glutAddMenuEntry("Line",     1);
    glutAddMenuEntry("Square",   2);
    glutAddMenuEntry("Triangle", 3);
    glutAddMenuEntry("Point",    4);
    glutAddMenuEntry("Circle",   5);
    glutAddMenuEntry("Eraser",6);
    glutAddMenuEntry("Seclect Delete",7);


    color_menu_handle = glutCreateMenu(color_menu);
    glutAddMenuEntry("Red",     1);
    glutAddMenuEntry("Green",   2);
    glutAddMenuEntry("Blue",    3);
    glutAddMenuEntry("Yellow",   4 );
    glutAddMenuEntry("Black",    5);
    glutAddMenuEntry("Orange",   6);
    glutAddMenuEntry("White",   7);

    brush_menu_handle=glutCreateMenu(brush_menu);
     glutAddMenuEntry("2",     2);
    glutAddMenuEntry("4",   4);
    glutAddMenuEntry("6",    6);
    glutAddMenuEntry("8",    8);
    glutAddMenuEntry("10",    10);
    glutAddMenuEntry("20",    20);
    glutAddMenuEntry("50",    50);

    line_menu_handle=glutCreateMenu(line_menu);
    glutAddMenuEntry("2",     2);
    glutAddMenuEntry("4",   4);
    glutAddMenuEntry("6",    6);





    glutCreateMenu(action_menu);
    glutAddSubMenu("Shape", shape_menu_handle);
    glutAddSubMenu("Color", color_menu_handle);
    glutAddSubMenu("Brush Size", brush_menu_handle);
    glutAddSubMenu("Line Size", line_menu_handle);
    glutAddMenuEntry("Clear", 1);
    glutAddMenuEntry("Quit",  2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

}



int main(int argc, char **argv) {

    glutInit(&argc, argv);


    glutInitWindowSize(windowHeight,windowWidth);

    glutCreateWindow("Paint Application");



    glutDisplayFunc(display);

    /* Called when a key stroke is entered. */
    glutKeyboardFunc(key);

    /* Called when the mouse is used. */
    glutMouseFunc(mouse);


    init();

    /* User defined to hold the menue code. */
    defineMenus();


    glutMainLoop();
}
