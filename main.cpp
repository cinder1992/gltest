/* include standard libaries */
#include <cstdio>
#include <cstdlib>
#include <string>

/* include GLEW, GLWF, and glm */
#include <GL/glew.h>
#include <GLFW/glfw3.h>

/* put all custom includes here */
#include "loadShaders.h"

/* declare our debugging code */
#define GL(CODE)  ((CODE), GL_real(#CODE))

int GL_real(const char* code_string) {
  GLenum err = glGetError();
  if (err != GL_NO_ERROR){
    printf("opengl error: 0x%x\n", err);
    printf("code: %s\n", code_string);
  }
  return (err = GL_NO_ERROR);
}
/* declare our constructors */
void error_callback(int, const char*);
void key_callback(GLFWwindow*, int, int, int, int);

int main() {
  using namespace std;

  /* Declare our variables */
  GLuint VertexArrayID;
  static const GLfloat g_vertex_buffer_data[] = { /* Triangle vertex buffer data */
    -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
  };

  if (!glfwInit()) { /* Initialise glfw and check for errors */
    fprintf( stderr, "Failed to initialise GLFW\n");
    return -1;
  }


  glfwSetErrorCallback(error_callback); /* set our error callback */

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); /* set our OpenGL context version, in this case openGL 3.3 */
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(640, 480, "Test window", NULL, NULL); /* Open a window */

  if (!window) { /* Did the window successfully open? */
    glfwTerminate();
    fprintf( stderr, "Failed to initialise GLEW window\n");
    return -1;
  }

  glfwMakeContextCurrent(window); /* make sure we have an OpenGL context */

  glewExperimental=GL_TRUE; /* Enable GLEW */
  if (glewInit() != GLEW_OK) {
    fprintf(stderr, "Failed to initialize GLEW\n");
    return -1;
  }

  glfwSetKeyCallback(window, key_callback); /* set our key callback */
  GL(0);
  /* set up our vertex array */
  GL(glGenBuffers(1, &VertexArrayID));
  GL(glBindBuffer(GL_ARRAY_BUFFER, VertexArrayID));
  GL(glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW));

  /* compile our shaders */
  GLuint programID = loadShaders( "../VertexShader.vert", "../FragmentShader.frag" );
  GL(0); /* check error status */
  GL(glUseProgram(programID));

  /* initialise the clear color */
  GL(glClearColor(0.0f, 0.0f, 0.4f, 0.0f));

  while(!glfwWindowShouldClose(window)) { /* keep swapping the buffers until we have to close the window */
    GL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)); /* Clear the screen */
    /* draw our triangle */
    GL(glEnableVertexAttribArray(0));

    GL(glUseProgram(programID));
    /* tell openGL to use our shader */
    GL(glBindBuffer(GL_ARRAY_BUFFER, VertexArrayID));
    GL(glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        0,
        NULL
    ));

    /* actually draw the array */
    GL(glDrawArrays(GL_TRIANGLES, 0, 3));
    GL(glDisableVertexAttribArray(0));

    glfwSwapBuffers(window);
    glfwWaitEvents();
  }
  glfwDestroyWindow(window); /* BANG CRUSH BYE-BYE WINDOW */
  glfwTerminate(); /* Cleanup after ourselves */
  return 0;
}

void error_callback(int error, const char* desc) { /* Error callback */
  fputs(desc, stderr);
}

void key_callback(GLFWwindow* win, int key, int scancode, int action, int mods) { /* key callback */
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(win, true);
  }
}
