#ifndef VM_ADDGOODS_H
#define VM_ADDGOODS_H

#include <QWidget>
#include <QMessageBox>
#include <QSqlQuery>
#include <QDebug>
#include <QRegExpValidator>
#include <QRegExp>

namespace Ui {
class Vm_AddGoods;
}

class Vm_AddGoods : public QWidget
{
    Q_OBJECT

public:
    explicit Vm_AddGoods(QWidget *parent = 0);
    ~Vm_AddGoods();

protected:
    void showEvent(QShowEvent *event);

private slots:
    void on_btn_commit_clicked();
    void on_btn_cancel_clicked();

private:
    Ui::Vm_AddGoods *ui;
    QString goodsType;
    QString goodsBrand;
    QString goodsPrice;
    void initAddGoods();
    void insertGoodsInDateBase();
};

#endif // VM_ADDGOODS_H
