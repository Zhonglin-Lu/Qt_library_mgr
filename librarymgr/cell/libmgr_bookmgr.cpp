#include "libmgr_bookmgr.h"
#include "ui_libmgr_bookmgr.h"

#include "lib/sqlmgr.h"
#include <QFileDialog>
#include <QMessageBox>
#include "dlg_bookau.h"
#include "dlg_bookgs.h"
#include "dlg_bookgs.h"

libmgr_BookMgr::libmgr_BookMgr(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::libmgr_BookMgr)
{
    ui->setupUi(this);
    ui->tableView->setModel(&m_model);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

}

libmgr_BookMgr::~libmgr_BookMgr()
{
    delete ui;
}

void libmgr_BookMgr::initPage(QString strCondition)
{
    //获取所有图书
    //查询数据库并且显示
    auto l = SqlMgr::getInstance()->getBooks(strCondition);
    m_model.clear();
    m_model.setHorizontalHeaderLabels(QStringList{"IBSN","书名","定价","类别1","类别2","类别3","数量","图片"});
    for(int i = 0;i < l.size();i++){
        QList<QStandardItem*> items;
        for(int j = 0;j < l[i].size();j++){
            items.append(new QStandardItem(l[i][j]));
        }
        m_model.appendRow(items);
    }

}

void libmgr_BookMgr::on_btn_add_clicked()
{
    Dlg_BookAU dlg;
    dlg.exec();
    initPage();
}


void libmgr_BookMgr::on_btn_update_clicked()
{
    int r = ui->tableView->currentIndex().row();
    if(r < 0){
        QMessageBox::critical(nullptr,"信息","无法选中");
    }else{
        auto id = m_model.item(r,0)->text();

        Dlg_BookAU dlg;

        dlg.setType(id.toInt());

        dlg.exec();
        initPage();
    }

}


void libmgr_BookMgr::on_btn_del_clicked()
{
    //删除
    int r = ui->tableView->currentIndex().row();
    if(r < 0){
        QMessageBox::critical(nullptr,"信息","无法选中");
    }else{
        auto id = m_model.item(r,0)->text();
        auto str = SqlMgr::getInstance()->delBook(id);
        if (!str.isEmpty()) {
            QMessageBox::critical(nullptr, "错误", "无法选中");
        } else {
            QMessageBox::information(nullptr, "成功", "删除成功");
        }
        initPage();
    }
}


void libmgr_BookMgr::on_btn_get_clicked()
{
    int r = ui->tableView->currentIndex().row();
    if(r < 0){
        QMessageBox::critical(nullptr,"信息","无法选中");
    }else{
        auto id = m_model.item(r,0)->text();

        auto cnt = m_model.item(r,6)->text().toInt();
        if(cnt <= 0){
            QMessageBox::critical(nullptr, "错误", "借阅失败，没有库存");
            return;
        }
        Dlg_BookGS dlg;
        dlg.sett(id.toInt());
        dlg.setBookId(id.toInt());
        int ret = dlg.exec();
        if (!ret) {
            QMessageBox::critical(nullptr, "错误", "借阅失败");
        } else {
            QMessageBox::information(nullptr, "成功", "借阅成功");
            initPage();
        }

    }

}




void libmgr_BookMgr::on_le_search_textChanged(const QString &arg1)
{
    QString strCond = QString("where name like '%%1%' or type1 like '%%1%' or type2 like '%%1%' or type3 like '%%1%'").arg(arg1);
    initPage(strCond);
}

