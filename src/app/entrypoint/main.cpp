#include "application.hpp"

int main(int argc, char** argv)
{
    IMGV::App::Application* app = new IMGV::App::Application();
    app->Run();
    delete app;

    return 0;
}