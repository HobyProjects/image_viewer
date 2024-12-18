#pragma once

#include "entity.hpp"

namespace IMGV::App
{
    struct TagComponent
    {
        String Tag{String()};
        Boolean Active{IMGV_FALSE};

        TagComponent() = default;
        TagComponent(const String& tag) : Tag(tag) {}
        ~TagComponent() = default;
    };

    struct TransformComponent
    {
        Vec3 Translation{0.0f, 0.0f, 0.0f};
        Vec3 Rotation{0.0f, 0.0f, 0.0f};
        Vec3 Scale{1.0f, 1.0f, 1.0f};

        TransformComponent() = default;
        ~TransformComponent() = default;

        Mat4 GetTransform() const
        {
            Mat4 T{translate(Mat4(1.0f), Translation)};

            Mat4 R{rotate(Mat4(1.0f), Rotation.x, Vec3(1, 0, 0)) *
                   rotate(Mat4(1.0f), Rotation.y, Vec3(0, 1, 0)) *
                   rotate(Mat4(1.0f), Rotation.z, Vec3(0, 0, 1))};

            Mat4 S{scale(Mat4(1.0f), Scale)};

            Mat4 TRS{T * R * S};
            return TRS;
        }
    };

    struct SpriteComponent
    {
        Ref<IMGV::Core::Texture2D> Texture{IMGV_NULLPTR};
        Vec4 Color{1.0f, 1.0f, 1.0f, 1.0f};

        SpriteComponent() = default;
        SpriteComponent(Vec4 color) : Color(color) {}
        SpriteComponent(Ref<IMGV::Core::Texture2D> texture) : Texture(texture) {}
        ~SpriteComponent() = default;
    };

    struct CameraComponent
    {
        IMGV::Core::Camera2D Camera;
        Boolean Primary{IMGV_FALSE};
        Boolean FixedAspectRatio{IMGV_FALSE};

        CameraComponent() = default;
        ~CameraComponent() = default;
    };

    struct NativeScriptComponent 
    {
        ScriptableEntity* Instance{nullptr};
        ScriptableEntity* (*InstantiateScript)() {nullptr};
        void(*DestroyScript)(NativeScriptComponent*) {nullptr};

        template<typename T>
        void Bind() {
            InstantiateScript = []() 
            {
                return static_cast<ScriptableEntity*>(new T());
            };

            DestroyScript = [](NativeScriptComponent* nsc) 
            {
                delete nsc->Instance;
                nsc->Instance = nullptr;
            };
        }

        NativeScriptComponent() = default;
        ~NativeScriptComponent() = default;
    };
}