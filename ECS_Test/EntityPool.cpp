#include "EntityPool.hpp"
#include "Id.hpp"

#include <iostream>

namespace Soon
{
	namespace ECS
	{
		Entity EntityPool::CreateEntity( void )
		{
			Id id;
			if (!_freeId.empty())
			{
				id._id = _freeId.back()._id;
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
			_idKilled.resize(amount);
		}

		bool EntityPool::IsValid( Id id )
		{
			TypeId nb = id.GetId();

			if (nb < 0 || nb > GetEntityCount() || _idKilled[nb])
				return (false);
			return (true);
		}

		void EntityPool::Remove( Id id )
		{
			_idKilled[id.GetId()] = true;
			_freeId.emplace_back(id);
		}

	}
}
