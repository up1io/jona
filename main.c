#define RGFW_IMPLEMENTATION
#define RGFW_OPENGL 
#include "RGFW.h"

#include <stdio.h>

#ifdef RGFW_MACOS
#include <OpenGL/gl.h> 
#else
#include <GL/gl.h>
#endif

void keyFunc(RGFW_window* win, RGFW_key key, u8 keyChar, RGFW_keymod keyMod, RGFW_bool repeat, RGFW_bool pressed) {
    RGFW_UNUSED(repeat);
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

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        glClearColor(0.43f, 0.48f, 0.64f, 1.0f);

        RGFW_window_swapBuffers_OpenGL(win);

        glFlush();
    }

    RGFW_window_close(win);
    return 0;
}
