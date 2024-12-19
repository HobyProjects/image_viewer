#pragma once

#include "texture.hpp"

namespace IMGV::Core
{
    struct IMGV_API TagComponent
    {
        std::string Tag{std::string()};
        Boolean Active{IMGV_FALSE};

        TagComponent() = default;
        TagComponent(const std::string& tag) : Tag(tag) {}
        ~TagComponent() = default;
    };
    
    struct IMGV_API TransformComponent
    {
        Vec3 Tanslation{0.0f, 0.0f, 0.0f};
        Vec3 Rotation{0.0f, 0.0f, 0.0f};
        Vec3 Scale{1.0f, 1.0f, 1.0f};

        TransformComponent() = default;
        ~TransformComponent() = default;

        Mat4 GetTransform() const
        {
            Mat4 T{translate(Mat4(1.0f), Tanslation)};

            Mat4 R{rotate(Mat4(1.0f), Rotation.x, Vec3(1, 0, 0)) *
                   rotate(Mat4(1.0f), Rotation.y, Vec3(0, 1, 0)) *
                   rotate(Mat4(1.0f), Rotation.z, Vec3(0, 0, 1))};

            Mat4 S{scale(Mat4(1.0f), Scale)};

            Mat4 TRS{ T * R * S };
            return TRS;
        }
    };

    struct IMGV_API SpriteComponent
    {
        Vec4 Color{1.0f, 1.0f, 1.0f, 1.0f};
        Reference<Texture2D> Texture{IMGV_NULLPTR};
        Boolean HasTextures{IMGV_FALSE};

        SpriteComponent() = default;
        SpriteComponent(Vec4 color) : Color(color), HasTextures(IMGV_FALSE) {}
        SpriteComponent(Reference<Texture2D> texture) : Texture(texture), HasTextures(IMGV_TRUE) {}
        ~SpriteComponent() = default;
    };
}