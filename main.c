#define RGFW_IMPLEMENTATION
#define RGFW_OPENGL 
#include "RGFW.h"

#include <stdio.h>

#ifdef RGFW_MACOS
#include <OpenGL/gl.h> 
#else
#include <GL/gl.h>
#endif

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

// Note(john): Order x, y, r, g, b
float data[] = {
    -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
    0.0f,  0.5f, 0.0f, 0.0f, 1.0f
};

int selectedVertex = 0;
float moveStep = 0.02f;

void keyFunc(RGFW_window* win, RGFW_key key, u8 keyChar, RGFW_keymod keyMod, RGFW_bool repeat, RGFW_bool pressed) {
    RGFW_UNUSED(repeat);
    RGFW_UNUSED(keyChar);
    RGFW_UNUSED(keyMod);

    // Note(john): update the vertex pos based on the a-,w-,s-,d-keys
    if (key == RGFW_a && pressed) {
        data[selectedVertex * 5] -= moveStep; 
    }
    if (key == RGFW_d && pressed) {
        data[selectedVertex * 5] += moveStep; 
    }
    if (key == RGFW_w && pressed) {
        data[selectedVertex * 5 + 1] += moveStep; 
    }
    if (key == RGFW_s && pressed) {
        data[selectedVertex * 5 + 1] -= moveStep; 
    }

    // Note(john): make sure the user can switch the selected vertex based on the 1-,2-,3-key
    if (key == RGFW_1 && pressed) {
        selectedVertex = 0;
    }
    if (key == RGFW_2 && pressed) {
        selectedVertex = 1;
    }
    if (key == RGFW_3 && pressed) {
        selectedVertex = 2;
    }

    if (key == RGFW_escape && pressed) {
        RGFW_window_setShouldClose(win, 1);
    }
}

int main() {
    RGFW_window* win = RGFW_createWindow("Jona", 0, 0, 800, 600, RGFW_windowOpenGL);

    
    RGFW_setKeyCallback(keyFunc);

    while (RGFW_window_shouldClose(win) == RGFW_FALSE) {
        RGFW_event event;
        while(RGFW_window_checkEvent(win, &event)) {
            if (event.type == RGFW_quit) break;
        }

        glClearColor(0.43f, 0.48f, 0.64f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        glBegin(GL_TRIANGLES);
            glColor3f(data[2], data[3], data[4]);
            glVertex2f(data[0], data[1]);

            glColor3f(data[7], data[8], data[9]);
            glVertex2f(data[5], data[6]);

            glColor3f(data[12], data[13], data[14]);
            glVertex2f(data[10], data[11]);
        glEnd();

        RGFW_window_swapBuffers_OpenGL(win);

        glFlush();
    }

    RGFW_window_close(win);
    return 0;
}
