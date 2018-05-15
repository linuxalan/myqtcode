#ifndef LOGINANDREGISTFORM_H
#define LOGINANDREGISTFORM_H

#include <QWidget>

namespace Ui {
class LoginAndRegistForm;
}

class LoginAndRegistForm : public QWidget
{
    Q_OBJECT

public:
    explicit LoginAndRegistForm(QWidget *parent = 0);
    ~LoginAndRegistForm();

private:
    Ui::LoginAndRegistForm *ui;
};

#endif // LOGINANDREGISTFORM_H
