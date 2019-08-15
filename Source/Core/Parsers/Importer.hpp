#pragma once

namespace Soon
{
	class Importer
	{
		virtual Import( void ) = 0;
		virtual ~Import( void ) = 0;
		template<class T>
		virtual Ressource import( std::string path ) = 0;
		virtual void valid_extension( std::string ext ) = 0;
		virtual void valid_type( std::string ext ) = 0;
	};
}
