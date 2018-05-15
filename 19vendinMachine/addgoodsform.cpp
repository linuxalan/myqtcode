#include "addgoodsform.h"
#include "ui_addgoodsform.h"
#include <QDebug>

AddGoodsForm::AddGoodsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddGoodsForm)
{
    ui->setupUi(this);
}

AddGoodsForm::~AddGoodsForm()
{
    delete ui;
}

void AddGoodsForm::on_btn_commit_clicked()
{
    if(ui->le_type->text().isEmpty() || ui->le_brand->text().isEmpty() || ui->le_price->text().isEmpty())
    {
        QMessageBox::information(this, tr("提示"), tr("商品信息不全，添加失败"), QMessageBox::Ok);
        ui->le_type->clear();
        ui->le_brand->clear();
        ui->le_price->clear();
        return;
    }
    QSqlQuery query;
    QString cmd1 = QString("insert into brands(type, brand, price) values(:type, :brand, :price)");
    query.prepare(cmd1);
    query.bindValue(":type", ui->le_type->text());
    query.bindValue(":brand", ui->le_brand->text());
    query.bindValue(":price", ui->le_price->text().toFloat());
    bool ret = query.exec();
    if(ret)
    {
        QMessageBox::information(this, tr("提示"), tr("添加成功"), QMessageBox::Ok);
        ui->le_type->clear();
        ui->le_brand->clear();
        ui->le_price->clear();
    }
    else
    {
        QMessageBox::information(this, tr("提示"), tr("添加失败，请重新添加"), QMessageBox::Ok);
        ui->le_type->clear();
        ui->le_brand->clear();
        ui->le_price->clear();
    }
}

void AddGoodsForm::on_btn_cancel_clicked()
{
    ui->le_type->clear();
    ui->le_brand->clear();
    ui->le_price->clear();
}
