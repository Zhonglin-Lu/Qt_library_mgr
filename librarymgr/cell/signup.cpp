#include "signup.h"
#include "ui_signup.h"

#include "dlg_login2.h"

Signup::Signup(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Signup)
{
    ui->setupUi(this);
    //设置图片
    QPixmap *pix = new QPixmap(":/library.jpg");
    QSize sz = ui->label_image->size();
    ui->label_image->setPixmap(pix->scaled(sz));
}

Signup::~Signup()
{
    delete ui;
}

void Signup::on_btn_return_2_clicked()
{
    Dlg_login2 *w = new Dlg_login2;
    w->show();
    this->close();

}

