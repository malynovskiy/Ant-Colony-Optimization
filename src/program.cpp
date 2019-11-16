#include <imgui.h>
#include <imgui-SFML.h>

#include <iostream>

#include "program.h"
#include "UIData.h"

#define ITERATIONS		(int) 5

#define NUMBEROFANTS	(int) 8
#define NUMBEROFCITIES	(int) 8

	// if (ALPHA == 0) { stochastic search & sub-optimal route }
#define ALPHA			(double) 0.5
// if (BETA  == 0) { sub-optimal route }
#define BETA			(double) 0.8
// Estimation of the suspected best route.
#define Q				(double) 80
// Pheromones evaporation. 
#define RO				(double) 0.2
// Maximum pheromone random number.
#define TAUMAX			(int) 2

#define INITIALCITY		(int) 0

namespace AntOptimization
{

	float Program::zoomAmount = 1.1f;
	float Program::moveAmount = 20.0f;

	Program::Program(const sf::Vector2u& windowSize, const std::string& windowName) :
		_settings(),
		_windowSize(windowSize),
		_windowName(windowName),
		_window(sf::VideoMode(windowSize.x, windowSize.y), windowName, sf::Style::Default),
		_view(),
		_cities(),
		_routes(),
		_ants(nullptr),
		_mode(Modes::Default)
	{
		InitializeWindowContext();
		ImGui::SFML::Init(_window);
		InitializeResources();
	}

	void Program::Run()
	{
		//maybe move to another place
		std::vector<sf::Vector2f> citiesCoordinates = getCitiesPositions(_ants);

		for (const auto cityCoordinates : citiesCoordinates)
			_cities.push_back(createVertexShape(cityCoordinates, UIData::citiesRadius, UIData::citiesColor, UIData::citiesBorderColor));
		//need to implement routes visualizations

		for (size_t i = 0, currentRoute = 0; i < NUMBEROFCITIES - 1; ++i)
		{
			for (size_t j = i+1; j < NUMBEROFCITIES; ++j)
			{
				_routes.push_back(sf::VertexArray(sf::Lines, 2));

				_routes[currentRoute][0].position = sf::Vector2f({ citiesCoordinates[i].x, citiesCoordinates[i].y});
				_routes[currentRoute][1].position = sf::Vector2f({ citiesCoordinates[j].x, citiesCoordinates[j].y });

				currentRoute++;
			}
		}

		while (_window.isOpen())
		{
			ProcessEvents();
			Render();
		}
	}

	void Program::InitializeWindowContext()
	{
		_window.setActive(true);

		_view.setCenter(sf::Vector2f(0.0f, 0.0f));
		_view.setSize(static_cast<float>(_windowSize.x), static_cast<float>(_windowSize.y));

		_window.setView(_view);
	}

	void Program::InitializeResources()
	{
		_ants = new ACO(NUMBEROFANTS, NUMBEROFCITIES, ALPHA, BETA, Q, RO, TAUMAX, INITIALCITY);
		_ants->init();

		_ants->setCITYPOSITION(0, 10, 10);
		_ants->setCITYPOSITION(1, 100, 100);
		_ants->setCITYPOSITION(2, 200, 100);
		_ants->setCITYPOSITION(3, 100, 300);
		_ants->setCITYPOSITION(4, 150, 50);
		_ants->setCITYPOSITION(5, 100, 10);
		_ants->setCITYPOSITION(6, 200, 200);
		_ants->setCITYPOSITION(7, 200, 300);

		for (size_t i = 0; i < NUMBEROFCITIES - 1; ++i)
			for (size_t j = i + 1; j < NUMBEROFCITIES; ++j)
				_ants->connectCITIES(i, j);
	}

	void Program::Render()
	{
		ImGui::SFML::Update(_window, _deltaClock.restart());

		_window.clear();

		drawUI();
		drawRoutes();
		drawCities();

		ImGui::SFML::Render(_window);

		_window.display();
	}

	void Program::drawUI()
	{
		ImGui::Begin("UI");

		ImGui::SetWindowPos({ _windowSize.x - UIData::UIBlockWidth - UIData::UIBlockPadding, UIData::UIBlockPadding });
		ImGui::SetWindowSize({ UIData::UIBlockWidth, 0.0f });

		if (ImGui::Button("Moving"))
		{
			ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
			_mode = Modes::Default;
		}

		if (ImGui::Button("Add new vertex"))
		{
			ImGui::SetMouseCursor(ImGuiMouseCursor_Arrow);
			_mode = Modes::Adding;
		}

		ImGui::SliderFloat("Vertex radius", &UIData::citiesRadius, 1.0f, 50.0f);

		ImGui::End();
	}


	void Program::ProcessEvents()
	{
		sf::Event event;

		static sf::Vector2f startMousePos;
		static bool isMouseMoving = false;

		while (_window.pollEvent(event))
		{
			ImGui::SFML::ProcessEvent(event);

			switch (event.type)
			{
			case sf::Event::Closed:
			{
				_window.close();
			}
			break;

			case sf::Event::Resized:
			{
				_windowSize = _window.getSize();

				sf::FloatRect resizedArea(-(event.size.width / 2.0f), -(event.size.height / 2.0f),
					static_cast<float>(event.size.width), static_cast<float>(event.size.height));
				_window.setView(sf::View(resizedArea));

				std::cout << " - Window has been resised -> (" << _windowSize.x << ", " << _windowSize.y << ")" << std::endl;
			}
			break;

			case sf::Event::MouseButtonPressed:
			{	
				if (event.mouseButton.button == sf::Mouse::Button::Left	&& event.mouseButton.x < _windowSize.x - UIData::UIBlockWidth)
				{
					if (_mode == Modes::Default)
					{
						isMouseMoving = true;
						startMousePos = getMouseCoordinates();
					}
					else if(_mode == Modes::Adding)
					{
						// add new city
						// rebuild routes
					}
				}
			}
			break;

			case  sf::Event::MouseButtonReleased:
			{	
				if (event.mouseButton.button == sf::Mouse::Button::Left && _mode == Modes::Default)
				{
					isMouseMoving = false;
				}
			}
			break;

			case sf::Event::MouseMoved:
			{
				if (!isMouseMoving)
					break;
				
				if (_mode != Modes::Default)
					break;

				const sf::Vector2f newMousePos = getMouseCoordinates();
				const sf::Vector2f deltaPos = startMousePos - newMousePos;
				moveViewTo(deltaPos);

				startMousePos = getMouseCoordinates();	
			}
			break;

			case sf::Event::MouseWheelScrolled:
			{
				if (event.mouseWheelScroll.delta > 0)
					zoomViewAt({ event.mouseWheelScroll.x, event.mouseWheelScroll.y }, (1.0f / zoomAmount));
				else if (event.mouseWheelScroll.delta < 0)
					zoomViewAt({ event.mouseWheelScroll.x, event.mouseWheelScroll.y }, zoomAmount);
			}
			break;
			};
		}
	}

	sf::Vector2f Program::getMouseCoordinates()
	{
		return _window.mapPixelToCoords(sf::Mouse::getPosition(_window));
	}

	void Program::drawCities()
	{
		for (const auto city : _cities)
			_window.draw(city);
	}

	void Program::drawRoutes()
	{
		for (const auto route : _routes)
			_window.draw(route);
	}

	void Program::zoomViewAt(const sf::Vector2i& pixel, const float& zoom)
	{
		const sf::Vector2f beforeCoord(_window.mapPixelToCoords(pixel));

		sf::View view(_window.getView());
		view.zoom(zoom);

		_window.setView(view);

		const sf::Vector2f afterCoord(_window.mapPixelToCoords(pixel));
		const sf::Vector2f offsetCoords(beforeCoord - afterCoord);

		view.move(offsetCoords);
		_window.setView(view);
		_view = view;
	}
	
	void Program::moveViewTo(const sf::Vector2f& displacement)
	{
		sf::View view(_window.getView());

		view.move(displacement);

		_window.setView(view);
		_view = view;
	}

	sf::CircleShape createVertexShape(const sf::Vector2f& position, const float radius,
		const sf::Color color, const sf::Color borderColor)
	{
		sf::CircleShape vertex(radius);
		vertex.setPosition(position.x - radius, position.y - radius);

		vertex.setFillColor(color);
		vertex.setOutlineColor(borderColor);
		vertex.setOutlineThickness(radius / 10.0f);

		return vertex;
	}

	std::vector<sf::Vector2f> getCitiesPositions(ACO* ants)
	{
		std::vector<sf::Vector2f> cityPositions;
		for (size_t i = 0; i < NUMBEROFCITIES; ++i)
			cityPositions.push_back(sf::Vector2f( ants->getCityCoordinateX(i), ants->getCityCoordinateY(i) ));

		return cityPositions;
	}
}
