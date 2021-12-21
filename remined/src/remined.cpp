#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <iostream>
#include <sstream>

#include "util/camera/camera.h"
#include "player/player.h"
#include "world/world.h"

void glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mode);
bool initOpenGL(GLFWwindow** window, const bool fullScreen, const int width, const int height, const char* const appTitle);
void showFPS(GLFWwindow* window, const char* const appTitle);

bool gWireFrame = false;

int main(void)
{
    const char* const appTitle = "remined";
    const int winWidth = 1920;
    const int winHeight = 1080;
    const bool fullScreen = false;

    GLFWwindow* window;
    if (!initOpenGL(&window, fullScreen, winWidth, winHeight, appTitle)) { return -1; }

    //limit frame rate to refresh rate
    //glfwSwapInterval(1);

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    World* world = World::getInstance(new Player(window, winWidth, winHeight, 1, false /*max 7?*/));

    while (!glfwWindowShouldClose(window))
    {
        if (!fullScreen)
            showFPS(window, appTitle);
        {
            world->update();
            world->render();
        }
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

bool initOpenGL(GLFWwindow** window, bool fullScreen, const int width, const int height, const char* const appTitle) {
    //initialize GLFW
    if (!glfwInit())
    {
        std::cerr << "GLFW initialization failed" << std::endl;
        return false;
    }

    //set openGL from compat to core at version 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    if (fullScreen)
    {
        GLFWmonitor* pMonitor = glfwGetPrimaryMonitor(); //get pointer to primary monitor
        const GLFWvidmode* pVidmode = glfwGetVideoMode(pMonitor);
        if (pVidmode != NULL)
        {
            *window = glfwCreateWindow(pVidmode->width, pVidmode->height, appTitle, pMonitor, NULL);
        }
    }
    else {
        *window = glfwCreateWindow(width, height, appTitle, NULL, NULL);
    }

    if (*window == NULL)
    {
        std::cout << "Failed to create GLFW Window" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(*window);
    glfwSetKeyCallback(*window, glfw_onKey);

    //Hides and grabs cursor, unlimited movement
    glfwSetInputMode(*window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPos(*window, width / 2.0, height / 2.0);

    //initialize GLEW on window creation
    // why was this here? //glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cout << "GLEW initialization failed." << std::endl;
        return false;
    }

    //set screen color
    glClearColor(0.23f, 0.38f, 0.47f, 1.0f); //RGBAlpha color channels, from 0 to 1
    glViewport(0, 0, width, height);

    return true;
}

void glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    //exit on esc
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

    if (key == GLFW_KEY_1 && action == GLFW_PRESS)
    {
        if (gWireFrame = !gWireFrame)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}

void showFPS(GLFWwindow* window, const char* const appTitle)
{
    static double previousSeconds = 0.0;
    static int frameCount = 0;
    double elapsedSeconds;
    double currentSeconds = glfwGetTime(); //returns number of seconds since GLFW started

    elapsedSeconds = currentSeconds - previousSeconds;

    //limit text update 4 times per second
    if (elapsedSeconds > 0.25)
    {
        previousSeconds = currentSeconds;
        double fps = (double)frameCount / elapsedSeconds;
        double msPerFrame = 1000.0 / fps;

        std::ostringstream outs;
        outs.precision(3);
        outs << std::fixed
            << appTitle << "  "
            << "FPS: " << fps << "  "
            << "Frame Time: " << msPerFrame << " (ms)";
        glfwSetWindowTitle(window, outs.str().c_str());

        frameCount = 0; //reset
    }
    frameCount++; //tick frames
}