#include "timesheet_view.h"

TimeSheetView::TimeSheetView(wxWindow* pID, API_driver* api, wxSize size)
    : wxPanel(pID, wxID_ANY, wxDefaultPosition, size) {
    c_api = api;
    // Parent size: 594, 468
    // SetSize(wxSize(594, 468));
    // SetSize(this->GetParent()->GetParent()->GetClientSize());

    CreateControls();
    ShowData();
}

void TimeSheetView::CreateControls() {
    mGrid =
        new wxGrid(this, wxID_ANY, wxDefaultPosition, wxSize(GetClientSize()));
    mGrid->ShowScrollbars(wxScrollbarVisibility::wxSHOW_SB_ALWAYS,
                          wxScrollbarVisibility::wxSHOW_SB_ALWAYS);
    mGrid->EnableEditing(false);
    mGrid->CreateGrid(0, 13);

    mGrid->SetColLabelValue(0, "ID");
    mGrid->SetColLabelValue(1, "Date");
    mGrid->SetColLabelValue(2, "Enter");
    mGrid->SetColLabelValue(3, "Studied");
    mGrid->SetColLabelValue(4, "CP");
    mGrid->SetColLabelValue(5, "Side Proj");
    mGrid->SetColLabelValue(6, "Exercise");
    mGrid->SetColLabelValue(7, "Games");
    mGrid->SetColLabelValue(8, "Is School");
    mGrid->SetColLabelValue(9, "Exit");
    mGrid->SetColLabelValue(10, "Avlble Time");
    mGrid->SetColLabelValue(11, "Waisted Time");
    mGrid->SetColLabelValue(12, "Not Waisted");

    mGrid->HideRowLabels();
}

void TimeSheetView::ShowData() {
    if (mGrid->GetNumberRows() > 0)
        mGrid->DeleteRows(0, mGrid->GetNumberRows());

    if (c_api->DB()->IsDataEmpty() == true) return;
    auto db = c_api->DB()->GetDataBase()->_entries;
    mGrid->AppendRows(db->size());
    for (int i = 0; i < db->size(); i++) {
        auto row = (*db)[i];
        mGrid->SetCellValue(i, 0, to_string(row._ID));
        mGrid->SetCellValue(i, 1, row._date.get());
        mGrid->SetCellValue(i, 2, row._EnterTime.get());
        mGrid->SetCellValue(i, 3, row._StudiedTime.get());
        mGrid->SetCellValue(i, 4, row._CPTime.get());
        mGrid->SetCellValue(i, 5, row._SideProjTime.get());
        mGrid->SetCellValue(i, 6, row._ExerciseTime.get());
        mGrid->SetCellValue(i, 7, row._GamesTime.get());
        mGrid->SetCellValue(i, 8, to_string(row._isSchool));
        mGrid->SetCellValue(i, 9, row._ExitTime.get());
        mGrid->SetCellValue(i, 10, row._AvlbleTime.get());
        mGrid->SetCellValue(i, 11, row._WaistedTime.get());
        mGrid->SetCellValue(i, 12, row._NWaistedTime.get());
    }
    mGrid->AutoSizeColumns();
    // mGrid->ShowScrollbars(wxScrollbarVisibility::wxSHOW_SB_ALWAYS,
    // wxScrollbarVisibility::wxSHOW_SB_ALWAYS);
}
