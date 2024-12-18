#include "scene.hpp"
#include "component.hpp"

namespace IMGV::App
{
    void Scene::OnUpdate(Core::Timer deltaTime)
    {
        m_Registry.view<NativeScriptComponent>().each([=](auto entity, auto& nsc)
        {
            if(!nsc.Instance)
            {
                nsc.Instance = nsc.InstantiateScript();
                nsc.Instance->m_Entity = Entity{entity, this};
                nsc.Instance->OnCreate();
            }

            nsc.Instance->OnUpdate(deltaTime);
        });

        IMGV::Core::Camera2D* primaryCamera{IMGV_NULLPTR};
        Mat4 cameraTransform{Mat4(1.0f)};

        auto view = m_Registry.view<TransformComponent, CameraComponent>();
        view.each([&](auto entity, TransformComponent& transform, CameraComponent& camera)
        {
            if(camera.Primary)
            {
                primaryCamera = &camera.Camera;
                cameraTransform = transform.GetTransform();
                return;
            }
        });

        if(primaryCamera != IMGV_NULLPTR)
        {
            //BatchRenderer2D::Begin(*primaryCamera, cameraTransform);

            auto group = m_Registry.group<TransformComponent>(entt::get<SpriteComponent>);
            group.each([&](auto entity, TransformComponent& transform, SpriteComponent& sprite)
            {
                BatchRenderer2D::Quad(transform.GetTransform(), sprite.Color);
            });

            //BatchRenderer2D::End();
        }
    }

    void Scene::OnWindowResize(UInt32 width, UInt32 height)
    {
        m_ViewportWidth = width;
        m_ViewportHeight = height;

        auto view = m_Registry.view<CameraComponent>();
        view.each([&](auto entity, CameraComponent& camera)
        {
            if(!camera.FixedAspectRatio)
            {
                camera.Camera.SetViewportSize(width, height);
            }
        });
    }

    Entity Scene::CreateEntity(const String& name)
    {
        Entity entity{m_Registry.create(), this};
        entity.AddComponent<TransformComponent>();
        auto& tag = entity.AddComponent<TagComponent>(name);
        tag.Tag = name.empty() ? "unnamed" : name;
        return entity;
    }

    void Scene::DestroyEntity(Entity entity)
    {
        m_Registry.destroy(entity);
    }

    Entity Scene::GetPrimaryCamera()
    {
        auto view = m_Registry.view<CameraComponent>();
        for(auto entity : view)
        {
            const auto& camera = view.get<CameraComponent>(entity);
            if(camera.Primary)
            {
                return Entity{entity, this};
            }
        }

        return Entity{entt::null, nullptr};
    }

    Entity::Entity(entt::entity handle, Scene * scene) : m_Handle(handle), m_Scene(scene)
    {
    }
}