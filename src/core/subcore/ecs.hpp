#pragma once

#include <entt/entt.hpp>

#include "asserts.hpp"
#include "components.hpp"
#include "typedef.hpp"

namespace IMGV::Core
{
    class IMGV_API Entity
    {
        public:
            Entity(entt::registry* registryPtr, entt::entity handle) : m_Registry(registryPtr), m_Handle(handle) {};
            ~Entity() = default;

            template<typename T>
            inline Boolean HasComponent() const
            {
                return m_Registry->any_of<T>(m_Handle);
            }

            template<typename T, typename... TArgs>
            inline T& InsertComponent(TArgs&&... args)
            {
                IMGV_ASSERT(!HasComponent<T>(), "Entity already has component");
                return m_Registry->emplace<T>(m_Handle, std::forward<TArgs>(args)...);
            }

            template<typename T>
            inline T& GetComponent() const
            {
                IMGV_ASSERT(HasComponent<T>(), "Entity does not have component");
                return m_Registry->get<T>(m_Handle);
            }

            template<typename T>
            inline void RemoveComponent()
            {
                IMGV_ASSERT(HasComponent<T>(), "Entity does not have component");
                m_Registry->remove<T>(m_Handle);
            }


            inline entt::entity GetHandle() const { return m_Handle; }
            operator Boolean() const { return m_Handle != entt::null; }
            operator UInt32() const { return (UInt32)m_Handle; }
            operator entt::entity() const { return m_Handle; }

            Boolean operator==(const Entity& other) const 
            {
                return m_Handle == other.m_Handle;
            }

            Boolean operator!=(const Entity& other) const 
            {
                return !(*this == other);
            }

        private:
            entt::entity m_Handle{entt::null};
            entt::registry* m_Registry{IMGV_NULLPTR};
    };

    IMGV_NODISCARD IMGV_API Entity* CreateEntity(const String& name);
    void IMGV_API DestroyEntity(Entity* entity);
}