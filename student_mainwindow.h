#ifndef STUDENT_MAINWINDOW_H
#define STUDENT_MAINWINDOW_H

#include <QDialog>

namespace Ui {
class student_mainwindow;
}

class student_mainwindow : public QDialog
{
    Q_OBJECT

public:
    explicit student_mainwindow(QWidget *parent = nullptr);
    ~student_mainwindow();
    /*void initpage();
    void deal();*/


private slots:

private:
    Ui::student_mainwindow *ui;
};

#endif // STUDENT_MAINWINDOW_H
