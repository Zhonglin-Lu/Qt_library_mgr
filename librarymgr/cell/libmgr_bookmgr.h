#ifndef LIBMGR_BOOKMGR_H
#define LIBMGR_BOOKMGR_H

#include <QStandardItemModel>
#include <QWidget>

namespace Ui {
class libmgr_BookMgr;
}

class libmgr_BookMgr : public QWidget
{
    Q_OBJECT

public:
    explicit libmgr_BookMgr(QWidget *parent = nullptr);
    ~libmgr_BookMgr();
    void initPage(QString strCondition = "");

private slots:
    void on_btn_add_clicked();

    void on_btn_update_clicked();

    void on_btn_del_clicked();

    void on_btn_get_clicked();

    // void on_btn_bk_clicked();

    void on_le_search_textChanged(const QString &arg1);

private:
    Ui::libmgr_BookMgr *ui;
    QStandardItemModel m_model;
};

#endif // LIBMGR_BOOKMGR_H
