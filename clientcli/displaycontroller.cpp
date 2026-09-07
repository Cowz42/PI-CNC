



#include"displaycontroller.h"



void (*key_functions[256])(int key, int action, int mods);



bool start() {
    std::cout << "Starting Display\n";
    glfwSetErrorCallback(error_callback);

    if (!glfwInit()) {
        return false;
    }

    GLFWwindow* window = glfwCreateWindow(640, 480, "PI-CNC", NULL, NULL);

    if (!window) {
        std::cerr << "GLFW Loading Error: Window load problem\n";
        close();
        return false;
    }

    glfwMakeContextCurrent(window);


    glfwSetWindowCloseCallback(window, close_callback);


    glfwSwapInterval(1);
    glfwWaitEvents();

}


void close() {
    glfwTerminate();
}

void error_callback(int error, const char* description) {
    std::cerr << "GLFW Error: " << description << "\n";
}

void close_callback(GLFWwindow* w) {
    glfwDestroyWindow(w);
}


static void input_callback(GLFWwindow* w, int key, int scancode, int action, int mods) {

}

void setKeyCallback(void (*fn)(int key, int action, int mods), unsigned int index) {
    if (index >= 256) {
        return;
    }
    key_functions[index] = fn;
}