#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class csv_saver
{
public:
	csv_saver();
	~csv_saver();

	void SetRaw(std::vector<std::vector<std::string> >);
	void Save(std::string);

private:
	std::vector<std::vector<std::string> > m_Raw;
};
