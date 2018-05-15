#include "findform.h"
#include "ui_findform.h"
#include <QDebug>

FindForm::FindForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FindForm)
{
    ui->setupUi(this);
}

FindForm::~FindForm()
{
    delete ui;
}

//点击商品查询按钮，发送signalFindGoods信号的处理槽
void FindForm::doProcessSignalFindGoods()
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
void FindForm::on_cob_type_currentTextChanged(const QString &arg1)
{
    ui->cob_brand->clear();
    ui->textEdit->clear();
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

//商品品牌文本变化处理槽
void FindForm::on_cob_brand_currentTextChanged(const QString &)
{
    ui->textEdit->clear();
}

//确认事件处理槽
void FindForm::on_btn_commit_clicked()
{
    QSqlQuery query;
    QString str1 = ui->cob_type->itemText(ui->cob_type->currentIndex());
    QString str2 = ui->cob_brand->itemText(ui->cob_brand->currentIndex());
    QString cmd = QString("select * from brands where type = :type and brand = :brand");
    query.prepare(cmd);
    query.bindValue(":type", str1);
    query.bindValue(":brand", str2);
    query.exec();
    while(query.next())
    {
        QString str3 = QString("类型:%1 品牌:%2 价格:%3元 已入库:%4件 已售卖:%5件 库存:%6件")
                .arg(query.value("type").toString())
                .arg(query.value("brand").toString())
                .arg(query.value("price").toString())
                .arg(query.value("sum").toString())
                .arg(query.value("sell").toString())
                .arg(query.value("last").toString());
        ui->textEdit->append(str3);
    }
}

//取消事件处理槽
void FindForm::on_btn_commit_2_clicked()
{
    doProcessSignalFindGoods();
    ui->textEdit->clear();
}
