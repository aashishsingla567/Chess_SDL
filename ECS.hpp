// entity component system

#pragma once
#include "Game.hpp"
// class Entity;
class Component;
class Event;
// generate type Id for new type of Component
int typeIdGen();
// type id getter

// get type id of Component
template <typename T>
int compTypeId()
{
	// defined here becuse linker does not recognise template fucntions 
	// that are not called in the same file
	static int id = typeIdGen();
	return id;
}

using CompType = int;
using CompId = int;

// type components map
class componentsMap
{
private:
	static std::unordered_map<CompType, std::vector<std::shared_ptr<Component>>> components_;
	using vectorIt = size_t;
	static std::unordered_map<CompId, vectorIt> componentsMapIter_;

public:
	static void addCompoenent(
		int compTypeId,
		int componentId,
		std::shared_ptr<Component> component
	);
	static void removeComponent(int compTypeId, int componentId);
	static void renderComponets();
	static void updateComponets();
};


class Entity {
protected:
	std::unordered_map<CompType, std::shared_ptr<Component>> myComponents_;
	bool isAlive_ = true;
public:
	Entity() = default;
	~Entity();
	
	template <typename T>
	T& addComponent(std::shared_ptr<T> component)
	{
		componentsMap::addCompoenent(
			compTypeId<T>(),
			component->getComponentId(),
			component
		);
		myComponents_[compTypeId<T>()] = component;
		return *component;
	}

	
	template <typename T>
	T& getComponent()
	{
		return *std::static_pointer_cast<T, Component>(myComponents_[compTypeId<T>()]);
	}

	template <typename T>
	void removeComponent()
	{
		// disown the component
		componentsMap::removeComponent(
			compTypeId<T>(),
			myComponents_[compTypeId<T>()]->getComponentId()
		);
		myComponents_.erase(compTypeId<T>());
	}

	void kill();

	void revive();

	bool isAlive() const
	{
		return isAlive_;
	}
};

class Component {
protected:
	std::shared_ptr<Entity> entity_;
	CompId componentId_;
	static int componentIdGen_;
public:

	// a component cannot be initialize without an entity
	template <typename compT>
	void init(std::shared_ptr<Entity> entity) {
		this->entity_ = (entity);
		this->componentId_ = (componentIdGen_++);
	}

	virtual ~Component()  = 0;
	virtual void render() = 0;
	virtual void update() = 0;

	inline int getComponentId() const
	{
		return componentId_;
	}

	virtual std::shared_ptr <Entity> getEntity() const
	{
		return entity_;
	}
};