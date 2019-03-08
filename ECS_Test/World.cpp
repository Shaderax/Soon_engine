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
		World::World( void ) : World(Soon::ECS::DEFAULT_POOL_SIZE)
		{

		}

		World::World( std::uint32_t poolSize ) :
			_entityPool( poolSize ),
			_entityAttributes( poolSize )
		{
		}

		World::~World( void )
		{

		}

		Entity World::CreateEntity( void )
		{
			CheckResizePool(1);

			_entityCache._alive.push_back(_entityPool.CreateEntity());
			Entity e(*this, _entityCache._alive.back().GetId());

			return (e);
		}

		std::size_t World::GetAliveEntityCount( void ) const
		{
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
			std::size_t newSize = GetAliveEntityCount() + amount;

			if (newSize > GetEntityCount())
				Resize(newSize);
		}
		
		bool World::IsValid( Id id )
		{
			return (_entityPool.IsValid(id));
		}

		bool World::IsActivated( Id id )
		{
			if (IsValid(id))
				return (_entityAttributes._attributes[id.GetId()]._activated);
			else
				return (false);
		}

		void	World::DesactivateEntity( Id id )
		{
			if (IsValid(id))
				_entityCache._desactivated.push_back(id);
		}

		void	World::ActivateEntity( Id id )
		{
			if (IsValid(id))
				_entityCache._activated.push_back(id);
		}

		void	World::KillEntity( Id id )
		{
			if (IsValid(id))
			{
				DesactivateEntity(id);
				_entityCache._killed.push_back(id);
			}
		}

		void World::Update( void )
		{
			for(Id& entityId : _entityCache._activated)
			{
				EntityAttributes::Attribute& attribute = _entityAttributes._attributes[entityId.GetId()]; 
				attribute._activated = true;

				// loop through all the systems within the world
				for(auto& system : _systemPool)
				{
					TypeId systemIndex = system.first;

					// if the entity passes the filter the system has and is not already part of the system
					if(system.second->PassFilters(_entityAttributes._componentPool.GetComponentTypeList( entityId )))
					{
						if(attribute._systems.size() <= systemIndex || !attribute._systems[systemIndex])
						{
							system.second->AddEntity(entityId); // add it to the system

							if (attribute._systems.size() < systemIndex)
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
						system.second->RemoveEntity(entityId); 
						attribute._systems[systemIndex] = false;
					}
				}
			}

			// go through all the deactivated entities from last call to refresh
			for(Id& entityId : _entityCache._desactivated)
			{
				EntityAttributes::Attribute& attribute = _entityAttributes._attributes[entityId.GetId()]; 
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
						system.second->RemoveEntity(entityId); 
						attribute._systems[systemIndex] = false;
					}
				}
			}

			// go through all the killed entities from last call to refresh
			for(Id& entityId : _entityCache._killed)
			{
				// remove the entity from the alive array
				_entityCache._alive.erase(std::remove(_entityCache._alive.begin(), _entityCache._alive.end(), entityId), _entityCache._alive.end()); 

				// destroy all the components it has
				_entityAttributes._componentPool.RemoveAllEntityComponents(entityId);

				// remove it from the id pool
				_entityPool.Remove(entityId.GetId());
			}
		}
	}
}
