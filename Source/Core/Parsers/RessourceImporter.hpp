#pragma once

#include "ECS/ClassTypeId.hpp"

namespace Soon
{
	class RessourceImporter
	{
		private:
			RessourceImporter( void )
			{

			}

		public:

			RessourceImporter* GetSingleton( void )
			{
				return (_singleton);
			}

			template<class T>
				AddImporter( Importer& imp )
				{
					T* imp = new T;
					importers.push_back(imp);
				}

			Importer* GetValidImporter( void )
			{
				for (Importer* imp : _importers)
				{
					
				}
			}

			template<class T>
				Ressource Loader(std::string path)
				{
					Ressource<T> res;

					Importer* imp = GetValidImporter();
					if (!imp)
					
					res = 


						std::cout << "Error : Wut kind of template is that ?" << std::endl;

					return (res);
				}

			std::list<Importer*>	_importers;
			RessourceImporter*		_singleton = nullptr;
	};
}

/*
   RessourceImporter::GetSingleton()->Loader<Mesh>("Coucou.obj");
*/
