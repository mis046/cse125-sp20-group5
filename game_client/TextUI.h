#pragma once
////////////////////////////////////////
// TextUI.h
// 
// Class that renders text to the screen
// https://learnopengl.com/In-Practice/Text-Rendering
////////////////////////////////////////

#pragma once

#include "Core.h"
#include "DrawableUI.h"

#include <ft2build.h>
#include FT_FREETYPE_H  

struct Character {
	unsigned int textureID; // ID handle of the glyph texture
	glm::ivec2   size;      // Size of glyph
	glm::ivec2   bearing;   // Offset from baseline to left/top of glyph
	unsigned int advance;   // Horizontal offset to advance to next glyph
};

enum BackgroundTexture { TEXT_BUBBLE, NUM_OF_BACKTEXT };

enum class FontType { CARTOON, CHUNK, NUM_OF_FONT_TYPE};

class TextUI : public DrawableUI
{
public:

	TextUI(uint shader, FontType usedFont, glm::vec3 usedColor = glm::vec3(1), std::string reservedText = "", glm::mat4 model = glm::mat4(1));
	~TextUI();

	std::map<GLchar, Character > initFont(const char* fontFile);

	void renderText(std::string text, float x, float y, float scale, glm::vec3 color);
	void renderTextInWorld(std::string text, glm::mat4 viewProjMtx, glm::mat4 modelMtx, float scale, glm::vec3 color);
	void renderFont(std::string text, float x, float y, float scale);

	// These variables are needed for the shader program
	static std::map<FontType, std::map<GLchar, Character >> fontCharacters;
	static GLuint VAO, VBO;
	static bool staticInitialized;
	
	uint shader;
	GLuint backgroundTextureIDs[NUM_OF_BACKTEXT];

	glm::mat4 model;
	std::string reservedText;
	FontType usedFont;
	glm::vec3 usedColor;

	void loadBackgroundTexture(const char* textureFile, uint id);

	// Overriden methods from Drawable
	void draw(SceneNode& node, const glm::mat4& viewProjMtx) override;
	void update(SceneNode* node) override;

private:
	const std::map<FontType, const char*> fontFileMap = {
		{ FontType::CARTOON, "font/From Cartoon Blocks.ttf" },
		{ FontType::CHUNK, "font/Chunk Five Print.otf" }
	};
};
