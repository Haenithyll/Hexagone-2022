#include "AssetManager.hpp"

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
