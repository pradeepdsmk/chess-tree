#pragma once

#include <string>
#include "Destinations.h"
#include "Constants.h"

namespace chess {	

	class Destinations;

	class Square
	{
	public:
		char piece;
		unsigned char row;
		unsigned char col;

		Destinations* dst;		

		Square(unsigned char _row, unsigned char _col);

		const std::string name();

		~Square();
	};

}