#include "vm_mainwidget.h"
#include "ui_vm_mainwidget.h"

Vm_MainWidget::Vm_MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Vm_MainWidget)
{
    ui->setupUi(this);
    initMainWidget();
    //开机显示售卖商品界面
    changeWidget(SALEGOODS);
    //第一次登录系统时创建数据库，新建商品信息表、用户信息表
    createDateBaseList();
    //连接信号与槽
    connectSignalsToSlots();
}

Vm_MainWidget::~Vm_MainWidget()
{
    delete ui;
}

//FUNCTIONS
void Vm_MainWidget::initMainWidget()
{
    //设置按钮阴影效果
    QGraphicsDropShadowEffect *shadow_sale_goods = new QGraphicsDropShadowEffect();
    shadow_sale_goods->setOffset(6, 6);
    shadow_sale_goods->setColor(Qt::black);
    shadow_sale_goods->setBlurRadius(8);
    ui->btn_sale_goods->setGraphicsEffect(shadow_sale_goods);

    QGraphicsDropShadowEffect *shadow_storage_goods = new QGraphicsDropShadowEffect();
    shadow_storage_goods->setOffset(6, 6);
    shadow_storage_goods->setColor(Qt::black);
    shadow_storage_goods->setBlurRadius(8);
    ui->btn_storage_goods->setGraphicsEffect(shadow_storage_goods);

    QGraphicsDropShadowEffect *shadow_add_goods = new QGraphicsDropShadowEffect();
    shadow_add_goods->setOffset(6, 6);
    shadow_add_goods->setColor(Qt::black);
    shadow_add_goods->setBlurRadius(8);
    ui->btn_add_goods->setGraphicsEffect(shadow_add_goods);

    QGraphicsDropShadowEffect *shadow_find_goods = new QGraphicsDropShadowEffect();
    shadow_find_goods->setOffset(6, 6);
    shadow_find_goods->setColor(Qt::black);
    shadow_find_goods->setBlurRadius(8);
    ui->btn_find_goods->setGraphicsEffect(shadow_find_goods);

    QGraphicsDropShadowEffect *shadow_setting = new QGraphicsDropShadowEffect();
    shadow_setting->setOffset(6, 6);
    shadow_setting->setColor(Qt::black);
    shadow_setting->setBlurRadius(8);
    ui->btn_setting->setGraphicsEffect(shadow_setting);
}

void Vm_MainWidget::changeWidget(SELECTFORM destForm)
{
    //隐藏所有页面
    ui->widget_SaleGoods->hide();
    ui->widget_StorageGoods->hide();
    ui->widget_AddGoods->hide();
    ui->widget_FindGoods->hide();
    ui->widget_Setting->hide();
    //选择页面显示
    selectWidget(destForm);
}

void Vm_MainWidget::selectWidget(SELECTFORM destForm)
{
    switch (destForm) {
    case SALEGOODS:
        ui->widget_SaleGoods->show();
        ui->label->setText("出售商品");
        break;
    case STORAGEGOODS:
        ui->widget_StorageGoods->show();
        ui->label->setText("商品入库");
        break;
    case ADDGOODS:
        ui->widget_AddGoods->show();
        ui->label->setText("添加商品");
        break;
    case FINDGOODS:
        ui->widget_FindGoods->show();
        ui->label->setText("商品查询");
        break;
    case SETTING:
        ui->widget_Setting->show();
        ui->label->setText("用户设置");
        break;
    default:
        break;
    }
}

void Vm_MainWidget::createDateBaseList()
{
    QString file = "./vendingMachine.db";
    QFileInfo info(file);
    bool exist = info.exists();

    QSqlDatabase datebase = QSqlDatabase::addDatabase("QSQLITE");
    datebase.setDatabaseName(file);

    if(datebase.open())
    {
        if(!exist)
        {
            QSqlQuery query;
            //新建商品信息表
            QString cmd = "create table goodsinfo(id integer primary key autoincrement, type text, brand text, price real default 0, \
                    sum integer default 0, sell integet default 0, last integer default 0)";

            //新建用户信息表
            QString cmd1 = "create table userinfo(id integer primary key autoincrement, name text unique, passwd text)";
            if(query.exec(cmd))
                qDebug() << "create table goodsinfo success";
            if(query.exec(cmd1))
                qDebug() << "create table userinfo success";

            QString cmd2 = "insert into goodsinfo(type, brand) values('请选择类型', '请选择品牌')";
            if(query.exec(cmd2))
            {
                qDebug() << "insert first record success";
            }
        }else
        {
            qDebug() << "table exist";
        }
    }else{
        qDebug() << "open datebase failed";
    }
}

void Vm_MainWidget::connectSignalsToSlots()
{

}
//END FUNCTIONS

//SLOTS
void Vm_MainWidget::on_btn_sale_goods_clicked()
{
    changeWidget(SALEGOODS);
}

void Vm_MainWidget::on_btn_storage_goods_clicked()
{
    changeWidget(STORAGEGOODS);
}

void Vm_MainWidget::on_btn_add_goods_clicked()
{
    changeWidget(ADDGOODS);
}

void Vm_MainWidget::on_btn_find_goods_clicked()
{
    changeWidget(FINDGOODS);
}

void Vm_MainWidget::on_btn_setting_clicked()
{
    changeWidget(SETTING);
}
//END SLOTS
