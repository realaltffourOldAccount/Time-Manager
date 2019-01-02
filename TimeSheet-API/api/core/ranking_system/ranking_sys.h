#pragma once
#include <vector>
#include <math.h>
#include <algorithm>
#include "../../defines.h"
#include "../../core/database_system/db_sys.h"

struct Rank {
	std::string _name;
	float _min = 0;
	float _max = 0;

	bool operator==(const Rank &rank) {
		if (_name == rank._name &&
			_min == rank._min &&
			_max == rank._max)
			return true;
		return false;
	}
};

class Ranking_sys
{
public:
	void Init(Log* log, DB_sys *api);
	void DeInit();

	void calc();

	Rank rank;
	vector<Rank> _ranks;
private:
	// 11 ranks

	DB_sys *c_api = nullptr;
	Log *_log = nullptr;
};

