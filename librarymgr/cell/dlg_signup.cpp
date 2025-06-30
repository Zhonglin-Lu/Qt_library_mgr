#include "dlg_signup.h"
#include "ui_dlg_signup.h"

#include "dlg_login2.h"

#include <lib/sqlmgr.h>

#include <QMessageBox>

Dlg_signup::Dlg_signup(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dlg_signup)
{
    ui->setupUi(this);
    //设置图片
    QPixmap *pix = new QPixmap(":/library.jpg");
    QSize sz = ui->label_image->size();
    ui->label_image->setPixmap(pix->scaled(sz));
}

Dlg_signup::~Dlg_signup()
{
    delete ui;
}

void Dlg_signup::on_btn_return_clicked()
{
    this->close();


}


void Dlg_signup::on_btn_sure_clicked()
{
    QString username = ui->le_username->text();
    QString password = ui->le_password->text();
    QString surepass = ui->le_surepass->text();
    QString grade = ui->grade->text();
    QString department = ui->department->text();
    QString name = ui->name->text();
    if (username.isEmpty() || password.isEmpty() || name.isEmpty()) {
        QMessageBox::critical(this, "错误", "用户名、密码和姓名不能为空");
        return;
    }
    //判断密码是否一致
    if(password == surepass){
        auto ret = SqlMgr::getInstance()->signup(username,password,grade,department,name);
        if(ret == 1){
            QMessageBox::information(nullptr, "成功", "注册成功！");
            this->hide();

        }else if(ret == 2){
            QMessageBox::critical(nullptr, "错误", "该用户名已被注册");
        }else{
            QMessageBox::critical(nullptr, "错误", "请检查信息是否有误");
        }
    }else{
        QMessageBox::critical(nullptr, "错误", "两次输入密码不一致，请重试");
    }

}

