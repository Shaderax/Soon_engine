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
			};

			Mesh(Entity& entity, std::vector<vec3<float>> vertex, std::vector<vec3<float>> vertexTexture, std::vector<vec3<float>> normal)
			{
				_owner = entity;
			};

			~Mesh()
			{

			};

			void ProcessNode(aiNode *node, const aiScene *scene);
			void LoadMesh(std::string path);

			VertexBufferInfo _inf =
			{
				0,
				0,
				(void*)0
			};

			ComponentRenderer _itRender;
		private:
			Entity				_owner;

			std::vector<Mesh> meshes;

			std::vector< vec3<float> >	_position;
			std::vector< vec3<float> >	_normal;
			std::vector< vec2<float> >	_texCoord;

			Material mat;
	};
}
