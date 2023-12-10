#include "Window/Input.h"
#include "Window/Window.h"

#include <GLFW/glfw3.h>
#include <GraphicLib/IndexBuffer.h>
#include <GraphicLib/Logger.h>
#include <GraphicLib/Shader.h>
#include <GraphicLib/Texture.h>
#include <GraphicLib/Utilities/Span.h>
#include <GraphicLib/VertexArray.h>
#include <GraphicLib/VertexBuffer.h>
#include <imgui/imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
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
                                 "   texCoord = vec2(aTexCoord.x, aTexCoord.y);\n"
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
    void RenderDebug();
    void OnMouseInput(EMouseButton button, EInputAction action);
    void Stop();

private:
    glm::mat4 _createProjectionViewMat() const;
    Window _window{};
    GraphicLib::Shader _shader{};
    GraphicLib::VertexArray _triangleVA{};
    GraphicLib::Texture _textureTest{};

    glm::vec3 _boxPos{};
    glm::vec3 _boxRot{30, 30, 0};
    glm::vec3 _boxScale{1, 1, 1};

    glm::vec3 _cameraPos{0, 0, 3};
    glm::vec3 _cameraDir{0, 0, -1};

    EMouseButton _latestMouseButton{};
    EInputAction _latestMouseAction{};

    float _cameraFOV{45.0f};
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

void RenderWindowDebugCallback(void* userData) {
    auto* application = static_cast<Application*>(userData);
    application->RenderDebug();
}

void MouseInputCallback(EMouseButton button, EInputAction action, void* userData) {
    auto* application = static_cast<Application*>(userData);
    application->OnMouseInput(button, action);
}
} // namespace

void Application::Initialise() {
    GraphicLib::Logger::SetSeverity(GraphicLib::Logger::Severity::NOTIFICATION);
    GraphicLib::Logger::SetCallback(LoggerCallback, nullptr);

    if (!_window.Create({800, 600}, "Example", this)) {
        return;
    }
    _window.SetOnCloseCallback(CloseWindowCallback);
    _window.SetOnRenderWindowCallback(RenderWindowCallback);
    _window.SetOnRenderWindowDebugCallback(RenderWindowDebugCallback);
    _window.SetMouseInputCallback(MouseInputCallback);

    _shouldUpdate = true;

    const float vertices[] = {-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.5f, 0.5f, 0.5f, 1.0f,
        1.0f, 0.5f, 0.5f, 0.5f, 1.0f, 1.0f, -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, -0.5f, 0.5f, 0.5f, 1.0f, 0.0f, -0.5f, 0.5f, -0.5f,
        1.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, -0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.5f, 0.5f,
        0.5f, 1.0f, 0.0f, 0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.5f,
        0.5f, 0.5f, 1.0f, 0.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.5f, 0.5f, 0.5f, 1.0f,
        0.0f, 0.5f, 0.5f, 0.5f, 1.0f, 0.0f, -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, -0.5f, 0.5f, -0.5f, 0.0f, 1.0f};
    const int vertexAttributes[] = {3, 2};

    const GraphicLib::IndexBufferDataElement indices[] = {
        // note that we start from 0!
        {0, 1, 3}, // first triangle
        {1, 2, 3}, // second triangle
    };

    _triangleVA.Initialise();
    _triangleVA.Bind();
    _triangleVA.GetVertexBuffer().Set({vertices}, {vertexAttributes});
    //_triangleVA.GetIndexBuffer().Set({indices});

    const GraphicLib::TextureParam textureParams[] = {
        {GraphicLib::ETextureParamName::WRAP_S, GraphicLib::ETextureParamValue::WRAP_REPEAT},
        {GraphicLib::ETextureParamName::WRAP_T, GraphicLib::ETextureParamValue::WRAP_REPEAT},
        {GraphicLib::ETextureParamName::MIN_FILTER, GraphicLib::ETextureParamValue::FILTER_LIEAR},
        {GraphicLib::ETextureParamName::MAG_FILTER, GraphicLib::ETextureParamValue::FILTER_LIEAR},
    };
    _textureTest.Initialise();
    _textureTest.Set("Resources/TextureTest.png", GraphicLib::ETextureType::TEXTURE_2D, {textureParams});

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
    _shader.Bind();
    _triangleVA.Bind();
    _textureTest.Draw(0);
    glm::mat4 model{1.0f};
    model = glm::rotate(model, glm::radians(_boxRot.x), {1, 0, 0});
    model = glm::rotate(model, glm::radians(_boxRot.y), {0, 1, 0});
    model = glm::rotate(model, glm::radians(_boxRot.z), {0, 0, 1});
    model = glm::translate(model, _boxPos);
    glm::mat4 MVP = _createProjectionViewMat() * model;
    _shader.SetUniformMat4Value("uMVP", glm::value_ptr(MVP));
    _triangleVA.Draw();
}

void Application::RenderDebug() {
    static bool show_demo_window = true;

    if (show_demo_window) {
        ImGui::ShowDemoWindow(&show_demo_window);
    }

    ImGui::Begin("Transforms");
    {
        ImGui::DragFloat3("_boxPos", glm::value_ptr(_boxPos));
        ImGui::DragFloat3("_boxRot", glm::value_ptr(_boxRot));
        ImGui::DragFloat3("_cameraPos", glm::value_ptr(_cameraPos));
        ImGui::DragFloat3("_cameraDir", glm::value_ptr(_cameraDir));
        ImGui::DragFloat("_cameraFOV", &_cameraFOV);
    }
    ImGui::End();

    ImGui::Begin("Mouse info");
    {
        ImGui::LabelText(InputUtils::MouseButtonToString(_latestMouseButton), "_latestMouseButton");
        ImGui::LabelText(InputUtils::MouseInputActionToString(_latestMouseAction), "_latestMouseAction");
    }
    ImGui::End();
}

void Application::OnMouseInput(EMouseButton button, EInputAction action) {
    _latestMouseButton = button;
    _latestMouseAction = action;
}

void Application::Stop() {
    _shouldUpdate = false;
}

glm::mat4 Application::_createProjectionViewMat() const {
    const WindowSize& windowSize{_window.GetSize()};
    const glm::mat4 projection{glm::perspective(glm::radians(_cameraFOV),             //
        static_cast<float>(windowSize.Width) / static_cast<float>(windowSize.Height), //
        0.1f,                                                                         //
        100.0f                                                                        //
        )};
    const glm::mat4 view = glm::lookAt(_cameraPos, _cameraPos + _cameraDir, {0, 1, 0});

    return projection * view;
}

int main() {
    Application app;
    app.Initialise();
    app.Start();
}