#ifndef LIBRARYMGR_H
#define LIBRARYMGR_H

#include <QMainWindow>

#include "libmgr_usermgr.h"
#include "libmgr_bookmgr.h"
#include "libmgr_his.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class librarymgr;
}
QT_END_NAMESPACE

class librarymgr : public QMainWindow
{
    Q_OBJECT

public:
    librarymgr(QWidget *parent = nullptr);
    ~librarymgr();
    void initPage();

    void dealMenu();
private:
    Ui::librarymgr *ui;
    libmgr_UserMgr *m_userPage;
    libmgr_BookMgr *m_bookPage;
    libmgr_his *m_hisPage;

};
#endif // LIBRARYMGR_H
