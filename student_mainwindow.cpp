#include "student_mainwindow.h"
#include "ui_student_mainwindow.h"
#include <QPushButton>
#include <QtDebug>
#include <QtWebEngineWidgets/QWebEngineView>
student_mainwindow::student_mainwindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::student_mainwindow)
{
    ui->setupUi(this);
    QString htmlPath = QCoreApplication::applicationDirPath() + "/library_system_2/public/index.html";
    QUrl url = QUrl::fromLocalFile(htmlPath);

    // 加载本地文件
    ui->web_1->load(url);
}

student_mainwindow::~student_mainwindow()
{
    delete ui;
}

/*void student_mainwindow::initpage()
{
    ui->stackedWidget->setCurrentIndex(0);
    auto l = ui->to->children();
     qDebug() << "Found" << l.size() << "child objects in ui->to";
    for(auto it:l){
        if(it->objectName().contains("btn")){
            connect(static_cast<QToolButton*>(it),&QToolButton::clicked,this,&student_mainwindow::deal);
        }
    }

}

void student_mainwindow::deal()
{
     qDebug() << "Deal function called. Sender:" << sender()->objectName();
    auto str = sender()->objectName();
    do{
        if("btn_user" == str){
            ui->stackedWidget->setCurrentIndex(0);
            break;
        }
        if("btn_book" == str){
            ui->stackedWidget->setCurrentIndex(1);
            break;
        }
        if("btn_record" == str){
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
}*/

