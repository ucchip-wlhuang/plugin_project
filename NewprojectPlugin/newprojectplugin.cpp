#include "newprojectplugin.h"
#include <wx/xrc/xmlres.h>
#include <wx/msgdlg.h> 

static NewprojectPlugin* thePlugin = NULL;

// Define the plugin entry point
CL_PLUGIN_API IPlugin* CreatePlugin(IManager* manager)
{
    if(thePlugin == NULL) {
	thePlugin = new NewprojectPlugin(manager);
    }
    return thePlugin;
}

CL_PLUGIN_API PluginInfo* GetPluginInfo()
{
    static PluginInfo info;
    info.SetAuthor(wxT("wlhuang"));
    info.SetName(wxT("NewprojectPlugin"));
    info.SetDescription(_(""));
    info.SetVersion(wxT("v1.0"));
    return &info;
}

CL_PLUGIN_API int GetPluginInterfaceVersion()
{
    return PLUGIN_INTERFACE_VERSION;
}

NewprojectPlugin::NewprojectPlugin(IManager* manager)
    : IPlugin(manager)
{
    m_longName = _("");
    m_shortName = wxT("NewprojectPlugin");
}

NewprojectPlugin::~NewprojectPlugin()
{
}

void NewprojectPlugin::CreateToolBar(clToolBar* toolbar)
{
    // You can add items to the main toolbar here
    wxUnusedVar(toolbar);
}

void NewprojectPlugin::CreatePluginMenu(wxMenu* pluginsMenu)
{
    wxMenu *menu = new wxMenu();
    
    wxMenuItem* item = new wxMenuItem(menu, XRCID("NewprojectPlugin"), _("New Project..."));
    menu->Append(item);
    item = new wxMenuItem(menu, XRCID("UnzipProject"), _("Unzip project.zip"));
    menu->Append(item);
    
    item = new wxMenuItem(pluginsMenu, wxID_ANY, wxT("New Project Plugin"));
    item->SetSubMenu(menu);
    pluginsMenu->Append(item);
    
    wxTheApp->Connect(XRCID("NewprojectPlugin"), wxEVT_COMMAND_MENU_SELECTED,
                         wxCommandEventHandler(NewprojectPlugin::OnWizard), NULL, (wxEvtHandler*)this);
    wxTheApp->Connect(XRCID("UnzipProject"), wxEVT_COMMAND_MENU_SELECTED,
                         wxCommandEventHandler(NewprojectPlugin::OnUnzip), NULL, (wxEvtHandler*)this);
    wxTheApp->Connect(XRCID("NewprojectPlugin"), wxEVT_UPDATE_UI,
                         wxUpdateUIEventHandler(NewprojectPlugin::OnNewProjectUI), NULL, (wxEvtHandler*)this);
}

void NewprojectPlugin::UnPlug()
{
    wxTheApp->Disconnect(XRCID("NewprojectPlugin"), wxEVT_COMMAND_MENU_SELECTED,
                         wxCommandEventHandler(NewprojectPlugin::OnWizard), NULL, (wxEvtHandler*)this);
    wxTheApp->Disconnect(XRCID("UnzipProject"), wxEVT_COMMAND_MENU_SELECTED,
                         wxCommandEventHandler(NewprojectPlugin::OnUnzip), NULL, (wxEvtHandler*)this);
    wxTheApp->Disconnect(XRCID("NewprojectPlugin"), wxEVT_UPDATE_UI,
                         wxUpdateUIEventHandler(NewprojectPlugin::OnNewProjectUI), NULL, (wxEvtHandler*)this);
}

void NewprojectPlugin::OnWizard(wxCommandEvent& event)
{
    wxFrame* mainFrame = EventNotifier::Get()->TopFrame();
    clNewProjectEvent newProjectEvent(wxEVT_NEW_PROJECT_WIZARD_SHOWING);
    newProjectEvent.SetEventObject(mainFrame);
    NewProjectWizard wiz(mainFrame, newProjectEvent.GetTemplates());
	if(wiz.RunWizard(wiz.GetFirstPage())) {
        ProjectData data = wiz.GetProjectData();
        CreateProject(data, wxEmptyString);
    }
}

void NewprojectPlugin::CreateProject(ProjectData& data, const wxString& workspaceFolder)
{
    wxString errMsg;
    if(clCxxWorkspaceST::Get()->GetName().IsEmpty()) {
        // create a workspace before creating a project
        //CreateWorkspace(data.m_name, data.m_path);
        bool res = clCxxWorkspaceST::Get()->CreateWorkspace(data.m_name, data.m_path, errMsg);
        if(!res) {
            wxMessageBox(errMsg, _("Error"), wxOK | wxICON_HAND);
            return;
        }
    }

    bool res = clCxxWorkspaceST::Get()->CreateProject(data.m_name, data.m_path,
                                                      data.m_srcProject->GetSettings()->GetProjectType(wxEmptyString),
                                                      workspaceFolder, false, errMsg);
    if(!res) {
        wxMessageBox(errMsg, _("Error"), wxOK | wxICON_HAND);
        return;
    }
    ProjectPtr proj = clCxxWorkspaceST::Get()->FindProjectByName(data.m_name, errMsg);

    // copy the project settings to the new one
    proj->SetSettings(data.m_srcProject->GetSettings());

    proj->SetProjectInternalType(data.m_srcProject->GetProjectInternalType());

    // now add the new project to the build matrix
    clCxxWorkspaceST::Get()->AddProjectToBuildMatrix(proj);
    ProjectSettingsPtr settings = proj->GetSettings();

    // set the compiler type
    ProjectSettingsCookie cookie;
    BuildConfigPtr bldConf = settings->GetFirstBuildConfiguration(cookie);
    BuilderPtr builder = BuildManagerST::Get()->GetBuilder(data.m_builderName);
    wxString outputfile;
    if(builder) { outputfile = builder->GetOutputFile(); }
    while(bldConf) {
#ifndef __WXMSW__
        // The -mwindows linker flag is at best useless in !MSW, and breaks linking in the latest g++ (fedora17)
        wxString linkoptions = bldConf->GetLinkOptions();
        if(linkoptions.Contains(wxT("-mwindows;"))) {
            linkoptions.Replace(wxT("-mwindows;"), wxT(""));
        }
        // And again, without the ';' to catch an end-of-line one
        else if(linkoptions.Contains(wxT(";-mwindows"))) {
            linkoptions.Replace(wxT(";-mwindows"), wxT(""));
        }

        bldConf->SetLinkOptions(linkoptions);
#endif
        // Update the compiler according to the user selection
        bldConf->SetCompilerType(data.m_cmpType);

        // Update the debugger according to the user selection
        bldConf->SetDebuggerType(data.m_debuggerType);

        // Update the build system
        bldConf->SetBuildSystem(data.m_builderName);

        // Set the output file name
        if(!outputfile.IsEmpty()) {
            bldConf->SetOutputFileName(wxEmptyString);
            bldConf->SetCommand(outputfile);
        }

        // Make sure that the build configuration has a project type associated with it
        if(bldConf->GetProjectType().IsEmpty()) { bldConf->SetProjectType(settings->GetProjectType(wxEmptyString)); }
        bldConf = settings->GetNextBuildConfiguration(cookie);
    }
    proj->SetSettings(settings);

    // copy the files as they appear in the source project
    proj->SetFiles(data.m_srcProject);

    // copy plugins data
    std::map<wxString, wxString> pluginsData;
    data.m_srcProject->GetAllPluginsData(pluginsData);
    proj->SetAllPluginsData(pluginsData);

    {
        // copy the actual files from the template directory to the new project path
        DirSaver ds;
        wxSetWorkingDirectory(proj->GetFileName().GetPath());

        // get list of files
        std::vector<wxFileName> files;
        data.m_srcProject->GetFilesAsVectorOfFileName(files);
        for(size_t i = 0; i < files.size(); i++) {
            wxFileName f(files.at(i));
            //construct new relative path
            wxString npath(f.GetPath());
            wxString project_path = data.m_srcProject->GetProjectPath();
            npath.Replace(project_path, ".");
            
            wxFileName nf(npath, f.GetFullName(), wxPATH_NATIVE);
            if(!wxFileName::DirExists(npath))
            {
                wxFileName::Mkdir(npath, wxS_DIR_DEFAULT, wxPATH_MKDIR_FULL);
            }
            wxCopyFile(f.GetFullPath(), nf.GetFullPath());
        }
    }

    wxString projectName = proj->GetName();
    //RetagProject(projectName, true);

    // Update the parser search paths
    //CallAfter(&Manager::UpdateParserPaths, false);

    // Notify that a project was added
    clCommandEvent evtProjectAdded(wxEVT_PROJ_ADDED);
    evtProjectAdded.SetString(projectName);
    evtProjectAdded.SetEventObject(this);
    EventNotifier::Get()->AddPendingEvent(evtProjectAdded);
}

void NewprojectPlugin::OnUnzip(wxCommandEvent& event)
{
    wxFrame* mainFrame = EventNotifier::Get()->TopFrame();
    ZipDialog zipdlg(mainFrame);
    zipdlg.ShowModal();
}


void NewprojectPlugin::OnNewProjectUI(wxUpdateUIEvent& event)
{
    event.Enable(!clCxxWorkspaceST::Get()->GetName().IsEmpty());
}