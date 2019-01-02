#ifndef _H_TIMER_H_
#define _H_TIMER_H_

#pragma once
#include <chrono>
#include <string>

struct Timer
{
	std::string _msg = "";
	std::chrono::system_clock::time_point _start, _end, _getVal;
	std::chrono::duration<float> duration;

	void Start()
	{
		_start = std::chrono::high_resolution_clock::now();
	}

	float get()
	{
		std::chrono::duration<float> duration;
		_getVal = std::chrono::high_resolution_clock::now();
		duration = _getVal - _start;

		float ms = duration.count() * 1000;
		return ms;
	}

	~Timer()
	{
		_end = std::chrono::high_resolution_clock::now();
		duration = _end - _start;

		float ms = duration.count() * 1000;

		_msg = "[TIMER] Timer Destruct at: ";
		_msg += std::to_string(ms);
	}
	void Terminate(std::string msg = "")
	{
		_end = std::chrono::high_resolution_clock::now();
		duration = _end - _start;

		float ms = duration.count() * 1000;

		_msg = "[TIMER] ";
		_msg += msg;
		_msg += " , At ";
		_msg += std::to_string(get());
		_msg += "ms";
	}
};
#endif // !_H_TIMER_H_
