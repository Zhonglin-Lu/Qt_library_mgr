#include "dlg_login.h"
#include "ui_dlg_login.h"
#include "lib/sqlmgr.h"

#include <QMessageBox>

Dlg_login::Dlg_login(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dlg_login)
{
    ui->setupUi(this);
}

Dlg_login::~Dlg_login()
{
    delete ui;
}

void Dlg_login::on_btn_login_clicked()
{
    int bookid = 0;
    auto ret = SqlMgr::getInstance()->login(ui->le_user->text(),ui->le_password->text(),bookid);
    if(ret){
        setResult(1);
        QMessageBox::information(nullptr, "成功", "登陆成功！");
        hide();
    }else{
        QMessageBox::critical(nullptr, "错误", "用户名或密码错误");
        setResult(0);
    }


}


void Dlg_login::on_btn_exit_clicked()
{
    setResult(0);
    hide();

}

