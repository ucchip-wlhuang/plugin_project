#include "NewProjectWizardBase.h"

NewProjectWizardBase::NewProjectWizardBase(wxWindow* parent, wxWindowID id, const wxString& title, const wxBitmap& bmp,
                                           const wxPoint& pos, long style)
{
    Create(parent, id, title, wxNullBitmap, pos, style);

    m_wizardPageTemplate = new wxWizardPageSimple(this, NULL, NULL, wxNullBitmap);
    m_pages.push_back(m_wizardPageTemplate);

    wxBoxSizer* boxSizer383 = new wxBoxSizer(wxVERTICAL);
    m_wizardPageTemplate->SetSizer(boxSizer383);

    m_banner386 = new wxBannerWindow(m_wizardPageTemplate, wxID_ANY, wxTOP, wxDefaultPosition,
                                     wxDLG_UNIT(m_wizardPageTemplate, wxSize(-1, -1)), 0);
    m_banner386->SetBitmap(wxNullBitmap);
    m_banner386->SetText(_("New Project"), _("Select the project template from the list below"));
    m_banner386->SetGradient(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE),
                             wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
    m_banner386->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT));

    boxSizer383->Add(m_banner386, 0, wxALL | wxEXPAND, WXC_FROM_DIP(2));

    wxBoxSizer* boxSizer572 = new wxBoxSizer(wxVERTICAL);

    boxSizer383->Add(boxSizer572, 1, wxALL | wxEXPAND, WXC_FROM_DIP(5));

    m_dataviewTemplates =
        new wxDataViewCtrl(m_wizardPageTemplate, wxID_ANY, wxDefaultPosition,
                           wxDLG_UNIT(m_wizardPageTemplate, wxSize(-1, -1)), wxDV_ROW_LINES | wxDV_SINGLE);
    m_dataviewTemplates->SetFocus();

    m_dataviewTemplatesModel = new DVTemplatesModel;
    m_dataviewTemplatesModel->SetColCount(1);
    m_dataviewTemplates->AssociateModel(m_dataviewTemplatesModel.get());

    boxSizer572->Add(m_dataviewTemplates, 1, wxALL | wxEXPAND, WXC_FROM_DIP(5));

    m_dataviewTemplates->AppendIconTextColumn(_("Template"), m_dataviewTemplates->GetColumnCount(),
                                              wxDATAVIEW_CELL_INERT, WXC_FROM_DIP(450), wxALIGN_LEFT,
                                              wxDATAVIEW_COL_RESIZABLE);
    m_wizardPageDetails = new wxWizardPageSimple(this, NULL, NULL, wxNullBitmap);
    m_pages.push_back(m_wizardPageDetails);

    wxBoxSizer* boxSizer396 = new wxBoxSizer(wxVERTICAL);
    m_wizardPageDetails->SetSizer(boxSizer396);

    m_banner398 = new wxBannerWindow(m_wizardPageDetails, wxID_ANY, wxTOP, wxDefaultPosition,
                                     wxDLG_UNIT(m_wizardPageDetails, wxSize(-1, -1)), 0);
    m_banner398->SetBitmap(wxNullBitmap);
    m_banner398->SetText(_("New Project"), _("Set the project path and name"));
    m_banner398->SetGradient(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE),
                             wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
    m_banner398->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT));

    boxSizer396->Add(m_banner398, 0, wxALL | wxEXPAND, WXC_FROM_DIP(2));

    wxFlexGridSizer* flexGridSizer15 = new wxFlexGridSizer(0, 2, 0, 0);
    flexGridSizer15->SetFlexibleDirection(wxBOTH);
    flexGridSizer15->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);
    flexGridSizer15->AddGrowableCol(1);

    boxSizer396->Add(flexGridSizer15, 1, wxALL | wxEXPAND, WXC_FROM_DIP(5));

    m_staticText16 = new wxStaticText(m_wizardPageDetails, wxID_ANY, _("Project name:"), wxDefaultPosition,
                                      wxDLG_UNIT(m_wizardPageDetails, wxSize(-1, -1)), 0);

    flexGridSizer15->Add(m_staticText16, 0, wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, WXC_FROM_DIP(5));

    m_txtProjName = new wxTextCtrl(m_wizardPageDetails, wxID_ANY, wxT(""), wxDefaultPosition,
                                   wxDLG_UNIT(m_wizardPageDetails, wxSize(-1, -1)), 0);
    m_txtProjName->SetToolTip(_("Set the project name. A project name can contains A-Z, 0-9 and _ characters only"));
    m_txtProjName->SetFocus();
#if wxVERSION_NUMBER >= 3000
    m_txtProjName->SetHint(wxT(""));
#endif

    flexGridSizer15->Add(m_txtProjName, 0, wxLEFT | wxTOP | wxBOTTOM | wxEXPAND, WXC_FROM_DIP(5));

    m_staticText18 = new wxStaticText(m_wizardPageDetails, wxID_ANY, _("Project path:"), wxDefaultPosition,
                                      wxDLG_UNIT(m_wizardPageDetails, wxSize(-1, -1)), 0);

    flexGridSizer15->Add(m_staticText18, 0, wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, WXC_FROM_DIP(5));

    wxBoxSizer* boxSizer30 = new wxBoxSizer(wxHORIZONTAL);

    flexGridSizer15->Add(boxSizer30, 0, wxEXPAND, WXC_FROM_DIP(5));

    m_textCtrlProjectPath = new wxTextCtrl(m_wizardPageDetails, wxID_ANY, wxT(""), wxDefaultPosition,
                                           wxDLG_UNIT(m_wizardPageDetails, wxSize(-1, -1)), 0);
    m_textCtrlProjectPath->SetToolTip(_("Select the location of the project. The location must exist."));
#if wxVERSION_NUMBER >= 3000
    m_textCtrlProjectPath->SetHint(wxT(""));
#endif

    boxSizer30->Add(m_textCtrlProjectPath, 1, wxALL | wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, WXC_FROM_DIP(5));

    m_buttonBrowse = new wxButton(m_wizardPageDetails, wxID_ANY, _("..."), wxDefaultPosition,
                                  wxDLG_UNIT(m_wizardPageDetails, wxSize(-1, -1)), wxBU_EXACTFIT);
    m_buttonBrowse->SetToolTip(_("Browse for folder"));

    boxSizer30->Add(m_buttonBrowse, 0, wxTOP | wxBOTTOM | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL,
                    WXC_FROM_DIP(5));

    flexGridSizer15->Add(0, 0, 0, wxALL, WXC_FROM_DIP(5));

    m_cbSeparateDir = new wxCheckBox(m_wizardPageDetails, wxID_ANY, _("Create the project under a separate directory"),
                                     wxDefaultPosition, wxDLG_UNIT(m_wizardPageDetails, wxSize(-1, -1)), 0);
    m_cbSeparateDir->SetValue(false);
    m_cbSeparateDir->SetToolTip(_("When checked, codelite will place the project under a separate directory. The full "
                                  "path of the project file is displayed below"));

    flexGridSizer15->Add(m_cbSeparateDir, 0, wxALL | wxEXPAND, WXC_FROM_DIP(5));

    m_stxtFullFileName = new wxStaticText(m_wizardPageDetails, wxID_ANY, wxT(""), wxDefaultPosition,
                                          wxDLG_UNIT(m_wizardPageDetails, wxSize(-1, -1)), 0);

    boxSizer396->Add(m_stxtFullFileName, 0, wxALL | wxEXPAND | wxALIGN_LEFT, WXC_FROM_DIP(2));

    m_wizardPageToolchain = new wxWizardPageSimple(this, NULL, NULL, wxNullBitmap);
    m_pages.push_back(m_wizardPageToolchain);
    if(m_pages.size() > 1) {
        for(size_t i = 1; i < m_pages.size(); i++) {
            wxWizardPageSimple::Chain(m_pages.at(i - 1), m_pages.at(i));
        }
    }
    GetPageAreaSizer()->Add(m_pages.at(0));

    wxBoxSizer* boxSizer388 = new wxBoxSizer(wxVERTICAL);
    m_wizardPageToolchain->SetSizer(boxSizer388);

    m_banner390 = new wxBannerWindow(m_wizardPageToolchain, wxID_ANY, wxTOP, wxDefaultPosition,
                                     wxDLG_UNIT(m_wizardPageToolchain, wxSize(-1, -1)), 0);
    m_banner390->SetBitmap(wxNullBitmap);
    m_banner390->SetText(_("New Project"), _("Select the project toolchain"));
    m_banner390->SetGradient(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE),
                             wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
    m_banner390->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT));

    boxSizer388->Add(m_banner390, 0, wxALL | wxEXPAND, WXC_FROM_DIP(2));

    wxFlexGridSizer* flexGridSizer412 = new wxFlexGridSizer(0, 2, 0, 0);
    flexGridSizer412->SetFlexibleDirection(wxBOTH);
    flexGridSizer412->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);
    flexGridSizer412->AddGrowableCol(1);

    boxSizer388->Add(flexGridSizer412, 0, wxALL | wxEXPAND, WXC_FROM_DIP(5));

    m_staticText414 = new wxStaticText(m_wizardPageToolchain, wxID_ANY, _("Compiler:"), wxDefaultPosition,
                                       wxDLG_UNIT(m_wizardPageToolchain, wxSize(-1, -1)), 0);

    flexGridSizer412->Add(m_staticText414, 0, wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, WXC_FROM_DIP(5));

    wxArrayString m_choiceCompilerArr;
    m_choiceCompiler = new wxChoice(m_wizardPageToolchain, wxID_ANY, wxDefaultPosition,
                                    wxDLG_UNIT(m_wizardPageToolchain, wxSize(-1, -1)), m_choiceCompilerArr, 0);

    flexGridSizer412->Add(m_choiceCompiler, 0, wxALL | wxEXPAND | wxALIGN_CENTER_VERTICAL, WXC_FROM_DIP(5));

    m_staticText418 = new wxStaticText(m_wizardPageToolchain, wxID_ANY, _("Debugger:"), wxDefaultPosition,
                                       wxDLG_UNIT(m_wizardPageToolchain, wxSize(-1, -1)), 0);

    flexGridSizer412->Add(m_staticText418, 0, wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, WXC_FROM_DIP(5));

    wxArrayString m_choiceDebuggerArr;
    m_choiceDebugger = new wxChoice(m_wizardPageToolchain, wxID_ANY, wxDefaultPosition,
                                    wxDLG_UNIT(m_wizardPageToolchain, wxSize(-1, -1)), m_choiceDebuggerArr, 0);

    flexGridSizer412->Add(m_choiceDebugger, 0, wxALL | wxEXPAND | wxALIGN_CENTER_VERTICAL, WXC_FROM_DIP(5));

    m_staticText569 = new wxStaticText(m_wizardPageToolchain, wxID_ANY, _("Build System:"), wxDefaultPosition,
                                       wxDLG_UNIT(m_wizardPageToolchain, wxSize(-1, -1)), 0);

    flexGridSizer412->Add(m_staticText569, 0, wxALL | wxALIGN_CENTER_VERTICAL, WXC_FROM_DIP(5));

    wxArrayString m_choiceBuildSystemArr;
    m_choiceBuildSystem = new wxChoice(m_wizardPageToolchain, wxID_ANY, wxDefaultPosition,
                                       wxDLG_UNIT(m_wizardPageToolchain, wxSize(-1, -1)), m_choiceBuildSystemArr, 0);

    flexGridSizer412->Add(m_choiceBuildSystem, 0, wxALL | wxEXPAND, WXC_FROM_DIP(5));

    SetName(wxT("NewProjectWizardBase"));
    SetMinClientSize(wxSize(500, 400));
    SetSize(wxDLG_UNIT(this, wxSize(-1, -1)));
    if(GetSizer()) { GetSizer()->Fit(this); }
    if(GetParent()) {
        CentreOnParent(wxBOTH);
    } else {
        CentreOnScreen(wxBOTH);
    }
#if wxVERSION_NUMBER >= 2900
    if(!wxPersistenceManager::Get().Find(this)) {
        wxPersistenceManager::Get().RegisterAndRestore(this);
    } else {
        wxPersistenceManager::Get().Restore(this);
    }
#endif
    // Connect events
    this->Connect(wxEVT_WIZARD_PAGE_CHANGING, wxWizardEventHandler(NewProjectWizardBase::OnPageChanging), NULL, this);
    this->Connect(wxEVT_WIZARD_FINISHED, wxWizardEventHandler(NewProjectWizardBase::OnFinish), NULL, this);
    m_dataviewTemplates->Connect(wxEVT_COMMAND_DATAVIEW_SELECTION_CHANGED,
                                 wxDataViewEventHandler(NewProjectWizardBase::OnItemSelected), NULL, this);
    m_txtProjName->Connect(wxEVT_COMMAND_TEXT_UPDATED,
                           wxCommandEventHandler(NewProjectWizardBase::OnProjectNameChanged), NULL, this);
    m_textCtrlProjectPath->Connect(wxEVT_COMMAND_TEXT_UPDATED,
                                   wxCommandEventHandler(NewProjectWizardBase::OnProjectPathUpdated), NULL, this);
    m_buttonBrowse->Connect(wxEVT_COMMAND_BUTTON_CLICKED,
                            wxCommandEventHandler(NewProjectWizardBase::OnBrowseProjectPath), NULL, this);
    m_cbSeparateDir->Connect(wxEVT_COMMAND_CHECKBOX_CLICKED,
                             wxCommandEventHandler(NewProjectWizardBase::OnProjectNameChanged), NULL, this);
    m_choiceCompiler->Connect(wxEVT_COMMAND_CHOICE_SELECTED,
                              wxCommandEventHandler(NewProjectWizardBase::OnCompilerSelected), NULL, this);
    m_choiceDebugger->Connect(wxEVT_COMMAND_CHOICE_SELECTED,
                              wxCommandEventHandler(NewProjectWizardBase::OnDebuggerSelected), NULL, this);
}

NewProjectWizardBase::~NewProjectWizardBase()
{
    this->Disconnect(wxEVT_WIZARD_PAGE_CHANGING, wxWizardEventHandler(NewProjectWizardBase::OnPageChanging), NULL,
                     this);
    this->Disconnect(wxEVT_WIZARD_FINISHED, wxWizardEventHandler(NewProjectWizardBase::OnFinish), NULL, this);
    m_dataviewTemplates->Disconnect(wxEVT_COMMAND_DATAVIEW_SELECTION_CHANGED,
                                    wxDataViewEventHandler(NewProjectWizardBase::OnItemSelected), NULL, this);
    m_txtProjName->Disconnect(wxEVT_COMMAND_TEXT_UPDATED,
                              wxCommandEventHandler(NewProjectWizardBase::OnProjectNameChanged), NULL, this);
    m_textCtrlProjectPath->Disconnect(wxEVT_COMMAND_TEXT_UPDATED,
                                      wxCommandEventHandler(NewProjectWizardBase::OnProjectPathUpdated), NULL, this);
    m_buttonBrowse->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED,
                               wxCommandEventHandler(NewProjectWizardBase::OnBrowseProjectPath), NULL, this);
    m_cbSeparateDir->Disconnect(wxEVT_COMMAND_CHECKBOX_CLICKED,
                                wxCommandEventHandler(NewProjectWizardBase::OnProjectNameChanged), NULL, this);
    m_choiceCompiler->Disconnect(wxEVT_COMMAND_CHOICE_SELECTED,
                                 wxCommandEventHandler(NewProjectWizardBase::OnCompilerSelected), NULL, this);
    m_choiceDebugger->Disconnect(wxEVT_COMMAND_CHOICE_SELECTED,
                                 wxCommandEventHandler(NewProjectWizardBase::OnDebuggerSelected), NULL, this);
}
