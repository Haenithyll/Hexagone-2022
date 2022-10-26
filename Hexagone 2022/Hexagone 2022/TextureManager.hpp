#pragma once

#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Sprite.hpp"

#include <string>
#include <map>

class TextureManager
{
	public:
		static void Init();

		static void Update(float deltaTime);

		static bool LoadTextureFromFile(const std::string& name, const std::string& path);

		static const sf::Texture& GetTexture(const std::string& name);

	private:

		TextureManager();

		std::map<std::string, sf::Texture> mTextures;

		static TextureManager* mInstance;
};
