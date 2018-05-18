#ifndef VM_ADDGOODS_H
#define VM_ADDGOODS_H

#include <QWidget>

namespace Ui {
class Vm_AddGoods;
}

class Vm_AddGoods : public QWidget
{
    Q_OBJECT

public:
    explicit Vm_AddGoods(QWidget *parent = 0);
    ~Vm_AddGoods();

private:
    Ui::Vm_AddGoods *ui;
};

#endif // VM_ADDGOODS_H
