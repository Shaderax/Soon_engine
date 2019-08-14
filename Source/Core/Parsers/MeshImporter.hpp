#pragma once

#include "Importer.hpp"
#include "RessourceImporter.hpp"
#include "ECS/ClassTypeId.hpp"
#include "Scene/3D/Components/Mesh.hpp"

namespace Soon
{
	class MeshImporter : Importer
	{
		MeshImporter( void ) {};
		~MeshImporter( void ) {};

		virtual void import( std::string path )
		{

		}

		virtual void valid_extension( void )
		{
			return (
				"3d;"
				"3ds;"
				"3mf;"
				"ac;"
				"ac3d;"
				"acc;"
				"amj;"
				"ase;"
				"ask;"
				"b3d;"
				"blend;"
				"bvh;"
				"cms;"
				"cob;"
				"dae;"
				"dxf;"
				"enff;"
				"fbx;"
				"gltf;"
				"hmb;"
				"ifc;"
				"irr;"
				"lwo;"
				"lws;"
				"lxo;"
				"md2;"
				"md3;"
				"md5;"
				"mdc;"
				"mdl;"
				"mesh;"
				"mot;"
				"ms3d;"
				"ndo;"
				"nff;"
				"obj;"
				"off;"
				"ogex;"
				"ply;"
				"pmx;"
				"prj;"
				"q3o;"
				"q3s;"
				"raw;"
				"scn;"
				"sib;"
				"smd;"
				"stp;"
				"stl;"
				"ter;"
				"uc;"
				"vta;"
				"x;"
				"x3d;"
				"xgl;"
				"zgl;");
		}

		virtual bool valid_type( std::string ext )
		{
			return (ClassTypeId<RessourceImporter>::GetId<Mesh>());
		}
	};
}
