
struct Texture2D
{
	Texture2D( void )
	{

	}

	Texture2D( std::string path )
	{
//		string filename = string(path);
//		filename = directory + '/' + filename;
//
//		unsigned int textureID;
//		glGenTexture2Ds(1, &textureID);
//
//		int width, height, nrComponents;
//		unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
//		if (data)
//		{
//			GLenum format;
//			if (nrComponents == 1)
//				format = GL_RED;
//			else if (nrComponents == 3)
//				format = GL_RGB;
//			else if (nrComponents == 4)
//				format = GL_RGBA;
//
//			glBind    Texture2D(GL_TEXTURE_2D, textureID);
//			glTexI    mage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
//			glGene    rateMipmap(GL_TEXTURE_2D);
//
//			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//			stbi_image_free(data);
//		}
//		else
//		{
//			std::cout << "Texture2D failed to load at path: " << path << std::endl;
//			stbi_image_free(data);
//		}
//
//		return textureID;
//
	}

	~Texture2D( void )
	{

	}

	stbi_uc* pixels;

};
