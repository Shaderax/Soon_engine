#pragma once

namespace Soon
{
	namespace ECS
	{
		template < TBase >
			class ClassTypeId
			{
				public:
					template < typename T >
					static std::uint32_t GetId()
					{
						static const std::uint32_t id = _nextId++;
						return (id);
					}

				private:
					static std::uint32_t _nextId;
			};

		template < typename T >
			std::uint32_t ClassTypeId<TBase>::_nextId{0};
	}
}
