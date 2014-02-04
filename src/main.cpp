/* include standard libaries */
#include <cstdio>
#include <cstdlib>
#include <string>

/* include GLEW, GLWF, and glm */
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
// glm::translate, glm::rotate, glm::scale
#include <glm/gtc/matrix_transform.hpp> 

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
  GLuint vertexbuffer;
  static const GLfloat g_vertex_buffer_data[] = { /* Triangle vertex buffer data */
        -1.0f,-1.0f,-1.0f, // triangle 1 : begin
        -1.0f,-1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f, // triangle 1 : end
         1.0f, 1.0f,-1.0f, // triangle 2 : begin
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f, // triangle 2 : end
         1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
         1.0f,-1.0f,-1.0f,
         1.0f, 1.0f,-1.0f,
         1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
         1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
         1.0f,-1.0f, 1.0f,
         1.0f, 1.0f, 1.0f,
         1.0f,-1.0f,-1.0f,
         1.0f, 1.0f,-1.0f,
         1.0f,-1.0f,-1.0f,
         1.0f, 1.0f, 1.0f,
         1.0f,-1.0f, 1.0f,
         1.0f, 1.0f, 1.0f,
         1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
         1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
         1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
         1.0f,-1.0f, 1.0f,
  };

  /* Declare our matricies */
  glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
  glm::mat4 Veiw = glm::lookAt(
          glm::vec3(4,3,-3), // Camera is at (4,3,3), in World Space
          glm::vec3(0,0,0), // and looks at the origin
          glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
      );
  glm::mat4 Model = glm::mat4(1.0f);
  glm::mat4 MVP = Projection * Veiw * Model;

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

  /* enable GL_DEPTH_TEST */

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  /* set up our vertex array */
  GL(glGenVertexArrays(1, &VertexArrayID));
  GL(glBindVertexArray(VertexArrayID));

  /* Generate our buffer */
  GL(glGenBuffers(1, &vertexbuffer));
  GL(glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer));
  GL(glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW));

  /* compile our shaders */
  GLuint programID = loadShaders( "shaders/VertexShader.vert", "shaders/FragmentShader.frag" );
  GL(0); /* check error status */
  GL(glUseProgram(programID));

  
  /* initialise the clear color */
  GL(glClearColor(0.0f, 0.0f, 0.4f, 0.0f));
  /* Get the location of our uniform values in the shader */
  GLuint MatrixID = glGetUniformLocation(programID, "MVP");
  GLuint ModMatrixID = glGetUniformLocation(programID, "ModelMatrix");

  while(!glfwWindowShouldClose(window)) { /* keep swapping the buffers until we have to close the window */
    GL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)); /* clear the screen */
    /* give our shader program our matricies */
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
    glUniformMatrix4fv(ModMatrixID, 1, GL_FALSE, &Model[0][0]);
    /* enable our program */
    GL(glUseProgram(programID));
    /* Bind our buffer */
    GL(glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer));
    /* use attrib array 0 */
    GL(glEnableVertexAttribArray(0));
    GL(glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        0,
        NULL
    ));
    /* actually draw the array */
    GL(glDrawArrays(GL_TRIANGLES, 0, 12*3));
    GL(glDisableVertexAttribArray(0));
    /* swap buffers and wait for input */
    glfwSwapBuffers(window);
    glfwWaitEvents();
  }
  glfwDestroyWindow(window); /* BANG CRUSH BYE-BYE WINDOW */
  glfwTerminate(); /* Cleanup after ourselves */
  glDeleteBuffers(1, &vertexbuffer);
  glDeleteVertexArrays(1, &VertexArrayID);
  glDeleteProgram(programID); /* Prevent more clutter */
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
