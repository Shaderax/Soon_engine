#include "MeshImporter.hpp"
#include "RessourceMap.hpp"
#include "Importer.hpp"
#include "RessourceImporter.hpp"
#include "ECS/ClassTypeId.hpp"
#include "Core/Scene/3D/Components/Mesh.hpp"
#include "Utilities/MeshArray.hpp"

#include "Math/vec3.hpp"
#include "Core/Scene/Object.hpp"

#include <cstring>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/material.h>

#include "Core/Scene/Common/Texture2D.hpp"

namespace Soon
{
	MeshImporter::MeshImporter( void ) { };
	MeshImporter::~MeshImporter( void ) {};

	uint32_t MeshImporter::IdValidType( void )
	{
		return (ClassTypeId<RessourceImporter>::GetId<MeshArray>());
	}

	bool MeshImporter::Import( std::string path )
	{
		Assimp::Importer importer;
		const aiScene *scene = importer.ReadFile(path.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);

		if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
			return false;
		}

		_path = path.substr(0, path.find_last_of('/'));

		std::cout << "Load Mesh : " << path << std::endl;
		MeshArray* ma = ProcessNode(scene->mRootNode, scene);
		ma->_path = path;

		GetRessourceMap<MeshArray>().emplace(std::make_pair(path, ma));

		return (true);
	}

	bool MeshImporter::Unload( std::string path )
	{
		try
		{
			MeshArray* ar = GetRessourceMap<T>().at(path);
			if (!ar)
				return false;
			for (Mesh& mesh : ar->_meshArray)
			{
				delete mesh->_vertices;
				mesh->_vertices = nullptr;
				delete mesh->_indices;
				mesh->_indices = nullptr;

				delete ar;
			}
			GetRessourceMap<T>().erase(path);
		}
		catch (std::out_of_range & )
		{
			std::cout << "Error : GetRessourceMap : Out of range" << std::endl; 
		}
	}

	void MeshImporter::ProcessMesh(Mesh& objMesh, aiMesh *mesh, const aiScene *scene)
	{
		// data to fill
		//		std::vector<Vertex> vertices;
		//		std::vector<unsigned int> indices;
		//std::vector<Texture2D> textures;

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
				vec3<float> vec;
				// a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't
				// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
				vec.x = mesh->mTextureCoords[0][i].x;
				vec.y = mesh->mTextureCoords[0][i].y;
				vec.z = mesh->mTextureCoords[0][i].z;
				vertex._texCoords = vec;
			}
			else
				vertex._texCoords = vec3<float>(0.0f, 0.0f, 0.0f);
			objMesh._vertices.push_back(vertex);
		}
		// now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
		for(unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			// retrieve all indices of the face and store them in the indices vector
			for(unsigned int j = 0; j < face.mNumIndices; j++)
			{
				objMesh._indices.push_back(face.mIndices[j]);
			}
		}
		// process materials
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		if (material)
		{
			// 1. diffuse maps
			///// TEST 3K /////
			LoadMaterialTextures(objMesh._material, material, aiTextureType_DIFFUSE, "texture_diffuse");

			//			std::vector<Texture2D> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
			//			textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
			//			// 2. specular maps
			//			std::vector<Texture2D> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
			//			textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

		}

		// 3. normal maps
		//		std::vector<Texture2D> normalMaps = LoadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
		//		objMesh._textures.insert(objMesh._textures.end(), normalMaps.begin(), normalMaps.end());
		//		// 4. height maps
		//		std::std::vector<Texture> heightMaps = LoadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
		//		textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

		// return a mesh object created from the extracted mesh data
		//		return Mesh(_owner, vertices, indices, textures);
	}

	void MeshImporter::LoadMaterialTextures(ShaderMaterial& material, aiMaterial *mat, aiTextureType type, std::string typeName)
	{
		///// TEST ////
		aiColor3D diff;
		aiColor3D ambient;
		aiColor3D spec;
		float shini = 0;
		aiReturn ret;
		//				ret = mat->Get(AI_MATKEY_COLOR_DIFFUSE, diff);
		//				std::cout << (ret == AI_SUCCESS ? "AI_SUCCESS" : "AI_FAILURE") << std::endl;
		//				std::cout << "Diffuse : " << diff.r << std::endl;
		//				std::cout << "Diffuse : " << diff.g << std::endl;
		//				std::cout << "Diffuse : " << diff.b << std::endl;
		//				ret = mat->Get(AI_MATKEY_COLOR_AMBIENT, ambient);
		//				std::cout << (ret == AI_SUCCESS ? "AI_SUCCESS" : "AI_FAILURE") << std::endl;
		//				std::cout << "Ambient : " << ambient.r << std::endl;
		//				std::cout << "Ambient : " << ambient.g << std::endl;
		//				std::cout << "Ambient : " << ambient.b << std::endl;
		//				ret = mat->Get(AI_MATKEY_COLOR_SPECULAR, spec);
		//				std::cout << (ret == AI_SUCCESS ? "AI_SUCCESS" : "AI_FAILURE") << std::endl;
		//				std::cout << "Specular : " << spec.r << std::endl;
		//				std::cout << "Specular : " << spec.g << std::endl;
		//				std::cout << "Specular : " << spec.b << std::endl;
		//				ret = mat->Get(AI_MATKEY_SHININESS_STRENGTH, shini);
		//				std::cout << (ret == AI_SUCCESS ? "AI_SUCCESS" : "AI_FAILURE") << std::endl;
		//				std::cout << "Shininess : " << shini << std::endl;

		vec3<float> tmp(ambient.r, ambient.g, ambient.b);
		material.SetVec3("ambient", tmp);
		tmp = vec3<float>(diff.r, diff.g, diff.b);
		material.SetVec3("diffuse", tmp);
		tmp = vec3<float>(spec.r, spec.g, spec.b);
		material.SetVec3("specular", tmp);
		material.SetFloat("shininess", shini);

		//std::cout << "mat->GetTextureCount(type) : " << mat->GetTextureCount(type) << std::endl;
		//if (mat->GetTextureCount(type) == 0)
		//	material.SetTexture("texSampler", RessourceImporter::GetSingleton().Load<Texture2D>("../Ressources/Textures/white.png"));
		for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
		{
			aiString str;
			mat->GetTexture(type, i, &str);
			// check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
			std::string filename(str.C_Str());
			int pos = filename.find_last_of('/');
			if (std::string::npos == (std::size_t)pos)
				pos = 0;
			Texture2D* t = RessourceImporter::GetSingleton().Load<Texture2D>(_path + "/" + filename.substr(pos, filename.length()));
			material.SetTexture("texSampler", t);
		}
	}

	MeshArray* MeshImporter::ProcessNode(aiNode *node, const aiScene *scene)
	{
		MeshArray* ma = new MeshArray();
		//process all the node's meshes (if any)
		for(unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];

			Mesh objMesh;
			objMesh._path = _path;

			ProcessMesh(objMesh, mesh, scene);

			//					objMesh._inf._nbVertex = objMesh._vertices.size();
			//					std::cout << "My Parser : Nb Vertice : " << objMesh._inf._nbVertex << std::endl;
			//					objMesh._inf._vertexSize = sizeof(Vertex) * objMesh._vertices.size();
			//					std::cout << "My Parser : vertexSize : " << objMesh._inf._vertexSize << std::endl;
			//					objMesh._inf._vertexData = objMesh._vertices.data();
			//					objMesh._inf._indexSize = objMesh._indices.size();
			//					std::cout << "My Parser : indexSize : " << objMesh._inf._indexSize << std::endl;
			//					objMesh._inf._indexData = objMesh._indices.data();
			//					objMesh._inf._material = &(objMesh._mat);

			//if (objMesh._material.GetTexture("texSampler"))
			//	exit(-1);
			ma->_meshArray.push_back(objMesh);
			//	if (ma->_meshArray.back()._material.GetTexture("texSampler"))
			//		exit(-1);
			//	if (ma->_meshArray[0]._material.GetTexture("texSampler"))
			//		exit(-1);
		}
		// then do the same for each of its children
		for(unsigned int i = 0; i < node->mNumChildren; i++)
			*ma += *(ProcessNode(node->mChildren[i], scene));
		return (ma);
	}
}
