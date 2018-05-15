#ifndef STORAGEFORM_H
#define STORAGEFORM_H

#include <QWidget>
#include <QSqlQuery>
#include <QMessageBox>
#include <QThread>

namespace Ui {
class StorageForm;
}

class StorageForm : public QWidget
{
    Q_OBJECT

public:
    explicit StorageForm(QWidget *parent = 0);
    ~StorageForm();

private slots:
    void on_cob_type_currentTextChanged(const QString &arg1);
    void on_btn_cancel_clicked();
    void doProcessSignalGetTypes();
    void on_cob_brand_currentTextChanged(const QString &arg1);
    void on_btn_commit_clicked();

private:
    Ui::StorageForm *ui;
    QString str1, str2;
};

#endif // STORAGEFORM_H
