#pragma once

#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Font.hpp"

#include <string>
#include <map>

class AssetManager
{
	public:
		static void Init();

		static bool LoadTextureFromFile(const std::string& name, const std::string& path);
		static bool LoadFontFromFile(const std::string& name, const std::string& path);

		static const sf::Texture& GetTexture(const std::string& name);
		static const sf::Font& GetFont(const std::string& name);

	private:

		AssetManager();

		std::map<std::string, sf::Texture> mTextures;
		std::map<std::string, sf::Font> mFonts;

		static AssetManager* mInstance;
};
