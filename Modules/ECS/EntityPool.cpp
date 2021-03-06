#include "EntityPool.hpp"
#include "Id.hpp"

#include <iostream>

namespace Soon
{
	namespace ECS
	{
		EntityPool::EntityPool( std::uint32_t poolSize ) :
			_nextId(0),
			_idKilled(poolSize)
		{
		}

		EntityPool::~EntityPool( void )
		{

		}

		Id EntityPool::CreateEntity( void )
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
			return (id);
		}

		std::size_t EntityPool::GetEntityCount( void ) const
		{
			return (_nextId);
		}

		void EntityPool::Resize( std::size_t amount )
		{
			_idKilled.resize(amount);
		}

		bool EntityPool::IsValid( Id id ) const
		{
			TypeId nb = id.GetId();

			if (nb > GetEntityCount() || _idKilled[nb])
				return (false);
			return (true);
		}

		void EntityPool::Remove( Id id )
		{
			_idKilled[id.GetId()] = true;
			_freeId.push_back(id);
		}

		void EntityPool::Clear( void )
		{
			_nextId = 0;
			_freeId.clear();
			_idKilled.clear();
		}
	}
}
