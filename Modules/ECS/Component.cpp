#include "Component.hpp"
#include "Id.hpp"
#include "ClassTypeId.hpp"
#include "Entity.hpp"

using namespace Soon::ECS;

namespace Soon
{
	namespace ECS
	{
				Component::Component( void )
                {
                    _componentId = TypeIdError;
                    _ownerId = TypeIdError;
                }

				Component::~Component( void )
                {

                }

                bool Component::IsActivated( void )
                {
                    Entity owner(_ownerId);

                    return (owner.IsComponentActivated(_componentId));
                }

				void Component::Enable( void )
                {
                    Entity owner(_ownerId);

                    owner.EnableComponent( _componentId );
                }

				void Component::Disable( void )
                {
                    Entity owner(_ownerId);
                    owner.DisableComponent( _componentId );
                }

				void Component::SetComponentId(TypeId id)
                {
                    _componentId = id;
                }

				void Component::SetOwner( TypeId entity )
                {
                    _ownerId = entity;
                }
	}
}