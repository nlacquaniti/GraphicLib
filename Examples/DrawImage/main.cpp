#include "Window.h"
#include <GraphicLib/IndexBuffer.h>
#include <GraphicLib/Shader.h>
#include <GraphicLib/Texture.h>
#include <GraphicLib/Utilities/Span.h>
#include <GraphicLib/VertexArray.h>
#include <GraphicLib/VertexBuffer.h>
#include <GraphicLib/Logger.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui/imgui.h>
#include <iostream>
#include <memory>

const char* vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "layout (location = 1) in vec2 aTexCoord;\n"
                                 "uniform mat4 uMVP;\n"
                                 "out vec2 texCoord;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = uMVP * vec4(aPos, 1.0);\n"
                                 "   texCoord = aTexCoord;\n"
                                 "}\0";
const char* fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "in vec2 texCoord;\n"
                                   "uniform sampler2D uTexture;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = texture(uTexture, texCoord);\n"
                                   "}\n\0";

class Application {
public:
    void Initialise();
    void Start();
    void Render();
    void Stop();

private:
    Window _window{};
    GraphicLib::Shader _shader{};
    GraphicLib::VertexArray _triangleVA{};
    GraphicLib::Texture _textureTest{};
    bool _shouldUpdate{};
};

namespace {
void LoggerCallback(const GraphicLib::Logger::Message& message) {
    std::cout << "[" << message.source << "]";
    std::cout << ": \"" << message.text << "\"\n" << std::endl;
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

    // Setup Dear ImGui context
    //IMGUI_CHECKVERSION();
    //ImGui::CreateContext();
    //ImGuiIO& io = ImGui::GetIO();
    //(void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
    //io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // Enable Docking
    //io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;   // Enable Multi-Viewport / Platform Windows
    // io.ConfigViewportsNoAutoMerge = true;
    // io.ConfigViewportsNoTaskBarIcon = true;

    _shouldUpdate = true;

    const float vertices[] = {
        0.5f, 0.5f, 0.0f, 1.0f, 1.0f,   // top right
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,  // top left
    };
    const int vertexAttributes[] = {3, 2};

    const GraphicLib::IndexBufferDataElement indices[] = {
        // note that we start from 0!
        {0, 1, 3}, // first triangle
        {1, 2, 3}, // second triangle
    };

    _triangleVA.Initialise();
    _triangleVA.GetVertexBuffer().Set({vertices}, {vertexAttributes});
    _triangleVA.GetIndexBuffer().Set({indices});

    const GraphicLib::TextureParam textureParams[] = {
        {GraphicLib::TextureParamName::WRAP_S, GraphicLib::TextureParamValue::WRAP_REPEAT},
        {GraphicLib::TextureParamName::WRAP_T, GraphicLib::TextureParamValue::WRAP_REPEAT},
        {GraphicLib::TextureParamName::MIN_FILTER, GraphicLib::TextureParamValue::FILTER_LIEAR},
        {GraphicLib::TextureParamName::MAG_FILTER, GraphicLib::TextureParamValue::FILTER_LIEAR},
    };
    _textureTest.Initialise();
    _textureTest.Set("Resources/TextureTest.png", GraphicLib::TextureType::TEXTURE_2D, {textureParams});

    _shader.Load(vertexShaderSource, fragmentShaderSource);
    _shader.Bind();
    _shader.SetUniformIntValue("uTexture", 0);
}

void Application::Start() {
    while (_shouldUpdate) {
        _window.Render();
    }
}

void Application::Render() {
    _textureTest.Draw(0);
    _shader.Bind();
    glm::mat4 MVP(1.0f);
    _shader.SetUniformMat4Value("uMVP", glm::value_ptr(MVP));
    _triangleVA.Draw();
}

void Application::Stop() {
    _shouldUpdate = false;
}

int main() {
    Application app;
    app.Initialise();
    app.Start();
}