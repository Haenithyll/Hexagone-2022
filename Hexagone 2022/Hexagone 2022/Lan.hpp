#pragma once
#include "Screen.hpp"
#include "Button.hpp"
#include "Gomoku.hpp"
#include "SFML/Network.hpp"

class Lan : public Screen
{
	public:
		Lan()
		{
			font.loadFromFile("Roboto-Thin.ttf");

			server.setBlocking(false);
		}

		int Run(sw::Window& window)
		{
			int _size = 19;
			bool limitless = true;

			sw::Button info(sf::FloatRect(50, 50, 75, 50), font, "Are you Server (S) or Client (C) ?");
			info.SetFillColor(sf::Color::Black);

			int state = 0;
			std::string ip;

			while (window.IsOpen())
			{
				sw::EventsData data = window.HandleEvents();

				if (data.close) return -1;
				else if (data.IsKeyPressed(sw::Key::Escape)) return 0;

				window.Clear(sf::Color(220, 179, 92));

				if (state == 0)
				{
					if (data.IsKeyPressed(sw::Key::C)) state = 1, isServer = false;
					else if (data.IsKeyPressed(sw::Key::S))
						if (server.listen(54000) == sf::Socket::Done)
						{
							state = 1, isServer = true, info.SetText(sf::IpAddress::getLocalAddress().toString());

							sw::Button minus(sf::FloatRect(35, 35, 10, 10), font, "-");
							minus.SetFillColor(sf::Color::Red);

							sw::Button sizeView(sf::FloatRect(50, 35, 15, 15), font, std::to_string(_size));
							sizeView.SetFillColor(sf::Color::Black);

							sw::Button plus(sf::FloatRect(65, 35, 10, 10), font, "+");
							plus.SetFillColor(sf::Color::Green);

							sw::Button isLimitless(sf::FloatRect(50, 60, 30, 20), font, "Sans limite");
							isLimitless.SetFillColor(sf::Color::Blue);
							isLimitless.SetTextColor(sf::Color::Black);

							while (window.IsOpen())
							{
								sw::EventsData data = window.HandleEvents();

								if (data.close) return -1;
								else if (data.IsKeyPressed(sw::Key::Escape)) return 0;
								else if (data.IsKeyPressed(sw::Key::Enter)) break;

								if (minus.IsMouseClick() && data.leftClick && _size > 6) _size -= 2, sizeView.SetText(std::to_string(_size));
								else if (plus.IsMouseClick() && data.leftClick) _size += 2, sizeView.SetText(std::to_string(_size));

								if (isLimitless.IsMouseClick() && data.leftClick)
								{
									limitless = !limitless;
									if (limitless) isLimitless.SetText("Sans Limite"), isLimitless.SetFillColor(sf::Color::Blue);
									else isLimitless.SetText("Avec Limite"), isLimitless.SetFillColor(sf::Color::Magenta);
								}

								window.Clear(sf::Color(220, 179, 92));

								window.Draw(minus);
								window.Draw(sizeView);
								window.Draw(plus);
								window.Draw(isLimitless);

								window.Display();
							}
						}
				}
				else if (state == 1)
				{
					if (!isServer)
					{
						if (data.IsKeyPressed(sw::Key::BackSpace) && !ip.empty()) ip.pop_back();
						else if (data.IsKeyPressed(sw::Key::Return))
						{
							if (client.connect(sf::IpAddress(ip), 54000, sf::seconds(5)) == sf::Socket::Done)
							{
								state = 2;
								client.setBlocking(true);
								sf::Socket::Status s = client.receive(sdata, 2, size);
								if (s == sf::Socket::Done) limitless = sdata[0] == 1, _size = sdata[1];
								else if (s == sf::Socket::Disconnected)
								{
									client.disconnect();
									window.SetView(window.GetDefaultView());
									return 0;
								}
							}
						}
						else if (!data.IsKeyDown(sw::Key::BackSpace)) ip += data.textEntered;
						if (ip.length() > 20) ip.erase(20, ip.length() - 20);
						info.SetText("Enter server IP :\n" + ip);
					}
					else if (server.accept(client) == sf::Socket::Done) client.setBlocking(true), state = 2, sdata[0] = limitless ? 1 : 0, sdata[1] = _size, client.send(sdata, 2);
				}
				else if (state == 2)
				{
					if (isServer) server.setBlocking(true);
					break;
				}

				window.Draw(info);

				window.Display();
			}

			gk::Gomoku game;
			game.SetStartSize(_size);
			game.SetLimitless(limitless);
			game.Reset();

			sw::View gridView = window.GetDefaultView();
			gridView.SetCenter(game.GetGameBounds().left + game.GetGameBounds().width / 2, game.GetGameBounds().top + game.GetGameBounds().height / 2);
			gridView.SetSize(game.GetGameBounds().width, game.GetGameBounds().height);
			gridView.SetScaleViewport(0.05f, 0.1f, 0.8f, 0.8f);
			gridView.SetMinZoom(5.f / (float)game.GetSize());
			gridView.SetMaxZoom(1.f);
			gridView.SetAutoLock(true);

			sw::Rectangle border(gridView.GetLocalBounds());
			border.SetTransform(sw::TopLeft, sw::Pixel, sw::World);
			border.SetOutline(1.f, sf::Color::Red);
			border.SetFillColor(sf::Color::Transparent);

			sw::Button victory(sf::FloatRect(55, 50, 40, 40), font, "");
			victory.SetOrigin(sw::Origin::Left);

			while (window.IsOpen())
			{
				sw::EventsData data = window.HandleEvents();

				if (data.close) return -1;
				else if (data.IsKeyPressed(sw::Key::Escape)) return 0;

				window.Clear(sf::Color(220, 179, 92));

				if (data.mouseWheelUp) gridView.Zoom(0.95f);
				if (data.mouseWheelDown) gridView.Zoom(1.f / 0.95f);

				if (data.IsKeyDown(sw::Key::Left) || data.IsKeyDown(sw::Key::Q))
					gridView.Move(-1.f * game.GetSize() / game.GetStartSize() * gridView.GetZoom(), 0.f);
				if (data.IsKeyDown(sw::Key::Right) || data.IsKeyDown(sw::Key::D))
					gridView.Move(1.f * game.GetSize() / game.GetStartSize() * gridView.GetZoom(), 0.f);
				if (data.IsKeyDown(sw::Key::Up) || data.IsKeyDown(sw::Key::Z))
					gridView.Move(0.f, -1.f * game.GetSize() / game.GetStartSize() * gridView.GetZoom());
				if (data.IsKeyDown(sw::Key::Down) || data.IsKeyDown(sw::Key::S))
					gridView.Move(0.f, 1.f * game.GetSize() / game.GetStartSize() * gridView.GetZoom());

				window.SetView(gridView);

				window.Draw(game);

				if (game.IsPlaying())
				{
					if (isServer)
					{
						sf::Vector2i point = game.GetClosestPoint(window.GetMousePosition(true));
						if (data.leftClick && game.PlayWhiteAt(window.GetMousePosition(true)))
						{
							if (game.WhitesWon())
							{
								victory.SetFillColor(sf::Color::Black), victory.SetTextColor(sf::Color::White), victory.SetText("White victory !");
								clock.restart();
							}

							client.setBlocking(true);
							std::cout << "server : envoie pose blanc " << point.x << " " << point.y << std::endl;
							sdata[0] = 0, sdata[1] = point.x, sdata[2] = point.y;
							sf::Socket::Status s = client.send(sdata, 3);
							if (s == sf::Socket::Status::Disconnected)
							{
								client.disconnect();
								server.close();
								window.SetView(window.GetDefaultView());
								return 0;
							}
						}

						client.setBlocking(false);
						status = client.receive(sdata, 3, size);
						if (status == sf::Socket::Done)
						{
							std::cout << "server : recu de client pose " << (sdata[0] == 1 ? "noir " : "blanc ") << (int)sdata[1] << " " << (int)sdata[2] << std::endl;
							if (sdata[0] == 1 && game.PlayBlackAt(sf::Vector2i(sdata[1], sdata[2])))
							{
								if (game.BlacksWon())
								{
									victory.SetFillColor(sf::Color::White), victory.SetTextColor(sf::Color::Black), victory.SetText("Black victory !");
									clock.restart();
								}

								std::cout << "server : envoie pose noir " << (int)sdata[1]  << " " << (int)sdata[2] << std::endl;
								client.setBlocking(true);
								sf::Socket::Status s = client.send(sdata, 3);
								if (s == sf::Socket::Status::Disconnected)
								{
									client.disconnect();
									server.close();
									window.SetView(window.GetDefaultView());
									return 0;
								}
							}
						}
						else if (status == sf::Socket::Disconnected)
						{
							client.disconnect();
							server.close();
							window.SetView(window.GetDefaultView());
							return 0;
						}
					}
					else
					{
						if (data.leftClick)
						{
							client.setBlocking(true);
							sf::Vector2i point = game.GetClosestPoint(window.GetMousePosition(true));
							std::cout << "client : envoie pose noir " << point.x << " " << point.y << std::endl;
							sdata[0] = 1, sdata[1] = point.x, sdata[2] = point.y;
							sf::Socket::Status s = client.send(sdata, 3);
							if (s == sf::Socket::Status::Disconnected)
							{
								client.disconnect();
								window.SetView(window.GetDefaultView());
								return 0;
							}
						}

						client.setBlocking(false);
						status = client.receive(sdata, 3, size);
						if (status == sf::Socket::Done)
						{
							std::cout << "client : recu de server pose " << (sdata[0] == 1 ? "noir " : "blanc ") << (int)sdata[1] << " " << (int)sdata[2] << std::endl;
							if (sdata[0] == 0)
							{
								if (game.PlayWhiteAt(sf::Vector2i(sdata[1], sdata[2])) && game.WhitesWon())
								{
									victory.SetFillColor(sf::Color::Black), victory.SetTextColor(sf::Color::White), victory.SetText("White victory !");
									clock.restart();
								}
							}
							else
							{
								if (game.PlayBlackAt(sf::Vector2i(sdata[1], sdata[2])) && game.BlacksWon())
								{
									victory.SetFillColor(sf::Color::White), victory.SetTextColor(sf::Color::Black), victory.SetText("Black victory !");
									clock.restart();
								}
							}
						}
						else if (status == sf::Socket::Disconnected)
						{
							client.disconnect();
							window.SetView(window.GetDefaultView());
							return 0;
						}
					}

					gridView.SetSize(game.GetGameBounds().width, game.GetGameBounds().height, true);
				}
				else if (clock.getElapsedTime().asSeconds() > 2)
				{
					game.Reset();
					gridView.SetSize(game.GetGameBounds().width, game.GetGameBounds().height);
				}

				gridView.SetCenter(game.GetGameBounds().left + game.GetGameBounds().width / 2, game.GetGameBounds().top + game.GetGameBounds().height / 2, true);
				gridView.SetMinZoom(5.f / (float)game.GetSize());

				window.SetView(window.GetDefaultView());

				window.Draw(border);
				if (game.GameWon()) window.Draw(victory);

				window.Display();
			}

			return -1;
		}

	private:
		sf::Font font;
		sf::Clock clock;

		bool isServer = false;

		sf::TcpListener server;
		sf::TcpSocket client;
		sf::Socket::Status status;

		char sdata[3] = { 0 };
		std::size_t size = 0;
};