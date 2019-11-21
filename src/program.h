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

	struct ACOData
	{
		unsigned short numberOfCities;
		unsigned short numberOfAnts;

		double alpha;
		double beta;
		double q;
		double ro;

		int tauMax;
		int short initialCity;
		int numberOfIterations;
	};

	struct ColorLine
	{
		sf::Vertex verticies[2];
		unsigned short numberOfVertices;
		sf::PrimitiveType type;
	};


	class Program
	{
	public:
		enum Mode {Moving, Adding};

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
		void ProcessUI();

		void drawCities();
		void drawRoutes();

		void drawBestRoute();

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

		void AntAlgorithmInitData();
		void AntAlgorithmRun();

		void AddNewCity();
		void AddNewCity(const sf::Vector2f& coords);
		void RebuildRoutes();

		void MarkUpBestRoute();

		std::vector<sf::CircleShape> _citiesShapes;
		std::vector<sf::VertexArray> _routesShapes;

		std::vector<ColorLine> _bestRouteShapes;

		std::vector<sf::Vector2f> _citiesPositions;

		ACO* _ants;
		ACOData _antsData;

		sf::ContextSettings _settings;
		sf::RenderWindow _window;
		sf::View _view;

		sf::Clock _deltaClock;
		sf::Clock _clock;

		std::string _windowName;
		sf::Vector2u _windowSize;

		Mode _mode;

		sf::Vector2f _startMousePos;

		bool _isMouseMoving;
		bool _isShowCities;
		bool _isShowRoutes;
		bool _isShowBestRoute;
	};

	sf::CircleShape createVertexShape(const sf::Vector2f& position, const float radius,
		const sf::Color color = sf::Color::Red, const sf::Color borderColor = sf::Color::White);

	std::vector<sf::Vector2f> getCitiesPositions(ACO* ants);
}
