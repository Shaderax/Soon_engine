#include "ECS/Component.hpp"
#include "Core/Math/vec2.hpp"
#include "Core/Math/vec3.hpp"
#include <vector>
#include <iostream>
#include "Graphics/Vulkan/GraphicsRenderer.hpp"

#include "Scene/Common/Material.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Soon
{
	// Vertex of a 3D Object
	class Mesh : public Component
	{
		public:
			Mesh(Entity& entity)
			{
				_owner = entity;
			}

			~Mesh()
			{

			}

			void ProcessNode(aiNode *node, const aiScene *scene);
			void LoadMesh(std::string path);
			void ProcessMesh(Mesh& objMesh, aiMesh *mesh, const aiScene *scene);
			std::vector<Texture2D> LoadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);

			VertexBufferInfo _inf =
			{
				0,
				0,
				(void*)0
			};

			ComponentRenderer _itRender;

			std::vector< Vertex >		_vertices;
			std::vector<uint32_t>	_indices;
			std::string					_path;

		private:
			Entity				_owner;
			Material			_mat;
	};
	      std::vector<Texture2D> LoadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
}
