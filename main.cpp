/* include standard libaries */
#include <cstdio>
#include <cstdlib>
#include <string>

/* include GLEW, GLWF, and glm */
#include <GL/glew.h>
#include <GLFW/glfw3.h>

/* put all custom includes here */
#include "loadShaders.h"
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

  /* set up our vertex array */
  glGenBuffers(1, &VertexArrayID);
  glBindBuffer(GL_ARRAY_BUFFER, VertexArrayID);
  glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);


  while(!glfwWindowShouldClose(window)) { /* keep swapping the buffers until we have to close the window */
    /* draw our triangle */
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VertexArrayID);
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        0,
        NULL
    );
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(0);

    glfwSwapBuffers(window);
    glfwPollEvents();
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
