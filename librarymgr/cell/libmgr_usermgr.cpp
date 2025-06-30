#include "libmgr_usermgr.h"
#include "ui_libmgr_usermgr.h"

#include "lib/sqlmgr.h"
#include <QFileDialog>
#include <QMessageBox>

libmgr_UserMgr::libmgr_UserMgr(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::libmgr_UserMgr)
{
    ui->setupUi(this);
    ui->tableView->setModel(&m_model);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);




#if 0
    for(int i = 0;i < 10;i++){
        QList<QStandardItem*> items;
        items.append(new QStandardItem("1"));
        items.append(new QStandardItem("人工智能与计算机学院"));
        items.append(new QStandardItem("计科申威2401"));
        items.append(new QStandardItem("张三"));
        items.append(new QStandardItem("123456"));
        items.append(new QStandardItem("shangsan"));
        items.append(new QStandardItem("SV"));
        m_model.appendRow(items);
    }
#endif

}

libmgr_UserMgr::~libmgr_UserMgr()
{
    delete ui;
}

void libmgr_UserMgr::initPage(QString strCondition)
{
    //查询数据库并且显示
    auto l = SqlMgr::getInstance()->getUsers(strCondition);
    m_model.clear();
    m_model.setHorizontalHeaderLabels(QStringList{"用户id","信誉积分","院系","班级","权限","姓名","密码","昵称"});
    for(int i = 0;i < l.size();i++){
        QList<QStandardItem*> items;
        for(int j = 0;j < l[i].size();j++){
            items.append(new QStandardItem(l[i][j]));
        }
        m_model.appendRow(items);
    }

}

void libmgr_UserMgr::on_btn_del_clicked()
{
    //删除用户
    int r = ui->tableView->currentIndex().row();
    if(r < 0){
        QMessageBox::information(nullptr,"信息","无法选中");
    }else{
        auto id = m_model.item(r,0)->text();
        SqlMgr::getInstance()->delUser(id);
        initPage();
    }

}


void libmgr_UserMgr::on_btn_import_clicked()
{
    //导入用户
    auto strPath = QFileDialog::getOpenFileName(nullptr,"输入文件路径");

    if(!strPath.isEmpty()){
        QFile f(strPath);
        f.open(QFile::ReadOnly);
        QVector<QStringList> vecData;

        while(!f.atEnd()){
            QString str = f.readLine();
            auto l = str.split("，");
            if(l.size() != 7){
                QMessageBox::information(nullptr,"信息","导入失败");
                return;
            }
            l[l.size() - 1] = l[l.size() - 1].chopped(2);
            vecData.push_back(l);
        }
        SqlMgr::getInstance()->AddUser(vecData);
    }
    ui->le_search->clear();
    initPage();


}


void libmgr_UserMgr::on_le_search_textChanged(const QString &arg1)
{
    //搜索用户
    QString strCond = QString("where username like '%%1%' or nickname like '%%1%'").arg(arg1);
    initPage(strCond);

}

