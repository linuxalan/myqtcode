#include "loginandregistform.h"
#include "ui_loginandregistform.h"

LoginAndRegistForm::LoginAndRegistForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginAndRegistForm)
{
    ui->setupUi(this);
}

LoginAndRegistForm::~LoginAndRegistForm()
{
    delete ui;
}
