#include "ecs.hpp"

namespace IMGV::Core
{
    static entt::registry s_Registry{};

    Entity* CreateEntity(const String& name)
    {
        Entity* entity = new Entity(&s_Registry, s_Registry.create());
        name.empty() ? entity->InsertComponent<TagComponent>("unnamed") : entity->InsertComponent<TagComponent>(name);
        entity->InsertComponent<TransformComponent>();
        return entity;
    }

    void DestroyEntity(Entity* entity)
    {
        if(entity == IMGV_NULLPTR)
        {
            IMGV_CORE_ERROR("Entity is null");
            return;
        }
        
        s_Registry.destroy(entity->GetHandle());
    }
}