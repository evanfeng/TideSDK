/**
 * Copyright (c) 2012 - 2014 TideSDK contributors 
 * http://www.tidesdk.org
 * Includes modified sources under the Apache 2 License
 * Copyright (c) 2008 - 2012 Appcelerator Inc
 * Refer to LICENSE for details of distribution and use.
 **/

#include <iostream>
#include <string>
#include <vector>
#include <gtk/gtk.h>
#include <glib.h>
#include <tideutils/file_utils.h>
#include <tideutils/boot_utils.h>
#include <tideutils/application.h>

using namespace TideUtils;
using TideUtils::Application;
using TideUtils::SharedApplication;
using TideUtils::KComponentType;
using std::string;
using std::vector;
class Installer;
class Job;
#include "job.h"

class Installer
{
    public:
    static Installer* instance;
    static string applicationPath;
    static string systemRuntimeHome;
    static string userRuntimeHome;
    static string updateFilename;

    Installer(vector<Job*>, int);
    ~Installer();
    void ResizeWindow(int width, int height);
    void CreateIntroView();
    void CreateProgressView();
    void CreateInfoBox(GtkWidget*);
    GdkPixbuf* GetApplicationPixbuf(int maxDimension);
    GtkWidget* GetIcon();
    GtkWidget* GetApplicationIcon();

    void StartInstallProcess();
    void StartDownloading();
    void StartInstalling();
    void UpdateProgress();
    void ShowError();
    void Finish();

    GtkWidget* GetWindow() { return this->window; }
    void SetWindow(GtkWidget* w) { this->window = w; }
    void Cancel();

    enum Stage
    {
        SUCCESS = 0,
        PREDOWNLOAD,
        DOWNLOADING,
        PREINSTALL,
        INSTALLING,
        CANCEL_REQUEST,
        SUDO_REQUEST,
        CANCELLED,
        ERROR
    };

    Stage GetStage()
    {
        return this->stage;
    }

    void SetStage(Stage stage)
    {
        this->stage = stage;
    }

    void SetError(string error)
    {
        this->error = error;
        this->stage = ERROR;
    }

    Job* CurrentJob()
    {
        return this->currentJob;
    }

    void SetCurrentJob(Job* job)
    {
        this->currentJob = job;
    }

    vector<Job*>& GetJobs()
    {
        return this->jobs;
    }

    int GetType()
    {
        return this->installType;
    }


    private:
    vector<Job*> jobs;
    SharedApplication app;
    int installType;
    Stage stage;

    Job* currentJob;
    string error;
    GtkWidget* window;
    GtkWidget* progressBar;
    GtkWidget* downloadingLabel;
    GtkWidget* installCombo;
    bool running;
    GThread* download_thread;

};
