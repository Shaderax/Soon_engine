#pragma once

#include "Core/Scene/Common/Texture.hpp"
#include "Math/vec3.hpp"
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

		void SetTexture( std::string name, Texture* texture )
		{
			_textures[name] = texture;
		}

		Texture* GetTexture( std::string name )
		{
			Texture* tt = nullptr;
			try
			{
				tt = _textures.at(name);
			}
			catch (const std::out_of_range& oor) {
				std::cerr << "For " << name << " Out of Range Get Texture error: " << oor.what() << '\n';
			}
			return tt;
		}

		void SetFloat( std::string name, float value )
		{
			_floats[name] = value;
		}

		float& GetFloat( std::string name )
		{
			return _floats[name];
		}

		void SetVec3( std::string name, vec3<float> vec )
		{
			_vec3s[name] = vec;
		}

		vec3<float>& GetVec3( std::string name )
		{
			return _vec3s[name];
		}

		std::unordered_map<std::string, Texture*>		_textures;
		std::unordered_map<std::string, float>			_floats;
		std::unordered_map<std::string, vec3<float>>	_vec3s;
	};
}
