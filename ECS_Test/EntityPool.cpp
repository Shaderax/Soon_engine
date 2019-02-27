#include "EntityPool.hpp"
#include <iostream>

namespace Soon
{
	namespace ECS
	{
		Entity EntityPool::CreateEntity( void )
		{
			Entity::Id id;
			if (!_freeId.empty())
			{
				id._id = _freeId.back();
				_idKilled[id.GetId()] = false;
				_freeId.pop_back();
			}
			else
			{
				id._id = _nextId;
				_nextId++;
			}
			Entity e(id.GetId());
			return (e);
		}

		std::size_t EntityPool::GetEntityCount( void )
		{
			return (_nextId);
		}

		void EntityPool::Resize( std::size_t amount )
		{

		}

		bool EntityPool::IsValid( Entity::Id id )
		{
			std::uint32_t nb = id.GetId();

			if (nb < 0 || nb > GetEntityCount() || _idKilled[nb])
				return (false);
			return (true);
		}

		void EntityPool::Remove( Entity::Id id )
		{
			_idKiled[id.GetId()] = true;
			_freeId.emplace_back(id);
		}

	}
}
