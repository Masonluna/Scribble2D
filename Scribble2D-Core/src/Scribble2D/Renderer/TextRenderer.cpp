#include "scbpch.h"
#include "Scribble2d/Renderer/TextRenderer.h"
#include "Scribble2D/Renderer/ResourceManager.h"

#include "glm-1.0.1/glm/gtc/matrix_transform.hpp"


#include "ft2build.h"
#include FT_FREETYPE_H

namespace Scribble {
	void TextRenderer::Init()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		m_VertexArray.Init();


		m_TextShader = ResourceManager::GetShader("textShader");
		m_TextShader.SetMat4("projection", glm::ortho(0.0f, static_cast<float>(Application::Get().GetWindow().GetWidth()), static_cast<float>(Application::Get().GetWindow().GetHeight()), 0.0f));

		glGenBuffers(1, &m_TextVBO);
		m_VertexArray.Bind();
		glBindBuffer(GL_ARRAY_BUFFER, m_TextVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void TextRenderer::LoadFont(std::string font, unsigned int fontSize)
	{
		m_Characters.clear();
		FT_Library ft;
		if (FT_Init_FreeType(&ft))
			SCB_CORE_ERROR("Could not init FreeType Library");

		FT_Face face;
		if (FT_New_Face(ft, font.c_str(), 0, &face))
			SCB_CORE_ERROR("Failed to load font");

		FT_Set_Pixel_Sizes(face, 0, fontSize);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		//c++, get it????
		for (GLubyte c = 0; c < 128; c++) {
			if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
				SCB_CORE_ERROR("Failed to load Glyph");
				continue;
			}


			unsigned int texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_RED,
				face->glyph->bitmap.width,
				face->glyph->bitmap.rows,
				0,
				GL_RED,
				GL_UNSIGNED_BYTE,
				face->glyph->bitmap.buffer
			);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			Character character = {
				texture,
				glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
				glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
				face->glyph->advance.x
			};
			m_Characters.insert(std::pair<char, Character>(c, character));
		}
		glBindTexture(GL_TEXTURE_2D, 0);
		FT_Done_Face(face);
		FT_Done_FreeType(ft);
	}

	void TextRenderer::DrawString(const std::string& text, glm::vec2& pos, float scale, const glm::vec3& color)
	{
		m_TextShader.Bind();
		m_TextShader.SetFloat3("textColor", color);
		glActiveTexture(GL_TEXTURE0);
		m_VertexArray.Bind();

		std::string::const_iterator c;
		for (c = text.begin(); c != text.end(); c++) {
			Character ch = m_Characters[*c];

			float xpos = pos.x + ch.Bearing.x * scale;
			float ypos = pos.y + (m_Characters['H'].Bearing.y - ch.Bearing.y) * scale;

			float w = ch.Size.x * scale;
			float h = ch.Size.y * scale;

			float vertices[6][4] = {
				{ xpos,     ypos + h,   0.0f, 1.0f },
				{ xpos + w, ypos,       1.0f, 0.0f },
				{ xpos,     ypos,       0.0f, 0.0f },

				{ xpos,     ypos + h,   0.0f, 1.0f },
				{ xpos + w, ypos + h,   1.0f, 1.0f },
				{ xpos + w, ypos,       1.0f, 0.0f }
			};

			glBindTexture(GL_TEXTURE_2D, ch.TextureID);
			glBindBuffer(GL_ARRAY_BUFFER, m_TextVBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			pos.x += (ch.Advance >> 6) * scale;
		}

		m_VertexArray.Unbind();
		glBindTexture(GL_TEXTURE_2D, 0);
	}

}
