#include "asserts.hpp"
#include "gl_shader.hpp"

namespace IMGV::Core
{
    GL_Shader::GL_Shader(const String& name, const FilePath& vtxShader, const FilePath& fragShader)
    {
        std::unordered_map<GLenum, String> shaderSources
        {
            {GL_VERTEX_SHADER, ReadShaderFiles(vtxShader)},
            {GL_FRAGMENT_SHADER, ReadShaderFiles(fragShader)}
        };

        CompileShaders(shaderSources);
        m_Name = name;
    }

    GL_Shader::~GL_Shader()
    {
        glDeleteProgram(m_programID);
    }

    void GL_Shader::Bind() const
    {
        glUseProgram(m_programID);
    }

    void GL_Shader::Unbind() const
    {
        glUseProgram(0);
    }

    ShaderProgramID GL_Shader::GetID() const
    {
        return m_programID;
    }

    const String & GL_Shader::GetName() const
    {
        return m_Name;
    }

    UniformLocation GL_Shader::GetUniformLocation(const String& uniformName)
    {
        if(m_UniformLocations.find(uniformName) != m_UniformLocations.end())
            return m_UniformLocations[uniformName];

        UniformLocation location = glGetUniformLocation(m_programID, uniformName.c_str());
        if(location >= 0)
        {
            m_UniformLocations[uniformName] = location;
            return location;
        }

        IMGV_CORE_WARN("Uniform '{0}' not found in shader '{1}'", uniformName, m_Name);
        return -1;
    }

    void GL_Shader::SetUnifrom(const String& uniformName, Float value)
    {
        glUniform1f(GetUniformLocation(uniformName), value);
    }

    void GL_Shader::SetUniform(const String& uniformName, Int32 value)
    {
        glUniform1i(GetUniformLocation(uniformName), value);
    }

    void GL_Shader::SetUniform(const String& uniformName, UInt32 value)
    {
        glUniform1i(GetUniformLocation(uniformName), value);
    }

    void GL_Shader::SetUniform(const String& uniformName, const Vec2& value)
    {
        glUniform2fv(GetUniformLocation(uniformName), 1, glm::value_ptr(value));
    }

    void GL_Shader::SetUniform(const String& uniformName, const Vec3& value)
    {
        glUniform3fv(GetUniformLocation(uniformName), 1, glm::value_ptr(value));
    }

    void GL_Shader::SetUniform(const String& uniformName, const Vec4& value)
    {
        glUniform4fv(GetUniformLocation(uniformName), 1, glm::value_ptr(value));
    }

    void GL_Shader::SetUniform(const String& uniformName, const Mat2& value)
    {
        glUniformMatrix2fv(GetUniformLocation(uniformName), 1, GL_FALSE, glm::value_ptr(value));
    }

    void GL_Shader::SetUniform(const String& uniformName, const Mat3& value)
    {
        glUniformMatrix3fv(GetUniformLocation(uniformName), 1, GL_FALSE, glm::value_ptr(value));
    }

    void GL_Shader::SetUniform(const String& uniformName, const Mat4& value)
    {
        glUniformMatrix4fv(GetUniformLocation(uniformName), 1, GL_FALSE, glm::value_ptr(value));
    }

    void GL_Shader::CompileShaders(std::unordered_map<GLenum, String>& shaders)
    {
        ShaderProgramID programID = glCreateProgram();
        if(!programID)
        {
            IMGV_CORE_ERROR("Failed to create shader program");
            return;
        }

        for (auto& source : shaders) 
        {
            GLenum type = source.first;
            const String& src = source.second;
            UInt32 shader = glCreateShader(type);
            const char* src_cstr = src.c_str();
            glShaderSource(shader, 1, &src_cstr, nullptr);
            glCompileShader(shader);
            glAttachShader(programID, shader);
        }

        glLinkProgram(programID);
        glValidateProgram(programID);
        m_programID = programID;
    }

    String GL_Shader::ReadShaderFiles(const FilePath& filePath)
    {
        String result{};
        std::ifstream in_file(filePath, std::ios::in | std::ios::binary);
        if (in_file) 
        {
            in_file.seekg(0, std::ios::end);
            result.resize(in_file.tellg());
            in_file.seekg(0, std::ios::beg);
            in_file.read(&result[0], result.size());
            return result;
        }

        IMGV_ASSERT(IMGV_FALSE, "Failed to read shader file!");
        return String();
    }
}