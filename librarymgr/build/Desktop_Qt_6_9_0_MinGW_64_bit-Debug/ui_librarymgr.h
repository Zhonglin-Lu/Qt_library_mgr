/********************************************************************************
** Form generated from reading UI file 'librarymgr.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LIBRARYMGR_H
#define UI_LIBRARYMGR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_librarymgr
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *librarymgr)
    {
        if (librarymgr->objectName().isEmpty())
            librarymgr->setObjectName("librarymgr");
        librarymgr->resize(800, 600);
        centralwidget = new QWidget(librarymgr);
        centralwidget->setObjectName("centralwidget");
        librarymgr->setCentralWidget(centralwidget);
        menubar = new QMenuBar(librarymgr);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 18));
        librarymgr->setMenuBar(menubar);
        statusbar = new QStatusBar(librarymgr);
        statusbar->setObjectName("statusbar");
        librarymgr->setStatusBar(statusbar);

        retranslateUi(librarymgr);

        QMetaObject::connectSlotsByName(librarymgr);
    } // setupUi

    void retranslateUi(QMainWindow *librarymgr)
    {
        librarymgr->setWindowTitle(QCoreApplication::translate("librarymgr", "librarymgr", nullptr));
    } // retranslateUi

};

namespace Ui {
    class librarymgr: public Ui_librarymgr {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LIBRARYMGR_H
