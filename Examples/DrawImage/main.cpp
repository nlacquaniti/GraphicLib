#include <GraphicLib/Logger.h>
#include <GraphicLib/Window.h>
#include <iostream>
#include <memory>

class Application {
public:
    void Initialise();
    void Start();
    void Render();
    void Stop();

private:
    std::unique_ptr<GraphicLib::Window> _window{};
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

    _window.reset(GraphicLib::CreateWindow(800, 600, "Example"));
    _window->SetOnCloseCallback(CloseWindowCallback, this);
    _window->SetOnRenderWindowCallback(RenderWindowCallback, this);
    _window->Initialise();
    _shouldUpdate = true;
}

void Application::Start() {
    while (_shouldUpdate) {
        _window->Render();
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