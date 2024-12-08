#pragma once

#include <filesystem>
#include <fstream>
#include <unordered_map>

#include "typedef.hpp"

namespace IMGV::Core
{
    class IMGV_API Shader
    {
        public:
            Shader() = default;
            virtual ~Shader() = default;

            virtual void Bind() const = IMGV_NULL;
            virtual void Unbind() const = IMGV_NULL;

            virtual ShaderProgramID GetID() const = IMGV_NULL;
            virtual const String& GetName() const = IMGV_NULL;
            virtual UniformLocation GetUniformLocation(const String& uniformName) = IMGV_NULL;

            virtual void SetUnifrom(const String& uniformName, Float value) = IMGV_NULL;
            virtual void SetUniform(const String& uniformName, Int32 value) = IMGV_NULL;
            virtual void SetUniform(const String& uniformName, UInt32 value) = IMGV_NULL;
            virtual void SetUniform(const String& uniformName, const Vec2& value) = IMGV_NULL;
            virtual void SetUniform(const String& uniformName, const Vec3& value) = IMGV_NULL;
            virtual void SetUniform(const String& uniformName, const Vec4& value) = IMGV_NULL;
            virtual void SetUniform(const String& uniformName, const Mat2& value) = IMGV_NULL;
            virtual void SetUniform(const String& uniformName, const Mat3& value) = IMGV_NULL;
            virtual void SetUniform(const String& uniformName, const Mat4& value) = IMGV_NULL;
    };

    IMGV_NODISCARD IMGV_API Ref<Shader> CreateShader(const String& name, const std::filesystem::path& vtxShader, const std::filesystem::path& fragShader);
}