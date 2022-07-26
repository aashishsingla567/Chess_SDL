// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "ECS.hpp"

// generate type id for component
int typeIdGen()
{
	static int id = 0;
	return id++;
}

Entity::~Entity()
{
	// kill();
	// Make me forget my components
	myComponents_.clear();
};
// template functions are defined in the header itself (other wise linking error will occur)

void Entity::kill()
{
	isAlive_ = false;
	// remove components form the components map
	for (const auto &pair : myComponents_)
	{
		componentsMap::removeComponent(pair.first, pair.second->getComponentId());
	}
}
void Entity::revive()
{
	if (isAlive_)
		return;
	// add components to the components map
	for (const auto &pair : myComponents_)
	{
		componentsMap::addCompoenent(
			pair.first,					   // compTypeId
			pair.second->getComponentId(), // componentId
			pair.second					   // Component
		);
	}
}

// components 
int Component::componentIdGen_ = 0;
 //Component::Component () = default;
 Component::~Component() = default;

// template fucntions are in the header ( as they cannot be exposed to linker )

// components map
std::unordered_map<
		int, std::vector < 
			std::shared_ptr < Component > 
		> 
	>
	componentsMap::components_;

using vectorIt = size_t;
std::unordered_map<int, vectorIt> componentsMap::componentsMapIter_;

void componentsMap::addCompoenent(int compTypeId, int componentId, std::shared_ptr<Component> component)
{
	components_[compTypeId].push_back(component);
	componentsMapIter_[componentId] = components_[compTypeId].size() - 1;
}

void componentsMap::removeComponent(int compTypeId, int componentId)
{
	auto it_it = componentsMapIter_.find(componentId);
	if (it_it == componentsMapIter_.end())
		return;
	auto vec_it = components_.find(compTypeId);
	if (vec_it == components_.end())
		return;

	auto &vec = vec_it->second;
	auto &it = it_it->second;

	vec.erase(vec.begin() + it);
	componentsMapIter_.erase(it_it);

	std::cout << "Component Removed "
			  << "ComponentId :: " << componentId
			  << " TypeId :: " << compTypeId
			  << std::endl;
}

void componentsMap::renderComponets()
{
	for (const auto &pair : components_)
	{
		for (const auto &component : pair.second)
		{
			component->render();
		}
	}
}

void componentsMap::updateComponets()
{
	for (const auto &pair : components_)
	{
		for (const auto &component : pair.second)
		{
			component->update();
		}
	}
}