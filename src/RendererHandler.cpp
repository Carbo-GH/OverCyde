#include "Utils/debugging.h"

#include "RendererHandler.h"
#include "RendererObj.h"
#include "Utils/global.h"
#include <vector>

RendererHandler::RendererHandler() : Handler() {
    this->projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    this->view = new ViewMatrix();
}

RendererHandler::~RendererHandler() {}

void *RendererHandler::Initialize() {
    if (!glfwInit())
        return nullptr;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    this->window = glfwCreateWindow(HEIGHT, WEIGHT, "OverCyde", NULL, NULL);
    if (!this->window) {
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(this->window);
    glewInit();
    printout_opengl_glsl_info();

    glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glEnable(GL_DEPTH_TEST);

    return this->window;
}

void RendererHandler::Shutdown() {
    glfwTerminate();
}

void RendererHandler::Update() {
    glClearColor(DESTRUCT(BACKGROUND_COLOR));
    glClear(GL_COLOR_BUFFER_BIT);

    // for(auto obj : this->objs )
    //     obj->Draw(deltaTime, this->projection, this->view);

    glfwSwapBuffers(window);
    glfwPollEvents();
}

void RendererHandler::AddElement(RendererObj *obj) {
    this->objs.__emplace_back(obj);
}

void RendererHandler::RemoveElement(RendererObj *obj) {
    auto iter = std::find(this->objs.begin(), this->objs.end(), obj);
    if (iter != this->objs.end()){
        std::iter_swap(iter, this->objs.end() - 1);
        this->objs.pop_back();
    }
}