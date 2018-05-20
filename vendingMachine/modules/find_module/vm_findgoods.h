#ifndef VM_FINDGOODS_H
#define VM_FINDGOODS_H

#include <QWidget>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>

namespace Ui {
class Vm_FindGoods;
}

class Vm_FindGoods : public QWidget
{
    Q_OBJECT

protected:
    void showEvent(QShowEvent *event);

public:
    explicit Vm_FindGoods(QWidget *parent = 0);
    ~Vm_FindGoods();

private slots:
    void on_cob_type_currentTextChanged(const QString &arg1);
    void on_btn_commit_clicked();
    void on_btn_cancel_clicked();

private:
    Ui::Vm_FindGoods *ui;
    QString goodsType;
    QString goodsBrand;
    int goodsPrice = 0;
    int goodsSum   = 0;
    int goodsSell  = 0;
    int goodsLast  = 0;
    void initComboType();
    void findFromDateBase();
    void showGoodsInformation();
};

#endif // VM_FINDGOODS_H
