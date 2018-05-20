#ifndef VM_SALEGOODS_H
#define VM_SALEGOODS_H

#include <QWidget>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>

namespace Ui {
class Vm_SaleGoods;
}

class Vm_SaleGoods : public QWidget
{
    Q_OBJECT

protected:
    void showEvent(QShowEvent *event);

public:
    explicit Vm_SaleGoods(QWidget *parent = 0);
    ~Vm_SaleGoods();

private slots:
    void on_cob_type_currentTextChanged(const QString &arg1);
    void on_cob_brand_currentTextChanged(const QString &);
    void on_sp_num_valueChanged(int arg1);
    void on_btn_commit_clicked();

    void on_btn_cancel_clicked();

private:
    Ui::Vm_SaleGoods *ui;
    QString goodsType;
    QString goodsBrand;
    int sell = 0;
    int last = 0;
    int price = 0;
    int showLastNum = 0;
    void initComboType();
};

#endif // VM_SALEGOODS_H
