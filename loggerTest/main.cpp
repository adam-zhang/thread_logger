#include <iostream>
#include <thread>
#include "Logger.h"

using namespace std;

int main(int argc, char** argv)
{
	Logger::instance().write("Hello");
	Logger::instance().write("Hello", "World");
	std::this_thread::sleep_for(2000ms);
	Logger::instance().quit();
	std::this_thread::sleep_for(100ms);
	return 0;
}
