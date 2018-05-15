#ifndef CHANGEPASSWDFORM_H
#define CHANGEPASSWDFORM_H

#include <QWidget>

namespace Ui {
class ChangePasswdForm;
}

class ChangePasswdForm : public QWidget
{
    Q_OBJECT

public:
    explicit ChangePasswdForm(QWidget *parent = 0);
    ~ChangePasswdForm();

private:
    Ui::ChangePasswdForm *ui;
};

#endif // CHANGEPASSWDFORM_H
