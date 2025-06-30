#include "dlg_login2.h"
#include "ui_dlg_login2.h"


#include <QMessageBox>
#include <QGraphicsDropShadowEffect>

#include <lib/sqlmgr.h>
#include "dlg_signup.h"


Dlg_login2::Dlg_login2(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dlg_login2)
{
    ui->setupUi(this);
    //设置图片
    QPixmap *pix = new QPixmap(":/library.jpg");
    QSize sz = ui->label_image->size();
    ui->label_image->setPixmap(pix->scaled(sz));

    //设置图片阴影效果
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(-3, 0);
    shadow->setColor(QColor("#888888"));
    shadow->setBlurRadius(30);
    ui->label_image->setGraphicsEffect(shadow);
}

Dlg_login2::~Dlg_login2()
{
    delete ui;
}




void Dlg_login2::on_btn_login_clicked()
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


void Dlg_login2::on_btn_exit_clicked()
{
    Dlg_signup dlg;
    dlg.exec();


}

