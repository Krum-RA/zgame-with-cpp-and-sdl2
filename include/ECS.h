#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

/**
 * @defgroup ECS ECS Core
 * @brief Contains the fundamental definitions for the Entity-Component System (ECS).
 */

class Component;
class Entity;
class Manager;

using Group = std::size_t;
using ComponentID = std::size_t;

inline ComponentID getNewComponentTypeID()
{
    static ComponentID lastID = 0u;
    return lastID++;

}

template<typename T> inline ComponentID getNewComponentTypeID() noexcept
{
    static ComponentID typeID = getNewComponentTypeID();
    return typeID;
}

constexpr std::size_t maxComponents = 32;
constexpr std::size_t maxGroups = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using GroupBitset = std::bitset<maxGroups>;

using ComponentArray = std::array<Component*, maxComponents>;

/**
 * @class Component
 * @ingroup ECS
 * @brief Represents a component that can be attached to an entity.
 */

class Component
{
public:
   
    Entity* entity;

    virtual void init() {}
    virtual void update() {}
    virtual void draw() {}

    virtual ~Component() {}
};

/**
 * @class Entity
 * @ingroup ECS
 * @brief Represents an entity in the ECS system.
 */
class Entity
{
private:
    Manager& manager;

    bool active = true;
    std::vector<std::unique_ptr<Component>> components;
    ComponentArray componentArray;
    ComponentBitSet componentBitSet;
    GroupBitset groupBitSet;

public:

    Entity(Manager& mManager) : manager(mManager) {}
    /**
    * @brief Updates all active entities in the ECS.
    */
    void update()
    {
        for (auto& c : components)
            c->update();
    }
   
    void draw() 
    {
        for (auto& c : components)
            c->draw();
    }
    bool isActive() const { return active; }

    void destroy() { active = false; }

    bool hasGroup(Group mGroup)
    {
        return groupBitSet[mGroup];
    }

    void addGroup(Group mGroup);
    void delGroup(Group mGroup)
    {
        groupBitSet[mGroup] = false;
    }

    template<typename T>
    bool hasComponent() const
    {
        return componentBitSet[getNewComponentTypeID<T>()];
    }

    template<typename T, typename... TArgs>
    T& addComponent(TArgs&&... mArgs)
    {
        T* c(new T(std::forward<TArgs>(mArgs)...));
        c->entity = this;
        std::unique_ptr<Component> uPtr{ c };
        components.emplace_back(std::move(uPtr));

        componentArray[getNewComponentTypeID<T>()] = c;
        componentBitSet[getNewComponentTypeID<T>()] = true;

        c->init();
        return *c;
    }

    template<typename T>
    T& getComponent() const
    {
        auto ptr = componentArray[getNewComponentTypeID<T>()];
        return *static_cast<T*>(ptr);
    }
};
/**
 * @class Manager
 * @ingroup ECS
 * @brief Manages entities and components in the ECS system.
 */
class Manager
{
private:
    std::vector<std::unique_ptr<Entity>> entities;
    std::array<std::vector<Entity*>, maxGroups> groupEntities;
public:
    void update()
    {
        for (auto& e : entities)
            e->update();
    }
    /**
   * @brief Draws all active entities in the ECS.
   */

    void draw()
    {
        for (auto& e : entities)
            e->draw();
    }
    /**
     * @brief Refreshes the ECS by removing inactive entities and entities not in groups.
     */
    void refresh()
    {
        for (auto i(0u); i < maxGroups; i++)
        {
            auto& v(groupEntities[i]);
            v.erase(
                std::remove_if(std::begin(v), std::end(v), 
                    [i](Entity* mEntity)
                    {
                        return !mEntity->isActive() || !mEntity->hasGroup(i);
                    }),
                std::end(v));
        }

        entities.erase(
            std::remove_if(
                std::begin(entities),
                std::end(entities),
                [](const std::unique_ptr<Entity>& mEntity)
                {
                    return !mEntity->isActive();
                }
            ),
            std::end(entities)
        );

        
    }
    /**
     * @brief Adds an entity to a specific group.
     * @param mEntity The entity to add.
     * @param mGroup The group to add the entity to.
     */
    void AddToGroup(Entity* mEntity, Group mGroup)
    {
        groupEntities[mGroup].emplace_back(mEntity);
    }
    /**
     * @brief Retrieves entities belonging to a specific group.
     * @param mGroup The group for which to retrieve entities.
     * @return A vector of entities belonging to the group.
     */
    std::vector<Entity*>& getGroup(Group mGroup)
    {
        return groupEntities[mGroup];
    }
    /**
     * @brief Adds a new entity to the ECS.
     * @return Reference to the newly added entity.
     */
    Entity& addEntity()
    {
        Entity* e = new Entity(*this);
        std::unique_ptr<Entity> uPtr{ e };
        entities.emplace_back(std::move(uPtr));
        return *e;
    }
};
