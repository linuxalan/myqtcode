#include "vm_storagegoods.h"
#include "ui_vm_storagegoods.h"

Vm_StorageGoods::Vm_StorageGoods(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Vm_StorageGoods)
{
    ui->setupUi(this);
}

Vm_StorageGoods::~Vm_StorageGoods()
{
    delete ui;
}
