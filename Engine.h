#pragma once

namespace chess {
	class Engine
	{
	public:
		void onMove(const std::string& input, std::string& output);
	};
}