#include <wx/wx.h>
#include <wx/aui/aui.h>

#include "config.h"

#include "api/core/login_system/login_sys.h"
#include "api/core/database_system/db_sys.h"

#include "api/driver/API_driver.h"

#include "api/utils/time/Time.h"

#include "dlgs/login_dlg.h"
#include "dlgs/dashboard_dlg.h"

//#define WX_TEST // for wx testing

//#define API_LOGIN_SYS_TEST
//#define API_TIME_SYS_TEST
//#define API_DB_SYS_TEST
//#define API_DRIVER_TEST

//#define API_STRESS_TEST

#define MAIN_APP // main app

/*
auto log = driver.getLogQueue();
for (int i = 0; i < log.size(); i++)
cout << log[i] << endl;

*/

#ifdef MAIN_APP

class Program : public wxApp
{
public:
	virtual bool OnInit();
	virtual int OnExit();

	API_driver* driver = nullptr;
};
wxIMPLEMENT_APP(Program);

bool Program::OnInit() {
	LoginDlg *dlg = new LoginDlg(nullptr);
	dlg->Show();

	return true;
}

int Program::OnExit() {
	if (!driver)
	delete driver;

	return 0;
}

#endif // MAIN_APP

#ifdef API_LOGIN_SYS_TEST

int main() {
	std::string user, pass;
	cout << "User:";
	cin >> user;
	cout << "Pass:";
	cin >> pass;
	createDir("data/");
	Log *log = new Log();
	LoginSys login;
	login.Init(log, user, pass);
	cout << log->get() << endl;
	system("PAUSE");
}

#endif // DEBUG

#ifdef API_TIME_SYS_TEST

int main() {
	Time time;
	time.set("14:32:00");

	//cout << time.get() << endl;

	//time.addMins(60);

	Time_PAM time2;
	
	time2.add(time._hour, time._min);

	cout << "12Hr format: " << time2.get() << endl;

	cout << "24Hr format: " << time.get() << endl;

	cin.get();
}

#endif // API_TIME_SYS_TEST

#ifdef API_DB_SYS_TEST

int main() {
	Log *log = new Log();
	DB_sys sys;
	sys.Init(log);
	//sys.CreateEmpty("admin", "admin");
	
	sys.Load("admin", "admin");

	cout << log->get() << endl;

	sys.ReCalc();

	cout << "Total Time: " << sys.GetDataBase()->_TotalTime.get() << endl;
	cout << "Total Time not waisted: " << sys.GetDataBase()->_TotalTimenotWaisted.get() << endl;
	cout << "Time Waisted: " << sys.GetDataBase()->_TotalTimeWaisted.get() << endl;
	cout << "" << endl;

	sys.Save();

	sys.IsThere();

	cout << (*log).get() << endl;

	cin.get();
}

#endif // API_DB_SYS_TEST

#ifdef API_DRIVER_TEST

int main() {

	API_driver driver;
	driver.Init();
	driver.CreateDB("admin", "admin");
	driver.LoadDB("admin", "admin");

	auto log = driver.getLogQueue();

	for (int i = 0; i < log.size(); i++)
		cout << log[i] << endl;

	driver.DeInit();
	cin.get();
	return 0;
}

#endif

#ifdef API_STRESS_TEST

void list() {
	cout << "Welcome To the TimeSheet API stress test" << endl;
	cout << "1. Create n Entries" << endl;
	cout << "2. Load Entries" << endl;
	cout << "3. Show Log" << endl;
	cout << "99. Exit " << endl;
	cout << "> ";
}
void createNEnteries(API_driver* api, int n) {
	system("CLS");
	cout << "Creating Entries . . . " << n << endl;

	Timer time_create;
	time_create.Start();

	for (int i = 0; i < n; i++) {
		Entry entry;
		entry._ID = i;
		entry._EnterTime.set(0, 0, 0);
		entry._ExitTime.set(0,0,0);
		api->DB()->AddEntry(entry);
		cout << "Creating Entry Number " << i+1 << endl;
		system("CLS");
	}

	auto create_duration = time_create.get();

	cout << "Created Entries . . . " << endl;
	cout << "================================" << endl;
	cout << "Results: " << endl;
	cout << "Created " << n << " Entries in " << create_duration << "ms" << endl;
	cout << "Speed: " << (1000*n)/create_duration << " Entry/sec" << endl;
	cout << "================================" << endl;

	cout << "Calculating these Entries . . . " << endl;

	Timer timer;
	timer.Start();

	api->DB()->ReCalc();

	auto duration = timer.get();
	
	cout << "================================" << endl;
	cout << "Results: " << endl;
	cout << "Calculated " << n << " in " << duration << "ms . . . " << endl;
	/*
		ms		ents
		5		100
		1000	?
	*/

	cout << "Speed: " << (1000*n)/duration << " Entry/sec" << endl;
	cout << "================================" << endl;
	timer.Terminate();

	cout << "Finished Calculating Entries . . ." << endl;
	cout << "Saving Entries . . . " << endl;
	Timer timer2;
	timer2.Start();

	api->DB()->Save();

	auto duration2 = timer2.get();

	cout << "Finished Saving . . . " << endl;
	cout << "================================" << endl;
	cout << "Results:" << endl;
	cout << "Saved " << n << " Entries in " << duration2 << endl;
	cout << "Speed: " << (1000*n)/duration2 << " Entry/sec" << endl;
	cout << "================================" << endl;

	system("PAUSE");
	system("CLS");
}
void loadEntries(API_driver* api, string user, string pass) {
	system("CLS");
	cout << "Loading Entries . . ." << endl;

	Timer time;
	time.Start();

	api->LoadDB(user, pass);

	auto duration = time.get();

	cout << "Loaded Entries . . . " << endl;
	cout << "================================" << endl;
	cout << "Results: " << endl;
	cout << "Loaded " << api->DB()->GetDataBase()->_entries->size() << " Entries in " << duration << "ms" << endl;
	cout << "Speed: " << (1000*api->DB()->GetDataBase()->_entries->size())/duration << " Entry/sec" << endl;
	cout << "================================" << endl;
	system("PAUSE");
	system("CLS");

	//api->DeInit();
	//api->Init();
}
int main() {

	API_driver driver;
	driver.Init();

	int input = 0;
	list();
	cin >> input;
	string str1, str2;
	while (input != 99) {
		
		auto log = driver.getLogQueue();
		switch (input)
		{
		case 1:
			int n;
			cout << "Entires Count: ";
			cin >> n;
			createNEnteries(&driver, n);
			break;
		case 2:
			cout << "User: ";
			cin >> str1;
			cout << "Pass: " ;
			cin >> str2;

			loadEntries(&driver, str1, str2);
			break;
		case 3:
			cout << "All the Log:" << endl;
			for (int i = 0; i < log.size(); i++)
				cout << log[i] << endl;
			break;
		case 99:
			driver.DeInit();
			exit(0);
			break;

		default:
			break;
		}

		list();
		cin >> input;
	}

	driver.DeInit();

	return 0;
}

#endif // API_STRESS_TEST

#ifdef WX_TEST

class MyFrame : public wxFrame
{
public:
	MyFrame(wxWindow* parent) : wxFrame(parent, -1, _("wxAUI Test"),
		wxDefaultPosition, wxSize(800, 600),
		wxDEFAULT_FRAME_STYLE)
	{
		// notify wxAUI which frame to use
		m_mgr.SetManagedWindow(this);

		// create several text controls
		wxTextCtrl* text1 = new wxTextCtrl(this, -1, _("Pane 1 - sample text"),
			wxDefaultPosition, wxSize(200, 150),
			wxNO_BORDER | wxTE_MULTILINE);

		wxTextCtrl* text2 = new wxTextCtrl(this, -1, _("Pane 2 - sample text"),
			wxDefaultPosition, wxSize(200, 150),
			wxNO_BORDER | wxTE_MULTILINE);

		wxTextCtrl* text3 = new wxTextCtrl(this, -1, _("Main content window"),
			wxDefaultPosition, wxSize(200, 150),
			wxNO_BORDER | wxTE_MULTILINE);

		// add the panes to the manager
		m_mgr.AddPane(text1, wxLEFT, wxT("Pane Number One"));
		m_mgr.AddPane(text2, wxBOTTOM, wxT("Pane Number Two"));
		m_mgr.AddPane(text3, wxCENTER);

		// tell the manager to "commit" all the changes just made
		m_mgr.Update();
	}

	~MyFrame()
	{
		// deinitialize the frame manager
		m_mgr.UnInit();
	}

private:
	wxAuiManager m_mgr;
};

// our normal wxApp-derived class, as usual
class MyApp : public wxApp
{
public:

	bool OnInit()
	{
		wxFrame* frame = new MyFrame(NULL);
		SetTopWindow(frame);
		frame->Show();
		return true;
	}
};

DECLARE_APP(MyApp);
IMPLEMENT_APP(MyApp);
#endif // WX_TEST