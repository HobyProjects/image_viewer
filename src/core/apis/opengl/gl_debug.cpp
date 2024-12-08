#include "gl_debug.hpp"

namespace IMGV::Core
{
    #ifdef IMGV_DEBUG
        void GLAPIENTRY DebugMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam)
        {       
            CString type_str        = IMGV_NULLPTR;
            CString severity_str    = IMGV_NULLPTR;
            CString source_str      = IMGV_NULLPTR;
            
            switch(type)
            {
                case GL_DEBUG_TYPE_ERROR:                   type_str = IMGV_TOSTRING(GL_DEBUG_TYPE_ERROR); break;
                case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:     type_str = IMGV_TOSTRING(GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR); break;
                case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:      type_str = IMGV_TOSTRING(GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR); break;
                case GL_DEBUG_TYPE_PORTABILITY:             type_str = IMGV_TOSTRING(GL_DEBUG_TYPE_PORTABILITY); break;
                case GL_DEBUG_TYPE_PERFORMANCE:             type_str = IMGV_TOSTRING(GL_DEBUG_TYPE_PERFORMANCE); break;
                case GL_DEBUG_TYPE_MARKER:                  type_str = IMGV_TOSTRING(GL_DEBUG_TYPE_MARKER); break;
                case GL_DEBUG_TYPE_PUSH_GROUP:              type_str = IMGV_TOSTRING(GL_DEBUG_TYPE_PUSH_GROUP); break;
                case GL_DEBUG_TYPE_POP_GROUP:               type_str = IMGV_TOSTRING(GL_DEBUG_TYPE_POP_GROUP); break;
                case GL_DEBUG_TYPE_OTHER:                   type_str = IMGV_TOSTRING(GL_DEBUG_TYPE_OTHER); break;
                default:                                    type_str = "GL_DEBUG_TYPE_UNKNOWN"; break;
            }
            
            switch(severity)
            {
                case GL_DEBUG_SEVERITY_HIGH:         severity_str = IMGV_TOSTRING(GL_DEBUG_SEVERITY_HIGH); break;
                case GL_DEBUG_SEVERITY_MEDIUM:       severity_str = IMGV_TOSTRING(GL_DEBUG_SEVERITY_MEDIUM); break;
                case GL_DEBUG_SEVERITY_LOW:          severity_str = IMGV_TOSTRING(GL_DEBUG_SEVERITY_LOW); break;
                case GL_DEBUG_SEVERITY_NOTIFICATION: severity_str = IMGV_TOSTRING(GL_DEBUG_SEVERITY_NOTIFICATION); break;
                default:                             severity_str = "GL_DEBUG_SEVERITY_UNKNOWN"; break;
            }

            switch(source)
            {
                case GL_DEBUG_SOURCE_API:             source_str = IMGV_TOSTRING(GL_DEBUG_SOURCE_API); break;
                case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   source_str = IMGV_TOSTRING(GL_DEBUG_SOURCE_WINDOW_SYSTEM); break;
                case GL_DEBUG_SOURCE_SHADER_COMPILER: source_str = IMGV_TOSTRING(GL_DEBUG_SOURCE_SHADER_COMPILER); break;
                case GL_DEBUG_SOURCE_THIRD_PARTY:     source_str = IMGV_TOSTRING(GL_DEBUG_SOURCE_THIRD_PARTY); break;
                case GL_DEBUG_SOURCE_APPLICATION:     source_str = IMGV_TOSTRING(GL_DEBUG_SOURCE_APPLICATION); break;
                case GL_DEBUG_SOURCE_OTHER:           source_str = IMGV_TOSTRING(GL_DEBUG_SOURCE_OTHER); break;
                default:                              source_str = "GL_DEBUG_SOURCE_UNKNOWN"; break;
            }

            IMGV_CORE_CRITICAL("<---------< GL DEBUG MESSAGE >--------->");
            IMGV_CORE_CRITICAL(" -> ID:         {0}", id);
            IMGV_CORE_CRITICAL(" -> SOURCE:     {0}", source_str);
            IMGV_CORE_CRITICAL(" -> TYPE:       {0}", type_str);
            IMGV_CORE_CRITICAL(" -> SEVERITY:   {0}", severity_str);
            IMGV_CORE_CRITICAL(" -> MESSAGE:    {0}", message);
            IMGV_CORE_CRITICAL("<------------------------------------------>");

            if(severity == GL_DEBUG_SEVERITY_HIGH)
                IMGV_DEBUGBREAK();
        }

    #endif
}