#include "Core/Math/vec2.hpp"
#include "Core/Math/vec3.hpp"
#include "Mesh.hpp"
#include <cstring>
#include "Scene/Object.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Scene/Common/ObjectOwner.hpp"

namespace Soon
{
	void Mesh::ProcessMesh(Mesh& objMesh, aiMesh *mesh, const aiScene *scene)
	{
		std::cout << "Enter" << std::endl;
		// data to fill
//		std::vector<Vertex> vertices;
//		std::vector<unsigned int> indices;
		std::vector<Texture2D> textures;

		// Walk through each of the mesh's vertices
		for(unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			Vertex vertex;
			vec3<float> vector;
			// positions
			vector.x = mesh->mVertices[i].x;
			vector.y = mesh->mVertices[i].y;
			vector.z = mesh->mVertices[i].z;
			vertex._position = vector;
			// normals
			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].y;
			vector.z = mesh->mNormals[i].z;
			vertex._normal = vector;
			// texture coordinates
			if(mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
			{
				vec2<float> vec;
				// a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
				// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
				vec.x = mesh->mTextureCoords[0][i].x; 
				vec.y = mesh->mTextureCoords[0][i].y;
				vertex._texCoords = vec;
			}
			else
				vertex._texCoords = vec2<float>(0.0f, 0.0f);
			objMesh._vertices.push_back(vertex);
		}
		// now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
		for(unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
//			std::cout << "Face : " << i << std::endl;
			aiFace face = mesh->mFaces[i];
			// retrieve all indices of the face and store them in the indices vector
			for(unsigned int j = 0; j < face.mNumIndices; j++)
			{
//				std::cout << "Indices : " << face.mIndices[j] << std::endl;
				objMesh._indices.push_back(face.mIndices[j]);
			}
//			std::cout << std::endl;
		}
		// process materials
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];    
		// we assume a convention for sampler names in the shaders. Each diffuse texture should be named
		// as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
		// Same applies to other texture as the following list summarizes:
		// diffuse: texture_diffuseN
		// specular: texture_specularN
		// normal: texture_normalN

		// 1. diffuse maps
		std::vector<Texture2D> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		// 2. specular maps
		std::vector<Texture2D> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

		if (!textures.empty())
			objMesh._mat._texture = textures.at(0);

		// 3. normal maps
//		std::vector<Texture2D> normalMaps = LoadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
//		objMesh._textures.insert(objMesh._textures.end(), normalMaps.begin(), normalMaps.end());
//		// 4. height maps
//		std::std::vector<Texture> heightMaps = LoadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
//		textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

  		// return a mesh object created from the extracted mesh data
//		return Mesh(_owner, vertices, indices, textures);
		std::cout << "Exit" << std::endl;
	}
	
	std::vector<Texture2D> Mesh::LoadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName)
	{
		std::vector<Texture2D> textures;

//		std::cout << mat->GetTextureCount(type) << std::endl;
		for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
		{
			aiString str;
			mat->GetTexture(type, i, &str);
//			std::cout << str.C_Str() << std::endl;
			// check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
//			bool skip = false;
//			for(unsigned int j = 0; j < textures_loaded.size(); j++)
//			{
//				if(std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
//				{
//					textures.push_back(textures_loaded[j]);
//					skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
//					break;
//				}
//			}
//			if(!skip)
//			{   // if texture hasn't been loaded already, load it
				std::string filename(str.C_Str());
				int pos = filename.find_last_of('/');
				if (std::string::npos == pos)
					pos = 0;
				Texture2D texture(_path + "/" + filename.substr(pos, filename.length()));
//				texture.id = TextureFromFile(str.C_Str(), this->directory);
//				texture.type = typeName;
//				texture.path = str.C_Str();
				textures.push_back(texture);
//				textures_loaded.push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
//			}
		}
		return textures;
	}

	void Mesh::ProcessNode(aiNode *node, const aiScene *scene)
	{
		//process all the node's meshes (if any)
		for(unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh *mesh = scene->mMeshes[node->mMeshes[i]]; 

			Object* obj = new Object(_owner.GetComponent<ObjectOwner>()._owner);
			Mesh objMesh = obj->AddComponent<Soon::Mesh>();
			objMesh._path = _path;

			ProcessMesh(objMesh, mesh, scene);

//			for (Vertex& vertex : objMesh._vertices)
//			{
//				std::cout << "Position : " ; vertex._position.show();
//				std::cout << "Normal : " ; vertex._normal.show();
//				std::cout << "Text : " ; vertex._texCoords.show();
//			}
//			for (uint32_t& indices : objMesh._indices)
//				std::cout << indices<< std::endl;

			objMesh._inf._nbVertex = objMesh._vertices.size();
			std::cout << "My Parser : Nb Vertice : " << objMesh._inf._nbVertex << std::endl;
			objMesh._inf._vertexSize = sizeof(Vertex) * objMesh._vertices.size();
			std::cout << "My Parser : vertexSize : " << objMesh._inf._vertexSize << std::endl;
			objMesh._inf._vertexData = objMesh._vertices.data();
			objMesh._inf._indexSize = objMesh._indices.size();
			std::cout << "My Parser : indexSize : " << objMesh._inf._indexSize << std::endl;
			objMesh._inf._indexData = objMesh._indices.data();
			GraphicsRenderer::GetInstance()->AddToRender(_owner.GetComponent<Transform3D>(), objMesh._inf);
		}
		// then do the same for each of its children
		for(unsigned int i = 0; i < node->mNumChildren; i++)
		{
			ProcessNode(node->mChildren[i], scene);
		}
	} 

	void Mesh::LoadMesh(std::string path)
	{
		Assimp::Importer importer;
		const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);

		if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
		{
			std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
			return;
		}

//		std::cout << scene->mNumMeshes << std::endl;

		_path = path.substr(0, path.find_last_of('/'));

		ProcessNode(scene->mRootNode, scene);
	}
};
