#ifndef VM_SALEGOODS_H
#define VM_SALEGOODS_H

#include <QWidget>

namespace Ui {
class Vm_SaleGoods;
}

class Vm_SaleGoods : public QWidget
{
    Q_OBJECT

public:
    explicit Vm_SaleGoods(QWidget *parent = 0);
    ~Vm_SaleGoods();

private:
    Ui::Vm_SaleGoods *ui;
};

#endif // VM_SALEGOODS_H
