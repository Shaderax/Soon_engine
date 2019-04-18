#pragma once

#include <string>
#include <iostream>

namespace Soon
{
	enum Error
	{
		SN_SUCCESS,
		SN_ERROR
	};

	template< bool ThrowIf >
	void Error( const char *Function, const char *FullFilePath, int Line, const char* msg )
	{
		std::cout << "Soon Engine: " << (ThrowIf ? "Fatal Error" : "Error") << " in " << Function << "() (" << FullFilePath << ", " << Line << "): " << msg << std::endl;

		if (ThrowIf)
			throw std::runtime_error(std::string(msg));
	}
	
#define SOON_ERR( condition, str )\
do	\
{	if (!condition)\
    		Soon::Error<false>(__FUNCTION__, __FILE__, __LINE__, str); \
} while(false)

#define SOON_ERR_THROW( condition, str )\
do	\
{	\
	if (!condition)\
		Soon::Error<true>(__FUNCTION__, __FILE__, __LINE__, str); \
} while(false)

}
