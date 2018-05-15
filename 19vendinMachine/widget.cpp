#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    init();
}

Widget::~Widget()
{
    delete ui;
}

//--------------FUNCTIONS------------------------//
void Widget::init()
{
    connect(this ,SIGNAL(signalGetTypes()), ui->widget_storage_goods, SLOT(doProcessSignalGetTypes()));
    connect(this, SIGNAL(signalInitSaleFormData()), ui->widget_sale, SLOT(doProcessSignalInitSaleFormData()));
    connect(this, SIGNAL(signalFindGoods()), ui->widget_find, SLOT(doProcessSignalFindGoods()));
    ui->label->setText("出售商品");
    ui->widget_storage_goods->hide();
    ui->widget_add_goods->hide();
    ui->widget_find->hide();
    ui->widget_change_passwd->hide();

    QString file = "./vendingMachine.db";
    QFileInfo info(file);
    bool ret = info.exists();

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./vendingMachine.db");
    bool ok = db.open();
    if(ok)
    {
        if(!ret)
        {
            QSqlQuery query;
            query.exec("create table brands(id integer primary key autoincrement, type text, brand text, \
                       price real, sum integer default 0, sell integer default 0, last integer default 0)");
            query.exec("create table passwd(passwd text unique)");
            //query.exec("create trigger trigger1 after insert on brands(sum) begin insert into brands(last) values(new.sum); end;");
        }
        emit signalInitSaleFormData();
    }
    else
    {
        qDebug() << "数据库打开/创建失败！";
    }
}
//-------------END FUNCTIONS----------------------//

//--------------------SLOTS------------------------//
void Widget::on_btn_sale_goods_clicked()
{
    ui->label->setText("出售商品");
    ui->widget_storage_goods->hide();
    ui->widget_add_goods->hide();
    ui->widget_find->hide();
    ui->widget_change_passwd->hide();
    ui->widget_sale->show();
    emit signalInitSaleFormData();
}

void Widget::on_btn_storage_goods_clicked()
{
    ui->label->setText("商品入库");
    ui->widget_sale->hide();
    ui->widget_add_goods->hide();
    ui->widget_find->hide();
    ui->widget_change_passwd->hide();
    ui->widget_storage_goods->show();
    emit signalGetTypes();
}

void Widget::on_btn_add_goods_clicked()
{
    ui->label->setText("添加商品");
    ui->widget_sale->hide();
    ui->widget_storage_goods->hide();
    ui->widget_find->hide();
    ui->widget_change_passwd->hide();
    ui->widget_add_goods->show();
}

void Widget::on_btn_find_goods_clicked()
{
    ui->label->setText("查询商品");
    ui->widget_sale->hide();
    ui->widget_storage_goods->hide();
    ui->widget_add_goods->hide();
    ui->widget_change_passwd->hide();
    ui->widget_find->show();
    emit signalFindGoods();
}

void Widget::on_btn_change_passwd_clicked()
{
    ui->label->setText("修改密码");
    ui->widget_sale->hide();
    ui->widget_storage_goods->hide();
    ui->widget_add_goods->hide();
    ui->widget_find->hide();
    ui->widget_change_passwd->show();
}
//----------------------END SLOTS--------------------------//
