#ifndef SALEFORM_H
#define SALEFORM_H

#include <QWidget>
#include <QSqlQuery>
#include <QMessageBox>

namespace Ui {
class SaleForm;
}

class SaleForm : public QWidget
{
    Q_OBJECT

public:
    explicit SaleForm(QWidget *parent = 0);
    ~SaleForm();

private slots:
    void doProcessSignalInitSaleFormData();

    void on_cob_type_currentTextChanged(const QString &arg1);

    void on_cob_brand_currentTextChanged(const QString &arg1);

    void on_sp_num_valueChanged(int arg1);

    void on_btn_commit_clicked();

    void on_btn_cancel_clicked();

private:
    Ui::SaleForm *ui;
    int lastGoods;
    int tmp_lastGoods;
    int sellGoods;
    QString str1,str2;
};

#endif // SALEFORM_H
