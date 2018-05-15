#ifndef ADDGOODSFORM_H
#define ADDGOODSFORM_H

#include <QWidget>
#include <QSqlQuery>
#include <QMessageBox>

namespace Ui {
class AddGoodsForm;
}

class AddGoodsForm : public QWidget
{
    Q_OBJECT

public:
    explicit AddGoodsForm(QWidget *parent = 0);
    ~AddGoodsForm();

private slots:
    void on_btn_commit_clicked();
    void on_btn_cancel_clicked();

private:
    Ui::AddGoodsForm *ui;
};

#endif // ADDGOODSFORM_H
