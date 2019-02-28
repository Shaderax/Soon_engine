#pragma once

namespace Soon
{
	namespace ECS
	{
		template < T >
			class ClassTypeId
			{
				public:
					static std::uint32_t GetId()
					{
						static const std::uint32_t id = _nextId++;
						return (id);
					}

				private:
					static std::uint32_t _nextId;
			};

		template < typename T >
			ClassTypeId ClassTypeId<T>::_nextId{0};
	}
}
