#include "ranking_sys.h"

void Ranking_sys::Init(Log * log, DB_sys * api)
{
	_log = log;
	c_api = api;

	Rank newbie, beginner, moderate, expert, lizard, wizard, mastermind,
		grandmaster, god_like, god_mode, bots;

	newbie._name = "Newbie";
	newbie._min = 0;
	newbie._max = 50;
	

	beginner._name = "Beginner";
	beginner._min = 50;
	beginner._max = 100;

	moderate._name = "Moderate";
	moderate._min = 100;
	moderate._max = 550;

	expert._name = "Expert";
	expert._min = 550;
	expert._max = 650;

	lizard._name = "Lizard";
	lizard._min = 650;
	lizard._max = 10000;

	wizard._name = "Wizard";
	wizard._min = 1000;
	wizard._max = 1500;

	mastermind._name = "Mastermind";
	mastermind._min = 1500;
	mastermind._max = 2500;

	grandmaster._name = "GrandMaster";
	grandmaster._min = 2500;
	grandmaster._max = 5000;

	god_like._name = "God-Like";
	god_like._min = 5000;
	god_like._max = 5500;

	god_mode._name = "God-Mode";
	god_mode._min = 5500;
	god_mode._max = 10000;

	bots._name = "B.O.T.S.";
	bots._min = 10000;
	bots._max = 20000;

	_ranks.push_back(newbie);
	_ranks.push_back(beginner);
	_ranks.push_back(moderate);
	_ranks.push_back(expert);
	_ranks.push_back(lizard);
	_ranks.push_back(wizard);
	_ranks.push_back(mastermind);
	_ranks.push_back(grandmaster);
	_ranks.push_back(god_like);
	_ranks.push_back(god_mode);
	_ranks.push_back(bots);

	*_log << "[RANK_SYS] Successfully Initialized !";
}

void Ranking_sys::DeInit()
{
}

void Ranking_sys::calc()
{
	c_api->ReCalc();
	auto time = c_api->GetDataBase()->_TotalTimenotWaisted;
	float hour = time._hr + (time._min/10) + (time._sec/100);

	for (int i = 0; i < _ranks.size(); i++) {
		if (hour >= _ranks[i]._min && hour <= _ranks[i]._max) {
			rank = _ranks[i];
			break;
		}
	}
}
