#include "Log.hpp"

Log* Log::mInstance = nullptr;

Log::Log()
{

}

void Log::Init()
{
	mInstance = new Log();
}

Message::Message()
{
	Text = "";
	Color = 0;
}

Message::Message(const std::string& message)
{
	Text = message;
	Color = 0;
}

Message::Message(const std::string& message, Party party)
{
	Text = message;

	switch (party)
	{
		case Party::AgglutinationPatriote:
			Color = ImColor(0.f, 255.f, 255.f);

			break;

		case Party::EnRoute:
			Color = ImColor(255.f, 255.f, 0.f);

			break;

		case Party::LesRebelles:
			Color = ImColor(255.f, 0.f, 0.f);

			break;

		case Party::Reprise:
			Color = ImColor(0.f, 0.f, 255.f);

			break;

		default:
			Color = 0;

			break;
	}
}


void Log::Print(const std::string& message)
{
	Message m = Message(message);
	mInstance->mMessages.push_back(m);
}

void Log::Print(const std::string& message, Party party)
{
	mInstance->mMessages.push_back(Message(message, party));
}

void Log::Print(const sf::Vector2f& vector)
{
	mInstance->mMessages.push_back(Message("( " + std::to_string(vector.x) + " ; " + std::to_string(vector.y) + " )"));
}

void Log::Print(const sf::Vector3i& vector)
{
	mInstance->mMessages.push_back(Message("( " + std::to_string(vector.x) + " ; " + std::to_string(vector.y) + " ; " + std::to_string(vector.z) + " )"));
}

void Log::BreakLine()
{
	mInstance->mMessages.push_back(Message());
}

void Log::Show()
{
	ImGui::Begin("Console");

	if (ImGui::Button(mInstance->mLookScroll ? "Lock scroll" : "Unlock scroll"))
		mInstance->mLookScroll = !mInstance->mLookScroll;

	ImGui::BeginChild(ImGui::GetID("Console"));

	for (const Message& message : mInstance->mMessages)
	{
		if (message.Color > 0)
		{
			ImGui::Bullet();

			ImVec2 pos = ImGui::GetCursorScreenPos();

			pos.x -= 10.f;
			pos.y += 6.f;

			ImGui::GetWindowDrawList()->AddCircleFilled(pos, 3.f, message.Color, 20);
		}

		ImGui::Text(message.Text.c_str());
	}

	if (mInstance->mLookScroll)
		ImGui::SetScrollHereY(1.f);

	ImGui::EndChild();

	ImGui::End();
}
