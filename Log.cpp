#include "Log.h"

Log *Log::thisRef = nullptr;

void Log::begin() {
	if (Log::thisRef == nullptr) {
		Log::thisRef = new Log();
	}
}

void Log::add(std::string line) {
	Log::thisRef->push(line);
}

void Log::push(std::string line) {
	q.push(line);
	if (q.size() > 100) {
		q.pop();
	}
}

void Log::end() {
	if (Log::thisRef == nullptr) {
		return;
	}

	delete Log::thisRef;
}

Log::~Log() {
	int i = 0;
	i++;
}