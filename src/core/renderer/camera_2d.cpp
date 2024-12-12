#include "camera_2d.hpp"

namespace IMGV::Core
{
    Camera2D::Camera2D(Float left, Float right, Float bottom, Float top)
    {
        m_OrthographicSize      = (right - left) / 2.0f;
        m_OrthographicNear      = -1.0f;
        m_OrthographicFar       =  1.0f;
        RefreshViewProjectionMatrix();
    }

    Camera2D::Camera2D(Float size, Float nearClip, Float farClip)
    {
        m_OrthographicSize      = size;
        m_OrthographicNear      = nearClip;
        m_OrthographicFar       = farClip;
        RefreshViewProjectionMatrix();
    }

    void Camera2D::SetAspectRatio(Float ratio)
    {
        m_AspectRatio = ratio;
        RefreshViewProjectionMatrix();
    }

    void Camera2D::SetRotation(Float rotation)
    {
        m_Rotation = rotation;
        RefreshViewProjectionMatrix();
    }

    void Camera2D::SetPosition(const Vec3& position)
    {
        m_Position = position;
        RefreshViewProjectionMatrix();
    }

    void Camera2D::SetProjection(Float size, Float nearClip, Float farClip)
    {
        m_OrthographicSize      = size;
        m_OrthographicNear      = nearClip;
        m_OrthographicFar       = farClip;
        RefreshViewProjectionMatrix();
    }

    void Camera2D::SetProjection(Float left, Float right, Float bottom, Float top)
    {
        m_OrthographicSize      = (right - left) / 2.0f;
        m_OrthographicNear      = -1.0f;
        m_OrthographicFar       =  1.0f;
        RefreshViewProjectionMatrix();
    }

    void Camera2D::RefreshViewProjectionMatrix()
    {
        Mat4 transform = translate(Mat4(1.0f), m_Position) *  rotate(Mat4(1.0f), radians(m_Rotation), {0.0f, 0.0f, 1.0f});
        m_View = inverse(transform);

        float left      = -m_OrthographicSize * m_AspectRatio * 0.5f;
        float right     =  m_OrthographicSize * m_AspectRatio * 0.5f;
        float top       =  m_OrthographicSize * 0.5f;
        float bottom    = -m_OrthographicSize * 0.5f;
        m_Projection    =  ortho(left, right, bottom, top, m_OrthographicNear, m_OrthographicFar);

        m_ViewProjection = m_View * m_Projection;
    }
}