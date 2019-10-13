#pragma once

#include "RessourceMap.hpp"

#include "Importer.hpp"
#include "RessourceImporter.hpp"
#include "ECS/ClassTypeId.hpp"
#include "Scene/3D/Components/Mesh.hpp"
#include "Utilities/MeshArray.hpp"

///
#include "Core/Math/vec2.hpp"
#include "Core/Math/vec3.hpp"
#include <cstring>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Soon
{
	class MeshImporter : public Importer
	{
		typedef MeshArray ValidType;
		public:
			std::string _path;
			MeshImporter( void );
			~MeshImporter( void );

			uint32_t IdValidType( void );

			bool import( std::string path );

			void ProcessMesh(Mesh& objMesh, aiMesh *mesh, const aiScene *scene);
#include "assimp/material.h"

			void LoadMaterialTextures(ShaderMaterial& material, aiMaterial *mat, aiTextureType type, std::string typeName);

			MeshArray& ProcessNode(aiNode *node, const aiScene *scene);
	};
}













