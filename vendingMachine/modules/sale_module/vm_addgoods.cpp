#include "vm_addgoods.h"
#include "ui_vm_addgoods.h"

Vm_AddGoods::Vm_AddGoods(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Vm_AddGoods)
{
    ui->setupUi(this);
    initAddGoods();
}

Vm_AddGoods::~Vm_AddGoods()
{
    delete ui;
}

//FUNCTIONS
void Vm_AddGoods::initAddGoods()
{
    //商品价格输入框只能输入数字
    QRegExp rx("[0-9]{7}");
    QRegExpValidator *rev = new QRegExpValidator(rx, this);
    ui->le_price->setValidator(rev);
}

void Vm_AddGoods::insertGoodsInDateBase()
{
    QSqlQuery query;
    //判重复
    QString cmd = "select * from goodsinfo where type = :type";
    query.prepare(cmd);
    query.bindValue(":type", goodsType);
    if(query.exec())
    {
        while(query.next())
        {
            if(query.value("brand").toString() == goodsBrand)
            {
                QMessageBox::warning(this, tr("Warning"), tr("Already Have This Goods"), QMessageBox::Ok);
                return;
            }
        }
    }else{
        qDebug() << "select type failed";
    }

    //插入记录
    cmd = "insert into goodsinfo(type, brand, price) values(:type, :brand, :price)";
    query.prepare(cmd);
    query.bindValue(":type", goodsType);
    query.bindValue(":brand", goodsBrand);
    query.bindValue(":price", goodsPrice);
    if(query.exec())
    {
        QMessageBox::information(this, tr("Information"), tr("Add Goods Success!"), QMessageBox::Ok);
        ui->le_type->clear();
        ui->le_brand->clear();
        ui->le_price->clear();
    }else
    {
        qDebug() << "insert goods failed";
        return;
    }
}
//END FUNCTIONS

//SLOTS
void Vm_AddGoods::on_btn_commit_clicked()
{
    goodsType  = ui->le_type->text();
    goodsBrand = ui->le_brand->text();
    goodsPrice = ui->le_price->text();
    //输入框必须有内容
    if(goodsType.isEmpty()
    || goodsBrand.isEmpty()
    || goodsPrice.isEmpty())
    {
        QMessageBox::warning(this, tr("Warning"), tr("Goodsinfo Incomplete"), QMessageBox::Ok);
        return;
    }

    //插入数据库
    insertGoodsInDateBase();
}

void Vm_AddGoods::on_btn_cancel_clicked()
{
    ui->le_type->clear();
    ui->le_brand->clear();
    ui->le_price->clear();
}
//END SLOTS

//EVENTS
void Vm_AddGoods::showEvent(QShowEvent *)
{
    ui->le_type->clear();
    ui->le_brand->clear();
    ui->le_price->clear();
}
//END EVENTS
