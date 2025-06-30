#ifndef LIBMGR_HIS_H
#define LIBMGR_HIS_H

#include <QStandardItemModel>
#include <QWidget>

namespace Ui {
class libmgr_his;
}

class libmgr_his : public QWidget
{
    Q_OBJECT

public:
    explicit libmgr_his(QWidget *parent = nullptr);
    ~libmgr_his();
    void initPage(QString strCondition = "");

private slots:


    void on_le_search_textChanged(const QString &arg1);

    void on_btn_clear_clicked();

    void on_pushButton_clicked();

private:
    Ui::libmgr_his *ui;
    QStandardItemModel m_model;
};

#endif // LIBMGR_HIS_H
