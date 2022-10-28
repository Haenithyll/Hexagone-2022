#include "AssetManager.hpp"

#include <fstream>

AssetManager* AssetManager::mInstance = nullptr;

AssetManager::AssetManager()
{

}

void AssetManager::Init()
{
	mInstance = new AssetManager();
}

bool AssetManager::LoadTextureFromFile(const std::string& name, const std::string& path)
{
	mInstance->mTextures[name] = sf::Texture();

	if (mInstance->mTextures[name].loadFromFile(path))
		return true;
	else
	{
		mInstance->mTextures.erase(name);

		return false;
	}
}

bool AssetManager::LoadFontFromFile(const std::string& name, const std::string& path)
{
	mInstance->mFonts[name] = sf::Font();

	if (mInstance->mFonts[name].loadFromFile(path))
		return true;
	else
	{
		mInstance->mFonts.erase(name);

		return false;
	}
}

const sf::Texture& AssetManager::GetTexture(const std::string& name)
{
	return mInstance->mTextures[name];
}

const sf::Font& AssetManager::GetFont(const std::string& name)
{
	return mInstance->mFonts[name];
}

bool AssetManager::LoadTextFromFile(const std::string& name, const std::string& path)
{
	std::ifstream file(path);

	if (!file.is_open())
		return false;

	std::string line;

	mInstance->mTexts[name] = std::vector<std::string>();

	while (std::getline(file, line))
		mInstance->mTexts[name].push_back(line);

	return true;
}

const std::vector<std::string>& AssetManager::GetText(const std::string& name)
{
	return mInstance->mTexts[name];
}
