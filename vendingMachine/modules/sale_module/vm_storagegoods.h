#ifndef VM_STORAGEGOODS_H
#define VM_STORAGEGOODS_H

#include <QWidget>

namespace Ui {
class Vm_StorageGoods;
}

class Vm_StorageGoods : public QWidget
{
    Q_OBJECT

public:
    explicit Vm_StorageGoods(QWidget *parent = 0);
    ~Vm_StorageGoods();

private:
    Ui::Vm_StorageGoods *ui;
};

#endif // VM_STORAGEGOODS_H
