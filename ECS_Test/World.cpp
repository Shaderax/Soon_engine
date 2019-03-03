#include <iostream>
#include "World.hpp"

namespace Soon
{
	namespace ECS
	{
		World::World( void ) : World(Soon:::ECS::DEFAULT_POOL_SIZE)
		{
			
		}

		World::World( std::size_t poolSize)
		{
			_entityPool(poolSize);
			_entityAttributes(poolSize);
		}

		World::~World( void )
		{

		}

		Entity World::CreateEntity( void )
		{
			CheckResizePool(1);

			_entityCache.alive.push_back(_entityPool.CreateEntity());
			return (_entityCache.alive.back());
		}

		//		EntityPool World::GetEntityPool( void )
		//		{
		//			return (_entityPool);
		//		}

		std::size_t World::GetAliveEntityCount( void ) const
		{
			return (_entityCache.alive.size());
		}

		void World::Resize( std::size_t amount )
		{
			_entityPool.Resize();
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

		void World::Update( void )
		{
			for(Entity::Id& entity : m_entityCache._activated)
			{
				EntityAttributes::Attribute& attribute = _entityAttributes._attributes[id.GetId()]; 
				attribute.activated = true;

				// loop through all the systems within the world
				for(auto& i : m_systems)
				{
					auto systemIndex = i.first;

					// if the entity passes the filter the system has and is not already part of the system
					if(i.second->getFilter().doesPassFilter(m_entityAttributes.componentStorage.getComponentTypeList(entity)))
					{
						if(attribute.systems.size() <= systemIndex || !attribute.systems[systemIndex])
						{
							i.second->add(entity); // add it to the system

							util::EnsureCapacity(attribute.systems, systemIndex); 
							attribute.systems[systemIndex] = true;
						}
					}
					// otherwise if the entity is within the system 
					// and is not relevant to the system anymore...
					// note: the entity has already failed the filter
					else if(attribute.systems.size() > systemIndex && attribute.systems[systemIndex])
					{
						// duplicate code (1)
						i.second->remove(entity); 
						attribute.systems[systemIndex] = false;
					}
				}
			}


			// go through all the deactivated entities from last call to refresh
			for(auto& entity : m_entityCache.deactivated)
			{
				EntityAttributes::Attribute& attribute = _entityAttributes._attributes[id.GetId()]; 
				attribute.activated = false;

				// loop through all the systems within the world
				for(auto& i : m_systems)
				{
					auto systemIndex = i.first;
					if(attribute.systems.size() <= systemIndex) continue;

					if(attribute.systems[systemIndex])
					{
						// duplicate code ...(1)
						i.second->remove(entity); 
						attribute.systems[systemIndex] = false;
					}
				}
			}

			// go through all the killed entities from last call to refresh
			for(Entity::Id& entity : m_entityCache.killed)
			{
				// remove the entity from the alive array
				_entityCache.alive.erase(std::remove(_entityCache.alive.begin(), _entityCache.alive.end(), entity), _entityCache.alive.end()); 

				// destroy all the components it has
				m_entityAttributes.componentStorage.removeAllComponents(entity);

				// remove it from the id pool
				_entityPool.remove(entity.GetId());
			}

			bool World::IsValid( Entity::Id id )
			{
				return (_entityPool.IsValid(id));
			}

			bool World::IsActivated( Entity::Id id )
			{
				if (IsValid(id))
					return (_entityAttributes._attributes[id.GetId()].activated);
				else
					return (false);
			}

			void	World::DesactivateEntity( Entity::Id id )
			{
				if (IsValid(id))
					_entityCache.deactivated.push_back(id);
			}
			
			void	World::ActivateEntity( Entity::Id id )
			{
				if (IsValid(id))
					_entityCache.activated.push_back(id);
			}

			void	World::KillEntity( Entity::Id id )
			{
				if (IsValid(id))
				{
					DesactivateEntity(id);
					_entityCache.killed.push_back(id);
				}
			}
		}
	}
