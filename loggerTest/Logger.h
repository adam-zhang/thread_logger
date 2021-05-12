#ifndef __LOGGER__H
#define __LOGGER__H

#include <string>
#include <sstream>
#include <thread>
#include "Queue.h"
#include "Singleton.h"

class Logger : public Singleton<Logger, RealLock>
{
public:
	Logger();
	~Logger();
private:
	Queue<std::string> queue_;
	std::thread thread_;
public:
	void write(const std::string& text);
	template<typename T>
	void write(const std::string& note, const T& value)
	{
		std::stringstream ss;
		ss << note << ":" << value;		
		write(ss.str());
	}
	void quit();
private:
	void writeToFile();
	bool shouldQuit_ = false;
};
#endif//__LOGGER__H
