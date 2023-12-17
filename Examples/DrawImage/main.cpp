#include "Window/Input.h"
#include "Window/Window.h"
#include "Utils/InputUtils.h"

#include <GLFW/glfw3.h>
#include <GraphicLib/FrameBuffer.h>
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
#include <string>

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
    void ProcessInput(EInputKey key, EInputAction action);
    void Update(double deltaTime);
    void Render();
    void RenderDebug();
    void Stop();

private:
    glm::mat4 _createProjectionViewMat() const;
    Window _window{};
    Input _input{};
    GraphicLib::Shader _shader{};
    GraphicLib::VertexArray _triangleVA{};
    GraphicLib::Texture _textureTest{};

    glm::vec3 _boxPos{};
    glm::vec3 _boxRot{30, 30, 0};
    glm::vec3 _boxScale{1, 1, 1};

    glm::vec3 _cameraPos{0, 0, 3};
    glm::vec3 _cameraDir{0, 0, -1};

    EInputKey _latestKey{};
    EInputAction _latestKeyAction{};
    bool _isRightMousePressed{};

    double _deltaTime{};
    float _cameraFOV{45.0f};
    bool _shouldUpdate{};
};

void Application::Initialise() {
    GraphicLib::Logger::SetSeverity(GraphicLib::Logger::Severity::MEDIUM);
    GraphicLib::Logger::SetCallback(
        [](const GraphicLib::Logger::Message& message) {
            std::cout << "[" << message.source << "]";
            std::cout << ": \"" << message.text << "\"\n" << std::endl;
        },
        nullptr);

    if (!_window.Initialise({800, 600}, "Example", this)) {
        return;
    }

    if (!_input.Initialise(_window)) {
        return;
    }

    _window.SetOnCloseCallback([](void* userData) {
        auto* application = static_cast<Application*>(userData);
        application->Stop();
    });

    _window.SetUpdateCallback([](double deltaTime, void* userData) {
        auto* application = static_cast<Application*>(userData);
        application->Update(deltaTime);
    });

    _window.SetOnRenderWindowCallback([](void* userData) {
        auto* application = static_cast<Application*>(userData);
        application->Render();
    });

    _window.SetOnRenderWindowDebugCallback([](void* userData) {
        auto* application = static_cast<Application*>(userData);
        application->RenderDebug();
    });

    _input.SetKeyInputCallback(
        [](EInputKey key, EInputAction action, void* userData) {
            auto* application = static_cast<Application*>(userData);
            application->ProcessInput(key, action);
        },
        this);

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
    _textureTest.Initialise(GraphicLib::ETextureType::TEXTURE_2D);
    _textureTest.Bind();
    _textureTest.Set("Resources/TextureTest.png", {textureParams});

    _shader.Load(vertexShaderSource, fragmentShaderSource);
    _shader.Bind();
    _shader.SetUniformIntValue("uTexture", 0);
}

void Application::Start() {
    while (_shouldUpdate) {
        _window.Update();
    }
}

void Application::ProcessInput(EInputKey key, EInputAction action) {
    _latestKey = key;
    _latestKeyAction = action;
}

void Application::Update(double deltaTime) {
    _deltaTime = deltaTime;

    _isRightMousePressed = _input.IsKeyPressed(EInputKey::MOUSE_RIGHT);
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

    // if (show_demo_window) {
    //     ImGui::ShowDemoWindow(&show_demo_window);
    // }
    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);

    ImGui::Begin("Transforms");
    {
        ImGui::DragFloat3("_boxPos", glm::value_ptr(_boxPos));
        ImGui::DragFloat3("_boxRot", glm::value_ptr(_boxRot));
        ImGui::DragFloat3("_cameraPos", glm::value_ptr(_cameraPos));
        ImGui::DragFloat3("_cameraDir", glm::value_ptr(_cameraDir));
        ImGui::DragFloat("_cameraFOV", &_cameraFOV);
    }
    ImGui::End();

    ImGui::Begin("Info");
    {
        ImGui::TextColored({0, 255, 0, 255}, "Delta time: %.0fms", _deltaTime * 1000);
        ImGui::TextColored({0, 255, 0, 255}, "Mouse pos: [%.0f, %.0f]", _input.GetMousePosition().X, _input.GetMousePosition().Y);
        ImGui::Text("_isRightMousePressed: %d", _isRightMousePressed);
        ImGui::LabelText(InputUtils::InputKeyToString(_latestKey), "_latestMouseButton");
        ImGui::LabelText(InputUtils::MouseInputActionToString(_latestKeyAction), "_latestMouseAction");
    }
    ImGui::End();

    ImGui::Begin("Scene");
    {
        const ImVec2& pos = ImGui::GetCursorScreenPos();
        const WindowSize& windowSize = _window.GetSize();
        ImGui::GetWindowDrawList()->AddImage(                                                                              //
            reinterpret_cast<void*>(static_cast<unsigned long long>(_window.GetWindowFrameBuffer().GetTexture().GetID())), //
            pos,                                                                                                           //
            {pos.x + windowSize.Width, pos.y + windowSize.Height},                                                         //
            {0, 1},                                                                                                        //
            {1, 0}                                                                                                         //
        );
    }
    ImGui::End();
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