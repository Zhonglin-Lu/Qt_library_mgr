#include "librarymgr.h"
#include "ui_librarymgr.h"

#include <QPushButton>
#include <QtDebug>

librarymgr::librarymgr(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::librarymgr)
    ,m_userPage(nullptr)
    ,m_bookPage(nullptr)
    ,m_hisPage(nullptr)
{
    ui->setupUi(this);
    initPage();
}

librarymgr::~librarymgr()
{
    delete ui;
}

void librarymgr::initPage()
{
    m_userPage = new libmgr_UserMgr(this);
    m_bookPage = new libmgr_BookMgr(this);
    m_hisPage = new libmgr_his(this);
    ui->stackedWidget->addWidget(m_userPage);
    ui->stackedWidget->addWidget(m_bookPage);
    ui->stackedWidget->addWidget(m_hisPage);
    ui->stackedWidget->setCurrentIndex(0);


    auto l = ui->tool->children();
    for(auto it:l){
        if(it->objectName().contains("btn")){
            connect(static_cast<QPushButton*>(it),&QPushButton::clicked,this,&librarymgr::dealMenu);
        }
    }
    m_userPage->initPage();
}

void librarymgr::dealMenu(){
    auto str = sender()->objectName();
    do{
        if("btn_user" == str){
            m_userPage->initPage();
            ui->stackedWidget->setCurrentIndex(0);
            break;
        }
        if("btn_book" == str){
            m_bookPage->initPage();
            ui->stackedWidget->setCurrentIndex(1);
            break;
        }
        if("btn_record" == str){
            m_hisPage->initPage();
            ui->stackedWidget->setCurrentIndex(2);
            break;
        }
        // if("btn_his" == str){
        //     m_hisPage->initPage();
        //     ui->stackedWidget->setCurrentIndex(3);
        //     break;
        // }
        if("btn_vip" == str){
            ui->stackedWidget->setCurrentIndex(3);
            break;
        }
    }while(false);
}
