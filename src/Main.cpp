#include "core/Application.h"

int main() {
    const auto app = Application::GetInstance();
    app->Init();
    app->Run();
    return 0;
}
