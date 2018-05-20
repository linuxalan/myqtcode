#ifndef VM_STORAGEGOODS_H
#define VM_STORAGEGOODS_H

#include <QWidget>
#include <QDebug>
#include <QSqlQuery>
#include <QMessageBox>

namespace Ui {
class Vm_StorageGoods;
}

class Vm_StorageGoods : public QWidget
{
    Q_OBJECT

public:
    explicit Vm_StorageGoods(QWidget *parent = 0);
    ~Vm_StorageGoods();

protected:
    void showEvent(QShowEvent *event);

private slots:
    void on_cob_type_currentTextChanged(const QString &arg1);
    void on_cob_brand_currentTextChanged(const QString &);
    void on_btn_commit_clicked();
    void on_btn_cancel_clicked();

private:
    Ui::Vm_StorageGoods *ui;
    void initComboType();
    void updateGoodsNum();
};

#endif // VM_STORAGEGOODS_H
