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

			RessourceImporter GetSingleton( void )
			{
				static RessourceImporter singleton;

				return (singleton);
			}

			template<class T>
				Importer* AddImporter( Importer& imp )
				{
					T* imp = new T;
					importers.push_back(imp);
	//		std::map< std::string ext, Importer* >		_extToImporter;
	//		std::map< uint32_t type, Importer* >		_typeToImporter;

					return (importers.back());
				}

			Importer* GetValidImporter( std::string ext )
			{
				for (Importer* imp : _importers)
				{
					for (std::string extension : imp->valid_extension())
						if (ext == extension)
							return (imp);
				}
				return (nullptr);
			}

			template<class T>
				Ressource Loader( std::string path )
				{
//					Ressource<T> res;

					Importer* imp = GetValidImporter(ext);
					if (!imp)
					{
						std::cout << "Error : Wut kind of template is that ?" << std::endl;
						std::cout << "Ouais nan tu as merde" << std::endl;
						exit(-1);
					}
					else
						res = imp->import(path);
					return (res);
				}

			std::list<Importer*>	_importers;
			std::map< std::string ext, Importer* >		_extToImporter;
			std::map< uint32_t type, Importer* >		_typeToImporter;
	};
}

/*
	///////////
	std::vector<Object*> obj = Instantiate<Mesh>(vec);
	//////////////
	
	RessourceImporter::GetSingleton()->AddImporter<MeshImporter>();
	RessourceImporter::GetSingleton()->AddImporter<TextureImporter>();
	RessourceImporter::GetSingleton()->AddImporter<CACAOUETImporter>();

	Ressource res = RessourceImporter::GetSingleton()->Loader<Mesh>("Coucou.obj");
	Ressource res = RessourceImporter::GetSingleton()->Loader<Texture>("Coucou.png");

//////////////////////////////////////

	ArrayMesh res = RessourceImporter::GetSingleton().Load<Mesh>();


	T Load(str::string path);

	check if importer good
	/
	Importer
	{
	template<class T>
		virtual T import(path);
	}

	meshImporter: Importer
	{
	template<>
		ArrayMesh import(path);
	}
*/	
