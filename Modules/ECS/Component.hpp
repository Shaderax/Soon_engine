#pragma once

#include "Id.hpp"
#include "ClassTypeId.hpp"

using namespace Soon::ECS;

namespace Soon
{
	namespace ECS
	{
		class Component
		{
			public:
				Component( void );
				virtual ~Component( void );

				virtual void Enable( void );
				virtual void Disable( void );

				bool IsActivated( void );

				void SetComponentId(TypeId id);
				void SetOwner(TypeId entity);

			private:
				TypeId _componentId;
				TypeId _ownerId;
		};

		template < typename T >
			TypeId GetComponentTypeId( void )
			{
				return (ClassTypeId<Component>::GetId<T>());
			}
	}
}