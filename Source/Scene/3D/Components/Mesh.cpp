#include "Core/Math/vec2.hpp"
#include "Core/Math/vec3.hpp"
#include "Mesh.hpp"
#include <cstring>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Soon
{
//	Mesh processMesh(aiMesh *mesh, const aiScene *scene)
//	{
//		// data to fill
//		vector<Vertex> vertices;
//		vector<unsigned int> indices;
//		vector<Texture> textures;
//
//		// Walk through each of the mesh's vertices
//		for(unsigned int i = 0; i < mesh->mNumVertices; i++)
//		{
//			Vertex vertex;
//			glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
//			// positions
//			vector.x = mesh->mVertices[i].x;
//			vector.y = mesh->mVertices[i].y;
//			vector.z = mesh->mVertices[i].z;
//			vertex.Position = vector;
//			// normals
//			vector.x = mesh->mNormals[i].x;
//			vector.y = mesh->mNormals[i].y;
//			vector.z = mesh->mNormals[i].z;
//			vertex.Normal = vector;
//			// texture coordinates
//			if(mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
//			{
//				glm::vec2 vec;
//				// a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
//				// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
//				vec.x = mesh->mTextureCoords[0][i].x; 
//				vec.y = mesh->mTextureCoords[0][i].y;
//				vertex.TexCoords = vec;
//			}
//			else
//				vertex.TexCoords = glm::vec2(0.0f, 0.0f);
//			// tangent
//			vector.x = mesh->mTangents[i].x;
//			vector.y = mesh->mTangents[i].y;
//			vector.z = mesh->mTangents[i].z;
//			vertex.Tangent = vector;
//			// bitangent
//			vector.x = mesh->mBitangents[i].x;
//			vector.y = mesh->mBitangents[i].y;
//			vector.z = mesh->mBitangents[i].z;
//			vertex.Bitangent = vector;
//			vertices.push_back(vertex);
//		}
//		// now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
//		for(unsigned int i = 0; i < mesh->mNumFaces; i++)
//		{
//			aiFace face = mesh->mFaces[i];
//			// retrieve all indices of the face and store them in the indices vector
//			for(unsigned int j = 0; j < face.mNumIndices; j++)
//				indices.push_back(face.mIndices[j]);
//		}
//		// process materials
//		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];    
//		// we assume a convention for sampler names in the shaders. Each diffuse texture should be named
//		// as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
//		// Same applies to other texture as the following list summarizes:
//		// diffuse: texture_diffuseN
//		// specular: texture_specularN
//		// normal: texture_normalN
//
//		// 1. diffuse maps
//		vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
//		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
//		// 2. specular maps
//		vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
//		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
//		// 3. normal maps
//		std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
//		textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
//		// 4. height maps
//		std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
//		textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
//
//		// return a mesh object created from the extracted mesh data
//		return Mesh(vertices, indices, textures);
//	}

	void Mesh::LoadMesh(std::string path)
	{
		Assimp::Importer importer;
//		const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
//
//		if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
//		{
//			std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
//			return;
//		}

//		directory = path.substr(0, path.find_last_of('/'));

//		processNode(scene->mRootNode, scene);

					std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
					std::vector<vec3< float >> temp_vertices;
					std::vector<vec2< float >> temp_uvs;
					std::vector<vec3< float >> temp_normals;
					int matches = 0;
			
					FILE * file = fopen(path.c_str(), "r");
					if( file == NULL )
						std::cout << "Fail Open" << std::endl;
					std::cout << "File Open : " << path << std::endl;
			
					while( 1 )
					{
			
						char lineHeader[128];
						// read the first word of the line
						int res = fscanf(file, "%s", lineHeader);
						if (res == EOF)
							break; // EOF = End Of File. Quit the loop.
			
						// else : parse lineHeader
			
						vec3< float > vertex;
						vec2< float > uv;
						vec3< float > normal;
						if ( strcmp( lineHeader, "v" ) == 0 )
						{
							fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
							temp_vertices.push_back(vertex);
						}
						else if ( strcmp( lineHeader, "vt" ) == 0 ){
							fscanf(file, "%f %f\n", &uv.x, &uv.y );
							uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
							temp_uvs.push_back(uv);
						}
						else if ( strcmp( lineHeader, "vn" ) == 0 ){
							fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
							temp_normals.push_back(normal);
						}
						else if ( strcmp( lineHeader, "f" ) == 0 )
						{
							uint32_t vertexIndex[4] = {}, uvIndex[4] = {}, normalIndex[4] = {};
							matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2], &vertexIndex[3], &uvIndex[3], &normalIndex[3]);
							if (matches < 9)
								std::cout << "Fail Parser" << std::endl;
							vertexIndices.push_back(vertexIndex[0]);
							vertexIndices.push_back(vertexIndex[1]);
							vertexIndices.push_back(vertexIndex[2]);
							uvIndices    .push_back(uvIndex[0]);
							uvIndices    .push_back(uvIndex[1]);
							uvIndices    .push_back(uvIndex[2]);
							normalIndices.push_back(normalIndex[0]);
							normalIndices.push_back(normalIndex[1]);
							normalIndices.push_back(normalIndex[2]);
			
							if (matches == 12)
							{
								vertexIndices.push_back(vertexIndex[3]);
								uvIndices    .push_back(uvIndex[3]);
								normalIndices.push_back(normalIndex[3]);
							}
						}
		}

		// For each vertex of each triangle
		for( unsigned int i=0; i<vertexIndices.size(); i++ )
		{
			if (i != 0 && !(i % 2) && matches == 12)
			{
				for( unsigned int j=0; j < 3; i++ )
				{
					unsigned int vertexIndex = vertexIndices[i - 3 + j + (j > 0 ? 1 : 0)];
					unsigned int uvIndex = uvIndices[i - 3 + j + (j > 0 ? 1 : 0)];
					unsigned int normalIndex = normalIndices[i - 3 + j + (j > 0 ? 1 : 0)];

					// Get the attributes thanks to the index
					vec3< float > vertex = temp_vertices[ vertexIndex - 1 ];
					vec2< float > uv = temp_uvs[ uvIndex - 1 ];
					vec3< float > normal = temp_normals[ normalIndex - 1 ];

					// Put the attributes in buffers
					_vertex.push_back(vertex);
					_vertexTexture.push_back(uv);
					_normal.push_back(normal);
				}
			}
			else
			{
				// Get the indices of its attributes
				unsigned int vertexIndex = vertexIndices[i];
				unsigned int uvIndex = uvIndices[i];
				unsigned int normalIndex = normalIndices[i];

				// Get the attributes thanks to the index
				vec3< float > vertex = temp_vertices[ vertexIndex - 1 ];
				vec2< float > uv = temp_uvs[ uvIndex - 1 ];
				vec3< float > normal = temp_normals[ normalIndex - 1 ];

				// Put the attributes in buffers
				_vertex.push_back(vertex);
				_vertexTexture.push_back(uv);
				_normal.push_back(normal);
			}
		}
		fclose(file);
		_inf._nbVertex = _vertex.size() * 3;
		_inf._size = _vertex.size() * 3 * sizeof(float);
		_inf._data = _vertex.data();
		_itRender = GraphicsRenderer::GetInstance()->AddToRender(_owner.GetComponent<Transform3D>(), _inf);
	}
	
//	void processNode(aiNode *node, const aiScene *scene)
//	{
//		//process all the node's meshes (if any)
//		for(unsigned int i = 0; i < node->mNumMeshes; i++)
//		{
//			aiMesh *mesh = scene->mMeshes[node->mMeshes[i]]; 
//			meshes.push_back(processMesh(mesh, scene));			
//		}
//		// then do the same for each of its children
//		for(unsigned int i = 0; i < node->mNumChildren; i++)
//		{
//			processNode(node->mChildren[i], scene);
//		}
//	} 

//	std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName)
//	{
//		std::vector<Texture> textures;
//		for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
//		{
//			aiString str;
//			mat->GetTexture(type, i, &str);
//			// check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
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
//				Texture texture;
//				texture.id = TextureFromFile(str.C_Str(), this->directory);
//				texture.type = typeName;
//				texture.path = str.C_Str();
//				textures.push_back(texture);
//				textures_loaded.push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
//			}
//		}
//		return textures;
//	}
}
