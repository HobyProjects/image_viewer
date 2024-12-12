#pragma once

#include "ecs.hpp"
#include "texture.hpp"

namespace IMGV::Core
{
    struct IMGV_API TransformComponent
    {
        Vec3 Tanslation{0.0f, 0.0f, 0.0f};
        Vec3 Rotation{0.0f, 0.0f, 0.0f};
        Vec3 Scale{1.0f, 1.0f, 1.0f};

        TransformComponent() = default;
        ~TransformComponent() = default;

        Mat4 GetTransform() const
        {
            Mat4 T{glm::translate(Mat4(1.0f), Tanslation)};

            Mat4 R{glm::rotate(Mat4(1.0f), Rotation.x, Vec3(1, 0, 0)) *
                   glm::rotate(Mat4(1.0f), Rotation.y, Vec3(0, 1, 0)) *
                   glm::rotate(Mat4(1.0f), Rotation.z, Vec3(0, 0, 1))};

            Mat4 S{glm::scale(Mat4(1.0f), Scale)};

            Mat4 TRS{ T * R * S };
            return TRS;
        }
    };

    struct IMGV_API SpriteComponent
    {
        Vec4 Color{1.0f, 1.0f, 1.0f, 1.0f};
        Ref<Texture2D> Texture{IMGV_NULLPTR};

        SpriteComponent() = default;
        SpriteComponent(Vec4 color) : Color(color) {}
        SpriteComponent(Ref<Texture2D> texture) : Texture(texture) {}
        ~SpriteComponent() = default;
    };
}