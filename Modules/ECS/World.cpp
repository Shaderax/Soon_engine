#include "World.hpp"
#include "Entity.hpp"
#include "Id.hpp"
#include "Config.hpp"

#include <iostream>
#include <algorithm>

namespace Soon
{
	namespace ECS
	{
//		World::World( void ) : World(Soon::ECS::DEFAULT_POOL_SIZE)
//		{
//			std::cout << __PRETTY_FUNCTION__ << std::endl;
//		}

		World::World( std::uint32_t poolSize ) :
			_entityPool( poolSize ),
			_entityAttributes( poolSize )
		{
			std::cout << __PRETTY_FUNCTION__ << std::endl;
		}

		World::~World( void )
		{

		}

		Entity World::CreateEntity( void )
		{
			CheckResizePool(1);

			_entityCache._alive.emplace_back(_entityPool.CreateEntity().GetId());

			return (_entityCache._alive.back());
		}

		Id World::CreateEntityId( void )
		{
			CheckResizePool(1);

			_entityCache._alive.emplace_back(_entityPool.CreateEntity().GetId());

			return (_entityCache._alive.back().GetId());
		}

		std::vector<Entity> World::CreateEntities(std::size_t amount)
		{
			std::vector<Entity> tmp;
			tmp.reserve(amount);

			CheckResizePool(amount);

			for( std::size_t i = 0; i < amount; ++i )
			{
				Entity e(_entityPool.CreateEntity().GetId());
				_entityCache._alive.push_back(e);
				tmp.push_back(e);
			}

			return tmp;
		}

		std::size_t World::GetAliveEntityCount( void ) const
		{
			std::cout << "dthpjietogim" << std::endl;
			if (_entityCache.ok == 50)
				std::cout << "Oui" << std::endl;
			else
				std::cout << "Non" << std::endl;
			std::cout << "dthpjietogim" << std::endl;
			return (_entityCache._alive.size());
		}

		void World::Resize( std::size_t amount )
		{
			_entityPool.Resize(amount);
			_entityAttributes.Resize(amount);
		}

		std::size_t World::GetEntityCount( void ) const
		{
			return (_entityPool.GetEntityCount());
		}

		void World::CheckResizePool( std::size_t amount )
		{
			std::cout << "Pass" << std::endl;
			std::size_t newSize = GetAliveEntityCount() + amount;
			std::cout << "dthpjietogim" << std::endl;

			if (newSize > GetEntityCount())
				Resize(newSize);
		}

		bool World::IsValid( Entity entity ) const
		{
			return (_entityPool.IsValid(entity.GetId()));
		}

		bool World::IsActivated( Entity entity )
		{
			if (IsValid(entity))
				return (_entityAttributes._attributes[entity.GetId()]._activated);
			else
				return (false);
		}

		void World::AddSystem( System* newSystem, TypeId SystemTypeId )
		{
			_systemPool[SystemTypeId] = newSystem;
		}

		void World::RemoveAllSystems( void )
		{
			for(auto& system : _systemPool)
				delete system.second;
			_systemPool.clear();
		}

		void World::RemoveSystem( TypeId SystemTypeId )
		{
			delete _systemPool[SystemTypeId];

			_systemPool.erase(SystemTypeId);
		}

		void	World::DesactivateEntity( Entity entity )
		{
			ECS_ASSERT(IsValid(entity), "Invalid id tried to be desactivated");

			_entityCache._desactivated.push_back(entity);
		}

		void	World::ActivateEntity( Entity entity )
		{
			ECS_ASSERT(IsValid(entity), "Invalid id tried to be activated");

			_entityCache._activated.push_back(entity);
		}

		void	World::KillEntity( Entity entity )
		{
			ECS_ASSERT(IsValid(entity), "Invalid id tried to kill entity");

			DesactivateEntity(entity);

			_entityCache._killed.push_back(entity);
		}

		void World::KillEntities(std::vector<Entity>& entities)
		{
			for(auto& i : entities)
			{
				KillEntity(i);
			}
		}

		void World::Update( void )
		{
			for(Entity& entity : _entityCache._activated)
			{
				EntityAttributes::Attribute& attribute = _entityAttributes._attributes[entity.GetId()]; 
				attribute._activated = true;

				// loop through all the systems within the world
				for(auto& system : _systemPool)
				{
					TypeId systemIndex = system.first;

					// if the entity passes the filter the system has and is not already part of the system
					if(system.second->PassFilters(_entityAttributes._componentPool.GetComponentTypeList( entity )))
					{
						if (attribute._systems.size() <= systemIndex || !attribute._systems[systemIndex])
						{
							system.second->AddEntity(entity); // add it to the system

							if (attribute._systems.size() <= systemIndex)
								attribute._systems.resize(systemIndex + 1);

							attribute._systems[systemIndex] = true;
						}
					}
					// otherwise if the entity is within the system 
					// and is not relevant to the system anymore...
					// note: the entity has already failed the filter
					else if(attribute._systems.size() > systemIndex && attribute._systems[systemIndex])
					{
						// duplicate code (1)
						system.second->RemoveEntity(entity); 
						attribute._systems[systemIndex] = false;
					}
				}
			}

			// go through all the deactivated entities from last call to refresh
			for(Entity& entity : _entityCache._desactivated)
			{
				EntityAttributes::Attribute& attribute = _entityAttributes._attributes[entity.GetId()]; 
				attribute._activated = false;

				// loop through all the systems within the world
				for(auto& system : _systemPool)
				{
					TypeId systemIndex = system.first;
					if(attribute._systems.size() <= systemIndex)
						continue;

					if(attribute._systems[systemIndex])
					{
						// duplicate code ...(1)
						system.second->RemoveEntity(entity); 
						attribute._systems[systemIndex] = false;
					}
				}
			}

			// go through all the killed entities from last call to refresh
			for(Entity& entity : _entityCache._killed)
			{
				// remove the entity from the alive array
				_entityCache._alive.erase(std::remove(_entityCache._alive.begin(), _entityCache._alive.end(), entity), _entityCache._alive.end()); 

				// destroy all the components it has
				_entityAttributes._componentPool.RemoveAllEntityComponents(entity.GetId());

				// remove it from the id pool
				_entityPool.Remove(entity.GetId());
			}
			_entityCache.ClearTemp();
		}

		void World::Clear( void )
		{
			RemoveAllSystems();

			_entityPool.Clear();
			_entityCache.Clear();
			_entityAttributes.Clear();
		}

		bool World::HasSystem( TypeId idSys ) const
		{
			return (_systemPool.find( idSys ) != _systemPool.end());
		}
	}
}
