#ifndef DLG_LOGIN2_H
#define DLG_LOGIN2_H

#include <QDialog>

namespace Ui {
class Dlg_login2;
}

class Dlg_login2 : public QDialog
{
    Q_OBJECT

public:
    explicit Dlg_login2(QWidget *parent = nullptr);
    ~Dlg_login2();

private slots:



    void on_btn_login_clicked();

    void on_btn_exit_clicked();

private:
    Ui::Dlg_login2 *ui;
};

#endif // DLG_LOGIN2_H
