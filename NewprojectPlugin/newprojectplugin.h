#ifndef __NewprojectPlugin__
#define __NewprojectPlugin__

#include "plugin.h"
#include "NewProjectWizard.h"
#include "globals.h"
#include "event_notifier.h"
#include "dirsaver.h"
#include "buildmanager.h"
#include "cl_standard_paths.h"
#include "clZipReader.h"
#include "ZipDialog.h"
#include <wx/dir.h>
#include <wx/filefn.h> 

class NewprojectPlugin : public IPlugin
{
public:
    NewprojectPlugin(IManager *manager);
    virtual ~NewprojectPlugin();

    //--------------------------------------------
    //Abstract methods
    //--------------------------------------------
    virtual void CreateToolBar(clToolBar* toolbar);
    /**
     * @brief Add plugin menu to the "Plugins" menu item in the menu bar
     */
    virtual void CreatePluginMenu(wxMenu *pluginsMenu);
    
    /**
     * @brief Unplug the plugin. Perform here any cleanup needed (e.g. unbind events, destroy allocated windows)
     */
    virtual void UnPlug();
    void OnWizard(wxCommandEvent& event);
    void OnUnzip(wxCommandEvent& event);
    void OnNewProjectUI(wxUpdateUIEvent& event);
    void CreateProject(ProjectData& data, const wxString& workspaceFolder);
};

#endif //NewprojectPlugin
