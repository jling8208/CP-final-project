#pragma once

#ifndef STOPWATCH_H
#define STOPWATCH_H
#include <SDL.h>
#include <time.h>
#include <string>

class Stopwatch
{
public:
	Stopwatch();
	~Stopwatch();
	void set_milisecond(int s);
	double get_milisecond();
	std::string get_minute_second();
	void start_timing();
	void timing();

private:
	double milisecond = 0;
	clock_t tStart;
};

#endif