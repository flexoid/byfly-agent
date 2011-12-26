#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QtGui>
#include <QCloseEvent>

#include "ui_settingsdialog.h"
#include "settingsfile.h"

class SettingsDialog : public QWidget, private Ui::SettingsDialog {
    Q_OBJECT
    Q_DISABLE_COPY(SettingsDialog)
public:
    explicit SettingsDialog(QWidget *parent = 0);

protected:
    virtual void changeEvent(QEvent *e);
    virtual void closeEvent(QCloseEvent *event);

private slots:
    void okClicked();
    int applyClicked();
    void showPasswordChanged(int state);

signals:
    void settingsApplied();
    void okClickedSignal();
};

#endif // SETTINGSDIALOG_H
