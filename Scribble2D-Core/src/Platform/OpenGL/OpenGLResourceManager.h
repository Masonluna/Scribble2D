#pragma once

#include "scbpch.h"

//#include "Texture.h"
#include "OpenGLShader.h"

namespace Scribble {


	class OpenGLResourceManager
	{
	public:
		static std::map<std::string, OpenGLShader> s_Shaders;
		//static std::map<std::string, OpenGLTexture2D> s_Textures;


		static void InitializeShaders();

		static OpenGLShader LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name);
		static OpenGLShader GetShader(std::string name);

		//static OpenGLTexture2D LoadTexture(const char* file, bool alpha, std::string name);
		//static OpenGLTexture2D GetTexture(std::string name);

		static void Clear();
	private:
		OpenGLResourceManager() {}
		static OpenGLShader LoadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFIle = nullptr);
		//static OpenGLTexture2D LoadTextureFromFile(const char* file, bool alpha);
	};


}