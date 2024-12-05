#pragma once

#include <glad/glad.h>
#include "typedef.hpp"

namespace IMGV::Core
{
    #ifdef IMGV_DEBUG
        void GLAPIENTRY DebugMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);
    #endif
}