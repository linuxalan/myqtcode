#include "vm_salegoods.h"
#include "ui_vm_salegoods.h"

Vm_SaleGoods::Vm_SaleGoods(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Vm_SaleGoods)
{
    ui->setupUi(this);
}

Vm_SaleGoods::~Vm_SaleGoods()
{
    delete ui;
}
//FUNCTIONS
void Vm_SaleGoods::initComboType()
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
//END FUNCTIONS

//EVENTS
void Vm_SaleGoods::showEvent(QShowEvent *)
{
    initComboType();
}
//END EVENTS

//SLOTS
void Vm_SaleGoods::on_cob_type_currentTextChanged(const QString &arg1)
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

void Vm_SaleGoods::on_cob_brand_currentTextChanged(const QString &)
{
    //显示单价
    ui->le_price->clear();
    QSqlQuery query;  
    this->goodsType = ui->cob_type->itemText(ui->cob_type->currentIndex());
    this->goodsBrand = ui->cob_brand->itemText(ui->cob_brand->currentIndex());
    QString cmd = "select price, sell, last from goodsinfo where type = :type and brand = :brand";
    query.prepare(cmd);
    query.bindValue(":type", goodsType);
    query.bindValue(":brand", goodsBrand);
    if(query.exec())
    {
        while(query.next())
        {
            this->price = query.value("price").toInt();
            this->last = query.value("last").toInt();
            this->sell = query.value("sell").toInt();
        }
    }else{
        qDebug() << "select price,last failed";
        return;
    }
    ui->le_price->setText(QString::number(this->price));

    //数量清0
    ui->sp_num->setValue(0);
    ui->sp_num->setMaximum(this->last);

    //显示剩余数量
    QString lastNum = "剩余数量:" + QString::number(this->last);
    ui->lb_remain_num->setText(lastNum);

    //初始化总价文本框
    ui->le_money->setText("0");
}

void Vm_SaleGoods::on_sp_num_valueChanged(int arg1)
{
    //临时改变剩余数量
    this->showLastNum = last - arg1;
    QString lastNum = "剩余数量:" + QString::number(this->showLastNum);
    ui->lb_remain_num->setText(lastNum);

    //显示总价
    int sum = this->price * arg1;
    ui->le_money->setText(QString::number(sum));
}

void Vm_SaleGoods::on_btn_commit_clicked()
{
    //判断是否已选商品
    QString text = ui->cob_type->itemText(ui->cob_type->currentIndex());
    if(text == "请选择类型")
    {
        QMessageBox::warning(this, tr("Warning"), tr("Please Choose Some Goods"), QMessageBox::Ok);
        return;
    }

    //确认总售卖数量
    int currentSellNum = ui->sp_num->value();
    this->sell += currentSellNum;

    //更新已售卖数量及库存
    QSqlQuery query;
    QString cmd = "update goodsinfo set sell = :sell, last = :last where type = :type and brand = :brand";
    query.prepare(cmd);
    query.bindValue(":sell", this->sell);
    query.bindValue(":last", this->showLastNum);
    query.bindValue(":type", this->goodsType);
    query.bindValue(":brand", this->goodsBrand);
    if(query.exec())
    {
        QMessageBox::information(this, tr("Information"), tr("Please Pay Money"), QMessageBox::Ok);
        initComboType();
    }else{
        qDebug() << "buy failed";
        return;
    }
}

void Vm_SaleGoods::on_btn_cancel_clicked()
{
    initComboType();
}
//END SLOTS
