#pragma once

#include <fstream>
#include <filesystem>
#include <string>
#include <memory>
#include <bitset>
#include <array>
#include <type_traits>
#include <vector>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>

using UInt64 = unsigned long long;
using Int64 = long long;
using Int32 = int;
using UInt32 = unsigned int;
using UInt16 = unsigned short;
using UInt8 = unsigned char;
using Int8 = char;
using Float = float;
using Double = double;
using String = std::string;
using CString = const char*;
using Boolean = bool;
using IMGV_Window = void*;  

template<typename T> 
using Reference = std::shared_ptr<T>;  

template<typename T> 
using WeakRef = std::weak_ptr<T>; 

template<typename T> 
using Scope = std::unique_ptr<T>;       

template<typename T, typename... Args> 
inline Reference<T> CreateRef(Args&&... args) 
{ 
    return std::make_shared<T>(std::forward<Args>(args)...); 
}

template<typename T, typename... Args> 
inline Scope<T>  CreateScope(Args&&... args) 
{ 
    return std::make_unique<T>(std::forward<Args>(args)...); 
}

#define IMGV_TRUE  1
#define IMGV_FALSE 0
#define IMGV_NULL 0
#define IMGV_SUCCESS 0
#define IMGV_FAILURE 1
#define IMGV_NULLPTR  nullptr
#define IMGV_NODISCARD [[nodiscard]]

//==============================================================================

using namespace glm;

using Vec2 = glm::vec2;
using Vec3 = glm::vec3;
using Vec4 = glm::vec4;
using Mat2 = glm::mat2;
using Mat3 = glm::mat3;
using Mat4 = glm::mat4;
using Quat = glm::quat;
using DVec2 = glm::dvec2;
using DVec3 = glm::dvec3;
using DVec4 = glm::dvec4;
using DMat2 = glm::dmat2;
using DMat3 = glm::dmat3;
using DMat4 = glm::dmat4;
using DQuat = glm::dquat;

//==============================================================================

using VertexBufferID = unsigned int;
using IndexBufferID = unsigned int;
using TextureID = unsigned int;
using ShaderID = unsigned int;
using ShaderProgramID = unsigned int;
using UniformLocation = unsigned int;
using VertexBufferData = float*;
using IndexBufferData = unsigned int*;
using VertexArrayID = unsigned int;
using TextureID = unsigned int;
using TextureData = unsigned char*;
using FrameBufferID = unsigned int;
using FrameBufferAttachmentID = unsigned int;