#include "csv_loaders.h"
#include <wx/file.h>

csv_loaders::csv_loaders()
{
}


csv_loaders::~csv_loaders()
{
}

vector<vector<string>> csv_loaders::Load(string path)
{
	vector<vector<string>> res;

	wxString raw;
	wxFile file(path);
	file.ReadAll(&raw);

	vector<string> raw2;

	string _row = "";
	for (int i = 0; i < raw.size(); i++) {
		if (raw[i] == '\n') {
			raw2.push_back(_row);
			_row.clear();
		}
		else _row.push_back(raw[i]);
	}


	for (int i = 0; i < raw2.size(); i++) {
		auto row = raw2[i];
		auto row_data = split(row, ",");
		res.push_back(row_data);
	}

	return res;
}
