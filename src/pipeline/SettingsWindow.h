#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QDialog>

#include "pipeline/Module.h"

namespace Ui {
    class SettingsWindow;
}

class SettingsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsWindow(mtv::Module* module);
    ~SettingsWindow();

private:
    Ui::SettingsWindow *ui;
    mtv::Module *module;

    void refreshSettings();
};

#endif // SETTINGSWINDOW_H
