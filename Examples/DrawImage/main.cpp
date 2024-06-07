#include "GraphicLib/Mesh.h"
#include "Window/Input.h"
#include "Window/Window.h"

#include <GLFW/glfw3.h>
#include <GraphicLib/FrameBuffer.h>
#include <GraphicLib/IndexBuffer.h>
#include <GraphicLib/Logger.h>
#include <GraphicLib/Shader.h>
#include <GraphicLib/Texture.h>
#include <GraphicLib/VertexArray.h>
#include <GraphicLib/VertexBuffer.h>
#include <backends/imgui_impl_glfw.h>
#include <imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <windows.h>
#include <wingdi.h>
#include <iostream>

struct Transform {
    glm::vec3 Position{};
    glm::vec3 Rotation{};
    glm::vec3 Scale{1, 1, 1};
    glm::mat4 Matrix() const {
        glm::mat4 model{1.0f};
        model = glm::translate(model, Position);
        model = glm::rotate(model, glm::radians(Rotation.x), {1, 0, 0});
        model = glm::rotate(model, glm::radians(Rotation.y), {0, 1, 0});
        model = glm::rotate(model, glm::radians(Rotation.z), {0, 0, 1});
        model = glm::scale(model, Scale);
        return model;
    }
};

static std::string GetResourceFullPath(const char* resourcePath) {
    std::string output{EXEC_PATH};
    output.append(resourcePath);
    return output;
}

class Application {
public:
    void Initialise();
    void Start();
    void ProcessInput(EInputKey key, EInputAction action);
    void Update(float deltaTime);
    void Render();
    void RenderDebug();
    void Stop();

private:
    glm::mat4 _createProjectionViewMat() const;

    Window _window{};
    Input _input{};

    GraphicLib::VertexArray _boxVA{};
    GraphicLib::Mesh _boxMesh;
    GraphicLib::Shader _boxShader;
    GraphicLib::Texture _boxTexture{};

    GraphicLib::VertexArray _gridVA{};
    GraphicLib::Shader _gridShader{};

    // Box 1
    Transform _box{glm::vec3{0.f, 0.5f, 4.f}, glm::vec3{0.f, 22.f, 0.f}};

    // Camera data
    glm::vec3 _cameraPos{0.f, 2.f, 0.f};
    glm::vec3 _cameraDir{};
    glm::vec3 _cameraDirRight{};
    glm::vec3 _cameraRot{-20.f, 90.f, 0};
    float _cameraMovementSpeed{5.0f};
    float _cameraRotSpeed{100.0f};
    float _cameraFOV{45.0f};
    float _cameraNear{0.1f};
    float _cameraFar{100.0f};

    // Mouse
    bool _isMouseBeingDragged{};
    MousePosition _mouseDraggedStartingPosition{};

    double _deltaTime{};
    bool _shouldUpdate{};
};

void Application::Initialise() {
    GraphicLib::Logger::SetSeverity(GraphicLib::Logger::Severity::NOTIFICATION);
    GraphicLib::Logger::SetCallback(
        [](const GraphicLib::Logger::Message& message) {
            std::cout << "[" << message.source << "]";
            std::cout << ": \"" << message.text << "\"\n" << std::endl;
        },
        nullptr);

    if (!_window.Initialise("Example", this)) {
        return;
    }

    if (!_input.Initialise(_window)) {
        return;
    }

    _window.SetOnCloseCallback([](void* userData) {
        auto* application = static_cast<Application*>(userData);
        application->Stop();
    });

    _window.SetUpdateCallback([](float deltaTime, void* userData) {
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

    std::vector<float> boxVertices{
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, //
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f,  //
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,   //
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,   //
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,  //
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, //
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,  //
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,   //
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,    //
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,    //
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,   //
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,  //
        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,   //
        -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,  //
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, //
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, //
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,  //
        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,   //
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,    //
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,   //
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f,  //
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f,  //
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f,   //
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,    //
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, //
        0.5f, -0.5f, -0.5f, 1.0f, 1.0f,  //
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,   //
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,   //
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,  //
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, //
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,  //
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,   //
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,    //
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,    //
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,   //
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f   //
    };
    std::vector<GraphicLib::VertexAttribute> boxVertexAttributes{{"Position", 3}, {"TexCoord", 2}};
    GraphicLib::VertexBufferData boxVertexBufferData{std::move(boxVertices), std::move(boxVertexAttributes)};
    // _boxMesh.Initialise();
    // _boxMesh._boxMesh.GetVertexArray().GetVertexBuffer().Set(std::move(vertices), std::move(vertexAttributes));
    _boxVA.Initialise();
    _boxVA.Set(std::move(boxVertexBufferData));

    GraphicLib::TextureData boxTextureData{};
    boxTextureData.Parameters = {
        {GraphicLib::ETextureParamName::WRAP_S, GraphicLib::ETextureParamValue::WRAP_REPEAT},
        {GraphicLib::ETextureParamName::WRAP_T, GraphicLib::ETextureParamValue::WRAP_REPEAT},
        {GraphicLib::ETextureParamName::MIN_FILTER, GraphicLib::ETextureParamValue::FILTER_LIEAR},
        {GraphicLib::ETextureParamName::MAG_FILTER, GraphicLib::ETextureParamValue::FILTER_LIEAR},
    };
    boxTextureData.FilePath = GetResourceFullPath("Resources/Diffuse.png");
    boxTextureData.Type = GraphicLib::ETextureType::TEXTURE_2D;
    _boxTexture.Initialise();
    _boxTexture.SetFromFile(std::move(boxTextureData));
    std::vector<GraphicLib::ShaderData> boxShaderParams{
        {GetResourceFullPath("Resources/Texture.vertex"), GraphicLib::EShaderType::VERTEX},
        {GetResourceFullPath("Resources/Texture.fragment"), GraphicLib::EShaderType::FRAGMENT},
    };
    _boxShader.Initialise();
    _boxShader.Set(std::move(boxShaderParams));
    _boxShader.Bind();
    _boxShader.SetUniformIntValue("Diffuse", 0);
    _boxShader.Unbind();

    std::vector<float> gridVertices{
        1, 1, 0,   //
        -1, -1, 0, //
        -1, 1, 0,  //
        -1, -1, 0, //
        1, 1, 0,   //
        1, -1, 0,  //
    };
    std::vector<GraphicLib::VertexAttribute> gridVertexAttributes{{"Position", 3}};
    GraphicLib::VertexBufferData gridVertexBufferData{std::move(gridVertices), std::move(gridVertexAttributes)};
    _gridVA.Initialise();
    _gridVA.Set(std::move(gridVertexBufferData));
    std::vector<GraphicLib::ShaderData> gridShaderParams{
        {GetResourceFullPath("Resources/Grid.vertex"), GraphicLib::EShaderType::VERTEX},
        {GetResourceFullPath("Resources/Grid.fragment"), GraphicLib::EShaderType::FRAGMENT},
    };
    _gridShader.Initialise();
    _gridShader.Set(std::move(gridShaderParams));
}

void Application::Start() {
    while (_shouldUpdate) {
        _window.Update();
    }
}

void Application::ProcessInput(EInputKey key, EInputAction action) {
}

void Application::Update(float deltaTime) {
    _deltaTime = deltaTime;

    const double yawCos = glm::cos(glm::radians(_cameraRot.y));
    const double yawSin = glm::sin(glm::radians(_cameraRot.y));
    const double pitchCos = glm::cos(glm::radians(_cameraRot.x));
    const double pitchSin = glm::sin(glm::radians(_cameraRot.x));
    _cameraDir.x = yawCos * pitchCos;
    _cameraDir.y = pitchSin;
    _cameraDir.z = yawSin * pitchCos;
    _cameraDir = glm::normalize(_cameraDir);
    _cameraDirRight = glm::normalize(glm::cross(_cameraDir, {0, 1, 0}));

    if (_input.IsKeyPressed(EInputKey::W)) {
        _cameraPos += _cameraDir * _cameraMovementSpeed * deltaTime;
    }
    if (_input.IsKeyPressed(EInputKey::S)) {
        _cameraPos -= _cameraDir * _cameraMovementSpeed * deltaTime;
    }
    if (_input.IsKeyPressed(EInputKey::D)) {
        _cameraPos += _cameraDirRight * _cameraMovementSpeed * deltaTime;
    }
    if (_input.IsKeyPressed(EInputKey::A)) {
        _cameraPos -= _cameraDirRight * _cameraMovementSpeed * deltaTime;
    }

    if (_input.IsKeyPressed(EInputKey::MOUSE_RIGHT) && !_isMouseBeingDragged) {
        _isMouseBeingDragged = true;
        _mouseDraggedStartingPosition = _input.GetMousePosition();
    }

    if (_input.IsKeyReleased(EInputKey::MOUSE_RIGHT) && _isMouseBeingDragged) {
        _isMouseBeingDragged = false;
        _mouseDraggedStartingPosition = {};
    }

    if (_isMouseBeingDragged) {
        const MousePosition& mousePosition = _input.GetMousePosition();
        if (mousePosition == _mouseDraggedStartingPosition) {
            return;
        }

        constexpr double _deadZone = 2;

        if (mousePosition.Y > _mouseDraggedStartingPosition.Y + _deadZone) {
            _cameraRot.x -= _cameraRotSpeed * deltaTime;
            if (_cameraRot.x <= -90) {
                _cameraRot.x = -90;
            }
        }
        if (mousePosition.Y < _mouseDraggedStartingPosition.Y - _deadZone) {
            _cameraRot.x += _cameraRotSpeed * deltaTime;
            if (_cameraRot.x >= 90) {
                _cameraRot.x = 90;
            }
        }
        if (mousePosition.X > _mouseDraggedStartingPosition.X + _deadZone) {
            _cameraRot.y += _cameraRotSpeed * deltaTime;
            if (_cameraRot.y > 360.0f) {
                _cameraRot.y = 0.0f;
            }
        }
        if (mousePosition.X < _mouseDraggedStartingPosition.X - _deadZone) {
            _cameraRot.y -= _cameraRotSpeed * deltaTime;
            if (_cameraRot.y < 0.0f) {
                _cameraRot.y = 360.0f;
            }
        }

        _mouseDraggedStartingPosition = mousePosition;
    }
}

void Application::Render() {
    const WindowSize& windowSize{_window.GetSize()};
    glm::mat4 projection{glm::perspective(glm::radians(_cameraFOV),                   //
        static_cast<float>(windowSize.Width) / static_cast<float>(windowSize.Height), //
        _cameraNear,                                                                  //
        _cameraFar                                                                    //
        )};

    glm::mat4 view = glm::lookAt(_cameraPos, _cameraPos + _cameraDir, {0, 1, 0});

    _gridShader.Bind();
    _gridShader.SetUniformMat4Value("uView", glm::value_ptr(view));
    _gridShader.SetUniformMat4Value("uProj", glm::value_ptr(projection));
    _gridShader.SetUniformFloatValue("uNear", _cameraNear);
    _gridShader.SetUniformFloatValue("uFar", _cameraFar);
    _gridVA.Bind();
    _gridVA.Draw();

    _boxShader.Bind();
    glm::mat4 PV = _createProjectionViewMat();
    glm::mat4 MVP = PV * _box.Matrix();
    _boxShader.SetUniformMat4Value("uMVP", glm::value_ptr(MVP));
    _boxVA.Bind();
    _boxTexture.SetTextureSlot(0);
    _boxTexture.Bind();
    _boxVA.Draw();

    // MVP = PV * _box1.Matrix();
    //_boxShader.SetUniformMat4Value("uMVP", glm::value_ptr(MVP));
    //_boxVA.Draw();
}

void Application::RenderDebug() {
    static bool show_demo_window = true;

    const ImGuiViewport* mainViewport = ImGui::GetMainViewport();
    ImGui::DockSpaceOverViewport(mainViewport->ID, mainViewport, ImGuiDockNodeFlags_PassthruCentralNode);

    if (show_demo_window) {
        // ImGui::ShowDemoWindow(&show_demo_window);
    }

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

    ImGui::Begin("Transforms");
    {
        ImGui::SeparatorText("Box");
        ImGui::DragFloat3("_boxPos", glm::value_ptr(_box.Position));
        ImGui::DragFloat3("_boxRot", glm::value_ptr(_box.Rotation));

        ImGui::SeparatorText("Camera");
        ImGui::DragFloat3("_cameraPos", glm::value_ptr(_cameraPos));
        ImGui::DragFloat3("_cameraRot", glm::value_ptr(_cameraRot));
        ImGui::InputFloat("_cameraSpeed", &_cameraMovementSpeed);
        ImGui::InputFloat("_cameraRotSpeed", &_cameraRotSpeed);
        ImGui::DragFloat("_cameraFOV", &_cameraFOV);
        ImGui::Text("_cameraDir [%.2f,%.2f,%.2f]", _cameraDir.x, _cameraDir.y, _cameraDir.z);
        ImGui::Text("_cameraDirRight [%.2f,%.2f,%.2f]", _cameraDirRight.x, _cameraDirRight.y, _cameraDirRight.z);
        ImGui::Text("_cameraDirLeft [%.2f,%.2f,%.2f]", -_cameraDirRight.x, -_cameraDirRight.y, -_cameraDirRight.z);
    }
    ImGui::End();

    ImGui::Begin("Info");
    {
        ImGui::SeparatorText("Performance");
        ImGui::Text("Delta time: %.0fms", _deltaTime * 1000);
        ImGui::Text("FPS: %.0f", 1 / _deltaTime);
        const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        ImGui::Text("Resolution %dx%d", mode->width, mode->height);

        ImGui::SeparatorText("Input");
        ImGui::Text("Mouse pos: [%.0f, %.0f]", _input.GetMousePosition().X, _input.GetMousePosition().Y);
        ImGui::Text("Dragging: %s", _isMouseBeingDragged ? "on" : "off");
        ImGui::Text("Dragging start mouse pos: [%.0f, %.0f]", _mouseDraggedStartingPosition.X, _mouseDraggedStartingPosition.Y);
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
