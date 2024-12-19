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

#include "base.hpp"
#include "asserts.hpp"

typedef unsigned long long          UInt64;
typedef long long                   Int64;
typedef int                         Int32;         
typedef unsigned int                UInt32;        
typedef unsigned short              UInt16;        
typedef unsigned char               UInt8;         
typedef char                        Int8;         
typedef float                       Float;         
typedef double                      Double;       
typedef std::string                 String;        
typedef const char*                 CString;       
typedef bool                        Boolean;
typedef void*                       IMGV_Window;    

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

#define IMGV_TRUE     1
#define IMGV_FALSE    0
#define IMGV_NULL     0
#define IMGV_NULLPTR  nullptr
#define IMGV_NODISCARD [[nodiscard]]

//==============================================================================

using namespace glm;

typedef glm::vec2   Vec2;
typedef glm::vec3   Vec3;
typedef glm::vec4   Vec4;
typedef glm::mat2   Mat2;
typedef glm::mat3   Mat3;
typedef glm::mat4   Mat4;
typedef glm::quat   Quat;
typedef glm::dvec2  DVec2;
typedef glm::dvec3  DVec3;
typedef glm::dvec4  DVec4;
typedef glm::dmat2  DMat2;
typedef glm::dmat3  DMat3;
typedef glm::dmat4  DMat4;
typedef glm::dquat  DQuat;

//==============================================================================

typedef unsigned int    VertexBufferID;
typedef unsigned int    IndexBufferID;
typedef unsigned int    TextureID;
typedef unsigned int    ShaderID;
typedef unsigned int    ShaderProgramID;
typedef unsigned int    UniformLocation;
typedef float*          VertexBufferData;
typedef unsigned int*   IndexBufferData;
typedef unsigned int    VertexArrayID;
typedef unsigned int    TextureID;
typedef unsigned char*  TextureData;
typedef unsigned int    FrameBufferID;
typedef unsigned int    FrameBufferAttachmentID;