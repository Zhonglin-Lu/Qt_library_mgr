#include "dlg_bookgs.h"
#include "ui_dlg_bookgs.h"

#include <lib/sqlmgr.h>
#include <QMessageBox>

Dlg_BookGS::Dlg_BookGS(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dlg_BookGS)
{
    ui->setupUi(this);
}

Dlg_BookGS::~Dlg_BookGS()
{
    delete ui;
}

void Dlg_BookGS::sett(int id)
{
    m_idd = id;
    //执行sql语句获取图书信息，并显示到对应的控件上
    auto l = SqlMgr::getInstance()->getBooks(QString("where bookid = %1").arg(id));
    if(1 == l.size()){
        auto data = l[0];
        ui->lb_name->setText(data[1]);
    }
}

void Dlg_BookGS::setBookId(int id)
{
    m_bookid = id;
}

void Dlg_BookGS::setType(bool isReturn)
{
    m_isReturn = isReturn;
    ui->btn_get->setText("归还");
}

void Dlg_BookGS::on_btn_get_clicked()
{
    do{
        auto strName = ui->le_user->text();
        auto strPass = ui->le_password->text();
        //判断用户名密码是否正确
        int userid = 0;
        auto ret = SqlMgr::getInstance()->login(strName,strPass,userid);
        if(!ret){
            this->done(0);
            break;
        }
        if(!m_isReturn){
            SqlMgr::getInstance()->borrowbook(QString::number(userid),QString::number(m_bookid));
        }else{
            QString ret = SqlMgr::getInstance()->returnbook(QString::number(userid),QString::number(m_bookid));
            QMessageBox::information(nullptr, "归还信息", ret);
        }
        this->done(1);
    }while(false);


    //图书库存-1

    //生成一条借阅记录



}


void Dlg_BookGS::on_btn_cancel_clicked()
{
    this->done(0);
}

