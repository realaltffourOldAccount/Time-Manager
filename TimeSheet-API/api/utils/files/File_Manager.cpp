#include "File_Manager.h"



File_Manager::File_Manager()
{
}


File_Manager::~File_Manager()
{
}

void File_Manager::Write(string file, vector<string> _data)
{
	ofstream stream(file);

	for (unsigned int i = 0; i < _data.size(); i++)
		stream << _data[i] + "\n";

	stream.close();
}

void File_Manager::Read(string file, vector<string>* _data)
{
	ifstream stream(file);

	string temp;
	while (stream >> temp)
		_data->push_back(temp);

	stream.close();
}
