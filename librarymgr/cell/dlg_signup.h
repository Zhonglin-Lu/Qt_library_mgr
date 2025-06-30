#ifndef DLG_SIGNUP_H
#define DLG_SIGNUP_H

#include <QDialog>

namespace Ui {
class Dlg_signup;
}

class Dlg_signup : public QDialog
{
    Q_OBJECT

public:
    explicit Dlg_signup(QWidget *parent = nullptr);
    ~Dlg_signup();

private slots:
    void on_btn_return_clicked();

    void on_btn_sure_clicked();

private:
    Ui::Dlg_signup *ui;
};

#endif // DLG_SIGNUP_H
