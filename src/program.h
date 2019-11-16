#pragma once

#include <SFML/Graphics.hpp>

#include "ACO.h"

#define DEFAULT_WINDOW_WIDTH 1200
#define DEFAULT_WINDOW_HEIGHT 720

namespace AntOptimization
{
	inline int numberOfRoutes(unsigned n)
	{
		if (n > 1)
			return n + numberOfRoutes(n - 1);
		else
			return 1;
	}

	class Program
	{
	public:

		enum Modes {Default, Adding};

		Program(const sf::Vector2u& windowSize, const std::string& windowName);
		~Program() {}

		void Run();

		void setWindowSize(float width, float height) { _windowSize.x = width; _windowSize.y = height; }
		void setWindowName(const std::string& name) { _windowName = name; }

		static float zoomAmount;
		static float moveAmount;

		sf::Vector2f getMouseCoordinates();
	private:
		void InitializeWindowContext();
		void InitializeResources();

		void Render();
		void drawUI();

		void drawCities();
		void drawRoutes();

		void ProcessEvents();
			   
		void zoomViewAt(const sf::Vector2i& pixel, const float& zoom);
		void moveViewTo(const sf::Vector2f& displacement);

		// Handlers
		void HandleEvent_Closed(const sf::Event& event);
		void HandleEvent_Resized(const sf::Event& event);
		void HandleEvent_MouseButtonPressed(const sf::Event& event);
		void HandleEvent_MouseButtonReleased(const sf::Event& event);
		void HandleEvent_MouseMoved(const sf::Event& event);
		void HandleEvent_MouseWheelScrolled(const sf::Event& event);

		std::vector<sf::CircleShape> _cities;
		std::vector<sf::VertexArray> _routes;

		ACO* _ants;

		sf::ContextSettings _settings;
		sf::RenderWindow _window;
		sf::View _view;

		sf::Clock _deltaClock;
		sf::Clock _clock;

		std::string _windowName;
		sf::Vector2u _windowSize;

		unsigned _numberOfCities;

		Modes _mode;

		sf::Vector2f _startMousePos;
		bool _isMouseMoving;
	};

	sf::CircleShape createVertexShape(const sf::Vector2f& position, const float radius,
		const sf::Color color = sf::Color::Red, const sf::Color borderColor = sf::Color::White);

	std::vector<sf::Vector2f> getCitiesPositions(ACO* ants);
}
