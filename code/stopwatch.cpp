#include "Stopwatch.h"
#include <time.h>

Stopwatch::Stopwatch()
{
	tStart = clock();
}

Stopwatch::~Stopwatch()
{

}

void Stopwatch::set_milisecond(int s)
{
	milisecond = s;
}

double Stopwatch::get_milisecond()
{
	return milisecond;
}

std::string Stopwatch::get_minute_second()
{
	int second = milisecond / 1000;
	int minute = second / 60;
	second = second % 60;
	return (minute < 10 ? "0" : "") + std::to_string(minute) + ":" 
		+ (second < 10 ? "0" : "") + std::to_string(second);
}

void Stopwatch::start_timing()
{
	tStart = clock();
}

void Stopwatch::timing()
{
	milisecond = (double)(clock() - tStart);
}