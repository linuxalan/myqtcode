#include "vm_findgoods.h"
#include "ui_vm_findgoods.h"

Vm_FindGoods::Vm_FindGoods(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Vm_FindGoods)
{
    ui->setupUi(this);
}

Vm_FindGoods::~Vm_FindGoods()
{
    delete ui;
}
