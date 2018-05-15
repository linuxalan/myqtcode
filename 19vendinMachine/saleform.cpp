#include "saleform.h"
#include "ui_saleform.h"

SaleForm::SaleForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SaleForm)
{
    ui->setupUi(this);
    lastGoods = 0;
    tmp_lastGoods = 0;
    sellGoods = 0;
}

SaleForm::~SaleForm()
{
    delete ui;
}

//新建数据库后会发送信号SignalInitSaleFormData()，此槽处理
void SaleForm::doProcessSignalInitSaleFormData()
{
    ui->cob_type->clear();
    QSqlQuery query;
    query.exec("select distinct(type) from brands");
    QStringList list;
    while(query.next())
    {
        list << query.value("type").toString();
    }
    ui->cob_type->addItems(list);
}

//商品类型文本变化信号处理槽
void SaleForm::on_cob_type_currentTextChanged(const QString &arg1)
{
    ui->cob_brand->clear();
    QSqlQuery query;
    QString cmd = QString("select brand from brands where type = :column");
    query.prepare(cmd);
    query.bindValue(":column", arg1);
    query.exec();
    QStringList list;
    while(query.next())
    {
        list << query.value("brand").toString();
    }
    ui->cob_brand->addItems(list);
}

//商品品牌文本变化信号处理槽
void SaleForm::on_cob_brand_currentTextChanged(const QString &)
{
    ui->sp_num->setValue(0);
    ui->le_price->setText(QString::number(0));
    ui->le_money->setText(QString::number(0));
    str1 = ui->cob_type->itemText(ui->cob_type->currentIndex());
    str2 = ui->cob_brand->itemText(ui->cob_brand->currentIndex());
    QSqlQuery query;
    QString cmd = QString("select price,last from brands where type = :type and brand = :brand");
    query.prepare(cmd);
    query.bindValue(":type", str1);
    query.bindValue(":brand", str2);
    query.exec();
    double priceGoods;
    while(query.next())
    {
        priceGoods = query.value("price").toDouble();
        lastGoods = query.value("last").toInt();
    }
    ui->le_price->setText(QString::number(priceGoods));
    QString strLast = QString("剩余数量:%1").arg(lastGoods);
    ui->lb_remain_num->setText(strLast);

    //未选择商品时无法选择购买数量
    if(str1 == QString("请选择类型"))
    {
        ui->sp_num->setEnabled(false);
    }else{
        ui->sp_num->setEnabled(true);
    }
}

//商品数量值变化信号处理槽
void SaleForm::on_sp_num_valueChanged(int arg1)
{

    //待实现：购买数量不能大于库存

    //记录剩余数量
    tmp_lastGoods = lastGoods - arg1;
    //记录购买数量
    sellGoods = arg1;
    QString strLast = QString("剩余数量:%1").arg(tmp_lastGoods);
    ui->lb_remain_num->setText(strLast);

    //设置价格
    int priceGoods = ui->le_price->text().toInt();
    int moneyGoods = priceGoods*arg1;
    QString strMoney = QString::number(moneyGoods);
    ui->le_money->setText(strMoney);
}

//确认按钮信号处理槽
void SaleForm::on_btn_commit_clicked()
{
    if(str1 == QString("请选择类型"))
    {
        QMessageBox::information(this, tr("提示"), tr("未选择商品类型，无法购买"), QMessageBox::Ok);
        doProcessSignalInitSaleFormData();
        return;
    }

    int ret = QMessageBox::information(this, tr("提示"), tr("请支付"), QMessageBox::Ok);
    if(ret == QMessageBox::Ok)
    {
        //可以添加获取是否支付成功的功能

        QSqlQuery query;
        QString cmd = QString("update brands set sell = :sell, last = :last where type = :type and brand = :brand");
        query.prepare(cmd);
        query.bindValue(":sell", sellGoods);
        query.bindValue(":last", tmp_lastGoods);
        query.bindValue(":type", str1);
        query.bindValue(":brand", str2);
        bool ok = query.exec();
        if(!ok)
        {
            QMessageBox::information(this, tr("提示"), tr("更新库存失败"), QMessageBox::Ok);
        }
        doProcessSignalInitSaleFormData();
    }
}

//取消按钮信号处理槽
void SaleForm::on_btn_cancel_clicked()
{
    doProcessSignalInitSaleFormData();
}
