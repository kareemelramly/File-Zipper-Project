/********************************************************************************
** Form generated from reading UI file 'decompress.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DECOMPRESS_H
#define UI_DECOMPRESS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Decompress
{
public:
    QPushButton *decom_sel;
    QPushButton *Dodecompression;
    QPushButton *pushButton;

    void setupUi(QDialog *Decompress)
    {
        if (Decompress->objectName().isEmpty())
            Decompress->setObjectName("Decompress");
        Decompress->resize(613, 461);
        decom_sel = new QPushButton(Decompress);
        decom_sel->setObjectName("decom_sel");
        decom_sel->setGeometry(QRect(210, 90, 191, 29));
        Dodecompression = new QPushButton(Decompress);
        Dodecompression->setObjectName("Dodecompression");
        Dodecompression->setGeometry(QRect(210, 180, 191, 29));
        pushButton = new QPushButton(Decompress);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(260, 240, 83, 29));

        retranslateUi(Decompress);

        QMetaObject::connectSlotsByName(Decompress);
    } // setupUi

    void retranslateUi(QDialog *Decompress)
    {
        Decompress->setWindowTitle(QCoreApplication::translate("Decompress", "Dialog", nullptr));
        decom_sel->setText(QCoreApplication::translate("Decompress", "Select a file", nullptr));
        Dodecompression->setText(QCoreApplication::translate("Decompress", "do decompression", nullptr));
        pushButton->setText(QCoreApplication::translate("Decompress", "decompress", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Decompress: public Ui_Decompress {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DECOMPRESS_H
