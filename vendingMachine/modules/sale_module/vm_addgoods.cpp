#include "vm_addgoods.h"
#include "ui_vm_addgoods.h"

Vm_AddGoods::Vm_AddGoods(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Vm_AddGoods)
{
    ui->setupUi(this);
}

Vm_AddGoods::~Vm_AddGoods()
{
    delete ui;
}
