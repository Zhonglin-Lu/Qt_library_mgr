#include "libmgr_his.h"
#include "ui_libmgr_his.h"

#include "lib/sqlmgr.h"
#include <QFileDialog>
#include <QMessageBox>
#include "dlg_bookgs.h"

libmgr_his::libmgr_his(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::libmgr_his)
{
    ui->setupUi(this);
    ui->tableView->setModel(&m_model);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
}

libmgr_his::~libmgr_his()
{
    delete ui;
}

void libmgr_his::initPage(QString strCondition)
{
    auto l = SqlMgr::getInstance()->getRecord(strCondition);
    m_model.clear();
    m_model.setHorizontalHeaderLabels(QStringList{"借阅记录编号","用户id","IBSN","开始时间","归还时间","信誉积分","班级","学院","用户类别","姓名","密码","昵称"
                                                    ,"书名","定价","类型1","类型2","类型3","剩余数量","图片"});
    for(int i = 0;i < l.size();i++){
        QList<QStandardItem*> items;
        for(int j = 0;j < l[i].size();j++){
            items.append(new QStandardItem(l[i][j]));
        }
        m_model.appendRow(items);
    }
}




void libmgr_his::on_le_search_textChanged(const QString &arg1)
{
    QString strCond = QString("where bookid like '%%1%' or userid like '%%1%'").arg(arg1);
    initPage(strCond);
}


void libmgr_his::on_btn_clear_clicked()
{
    SqlMgr::getInstance()->clearRecord();
    initPage();
}


void libmgr_his::on_pushButton_clicked()
{
    int r = ui->tableView->currentIndex().row();
    if(r < 0){
        QMessageBox::critical(nullptr,"信息","无法选中");
    }else{
        Dlg_BookGS dlg;
        auto id = m_model.item(r,2)->text();
        dlg.setType(true);
        dlg.setBookId(id.toInt());
        int ret = dlg.exec();
        if (!ret) {
            QMessageBox::critical(nullptr, "错误", "归还失败");
        } else {
            QMessageBox::information(nullptr, "成功", "归还成功");
            initPage();
        }

    }
}

