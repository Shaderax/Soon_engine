#pragma once

#include "Component.hpp"
#include "World.hpp"
#include "Config.hpp"
#include "Id.hpp"

using namespace Soon::ECS;

namespace Soon
{
	namespace ECS
	{
		class World;

		class Entity
		{
			public:
				Entity( World& world, TypeId id = 0 );
				~Entity( void );

				TypeId GetId( void ) { return (_id.GetId()); };
				Id GetIdClass( void ) const { return (_id); };

				bool IsValid() const;

				World& GetWorld( void ) const;
				bool IsActivated( void ) const;
				void Activate( void );
				void Desactivate( void );
				void Kill( void );

				template< typename T >
					void AddComponent( void );

				template< typename T, typename ... Args >
					void AddComponent( Args && ... args );

				void AddComponent( Component* component, TypeId componentId);

				template <typename T>
					bool HasComponent( void ) const;

				template < typename T >
					bool HasComponent( TypeId componentId ) const;

			private:
				Id _id;

				World* _world;
		};
	}
}
