#include "vm_storagegoods.h"
#include "ui_vm_storagegoods.h"

Vm_StorageGoods::Vm_StorageGoods(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Vm_StorageGoods)
{
    ui->setupUi(this);
}

Vm_StorageGoods::~Vm_StorageGoods()
{
    delete ui;
}

//FUCTIONS
void Vm_StorageGoods::initComboType()
{
    //更新cob_type
    ui->cob_type->clear();
    QSqlQuery query;
    QStringList typeList;
    QString cmd = "select distinct(type) from goodsinfo";
    if(query.exec(cmd))
    {
        while(query.next())
        {
            QString str = query.value("type").toString();
            typeList << str;
        }
        ui->cob_type->addItems(typeList);
    }else{
        qDebug() << "set type failed";
    }
}

void Vm_StorageGoods::updateGoodsNum()
{
    //获取已入库商品数及商品库存
    int goodsSum;
    int goodsLast;
    QSqlQuery query;
    QString goodsType = ui->cob_type->itemText(ui->cob_type->currentIndex());
    QString goodsBrand = ui->cob_brand->itemText(ui->cob_brand->currentIndex());
    int goodsNum = ui->sp_num->value();
    qDebug() << goodsType;
    qDebug() << goodsBrand;
    QString cmd = "select sum, last from goodsinfo where type = :type and brand = :brand";
    query.prepare(cmd);
    query.bindValue(":type",  goodsType);
    query.bindValue(":brand", goodsBrand);
    if(query.exec())
    {
        while(query.next())
        {
            goodsSum = query.value("sum").toInt();
            qDebug() << goodsSum;
            goodsLast = query.value("last").toInt();
            qDebug() << goodsLast;
        }
    }else{
        qDebug() << "select goodsSum, goodsLast failed";
        return;
    }

    goodsSum += goodsNum;
    goodsLast += goodsNum;

    QString cmd1 = "update goodsinfo set sum = :sum, last = :last where type = :type and brand = :brand";
    query.prepare(cmd1);
    query.bindValue(":sum", goodsSum);
    query.bindValue(":last", goodsLast);
    query.bindValue(":type", goodsType);
    query.bindValue(":brand", goodsBrand);
    if(query.exec())
    {
        QMessageBox::information(this, tr("Information"), tr("Add GoodsNum Success"));
        initComboType();
        return;
    }else{
        qDebug() << "update goodsinfo failed";
        return;
    }
}
//END FUNCTIONS

//EVENTS
void Vm_StorageGoods::showEvent(QShowEvent *)
{
    initComboType();
}
//END EVENTS

//SLOTS
void Vm_StorageGoods::on_cob_type_currentTextChanged(const QString &arg1)
{
    //更新cob_brand
    ui->cob_brand->clear();
    QSqlQuery query;
    QStringList brandList;
    QString cmd = "select brand from goodsinfo where type = :type";
    query.prepare(cmd);
    query.bindValue(":type", arg1);
    if(query.exec())
    {
        while(query.next())
        {
            QString str = query.value("brand").toString();
            brandList << str;
        }
        ui->cob_brand->addItems(brandList);
    }else
    {
        qDebug() << "set brand failed";
        return;
    }
}

void Vm_StorageGoods::on_cob_brand_currentTextChanged(const QString &)
{
    ui->sp_num->setValue(0);
}

void Vm_StorageGoods::on_btn_commit_clicked()
{
    QString text = ui->cob_type->itemText(ui->cob_type->currentIndex());
    if(text == "请选择类型")
    {
        QMessageBox::warning(this, tr("Warning"), tr("Please Choose Some Goods"), QMessageBox::Ok);
        return;
    }

    if(ui->sp_num->value() == 0)
    {
        QMessageBox::warning(this, tr("Warning"), tr("Please Choose Goods Number"), QMessageBox::Ok);
        return;
    }

    //更新商品数量
    updateGoodsNum();
}

void Vm_StorageGoods::on_btn_cancel_clicked()
{
    initComboType();
}
//END SLOTS
