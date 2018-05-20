#include "vm_findgoods.h"
#include "ui_vm_findgoods.h"

Vm_FindGoods::Vm_FindGoods(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Vm_FindGoods)
{
    ui->setupUi(this);
}

Vm_FindGoods::~Vm_FindGoods()
{
    delete ui;
}

//FUNCTIONS
void Vm_FindGoods::initComboType()
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

void Vm_FindGoods::findFromDateBase()
{
    QSqlQuery query;

    this->goodsType = ui->cob_type->itemText(ui->cob_type->currentIndex());
    this->goodsBrand = ui->cob_brand->itemText(ui->cob_brand->currentIndex());

    QString cmd = "select * from goodsinfo where type = :type and brand = :brand";
    query.prepare(cmd);
    query.bindValue(":type", this->goodsType);
    query.bindValue(":brand", this->goodsBrand);
    if(query.exec())
    {
        while(query.next())
        {
            this->goodsPrice = query.value("price").toInt();
            this->goodsSum   = query.value("sum").toInt();
            this->goodsSell  = query.value("sell").toInt();
            this->goodsLast  = query.value("last").toInt();
        }
    }else{
        qDebug() << "find failed";
    }

    //显示在textEdit
    showGoodsInformation();
}

void Vm_FindGoods::showGoodsInformation()
{
    QString goodsInfo;
    goodsInfo += "商品类型:";
    goodsInfo += this->goodsType;
    goodsInfo += " ";
    goodsInfo += "商品品牌:";
    goodsInfo += this->goodsBrand;
    goodsInfo += " ";
    goodsInfo += "单价:";
    goodsInfo += QString::number(this->goodsPrice);
    goodsInfo += "元 ";
    goodsInfo += "已入库:";
    goodsInfo += QString::number(this->goodsSum);
    goodsInfo += "件 ";
    goodsInfo += "已售卖:";
    goodsInfo += QString::number(this->goodsSell);
    goodsInfo += "件 ";
    goodsInfo += "库存:";
    goodsInfo += QString::number(this->goodsLast);
    goodsInfo += "件";
    ui->textEdit->append(goodsInfo);
}
//END FUNCTIONS

//EVENTS
void Vm_FindGoods::showEvent(QShowEvent *)
{
    initComboType();
    ui->textEdit->clear();
}
//END EVENTS

//SLOTS
void Vm_FindGoods::on_cob_type_currentTextChanged(const QString &arg1)
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

void Vm_FindGoods::on_btn_commit_clicked()
{
    QString text = ui->cob_type->itemText(ui->cob_type->currentIndex());
    if(text == "请选择类型")
    {
        QMessageBox::warning(this, tr("Warning"), tr("Please Choose Some Goods"), QMessageBox::Ok);
        return;
    }

    //搜索商品信息
    findFromDateBase();
}

void Vm_FindGoods::on_btn_cancel_clicked()
{
    initComboType();
}
//END SLOTS


