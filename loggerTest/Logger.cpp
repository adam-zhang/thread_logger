#include "Logger.h"
#include <chrono>
#include <iomanip>
#include <fstream>

using namespace std;
using namespace chrono;

Logger::Logger()
	: thread_(std::thread(Logger::writeToFile, this))
{
}

Logger::~Logger()
{
}

static string getFileName()
{
	auto current = system_clock::now();
	auto t = system_clock::to_time_t(current);
	stringstream ss;
	ss << put_time(localtime(&t), "%Y-%m-%d");
	return ss.str();
}

static int getMilliseconds(const time_point<system_clock>& current)
{
        auto s = duration_cast<seconds>(current.time_since_epoch()).count();
	auto millis = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
	return millis - s * 1000;
}

static string getTime()
{
	auto current = system_clock::now();
	auto t = system_clock::to_time_t(current);
	stringstream ss;
	ss << put_time(localtime(&t), "%H:%M:%S.") << setw(3) << setfill('0') << getMilliseconds(current);
	return ss.str();
}



static void writeToFile(const string& fileName, const string& text )
{
	ofstream file(fileName, ios_base::app);
	file << getTime() << "\t" << text << "\n";
}

void Logger::writeToFile()
{
	while(!shouldQuit_)
	{
		auto text = queue_.pop();
		::writeToFile(getFileName(), text);
	}
}

void Logger::write(const string& text)
{
	queue_.push(text);
}

void Logger::quit()
{
	shouldQuit_ = true;
}

