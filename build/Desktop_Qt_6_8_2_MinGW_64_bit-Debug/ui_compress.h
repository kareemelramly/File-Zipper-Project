/********************************************************************************
** Form generated from reading UI file 'compress.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMPRESS_H
#define UI_COMPRESS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_compress
{
public:
    QPushButton *com_sel;
    QPushButton *docompression;
    QLabel *percentageLabel;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *before;
    QLabel *after;

    void setupUi(QDialog *compress)
    {
        if (compress->objectName().isEmpty())
            compress->setObjectName("compress");
        compress->resize(690, 540);
        com_sel = new QPushButton(compress);
        com_sel->setObjectName("com_sel");
        com_sel->setGeometry(QRect(200, 150, 251, 31));
        docompression = new QPushButton(compress);
        docompression->setObjectName("docompression");
        docompression->setGeometry(QRect(200, 240, 251, 29));
        percentageLabel = new QLabel(compress);
        percentageLabel->setObjectName("percentageLabel");
        percentageLabel->setGeometry(QRect(410, 320, 63, 20));
        label = new QLabel(compress);
        label->setObjectName("label");
        label->setGeometry(QRect(210, 320, 181, 20));
        label_2 = new QLabel(compress);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(210, 350, 81, 20));
        label_3 = new QLabel(compress);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(210, 380, 71, 20));
        before = new QLabel(compress);
        before->setObjectName("before");
        before->setGeometry(QRect(310, 350, 63, 20));
        after = new QLabel(compress);
        after->setObjectName("after");
        after->setGeometry(QRect(310, 380, 63, 20));

        retranslateUi(compress);

        QMetaObject::connectSlotsByName(compress);
    } // setupUi

    void retranslateUi(QDialog *compress)
    {
        compress->setWindowTitle(QCoreApplication::translate("compress", "Dialog", nullptr));
        com_sel->setText(QCoreApplication::translate("compress", "select file ", nullptr));
        docompression->setText(QCoreApplication::translate("compress", "Do compression", nullptr));
        percentageLabel->setText(QCoreApplication::translate("compress", "0%", nullptr));
        label->setText(QCoreApplication::translate("compress", "Compression Percentage: ", nullptr));
        label_2->setText(QCoreApplication::translate("compress", "size before:", nullptr));
        label_3->setText(QCoreApplication::translate("compress", "size after:", nullptr));
        before->setText(QString());
        after->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class compress: public Ui_compress {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMPRESS_H
