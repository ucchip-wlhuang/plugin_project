#include <wx/wx.h>
#include <wx/msgdlg.h>
#include <wx/sizer.h>
#include <wx/dir.h>
#include <wx/filefn.h> 
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/dialog.h>
#include "clZipReader.h"
#include "event_notifier.h"
#include "cl_standard_paths.h"
#include "file_logger.h"

enum
{
	ID_ZipPath = 2000,
	ID_ChooseBtn,
	ID_UnzipAll,
	ID_Unzip,
	ID_Help
};

class ZipDialog : public wxDialog
{
public:
	ZipDialog(wxWindow *parent);
	~ZipDialog();
	void OnShowChoice(wxCommandEvent& event);
	void OnTips(wxCommandEvent& event);
	void OnImport(wxCommandEvent& event);
	void OnUnzipAll(wxCommandEvent& event);
private:
	wxTextCtrl* zip_path;
	wxButton* btn_choose;
	wxButton* btn_ok;
	wxButton* btn_all;
	wxButton* btn_help;
};