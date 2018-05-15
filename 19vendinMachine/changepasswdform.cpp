#include "changepasswdform.h"
#include "ui_changepasswdform.h"

ChangePasswdForm::ChangePasswdForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChangePasswdForm)
{
    ui->setupUi(this);
}

ChangePasswdForm::~ChangePasswdForm()
{
    delete ui;
}
