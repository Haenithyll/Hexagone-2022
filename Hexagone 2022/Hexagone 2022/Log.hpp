#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"

#include <vector>

class Log
{
	public:
		static void Init();

		static void Print(const std::string& message);

		static const std::vector<std::string>& GetMessages();

	private:
		Log();

		std::vector<std::string> mMessages;

		static Log* mInstance;
};
