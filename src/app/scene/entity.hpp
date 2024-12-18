#pragma once

#include "scene.hpp"

namespace IMGV::App
{
    class Entity
    {
        public:
            Entity() = default;
            Entity(entt::entity handle, Scene* scene);
            ~Entity() = default;

            template<typename T>
            Boolean HasComponent() const
            {
                return m_Scene->m_Registry.any_of<T>(m_Handle);
            }

            template<typename T, typename... Args>
            T& AddComponent(Args&&... args)
            {
                IMGV_ASSERT(!HasComponent<T>(), "Entity already has component!");
                return m_Scene->m_Registry.emplace<T>(m_Handle, std::forward<Args>(args)...);
            }

            template<typename T>
            T& GetComponent()
            {
                IMGV_ASSERT(HasComponent<T>(), "Entity does not have component!");
                return m_Scene->m_Registry.get<T>(m_Handle);
            }

            template<typename T>
            void RemoveComponent()
            {
                IMGV_ASSERT(HasComponent<T>(), "Entity does not have component!");
                m_Scene->m_Registry.remove<T>(m_Handle);
            }

            operator Boolean() const { return m_Handle != entt::null; }
            operator UInt32() const { return static_cast<UInt32>(m_Handle); }
            operator entt::entity() const { return m_Handle; }

            Boolean operator==(const Entity& other) const
            {
                return m_Handle == other.m_Handle && m_Scene == other.m_Scene;
            }

            Boolean operator!=(const Entity& other) const
            {
                return !(*this == other);
            }

        private:
            entt::entity m_Handle{entt::null};
            Scene* m_Scene{IMGV_NULLPTR};
    };

    class ScriptableEntity 
    {
        public:
            ScriptableEntity() = default;
            virtual ~ScriptableEntity() = default;

            template<typename T>
            T& GetComponent() 
            {
                return m_Entity.GetComponent<T>();
            }

        protected:
            virtual void OnCreate() {} 
            virtual void OnUpdate(IMGV::Core::Timer deltaTime) {}
            virtual void OnDestroy() {}

        private:
            Entity m_Entity;
            friend class Scene;
    };
}