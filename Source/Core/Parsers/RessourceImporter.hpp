#pragma once

#include "ECS/ClassTypeId.hpp"
#include "Importer.hpp"
#include <list>
#include <unordered_map>
#include <iostream>

namespace Soon
{
	class RessourceImporter
	{
		private:
			RessourceImporter( void )
			{

			}

		public:

			static RessourceImporter GetSingleton( void )
			{
				static RessourceImporter singleton;

				return (singleton);
			}

			template<class T>
				Importer* AddImporter( void )
				{
					T* imp = new T;
					_importers.push_back(imp);

					return (_importers.back());
				}

			template<class T>
				Importer* GetValidImporter( void )
				{
					for (auto& ok : _importers)
						if (ClassTypeId<RessourceImporter>::GetId<T>() == ClassTypeId<RessourceImporter>::GetId<T>())
							return (ok);
					return (nullptr);
				}

			template<class T>
				T Load( std::string path )
				{
					T* ret;
					Importer* imp = GetValidImporter<T>();
					if (!imp)
					{
						std::cout << "Error : Wut kind of template is that ?" << std::endl;
						exit(-1);
					}
					else
						ret = imp->import<T>(path);
					return (*ret);
				}

			std::list<Importer*>	_importers;
			std::unordered_map< uint32_t, Importer* >		_typeToImporter;
	};
}

/*
   MeshImporter* imp =  RessourceImporter::GetSingleton()->AddImporter<MeshImporter>();
   TextureImporter* imp =  RessourceImporter::GetSingleton()->AddImporter<TextureImporter>();

   ArrayMesh res = RessourceImporter::GetSingleton()->Loader<Mesh>("Coucou.obj");
   Texture res = RessourceImporter::GetSingleton()->Loader<Texture>("Coucou.png");
   */	
