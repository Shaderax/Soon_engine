#include "Core/Math/vec2.hpp"
#include "Core/Math/vec3.hpp"
#include "Core/Parsers/3DObject.hpp"
#include <cstring>

namespace Soon
{
	void ObjFile::LoadObjFile(std::string path)
	{
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
				uint32_t vertexIndex[4], uvIndex[4], normalIndex[4];
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
					_vectexTexture.push_back(uv);
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
				_vectexTexture.push_back(uv);
				_normal.push_back(normal);
			}
		}
		fclose(file);
		_inf._nbVertex = _vertex.size() * 3;
		_inf._size = _vertex.size() * 3 * sizeof(float);
		_inf._data = _vertex.data();
		_itRender = GraphicsRenderer::GetInstance()->AddToRender(_owner.GetComponent<Transform3D>(), _inf);
	}
}
