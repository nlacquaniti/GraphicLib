#include "GraphicLib/IndexBuffer.h"
#include "GraphicLib/Utilities/Span.h"
#include "GraphicLib/VertexArray.h"
#include "GraphicLib/VertexBuffer.h"
#include <GraphicLib/Logger.h>
#include <GraphicLib/Window.h>
#include <iostream>
#include <memory>

const char* vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";
const char* fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                   "}\n\0";

class Application {
public:
    void Initialise();
    void Start();
    void Render();
    void Stop();

private:
    GraphicLib::Window _window{};
    bool _shouldUpdate{};
};

namespace {
void LoggerCallback(const GraphicLib::Logger::Message& message) {
    std::cout << "Source [" << message.source << "]\n";
    std::cout << "Type [" << message.type << "]\n";
    std::cout << "Message [" << message.text << "]" << std::endl;
}
void CloseWindowCallback(void* userData) {
    auto* application = static_cast<Application*>(userData);
    application->Stop();
}

void RenderWindowCallback(void* userData) {
    auto* application = static_cast<Application*>(userData);
    application->Render();
}
} // namespace

void Application::Initialise() {
    GraphicLib::Logger::SetSeverity(GraphicLib::Logger::Severity::NOTIFICATION);
    GraphicLib::Logger::SetCallback(LoggerCallback, nullptr);

    _window.SetOnCloseCallback(CloseWindowCallback);
    _window.SetOnRenderWindowCallback(RenderWindowCallback);
    if (!_window.Create({800, 600}, "Example", this)) {
        return;
    }
    _shouldUpdate = true;

    const float vertexData[] = {
        -0.5f, -0.5f, 0.0f, //
        0.5f, -0.5f, 0.0f,  //
        0.0f, 0.5f, 0.0f    //
    };
    const int vertexAttributes[] = {3};
    const GraphicLib::IndexBufferDataElement indices[] = {{0, 1, 3}};

    GraphicLib::VertexArray vertexArray{};
    vertexArray.Bind();
    vertexArray.GetVertexBuffer().Set({vertexData}, {vertexAttributes});
    vertexArray.GetIndexBuffer().Set({indices});
}

void Application::Start() {
    while (_shouldUpdate) {
        _window.Render();
    }
}

void Application::Render() {
}

void Application::Stop() {
    _shouldUpdate = false;
}

int main() {
    Application app;
    app.Initialise();
    app.Start();
}