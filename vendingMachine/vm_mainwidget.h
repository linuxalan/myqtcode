#ifndef VM_MAINWIDGET_H
#define VM_MAINWIDGET_H

#include <QWidget>
#include <QGraphicsDropShadowEffect>
#include <QFileInfo>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>

namespace Ui {
class Vm_MainWidget;
}

class Vm_MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit Vm_MainWidget(QWidget *parent = 0);
    ~Vm_MainWidget();

    enum SELECTFORM{
        SALEGOODS,
        STORAGEGOODS,
        ADDGOODS,
        FINDGOODS,
        SETTING
    };

private slots:
    void on_btn_sale_goods_clicked();
    void on_btn_storage_goods_clicked();
    void on_btn_add_goods_clicked();
    void on_btn_find_goods_clicked();
    void on_btn_setting_clicked();

private:
    Ui::Vm_MainWidget *ui;
    void initMainWidget();
    void changeWidget(SELECTFORM destForm);
    void selectWidget(SELECTFORM destForm);
    void createDateBaseList();
    void connectSignalsToSlots();
};

#endif // VM_MAINWIDGET_H
