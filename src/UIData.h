#pragma once

#include <SFML/Graphics.hpp>

namespace AntOptimization
{
	class UIData
	{
	public:
		static UIData& getInstance() { return _instance; }
		
		static float UIBlockWidth;
		static float UIBlockPadding;

		static float citiesRadius;
		static sf::Color citiesColor;
		static sf::Color citiesBorderColor;
	private:
		UIData();
		static UIData _instance;
	};
}