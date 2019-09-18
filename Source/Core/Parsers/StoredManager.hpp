#pragma once

namespace Soon
{
		template < typename TBase >
			class ClassType
			{
				public:
						static std::unordered_map<std::string, TBase> GetMap( void )
						{
							return (_map);
						}

				private:
					static std::unordered_map<std::string, TBase> _map;
			};

		template < typename TBase >
			std::unordered_map<std::string, TBase> ClassType<TBase>::_map = {};
}
