#include "Menu.h"

Menu::Menu() {

}

void Menu::MenuDisplay() {


    // Czyszczenie bufora koloru i bufora g³êbi.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Fioletowe t³o
    glClearColor(0.60, 0.34, 0.71, 1.0);
    // Wybór macierzy modelowania.
    glMatrixMode(GL_MODELVIEW);
    // Macierz jednostkowa.
    glLoadIdentity();


        glBegin(GL_QUADS);
            //Lekko ciemny prostok¹t
            glColor3f(0.36, 0.42, 0.49);

            glVertex3f(-0.97, -0.95, 0.0);
            glVertex3f(-0.97, 0.95, 0.0);
            glVertex3f(0.97, 0.95, 0.0);
            glVertex3f(0.97, -0.95, 0.0);

            //Ciemny górny prostok¹ty
            glColor3f(0.33, 0.39, 0.49);

            glVertex3f(-0.94, 0.2, 0.0);
            glVertex3f(-0.94, 0.9, 0.0);
            glVertex3f(0.94, 0.9, 0.0);
            glVertex3f(0.94, 0.2, 0.0);

            //Ciemny lewy œrodkowy prostok¹ty
            glVertex3f(-0.94, -0.55, 0.0);
            glVertex3f(-0.94, 0.15, 0.0);
            glVertex3f(-0.015, 0.15, 0.0);
            glVertex3f(-0.015, -0.55, 0.0);

            //Przycisk Play
            glColor3f(0.75, 0.22, 0.18);

            glVertex3f(-0.86, -0.46, 0.0);
            glVertex3f(-0.86, 0.06, 0.0);
            glVertex3f(-0.095, 0.06, 0.0);
            glVertex3f(-0.095, -0.46, 0.0);

            glColor3f(0.90, 0.30, 0.23);

            glVertex3f(-0.80, -0.4, 0.0);
            glVertex3f(-0.80, 0.0, 0.0);
            glVertex3f(-0.155, 0.0, 0.0);
            glVertex3f(-0.155, -0.4, 0.0);

            //Ciemny prawy œrodkowy prostok¹ty
            glColor3f(0.33, 0.39, 0.49);
            glVertex3f(0.015, -0.55, 0.0);
            glVertex3f(0.015, 0.15, 0.0);
            glVertex3f(0.94, 0.15, 0.0);
            glVertex3f(0.94, -0.55, 0.0);

            glVertex3f(-0.94, -0.88, 0.0);
            glVertex3f(-0.94, -0.61, 0.0);
            glVertex3f(-0.015, -0.61, 0.0);
            glVertex3f(-0.015, -0.88, 0.0);

            //Przycisk Load
            glColor3f(0.16, 0.50, 0.72);

            glVertex3f(0.86, -0.46, 0.0);
            glVertex3f(0.86, 0.06, 0.0);
            glVertex3f(0.095, 0.06, 0.0);
            glVertex3f(0.095, -0.46, 0.0);

            glColor3f(0.36, 0.67, 0.88);

            glVertex3f(0.80, -0.4, 0.0);
            glVertex3f(0.80, 0.0, 0.0);
            glVertex3f(0.155, 0.0, 0.0);
            glVertex3f(0.155, -0.4, 0.0);

            //Ciemny dolny prostok¹ty
            glColor3f(0.33, 0.39, 0.49);
            glVertex3f(0.015, -0.88, 0.0);
            glVertex3f(0.015, -0.61, 0.0);
            glVertex3f(0.94, -0.61, 0.0);
            glVertex3f(0.94, -0.88, 0.0);
        glEnd();

    // skierowanie poleceñ do wykonania
    glFlush();
    // zamiana buforów koloru
    glutSwapBuffers();
}

void Menu::MenuReshape(int w, int h) {
    glViewport(0, 0, w, h);
}

int Menu::MenuMouse(int button, int state, int x, int y) {

    double x1 = (((double)x / glutGet(GLUT_WINDOW_WIDTH)) * 2 - 1);
    double y1 = -(((double)y / glutGet(GLUT_WINDOW_HEIGHT)) * 2 - 1);

    cout << x1 << "   " << y1 << endl;
    if (x1 > -0.86 && x1<-0.095 && y1>-0.46 && y1 < 0.06) {
        return 1;
    }
    else if (x1 > 0.095 && x1<0.86 && y1>-0.46 && y1 < 0.06) {
        return 2;
    }
    else
        return 0;
}

void Menu::MenuMouseMove(int x, int y) {

    double x1 = (((double)x / glutGet(GLUT_WINDOW_WIDTH)) * 2 - 1);
    double y1 = -(((double)y / glutGet(GLUT_WINDOW_HEIGHT)) * 2 - 1);
    if (x1 > -0.86 && x1<-0.095 && y1>-0.46 && y1 < 0.06) {
        glutSetCursor(GLUT_CURSOR_SPRAY);
    }
    else if (x1 > 0.095 && x1<0.86 && y1>-0.46 && y1 < 0.06) {
        glutSetCursor(GLUT_CURSOR_SPRAY);
    }
    else {
        glutSetCursor(GLUT_CURSOR_RIGHT_ARROW);
    }
}

void Menu::MenuTimer() {
    
}