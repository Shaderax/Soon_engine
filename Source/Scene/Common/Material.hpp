#pragma once

#include "Scene/Common/Texture.hpp"
#include "Core/Math/vec3.hpp"
#include <unordered_map>
#include <string>

namespace Soon
{
	struct Material
	{
		Material( void )
		{

		}

		virtual ~Material( void )
		{

		}

		void SetTexture( std::string name, Texture& texture )
		{
			_textures[name] = &texture;
		}

		Texture* GetTexture( std::string name )
		{
			return (_textures[name]);
		}

		void SetFloat( std::string name, float& value )
		{
			_floats[name] = value;
		}

		void SetVec3( std::string name, vec3<float>& vec )
		{
			_vec3s[name] = &vec;
		}

		std::unordered_map<std::string, Texture*> _textures;
		std::unordered_map<std::string, float> _floats;
		std::unordered_map<std::string, vec3<float>*> _vec3s;
	};
}
