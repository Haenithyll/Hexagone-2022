#include "TextureManager.hpp"

TextureManager* TextureManager::mInstance = nullptr;

TextureManager::TextureManager()
{

}

void TextureManager::Init()
{
	mInstance = new TextureManager();
}

void TextureManager::Update(float deltaTime)
{

}

bool TextureManager::LoadTextureFromFile(const std::string& name, const std::string& path)
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

const sf::Texture& TextureManager::GetTexture(const std::string& name)
{
	return mInstance->mTextures[name];
}
