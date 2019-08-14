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
				Importer* AddImporter( Importer& imp )
				{
					T* imp = new T;
					importers.push_back(imp);

					return (importers.back());
				}

			Importer* GetValidImporter( std::string ext )
			{
				for (Importer* imp : _importers)
				{
					for (std::string extension : strsplit(imp->valid_extension(), ';'))
						if (ext == extension)
							return (imp);
				}
				return (nullptr);
			}

			template<class T>
				Ressource Loader( std::string path )
				{
					Ressource<T> res;

					std::string ext = path.substr(fn.find_last_of(".") + 1);
					Importer* imp = GetValidImporter(ext);
					if (!imp)
					{
						std::cout << "Error : Wut kind of template is that ?" << std::endl;
						std::cout << "Ouais nan tu as merde" << std::endl;
						exit(-1);
					}
					else
						res = imp->import("path");
					return (res);
				}

			std::list<Importer*>	_importers;
			RessourceImporter*		_singleton = nullptr;
			std::map< std::string ext, Importer* >		_extToImporter;
			std::map< uint32_t type, Importer* >		_typeToImporter;
	};
}

/*
   Ressource res = RessourceImporter::GetSingleton()->Loader<Mesh>("Coucou.obj");
	std::vector<Mesh> vec = res.GetData();

	///////////
	std::vector<Object*> obj = Instantiate<Mesh>(vec);


	//////////////
	RessourceImporter::GetSingleton()->AddImporter<MeshImporter>();
	RessourceImporter::GetSingleton()->AddImporter<TextureImporter>();
	RessourceImporter::GetSingleton()->AddImporter<TextureImporter>();
	RessourceImporter::GetSingleton()->AddImporter<TextureImporter>();
	RessourceImporter::GetSingleton()->AddImporter<TextureImporter>();
	RessourceImporter::GetSingleton()->AddImporter<TextureImporter>();
	RessourceImporter::GetSingleton()->AddImporter<TextureImporter>();
	RessourceImporter::GetSingleton()->AddImporter<TextureImporter>();
	RessourceImporter::GetSingleton()->AddImporter<TextureImporter>();
	RessourceImporter::GetSingleton()->AddImporter<TextureImporter>();
	RessourceImporter::GetSingleton()->AddImporter<TextureImporter>();
	RessourceImporter::GetSingleton()->AddImporter<TextureImporter>();
   */
