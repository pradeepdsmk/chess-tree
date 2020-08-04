#pragma once

#include <queue>
#include <string>

class Log
{
	std::queue<std::string> q;
	static Log *thisRef;

	Log() {
		int i = 0;
		i++;
	} 
	
public:
	static void begin();
	static void add(std::string line);
	static void end();
	void push(std::string line);
	~Log();
};

