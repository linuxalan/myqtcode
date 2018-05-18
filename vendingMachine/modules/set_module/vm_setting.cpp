#include "vm_setting.h"
#include "ui_vm_setting.h"

Vm_Setting::Vm_Setting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Vm_Setting)
{
    ui->setupUi(this);
}

Vm_Setting::~Vm_Setting()
{
    delete ui;
}
