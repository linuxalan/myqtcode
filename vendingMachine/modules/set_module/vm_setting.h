#ifndef VM_SETTING_H
#define VM_SETTING_H

#include <QWidget>
#include <QSqlQuery>
#include <QDebug>

namespace Ui {
class Vm_Setting;
}

class Vm_Setting : public QWidget
{
    Q_OBJECT

public:
    explicit Vm_Setting(QWidget *parent = 0);
    ~Vm_Setting();

private:
    Ui::Vm_Setting *ui;
};

#endif // VM_SETTING_H
