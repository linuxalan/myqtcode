#include "storageform.h"
#include "ui_storageform.h"
#include <QDebug>

StorageForm::StorageForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StorageForm)
{
    ui->setupUi(this);
}

StorageForm::~StorageForm()
{
    delete ui;
}

//按下【商品入库】按钮的槽事件
void StorageForm::doProcessSignalGetTypes()
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

//商品类型下拉框文本改变信号处理槽
void StorageForm::on_cob_type_currentTextChanged(const QString &arg1)
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

//商品品牌下拉框文本改变信号处理槽
void StorageForm::on_cob_brand_currentTextChanged(const QString &)
{
    ui->sp_num->setValue(0);
    str1 = ui->cob_type->itemText(ui->cob_type->currentIndex());
    str2 = ui->cob_brand->itemText(ui->cob_brand->currentIndex());
    //未选择商品时无法选择购买数量
    if(str1 == QString("请选择类型"))
    {
        ui->sp_num->setEnabled(false);
    }else{
        ui->sp_num->setEnabled(true);
    }
}

//确认按钮信号处理槽
void StorageForm::on_btn_commit_clicked()
{
    //未选择类型，无法入库
    if(str1 == QString("请选择类型") || ui->sp_num->text().toInt() == 0)
    {
        QMessageBox::information(this, tr("提示"), tr("入库失败"), QMessageBox::Ok);
        doProcessSignalGetTypes();
        return;
    }

    QSqlQuery query;

    int num = ui->sp_num->text().toInt();

    //获取已入库的数量
    QString cmd1 = QString("select sum from brands where type = :type and brand = :brand");
    query.prepare(cmd1);
    query.bindValue(":type", str1);
    query.bindValue(":brand", str2);
    bool ok = query.exec();
    if(!ok)
    {
        QMessageBox::information(this, tr("提示"), tr("获取已入库数据异常"), QMessageBox::Ok);
        doProcessSignalGetTypes();
        return;
    }
    int sumGoods = 0;
    while(query.next())
    {
        sumGoods = query.value("sum").toInt();
    }

    //获取库存
    QString cmd2 = QString("select last from brands where type = :type and brand = :brand");
    query.prepare(cmd2);
    query.bindValue(":type", str1);
    query.bindValue(":brand", str2);
    ok = query.exec();
    if(!ok)
    {
        QMessageBox::information(this, tr("提示"), tr("获取库存数据异常"), QMessageBox::Ok);
        doProcessSignalGetTypes();
        return;
    }

    int lastGoods = 0;
    while(query.next())
    {
        lastGoods = query.value("last").toInt();
    }

    //更新已入库数据及库存
    QString cmd3 = QString("update brands set sum = :sum, last = :last where type = :type and brand = :brand");
    query.prepare(cmd3);
    query.bindValue(":sum", num + sumGoods);
    query.bindValue(":last", num + lastGoods);
    query.bindValue(":type", str1);
    query.bindValue(":brand", str2);
    ok = query.exec();

    if(ok)
    {
        QMessageBox::information(this, tr("提示"), tr("入库成功"), QMessageBox::Ok);
        doProcessSignalGetTypes();
    }
    else
    {
        QMessageBox::information(this, tr("提示"), tr("入库失败"), QMessageBox::Ok);
        doProcessSignalGetTypes();
        return;
    }
}

//取消按钮信号处理槽
void StorageForm::on_btn_cancel_clicked()
{
    doProcessSignalGetTypes();
}
