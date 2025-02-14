#include "scbpch.h"
#include "Scribble2D/Renderer/ResourceManager.h"
#include "glad/glad.h"
#include "Scribble2D/Core/stb_image.h"

#include <filesystem>

namespace Scribble {
	std::string getResourcePath(const std::string& fileName)
	{
		return std::string(RESOURCE_PATH) + fileName;
	}

	std::map<std::string, Texture2D>    ResourceManager::s_Textures;
	std::map<std::string, Shader>       ResourceManager::s_Shaders;

	void ResourceManager::InitializeShaders()
	{
		LoadShader(getResourcePath("Shaders/renderer.vs.glsl").c_str(), getResourcePath("Shaders/renderer_col_sprite.fs.glsl").c_str(), nullptr, "solidShader");
		LoadShader(getResourcePath("Shaders/renderer.vs.glsl").c_str(), getResourcePath("Shaders/renderer_tex_sprite.fs.glsl").c_str(), nullptr, "textureShader");
		LoadShader(getResourcePath("Shaders/text.vs.glsl").c_str(),     getResourcePath("Shaders/text.fs.glsl").c_str(),                nullptr, "textShader");
	}

	void ResourceManager::InitializeTextures()
	{
		// If I want pre-genned textures, they should go here.
	}

	Shader ResourceManager::LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name)
	{
		s_Shaders[name] = LoadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
		return s_Shaders[name];
	}

	Shader ResourceManager::GetShader(std::string name)
	{
		if (s_Shaders.find(name) == s_Shaders.end()) {
			SCB_CORE_FATAL("Shader {0} does not exist", name);
		}
		return s_Shaders[name];
	}

	Texture2D ResourceManager::LoadTexture(const char* file, bool alpha, std::string name)
	{
		s_Textures[name] = LoadTextureFromFile(file, alpha);
		return s_Textures[name];
	}

	Texture2D ResourceManager::GetTexture(std::string name)
	{
		return s_Textures[name];
	}

	void ResourceManager::Clear()
	{
		for (auto i : s_Shaders)
			glDeleteProgram(i.second.m_ShaderID);
		for (auto i : s_Textures)
			glDeleteTextures(1, &i.second.m_TextureID);
			
		s_Shaders.clear();
		s_Textures.clear();
	}



	Shader ResourceManager::LoadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile)
	{
		std::string vertexCode;
		std::string fragmentCode;
		std::string geometryCode;
		try
		{

			std::ifstream vertexShaderFile(vShaderFile);
			std::ifstream fragmentShaderFile(fShaderFile);
			std::stringstream vShaderStream, fShaderStream;

			vShaderStream << vertexShaderFile.rdbuf();
			fShaderStream << fragmentShaderFile.rdbuf();

			vertexShaderFile.close();
			fragmentShaderFile.close();

			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();

			if (gShaderFile != nullptr)
			{
				std::ifstream geometryShaderFile(gShaderFile);
				std::stringstream gShaderStream;
				gShaderStream << geometryShaderFile.rdbuf();
				geometryShaderFile.close();
				geometryCode = gShaderStream.str();
			}
		}
		catch (std::exception e)
		{
			SCB_ERROR("Failed to read shader files");
		}
		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();
		const char* gShaderCode = geometryCode.c_str();

		Shader shader;
		shader.Compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);
		return shader;
	}

	Texture2D ResourceManager::LoadTextureFromFile(const char* file, bool alpha)
	{
		Texture2D tex;
		if (alpha) {
			tex.m_InternalFormat = GL_RGBA;
			tex.m_ImageFormat = GL_RGBA;
		}

		int width, height, numChannels;
		unsigned char* data = stbi_load(file, &width, &height, &numChannels, 0);

		tex.Generate(width, height, data);
		stbi_image_free(data);
		return tex;
	}
}
