#pragma once

#include "camera.hpp"

namespace IMGV::Core
{
    class IMGV_API Camera2D : public Camera
    {
        public:
            Camera2D(Float size = 10.0f, Float nearClip = -1.0f, Float farClip = 1.0f);
            virtual ~Camera2D() = default;

            CameraType GetCameraType() const { return CameraType::Camera_2D; }

            void SetAspectRatio(Float ratio);
            void SetRotation(Float rotation);
            void SetPosition(const Vec3& position);
            void SetProjection(Float size = 10.0f, Float nearClip = -1.0f, Float farClip = 1.0f);

            const Mat4& GetView() const { return m_View; }
            const Mat4& GetProjection() const { return m_Projection; }
            const Mat4& GetViewProjection() const { return m_ViewProjection; }

            Float GetSize() const { return m_OrthographicSize; }
            Float GetNearClip() const { return m_OrthographicNear; }
            Float GetFarClip() const { return m_OrthographicFar; }

        private:
            void RefreshViewProjectionMatrix();

        private:
            Float m_AspectRatio{1.0f};
            Float m_OrthographicSize{10.0f};
            Float m_OrthographicNear{-1000.0f};
            Float m_OrthographicFar{1000.0f};
            Mat4 m_ViewProjection{1.0f};
    };
}