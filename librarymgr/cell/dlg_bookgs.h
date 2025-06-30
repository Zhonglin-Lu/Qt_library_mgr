#ifndef DLG_BOOKGS_H
#define DLG_BOOKGS_H

#include <QDialog>

namespace Ui {
class Dlg_BookGS;
}

class Dlg_BookGS : public QDialog
{
    Q_OBJECT

public:
    explicit Dlg_BookGS(QWidget *parent = nullptr);
    ~Dlg_BookGS();

    void sett(int id);
    void setBookId(int id);
    void setType(bool isReturn);

private slots:
    void on_btn_get_clicked();

    void on_btn_cancel_clicked();

private:
    Ui::Dlg_BookGS *ui;
    int m_bookid;
    bool m_isReturn = false;
    int m_idd = -1;
};

#endif // DLG_BOOKGS_H
