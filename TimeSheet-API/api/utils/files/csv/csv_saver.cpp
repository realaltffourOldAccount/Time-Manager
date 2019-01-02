#include "csv_saver.h"

csv_saver::csv_saver()
{
}

csv_saver::~csv_saver()
{
}

void csv_saver::SetRaw(std::vector<std::vector<std::string>> r)
{
	m_Raw = r;
}

void csv_saver::Save(std::string path)
{
	using namespace std;

	ofstream stream(path);

	for (unsigned int i = 0; i < m_Raw.size(); i++) {
		string str;
		for (unsigned int j = 0; j < m_Raw[i].size(); j++) {
			bool isSpace = false;

			if (m_Raw[i][j].find(' ') != string::npos) {
				str.append("/");
				isSpace = true;
			}

			for (unsigned int m = 0; m < m_Raw[i][j].size(); m++) {
				if (m_Raw[i][j][m] == '"')
					str.append("/");
				str += m_Raw[i][j][m];
			}

			if (isSpace)
				str.append("/");

			str += ",";
		}
			str += "\n";
			stream << str;
	}
	stream.flush();
	stream.close();
}
