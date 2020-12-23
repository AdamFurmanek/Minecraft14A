#include "Menu.h"

void Menu::InitMenu() {
    glLineWidth(5);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glutSetCursor(GLUT_CURSOR_RIGHT_ARROW);
    MenuReshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
    CheckSaves();
}

void Menu::MenuDisplay() {

    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glClearColor(asbestos[0], asbestos[1], asbestos[2], 1.0);
    RenderRectangle(-0.97, -0.95, 0.97, 0.95, concrete);
    RenderRectangle(-0.94, 0.2, 0.94, 0.9, asbestos);
    RenderRectangle(-0.94, -0.55, -0.015, 0.15, asbestos);
    RenderRectangle(-0.86, -0.46, -0.095, 0.06, pomegranate);
    RenderRectangle(-0.80, -0.4, -0.155, 0.0, alizarin);
    RenderRectangle(0.015, -0.55, 0.94, 0.15, asbestos);
    RenderRectangle(-0.94, -0.90, -0.015, -0.61, asbestos);
    RenderRectangle(0.86, -0.46, 0.095, 0.06, belizeHole);
    RenderRectangle(0.80, -0.4, 0.155, 0.0, peterRiver);
    RenderRectangle(0.015, -0.90, 0.94, -0.61, asbestos);

    RenderText("Minecraft 14A", -0.87, 0.46, 0.002, pumpkin, carrot);
    RenderText("New Game", -0.75, -0.23, 0.0008, silver, clouds);
    RenderText("Load Game", 0.19, -0.23, 0.0008, silver, clouds);
    RenderText("Adam Furmanek", -0.9, -0.80, 0.0008, nephritis, emerald);
    RenderText("Tomasz Gebski", 0.11, -0.80, 0.0008, orange, sunFlower);

    glFlush();
    glutSwapBuffers();
}

void Menu::MenuReshape(int w, int h) {

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);

}

int Menu::MenuMouse(int x, int y) {

    double x1 = (((double)x / glutGet(GLUT_WINDOW_WIDTH)) * 2 - 1);
    double y1 = -(((double)y / glutGet(GLUT_WINDOW_HEIGHT)) * 2 - 1);

    if (x1 > -0.86 && x1<-0.095 && y1>-0.46 && y1 < 0.06)
        return 1;
    else if (x1 > 0.095 && x1<0.86 && y1>-0.46 && y1 < 0.06)
        return 2;
    else
        return 0;
}

void Menu::MenuMouseMove(int x, int y) {

    double x1 = (((double)x / glutGet(GLUT_WINDOW_WIDTH)) * 2 - 1);
    double y1 = -(((double)y / glutGet(GLUT_WINDOW_HEIGHT)) * 2 - 1);
    if (x1 > -0.86 && x1<-0.095 && y1>-0.46 && y1 < 0.06)
        glutSetCursor(GLUT_CURSOR_SPRAY);
    else if (x1 > 0.095 && x1<0.86 && y1>-0.46 && y1 < 0.06)
        glutSetCursor(GLUT_CURSOR_SPRAY);
    else
        glutSetCursor(GLUT_CURSOR_RIGHT_ARROW);
}

void Menu::SavingMenuDisplay() {

    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glClearColor(asbestos[0], asbestos[1], asbestos[2], 1.0);
    RenderRectangle(-0.97, -0.95, 0.97, 0.95, concrete);
    RenderRectangle(-0.94, 0.90, -0.015, 0.4875, asbestos);
    RenderRectangle(0.015, 0.90, 0.94, 0.4875, asbestos);
    RenderRectangle(-0.94, 0.4375, -0.015, 0.025, asbestos);
    RenderRectangle(0.015, 0.4375, 0.94, 0.025, asbestos);
    RenderRectangle(-0.94, -0.90, -0.015, -0.4875, asbestos);
    RenderRectangle(0.015, -0.90, 0.94, -0.4875, asbestos);
    RenderRectangle(-0.94, -0.4375, -0.015, -0.025, asbestos);
    RenderRectangle(0.015, -0.4375, 0.94, -0.025, asbestos);

    if (saves[0])
        RenderText("World 1", -0.85, 0.62, 0.0013, nephritis, emerald);
    else
        RenderText("No World", -0.85, 0.62, 0.0013, pomegranate, alizarin);
    if (saves[1])
        RenderText("World 2", 0.11, 0.62, 0.0013, nephritis, emerald);
    else
        RenderText("No World", 0.11, 0.62, 0.0013, pomegranate, alizarin);
    if(saves[2])
        RenderText("World 3", -0.85, 0.16, 0.0013, nephritis, emerald);
    else
        RenderText("No World", -0.85, 0.16, 0.0013, pomegranate, alizarin);
    if (saves[3])
        RenderText("World 4", 0.11, 0.16, 0.0013, nephritis, emerald);
    else
        RenderText("No World", 0.11, 0.16, 0.0013, pomegranate, alizarin);
    if (saves[4])
        RenderText("World 5", -0.85, -0.31, 0.0013, nephritis, emerald);
    else
        RenderText("No World", -0.85, -0.31, 0.0013, pomegranate, alizarin);
    if (saves[5])
        RenderText("World 6", 0.11, -0.31, 0.0013, nephritis, emerald);
    else
        RenderText("No World", 0.11, -0.31, 0.0013, pomegranate, alizarin);
    if (saves[6])
        RenderText("World 7", -0.85, -0.77, 0.0013, nephritis, emerald);
    else
        RenderText("No World", -0.85, -0.77, 0.0013, pomegranate, alizarin);
    if (saves[7])
        RenderText("World 8", 0.11, -0.77, 0.0013, nephritis, emerald);
    else
        RenderText("No World", 0.11, -0.77, 0.0013, pomegranate, alizarin);

    glFlush();
    glutSwapBuffers();
}

int Menu::SavingMenuMouse(int x, int y) {
    double x1 = (((double)x / glutGet(GLUT_WINDOW_WIDTH)) * 2 - 1);
    double y1 = -(((double)y / glutGet(GLUT_WINDOW_HEIGHT)) * 2 - 1);

    if (x1 > -0.94 && x1 < -0.015 && y1 > 0.4875 && y1 < 0.90)
        return 1;
    else if (x1 > 0.015 && x1 < 0.94 && y1 > 0.4875 && y1 < 0.90)
        return 2;
    else if (x1 > -0.94 && x1 < -0.015 && y1 > 0.025 && y1 < 0.4375)
        return 3;
    else if (x1 > 0.015 && x1 < 0.94 && y1 > 0.025 && y1 < 0.4375)
        return 4;
    else if (x1 > -0.94 && x1 < -0.015 && y1 > -0.4375 && y1 < -0.025)
        return 5;
    else if (x1 > 0.015 && x1 < 0.94 && y1 > -0.4375 && y1 < -0.025)
        return 6;
    else if (x1 > -0.94 && x1 < -0.015 && y1 > -0.90 && y1 < -0.4875)
        return 7;
    else if (x1 > 0.015 && x1 < 0.94 && y1 > -0.90 && y1 < -0.4875)
        return 8;
    else
        return 0;
}

int Menu::SavingMenuMouseChecked(int x, int y) {

    int id = SavingMenuMouse(x, y);
    if (id == 0 || !saves[id - 1])
        return 0;
    else
        return id;
}

void Menu::SavingMenuMouseMove(int x, int y) {
    double x1 = (((double)x / glutGet(GLUT_WINDOW_WIDTH)) * 2 - 1);
    double y1 = -(((double)y / glutGet(GLUT_WINDOW_HEIGHT)) * 2 - 1);

    if (x1 > -0.94 && x1 < -0.015 && y1 > 0.4875 && y1 < 0.90)
        glutSetCursor(GLUT_CURSOR_SPRAY);
    else if (x1 > 0.015 && x1 < 0.94 && y1 > 0.4875 && y1 < 0.90)
        glutSetCursor(GLUT_CURSOR_SPRAY);
    else if (x1 > -0.94 && x1 < -0.015 && y1 > 0.025 && y1 < 0.4375)
        glutSetCursor(GLUT_CURSOR_SPRAY);
    else if (x1 > 0.015 && x1 < 0.94 && y1 > 0.025 && y1 < 0.4375)
        glutSetCursor(GLUT_CURSOR_SPRAY);
    else if (x1 > -0.94 && x1 < -0.015 && y1 > -0.4375 && y1 < -0.025)
        glutSetCursor(GLUT_CURSOR_SPRAY);
    else if (x1 > 0.015 && x1 < 0.94 && y1 > -0.4375 && y1 < -0.025)
        glutSetCursor(GLUT_CURSOR_SPRAY);
    else if (x1 > -0.94 && x1 < -0.015 && y1 > -0.90 && y1 < -0.4875)
        glutSetCursor(GLUT_CURSOR_SPRAY);
    else if (x1 > 0.015 && x1 < 0.94 && y1 > -0.90 && y1 < -0.4875)
        glutSetCursor(GLUT_CURSOR_SPRAY);
    else
        glutSetCursor(GLUT_CURSOR_RIGHT_ARROW);
}

void Menu::RenderRectangle(float a1, float b1, float a2, float b2, const float color[3]) {
    glLoadIdentity();
    glBegin(GL_QUADS);
    glColor3fv(color);
    glVertex3f(a1, b1, 0.0);
    glVertex3f(a1, b2, 0.0);
    glVertex3f(a2, b2, 0.0);
    glVertex3f(a2, b1, 0.0);
    glEnd();
}

void Menu::RenderText(std::string text, float x, float y, float scale, const float colorB[3], const float colorF[3]) {
    glLoadIdentity();
    glColor3fv(colorB);
    glTranslatef(x, y, 0);
    glScalef(scale, scale, 1);
    glutStrokeString(GLUT_STROKE_ROMAN, (unsigned char*)text.c_str());

    glLoadIdentity();
    glColor3fv(colorF);
    glTranslatef(x - 0.008, y + 0.008, 0);
    glScalef(scale, scale, 1);
    glutStrokeString(GLUT_STROKE_ROMAN, (unsigned char*)text.c_str());
}

void Menu::CheckSaves() {
    for (int i = 0; i < 8; i++) {
        std::string name = "save1.sav";
        name[4] = (i + 49);
        struct stat buffer;
        if (stat(name.c_str(), &buffer) == 0)
            saves[i] = true;
        else
            saves[i] = false;
    }
}