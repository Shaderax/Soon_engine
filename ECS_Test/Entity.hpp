#pragma once

#include "Ecs.hpp"

namespace Soon
{
	namespace ECS
	{
		class Entity
		{
			public:
				struct Id
				{
					Id( std::uint32_t id ) { _id = id; };
					std::uint32_t GetId( void ) { return (_id); };
					std::uint32_t _id;
				}

				Entity( World* world, std::uint32_t id = 0 );
				~Entity( void );

				std::uint32_t GetId( void ) { return (_id.GetId()); };
				Entity::Id GetIdClass( void ) { return (_id); };

				bool IsValid() const;

				World& GetWorld( void ) const;
				bool IsActivated( void ) const;
				void Activate( void );
				void Deactivate( void );
				void Kill( void )

				template< typename T, Args && ... args > void AddComponent( Args && ... args );

				template < typename T >
				void AddComponent( T component, std::uint32_t componentId);



			private:
				Id _id;

				World* _world;
		};
	}
}
