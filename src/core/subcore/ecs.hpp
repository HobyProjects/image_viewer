#pragma once

#include "typedef.hpp"

namespace IMGV::Core
{
    class Entity;
    class Component;

    using ComponentTypeID = UInt64;

    inline IMGV_API ComponentTypeID GetUniqueComponentTypeID()
    {
        static ComponentTypeID lastID = IMGV_NULL;
        return lastID++;
    }

    template<typename T>
    inline IMGV_API ComponentTypeID GetComponentTypeID()
    {
        static_assert(std::is_base_of<Component, T>::value, "Type is not based on component class");
        static const ComponentTypeID typeID = GetUniqueComponentTypeID();
        return typeID;
    }

    constexpr UInt32 MAX_ENTITIES      = 5000;
    constexpr UInt32 MAX_COMPONENTS    = 32;

    using ComponentBitset   = std::bitset<MAX_ENTITIES>;
    using ComponentList     = std::array<Component*, MAX_COMPONENTS>;

    class IMGV_API Entity
    {
        public:
            Entity() = default;
            ~Entity() = default;

            template<typename T, typename... TArgs>
            inline T& InsertComponent(TArgs&&... args)
            {
                T* component(new T(std::forward<TArgs>(args)...));
                component->entity = this;
                std::unique_ptr<Component> uptr{ component };
                m_components.emplace_back(std::move(uptr));
                if (component->Init())
                {
                    m_compoList[GetComponentTypeID<T>()] = component;
                    m_compoBitset[GetComponentTypeID<T>()] = true;
                    component->entity = this;
                    m_isAlive = true;
                    return *component;
                }

                return *static_cast<T*>(nullptr);
            }

            template<typename T>
            inline T& GetComponent() const
            {
                auto ptr(m_compoList[GetComponentTypeID<T>()]);
                return *static_cast<T*>(ptr);
            }

            template<typename T>
            inline Boolean HasComponent() const
            {
                return m_compoBitset[GetComponentTypeID<T>()];
            }

            inline Boolean IsAlive() const { return m_isAlive; }

        private:
            Boolean m_isAlive{ IMGV_FALSE };
            ComponentBitset m_compoBitset;
            ComponentList m_compoList;
            std::vector<std::unique_ptr<Component>> m_components;
    };

    class IMGV_API Component
    {
        public:
            Component() = default;
            virtual ~Component() = default;

            virtual Boolean Init() {}
            virtual void Update() {}
            virtual void Render() {}
            virtual void Refresh() {}

        public:
            Entity* entity{ IMGV_NULLPTR };
    };
}