#include "librarymgr.h"

#include <QApplication>

#include "dlg_login2.h"

#include "lib/sqlmgr.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    SqlMgr::getInstance()->init();
    //int bookid = 0;
    //qDebug()<<"login ret"<<SqlMgr::getInstance()->login("zhangsan","123456",bookid);

    Dlg_login2 dlg;
    int ret = dlg.exec();

    if(1 == ret){
        librarymgr w;
        w.show();
        return a.exec();
    }
    if(0 == ret){
        exit(0);
        return 0;
    }
    return 0;

}
