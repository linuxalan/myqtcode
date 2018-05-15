#ifndef FINDFORM_H
#define FINDFORM_H

#include <QWidget>
#include <QSqlQuery>

namespace Ui {
class FindForm;
}

class FindForm : public QWidget
{
    Q_OBJECT

public:
    explicit FindForm(QWidget *parent = 0);
    ~FindForm();

private slots:
    void doProcessSignalFindGoods();
    void on_btn_commit_clicked();
    void on_btn_commit_2_clicked();

    void on_cob_type_currentTextChanged(const QString &arg1);

    void on_cob_brand_currentTextChanged(const QString &arg1);

private:
    Ui::FindForm *ui;
};

#endif // FINDFORM_H
