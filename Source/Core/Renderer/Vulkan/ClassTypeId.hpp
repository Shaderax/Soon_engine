#pragma once

namespace Soon
{
	template < typename TBase >
		class ClassTypeId
		{
			public:
				template < typename T >
					static uint32_t GetId( void )
					{
						static const uint32_t id = _nextId++;
						return (id);
					}

			private:
				static uint32_t _nextId;
		};

	template < typename TBase >
		uint32_t  ClassTypeId<TBase>::_nextId = 0;
}
