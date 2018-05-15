#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFileInfo>
#include <QSqlDatabase>
#include <QSqlQuery>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

signals:
    void signalGetTypes();
    void signalInitSaleFormData();
    void signalFindGoods();

private slots:
    void on_btn_find_goods_clicked();
    void on_btn_add_goods_clicked();
    void on_btn_sale_goods_clicked();
    void on_btn_storage_goods_clicked();
    void on_btn_change_passwd_clicked();

private:
    Ui::Widget *ui;
    void init();
};

#endif // WIDGET_H
