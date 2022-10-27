#include "Log.hpp"

Log* Log::mInstance = nullptr;

Log::Log()
{

}

void Log::Init()
{
	mInstance = new Log();
}

void Log::Print(const std::string& message)
{
	mInstance->mMessages.push_back(message);
}

void Log::Print(const sf::Vector2f& vector)
{
	mInstance->mMessages.push_back("( " + std::to_string(vector.x) + " ; " + std::to_string(vector.y) + " )");
}

const std::vector<std::string>& Log::GetMessages()
{
	return mInstance->mMessages;
}
