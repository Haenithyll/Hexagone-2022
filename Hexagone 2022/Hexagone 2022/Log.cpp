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

const std::vector<std::string>& Log::GetMessages()
{
	return mInstance->mMessages;
}
