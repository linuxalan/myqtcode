#include "vm_salegoods.h"
#include "ui_vm_salegoods.h"

Vm_SaleGoods::Vm_SaleGoods(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Vm_SaleGoods)
{
    ui->setupUi(this);
}

Vm_SaleGoods::~Vm_SaleGoods()
{
    delete ui;
}
