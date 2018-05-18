#ifndef VM_FINDGOODS_H
#define VM_FINDGOODS_H

#include <QWidget>

namespace Ui {
class Vm_FindGoods;
}

class Vm_FindGoods : public QWidget
{
    Q_OBJECT

public:
    explicit Vm_FindGoods(QWidget *parent = 0);
    ~Vm_FindGoods();

private:
    Ui::Vm_FindGoods *ui;
};

#endif // VM_FINDGOODS_H
