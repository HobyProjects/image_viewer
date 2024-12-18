#pragma once

#include <entt/entt.hpp>
#include "core.hpp"

namespace IMGV::App
{
    class Entity;
    class ScenePropertyPanels;

    class Scene
    {
        public:
            Scene() = default;
            ~Scene() = default;

            void OnUpdate(IMGV::Core::Timer deltaTime);
            void OnWindowResize(UInt32 width, UInt32 height);

            Entity CreateEntity(const String& name);
            void DestroyEntity(Entity entity);

            Entity GetPrimaryCamera();

        private:
            entt::registry m_Registry;
            UInt32 m_ViewportWidth{IMGV_NULL};
            UInt32 m_ViewportHeight{IMGV_NULL};

            friend class Entity;
            friend class ScenePropertyPanels;
    };
}
