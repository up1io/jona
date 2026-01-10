#include <stdio.h>

#define RGFW_DEBUG
#define RGFW_OPENGL
#define RGFW_IMPLEMENTATION

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define CLAY_IMPLEMENTATION
#include <clay/clay.h>

#include "RGFW.h"
#include "shader.h"
#include "jona/arena.h"
#include <cglm/cglm.h>

#ifdef RGFW_MACOS
#include <OpenGL/gl.h>
#else
#include <glad/glad.h>
#include <GL/gl.h>
#endif

float vertices[] = {
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
    -0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 1.0f,   0.0f, 1.0f
};

unsigned int indices[] = {  
    0, 1, 3,
    1, 2, 3,
};  

float texCords[] = {
  0.0f, 0.0f,
  1.0f, 0.0f,
  0.5f, 1.0f
};

int selectedVertex = 0;
float moveStep = 0.02f;

int screenWidth = 800;
int screenHeight = 600;
    
void keyFunc(RGFW_window* win, RGFW_key key, u8 keyChar, RGFW_keymod keyMod, RGFW_bool repeat, RGFW_bool pressed) {
    RGFW_UNUSED(repeat);
    RGFW_UNUSED(keyChar);
    RGFW_UNUSED(keyMod);

    // Note(john): update the vertex pos based on the a-,w-,s-,d-keys
    /*
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
    */

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

void jo_clay_handler_errors(Clay_ErrorData error_data) {
  printf("%s", error_data.errorText.chars);
} 

int main(void) {
    RGFW_window* win = RGFW_createWindow("Jona", 0, 0, screenWidth, screenHeight, RGFW_windowOpenGL | RGFW_windowFloating);
    RGFW_setKeyCallback(keyFunc);

    if (!gladLoadGL()) {
        fprintf(stderr, "Failed to initialize GLAD\n");
        return -1;
    }

    //
    // ARENA TEST
    //

    arena_t test_arena;
    arena_init(&test_arena, 1024);

    int *a = arena_alloc(&test_arena, sizeof(int));

    *a = 10;

    printf("%d \n", *a);

    arena_destroy(&test_arena);

    //
    // ARENA TEST END
    //

    //printf("OpenGL version: %s\n", glGetString(GL_VERSION));

    glViewport(0,0,800,600);

    uint64_t totalMemorySize = Clay_MinMemorySize();
    Clay_Arena arena = Clay_CreateArenaWithCapacityAndMemory(totalMemorySize, malloc(totalMemorySize));

    Clay_Initialize(arena, (Clay_Dimensions) { screenWidth, screenHeight }, (Clay_ErrorHandler) { jo_clay_handler_errors });

    // RGFW_window_makeCurrentContext_OpenGL(win);
    //
    //int success;
    //char infoLog[512];

    // int nrAttributes = glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    // printf("INFO: %p\n", nrAttributes);

    /*
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        printf("ERROR: %s\n", infoLog);
    }

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        printf("ERROR: %s\n", infoLog);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    */

    jo_shader_t *shader;
    jo_shader_error_t err;

    err = jo_shader_create(&shader, "shader/default_vertex.glsl", "shader/default_fragment.glsl");
    if (err != JO_SHADER_OK) {
      printf("ERROR: %u\n", err);
      return 0;
    }

    // VBO
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    
    // VAO
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // EBO
    unsigned int EBO;
    glGenBuffers(1, &EBO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    // glEnableVertexAttribArray(0);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6* sizeof(float)));
    glEnableVertexAttribArray(2);

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    stbi_set_flip_vertically_on_load(1);

    int width, height, nrChannels;
    unsigned char *data = stbi_load("resource/checker-texture.jpg", &width, &height, &nrChannels, 0); 
    if (data) {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(GL_TEXTURE_2D);
    } else {
      fprintf(stderr, "failed to load texture");
    }
    stbi_image_free(data);

    unsigned int texture2;
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);

    unsigned char *data2 = stbi_load("resource/smile.jpg", &width, &height, &nrChannels, 0); 
    if (data2) {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data2);
      glGenerateMipmap(GL_TEXTURE_2D);
    } else {
      fprintf(stderr, "failed to load texture");
    }
    stbi_image_free(data2);

    jo_shader_use(shader);
    jo_shader_set_int(shader, "texture1", 0);
    jo_shader_set_int(shader, "texture2", 1);

    //glUniform1i(glGetUniformLocati

    mat4 model, view, projection, mvp;
    
    glm_mat4_identity(model);
    glm_mat4_identity(view);
    glm_mat4_identity(projection);

    glm_translate(view, (vec3){0.0f, 0.5f, -2.0f});
    glm_perspective(glm_rad(45.0f), 800.0f / 600.0f, 0.1f, 100.0f, projection);

    while (RGFW_window_shouldClose(win) == RGFW_FALSE) {
      RGFW_event event;
      while(RGFW_window_checkEvent(win, &event)) {
        if (event.type == RGFW_quit) break;
      }

      Clay_SetLayoutDimensions((Clay_Dimensions) { screenWidth, screenHeight });
      
      Clay_BeginLayout();

      CLAY(CLAY_ID("OuterContainer"), { .layout = { .sizing = {CLAY_SIZING_GROW(0), CLAY_SIZING_GROW(0)}, .padding = CLAY_PADDING_ALL(16), .childGap = 16 }, .backgroundColor = {250,250,255,255} }) {
      }
      /*
      CLAY({
          .sizing = {
            .width = FIXED(800),
            .height = FIXED(600),
          },
          .backgroundColor = BLUE,
      });
      */

      // Clay_RenderCommandArray renderCommands = Clay_EndLayout();
      Clay_EndLayout();

      glClearColor(0.43f, 0.48f, 0.64f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      // int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
      // glUseProgram(shaderProgram);
      //glUniform4f(vertexColorLocation, 0.0f, 1.0f, 0.0f, 1.0f);

      // glUseProgram(shaderProgram);
      // jo_shader_use(shader);

      static float angle = 0.0f;
      angle += 0.2f; 

      glm_mat4_identity(model);
      glm_rotate(model, angle, (vec3){0.2f, 1.0f, 0.0f});

      glm_mat4_mul(view, model, mvp);
      glm_mat4_mul(projection, mvp, mvp);

      // jo_shader_set_float(shader, "mvp", (float)mvp);
      jo_shader_set_mat4(shader, "MVP", (float *)mvp);

      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D, texture);
      glActiveTexture(GL_TEXTURE1);
      glBindTexture(GL_TEXTURE_2D, texture2);


      glBindVertexArray(VAO);
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
      glBindVertexArray(0);

      RGFW_window_swapBuffers_OpenGL(win);

      glFlush();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    // glDeleteProgram(shaderProgram);

    jo_shader_destroy(shader);

    RGFW_window_close(win);
    return 0;
}
