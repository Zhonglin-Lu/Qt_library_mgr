#ifndef LIBMGR_USERMGR_H
#define LIBMGR_USERMGR_H

#include <QWidget>
#include <QStandardItemModel>

namespace Ui {
class libmgr_UserMgr;
}

class libmgr_UserMgr : public QWidget
{
    Q_OBJECT

public:
    explicit libmgr_UserMgr(QWidget *parent = nullptr);
    ~libmgr_UserMgr();

    void initPage(QString strCondition = "");

private slots:
    void on_btn_del_clicked();

    void on_btn_import_clicked();

    void on_le_search_textChanged(const QString &arg1);

private:
    Ui::libmgr_UserMgr *ui;
    QStandardItemModel m_model;
};

#endif // LIBMGR_USERMGR_H
