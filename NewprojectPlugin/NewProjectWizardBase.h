
#ifndef _CODELITE_LITEEDITOR_WXCRAFTER_BASE_CLASSES_H
#define _CODELITE_LITEEDITOR_WXCRAFTER_BASE_CLASSES_H

#include <wx/settings.h>
#include <wx/xrc/xmlres.h>
#include <wx/xrc/xh_bmp.h>
#include <wx/panel.h>
#include <wx/artprov.h>
#include <wx/sizer.h>
#include <wx/splitter.h>
#include <wx/choice.h>
#include <wx/arrstr.h>
#include <wx/imaglist.h>
#include <wx/bitmap.h>
#include <map>
#include <wx/icon.h>
#include <wx/dialog.h>
#include <wx/iconbndl.h>
#include <wx/dataview.h>
#include "clThemedListCtrl.h"
#include <wx/button.h>
#include <wx/filepicker.h>
#include <wx/scrolwin.h>
#include <wx/statbmp.h>
#include <wx/commandlinkbutton.h>
#include <wx/simplebook.h>
#include <wx/toolbar.h>
#include "clToolBar.h"
#include "clThemedSplitterWindow.h"
#include <wx/treectrl.h>
#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/wizard.h>
#include <vector>
#include <wx/bannerwindow.h>
#include "dvtemplatesmodel.h"
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/stc/stc.h>
#if wxVERSION_NUMBER >= 2900
#include <wx/persist.h>
#include <wx/persist/toplevel.h>
#include <wx/persist/bookctrl.h>
#include <wx/persist/treebook.h>
#endif

#ifdef WXC_FROM_DIP
#undef WXC_FROM_DIP
#endif
#if wxVERSION_NUMBER >= 3100
#define WXC_FROM_DIP(x) wxWindow::FromDIP(x, NULL)
#else
#define WXC_FROM_DIP(x) x
#endif

class NewProjectWizardBase : public wxWizard
{
protected:
    std::vector<wxWizardPageSimple*> m_pages;

    wxWizardPageSimple* m_wizardPageTemplate;
    wxBannerWindow* m_banner386;
    wxDataViewCtrl* m_dataviewTemplates;
    wxObjectDataPtr<DVTemplatesModel> m_dataviewTemplatesModel;

    wxWizardPageSimple* m_wizardPageDetails;
    wxBannerWindow* m_banner398;
    wxStaticText* m_staticText16;
    wxTextCtrl* m_txtProjName;
    wxStaticText* m_staticText18;
    wxTextCtrl* m_textCtrlProjectPath;
    wxButton* m_buttonBrowse;
    wxCheckBox* m_cbSeparateDir;
    wxStaticText* m_stxtFullFileName;
    wxWizardPageSimple* m_wizardPageToolchain;
    wxBannerWindow* m_banner390;
    wxStaticText* m_staticText414;
    wxChoice* m_choiceCompiler;
    wxStaticText* m_staticText418;
    wxChoice* m_choiceDebugger;
    wxStaticText* m_staticText569;
    wxChoice* m_choiceBuildSystem;

protected:
    virtual void OnPageChanging(wxWizardEvent& event) { event.Skip(); }
    virtual void OnFinish(wxWizardEvent& event) { event.Skip(); }
    virtual void OnItemSelected(wxDataViewEvent& event) { event.Skip(); }
    virtual void OnProjectNameChanged(wxCommandEvent& event) { event.Skip(); }
    virtual void OnProjectPathUpdated(wxCommandEvent& event) { event.Skip(); }
    virtual void OnBrowseProjectPath(wxCommandEvent& event) { event.Skip(); }
    virtual void OnCompilerSelected(wxCommandEvent& event) { event.Skip(); }
    virtual void OnDebuggerSelected(wxCommandEvent& event) { event.Skip(); }

public:
    wxBannerWindow* GetBanner386() { return m_banner386; }
    wxDataViewCtrl* GetDataviewTemplates() { return m_dataviewTemplates; }
    wxWizardPageSimple* GetWizardPageTemplate() { return m_wizardPageTemplate; }
    wxBannerWindow* GetBanner398() { return m_banner398; }
    wxStaticText* GetStaticText16() { return m_staticText16; }
    wxTextCtrl* GetTxtProjName() { return m_txtProjName; }
    wxStaticText* GetStaticText18() { return m_staticText18; }
    wxTextCtrl* GetTextCtrlProjectPath() { return m_textCtrlProjectPath; }
    wxButton* GetButtonBrowse() { return m_buttonBrowse; }
    wxCheckBox* GetCbSeparateDir() { return m_cbSeparateDir; }
    wxStaticText* GetStxtFullFileName() { return m_stxtFullFileName; }
    wxWizardPageSimple* GetWizardPageDetails() { return m_wizardPageDetails; }
    wxBannerWindow* GetBanner390() { return m_banner390; }
    wxStaticText* GetStaticText414() { return m_staticText414; }
    wxChoice* GetChoiceCompiler() { return m_choiceCompiler; }
    wxStaticText* GetStaticText418() { return m_staticText418; }
    wxChoice* GetChoiceDebugger() { return m_choiceDebugger; }
    wxStaticText* GetStaticText569() { return m_staticText569; }
    wxChoice* GetChoiceBuildSystem() { return m_choiceBuildSystem; }
    wxWizardPageSimple* GetWizardPageToolchain() { return m_wizardPageToolchain; }
    NewProjectWizardBase(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("New Project Wizard"), const wxBitmap& bmp = wxNullBitmap, const wxPoint& pos = wxDefaultPosition, long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER);
    wxWizardPageSimple* GetFirstPage() const { if(!m_pages.empty()) return m_pages.at(0); return NULL; }
    virtual ~NewProjectWizardBase();
};

#endif