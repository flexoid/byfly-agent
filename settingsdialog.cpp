#include "settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QWidget(parent, Qt::Dialog){
    setupUi(this);
    this->setFixedSize(this->size());

    setWindowTitle(qApp->applicationName() + " - " + tr("Settings"));
    loginEdit->setText(SettingsFile::getLogin());
    passwordEdit->setText(SettingsFile::getPassword());
    updateIntervalBox->setValue(SettingsFile::getUpdateInterval());
    snapToEdgesBox->setChecked(SettingsFile::getSnapToEdges());
    alwaysOnTopBox->setChecked(SettingsFile::getAlwaysOnTop());
    QString lang = SettingsFile::getLanguage();
    if (lang == "ru")
        langBox->setCurrentIndex(0);
    else if (lang == "by")
        langBox->setCurrentIndex(1);

    if (SettingsFile::getAutorunState() == SettingsFile::autorunForAllUsers)
        autorunRadioButton_1->setChecked(true);
    else if (SettingsFile::getAutorunState() == SettingsFile::autorunForCurrentUser)
        autorunRadioButton_2->setChecked(true);
    else if (SettingsFile::getAutorunState() == SettingsFile::autorunDisabled)
        autorunRadioButton_3->setChecked(true);

    loginEdit->setValidator(new QRegExpValidator(QRegExp("([0-9]{4}\\-[0-9]{7}\\-[0-9]{2})|([0-9]{13})"), this));
    passwordEdit->setValidator(new QRegExpValidator(QRegExp("[0-9a-zA-Z]{4,}"), this));

    connect(showPasswordBox, SIGNAL(stateChanged(int)), this, SLOT(showPasswordChanged(int)));
    connect(applyButton, SIGNAL(clicked()), this, SLOT(applyClicked()));
    connect(okButton, SIGNAL(clicked()), this, SLOT(okClicked()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));

    show();
}

void SettingsDialog::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        retranslateUi(this);
        break;
    default:
        break;
    }
}

void SettingsDialog::closeEvent(QCloseEvent *event)
{
    QWidget::closeEvent(event);
}

void SettingsDialog::showPasswordChanged(int state)
{
    if (state)
        passwordEdit->setEchoMode(QLineEdit::Normal);
    else
        passwordEdit->setEchoMode(QLineEdit::Password);
}

void SettingsDialog::okClicked()
{
    if (applyClicked() != -1)
    {
        close();
        okClickedSignal();
    }
}

int SettingsDialog::applyClicked()
{
    int pos = 0;
    QString lineEditText = loginEdit->text();
    if (loginEdit->validator()->validate(lineEditText, pos) != QValidator::Acceptable)
    {
        QToolTip::showText(mapToGlobal(loginEdit->pos()) + QPoint(0,40), tr("Check if login was entered correctly"));
        return -1;
    }
    pos = 0;
    lineEditText = passwordEdit->text();
    if (passwordEdit->validator()->validate(lineEditText, pos) != QValidator::Acceptable)
    {
        QToolTip::showText(mapToGlobal(passwordEdit->pos()) + QPoint(0,40), tr("Check if password was entered correctly"));
        return -1;
    }

    SettingsFile::setLogin(loginEdit->text());
    SettingsFile::setPassword(passwordEdit->text());
    SettingsFile::setUpdateInterval(updateIntervalBox->value());
    SettingsFile::setSnapToEdges(QVariant(snapToEdgesBox->checkState()).toBool());
    SettingsFile::setAlwaysOnTop(QVariant(alwaysOnTopBox->checkState()).toBool());

    if (langBox->currentIndex() == 0)
        SettingsFile::setLanguage("ru");
    else if (langBox->currentIndex() == 1)
        SettingsFile::setLanguage("by");

    if (autorunRadioButton_1->isChecked())
        SettingsFile::setAutorunState(SettingsFile::autorunForAllUsers);
    else if (autorunRadioButton_2->isChecked())
        SettingsFile::setAutorunState(SettingsFile::autorunForCurrentUser);
    else if (autorunRadioButton_3->isChecked())
        SettingsFile::setAutorunState(SettingsFile::autorunDisabled);

    settingsApplied();

    return 0;
}
