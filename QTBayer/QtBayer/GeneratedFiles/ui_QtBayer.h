/********************************************************************************
** Form generated from reading UI file 'QtBayer.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTBAYER_H
#define UI_QTBAYER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtBayerClass
{
public:
    QWidget *centralWidget;
    QLabel *label_input;
    QLabel *label_serial;
    QLabel *label_section;
    QLabel *label_for;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_ser;
    QLabel *label_sec;
    QLabel *label_for_2;
    QGroupBox *groupBox;
    QPushButton *pushButton_load;
    QPushButton *pushButton_serial;
    QPushButton *pushButton_section;
    QPushButton *pushButton_for;
    QLabel *label_6;
    QLabel *label_7;
    QPushButton *pushButton_savebit;
    QPushButton *pushButton_savebit_2;
    QLabel *label_8;
    QPushButton *pushButton_savebit_3;
    QLabel *label_9;
    QLabel *label_10;
    QTextBrowser *textBrowser_w;
    QTextBrowser *textBrowser_h;
    QLabel *label_ser_2;
    QLabel *label_ser_3;
    QPushButton *pushButton_info;
    QCheckBox *checkBox;
    QTextBrowser *textBrowser_ser;
    QTextBrowser *textBrowser_sec;
    QTextBrowser *textBrowser_for;
    QPushButton *input_z;
    QPushButton *serial_z;
    QPushButton *section_z;
    QPushButton *for_z;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QtBayerClass)
    {
        if (QtBayerClass->objectName().isEmpty())
            QtBayerClass->setObjectName(QStringLiteral("QtBayerClass"));
        QtBayerClass->resize(1146, 636);
        QtBayerClass->setLayoutDirection(Qt::LeftToRight);
        QtBayerClass->setStyleSheet(QStringLiteral("background-color: rgb(161, 161, 161);"));
        centralWidget = new QWidget(QtBayerClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label_input = new QLabel(centralWidget);
        label_input->setObjectName(QStringLiteral("label_input"));
        label_input->setGeometry(QRect(58, 30, 326, 244));
        label_input->setStyleSheet(QStringLiteral("background-color: rgb(203, 203, 203);"));
        label_serial = new QLabel(centralWidget);
        label_serial->setObjectName(QStringLiteral("label_serial"));
        label_serial->setGeometry(QRect(58, 320, 326, 244));
        label_serial->setStyleSheet(QStringLiteral("background-color: rgb(203, 203, 203);"));
        label_section = new QLabel(centralWidget);
        label_section->setObjectName(QStringLiteral("label_section"));
        label_section->setGeometry(QRect(404, 320, 326, 244));
        label_section->setStyleSheet(QStringLiteral("background-color: rgb(203, 203, 203);"));
        label_for = new QLabel(centralWidget);
        label_for->setObjectName(QStringLiteral("label_for"));
        label_for->setGeometry(QRect(750, 320, 326, 244));
        label_for->setStyleSheet(QStringLiteral("background-color: rgb(203, 203, 203);"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(178, 280, 71, 31));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(120, 580, 71, 31));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(440, 580, 141, 31));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(800, 580, 111, 31));
        label_ser = new QLabel(centralWidget);
        label_ser->setObjectName(QStringLiteral("label_ser"));
        label_ser->setGeometry(QRect(200, 580, 101, 31));
        label_sec = new QLabel(centralWidget);
        label_sec->setObjectName(QStringLiteral("label_sec"));
        label_sec->setGeometry(QRect(590, 580, 101, 31));
        label_for_2 = new QLabel(centralWidget);
        label_for_2->setObjectName(QStringLiteral("label_for_2"));
        label_for_2->setGeometry(QRect(920, 580, 101, 31));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(540, 20, 531, 251));
        QFont font;
        font.setFamily(QStringLiteral("Calibri"));
        font.setPointSize(15);
        font.setBold(true);
        font.setWeight(75);
        groupBox->setFont(font);
        pushButton_load = new QPushButton(groupBox);
        pushButton_load->setObjectName(QStringLiteral("pushButton_load"));
        pushButton_load->setGeometry(QRect(30, 90, 101, 31));
        QFont font1;
        font1.setPointSize(11);
        font1.setBold(true);
        font1.setWeight(75);
        pushButton_load->setFont(font1);
        pushButton_serial = new QPushButton(groupBox);
        pushButton_serial->setObjectName(QStringLiteral("pushButton_serial"));
        pushButton_serial->setGeometry(QRect(250, 90, 71, 31));
        pushButton_serial->setFont(font1);
        pushButton_section = new QPushButton(groupBox);
        pushButton_section->setObjectName(QStringLiteral("pushButton_section"));
        pushButton_section->setGeometry(QRect(250, 140, 71, 31));
        pushButton_section->setFont(font1);
        pushButton_for = new QPushButton(groupBox);
        pushButton_for->setObjectName(QStringLiteral("pushButton_for"));
        pushButton_for->setGeometry(QRect(250, 190, 71, 31));
        pushButton_for->setFont(font1);
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(170, 140, 71, 31));
        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(170, 190, 71, 31));
        pushButton_savebit = new QPushButton(groupBox);
        pushButton_savebit->setObjectName(QStringLiteral("pushButton_savebit"));
        pushButton_savebit->setGeometry(QRect(360, 90, 121, 28));
        pushButton_savebit->setFont(font1);
        pushButton_savebit_2 = new QPushButton(groupBox);
        pushButton_savebit_2->setObjectName(QStringLiteral("pushButton_savebit_2"));
        pushButton_savebit_2->setGeometry(QRect(360, 140, 121, 31));
        pushButton_savebit_2->setFont(font1);
        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(380, 50, 71, 31));
        pushButton_savebit_3 = new QPushButton(groupBox);
        pushButton_savebit_3->setObjectName(QStringLiteral("pushButton_savebit_3"));
        pushButton_savebit_3->setGeometry(QRect(360, 190, 121, 31));
        pushButton_savebit_3->setFont(font1);
        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(40, 50, 71, 31));
        label_10 = new QLabel(groupBox);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(190, 50, 101, 31));
        textBrowser_w = new QTextBrowser(groupBox);
        textBrowser_w->setObjectName(QStringLiteral("textBrowser_w"));
        textBrowser_w->setGeometry(QRect(90, 150, 51, 31));
        QFont font2;
        font2.setPointSize(12);
        font2.setBold(true);
        font2.setWeight(75);
        textBrowser_w->setFont(font2);
        textBrowser_w->setLayoutDirection(Qt::RightToLeft);
        textBrowser_w->setFrameShape(QFrame::NoFrame);
        textBrowser_h = new QTextBrowser(groupBox);
        textBrowser_h->setObjectName(QStringLiteral("textBrowser_h"));
        textBrowser_h->setGeometry(QRect(90, 190, 51, 31));
        textBrowser_h->setFont(font2);
        textBrowser_h->setLayoutDirection(Qt::RightToLeft);
        textBrowser_h->setFrameShape(QFrame::NoFrame);
        label_ser_2 = new QLabel(groupBox);
        label_ser_2->setObjectName(QStringLiteral("label_ser_2"));
        label_ser_2->setGeometry(QRect(20, 150, 101, 31));
        label_ser_3 = new QLabel(groupBox);
        label_ser_3->setObjectName(QStringLiteral("label_ser_3"));
        label_ser_3->setGeometry(QRect(20, 190, 101, 31));
        pushButton_info = new QPushButton(groupBox);
        pushButton_info->setObjectName(QStringLiteral("pushButton_info"));
        pushButton_info->setGeometry(QRect(490, 190, 31, 31));
        pushButton_info->setFont(font1);
        checkBox = new QCheckBox(groupBox);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(170, 90, 71, 31));
        checkBox->setFont(font1);
        pushButton_load->raise();
        pushButton_serial->raise();
        pushButton_section->raise();
        pushButton_for->raise();
        label_6->raise();
        label_7->raise();
        pushButton_savebit->raise();
        pushButton_savebit_2->raise();
        label_8->raise();
        pushButton_savebit_3->raise();
        label_9->raise();
        label_10->raise();
        label_ser_2->raise();
        label_ser_3->raise();
        textBrowser_w->raise();
        textBrowser_h->raise();
        pushButton_info->raise();
        checkBox->raise();
        textBrowser_ser = new QTextBrowser(centralWidget);
        textBrowser_ser->setObjectName(QStringLiteral("textBrowser_ser"));
        textBrowser_ser->setGeometry(QRect(190, 580, 81, 31));
        textBrowser_ser->setFont(font2);
        textBrowser_ser->setLayoutDirection(Qt::RightToLeft);
        textBrowser_ser->setFrameShape(QFrame::NoFrame);
        textBrowser_sec = new QTextBrowser(centralWidget);
        textBrowser_sec->setObjectName(QStringLiteral("textBrowser_sec"));
        textBrowser_sec->setGeometry(QRect(580, 580, 81, 31));
        textBrowser_sec->setFont(font2);
        textBrowser_sec->setLayoutDirection(Qt::RightToLeft);
        textBrowser_sec->setFrameShape(QFrame::NoFrame);
        textBrowser_for = new QTextBrowser(centralWidget);
        textBrowser_for->setObjectName(QStringLiteral("textBrowser_for"));
        textBrowser_for->setGeometry(QRect(910, 580, 81, 31));
        textBrowser_for->setFont(font2);
        textBrowser_for->setLayoutDirection(Qt::RightToLeft);
        textBrowser_for->setFrameShape(QFrame::NoFrame);
        input_z = new QPushButton(centralWidget);
        input_z->setObjectName(QStringLiteral("input_z"));
        input_z->setGeometry(QRect(363, 280, 21, 21));
        serial_z = new QPushButton(centralWidget);
        serial_z->setObjectName(QStringLiteral("serial_z"));
        serial_z->setGeometry(QRect(363, 570, 21, 21));
        section_z = new QPushButton(centralWidget);
        section_z->setObjectName(QStringLiteral("section_z"));
        section_z->setGeometry(QRect(709, 570, 21, 21));
        for_z = new QPushButton(centralWidget);
        for_z->setObjectName(QStringLiteral("for_z"));
        for_z->setGeometry(QRect(1055, 570, 21, 21));
        QtBayerClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(QtBayerClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        QtBayerClass->setStatusBar(statusBar);

        retranslateUi(QtBayerClass);
        QObject::connect(pushButton_load, SIGNAL(clicked()), QtBayerClass, SLOT(LoadRawImage()));
        QObject::connect(pushButton_serial, SIGNAL(clicked()), QtBayerClass, SLOT(serial()));
        QObject::connect(pushButton_section, SIGNAL(clicked()), QtBayerClass, SLOT(pa_section()));
        QObject::connect(pushButton_for, SIGNAL(clicked()), QtBayerClass, SLOT(pa_for()));
        QObject::connect(pushButton_savebit, SIGNAL(clicked()), QtBayerClass, SLOT(serial_save()));
        QObject::connect(pushButton_savebit_2, SIGNAL(clicked()), QtBayerClass, SLOT(section_save()));
        QObject::connect(pushButton_savebit_3, SIGNAL(clicked()), QtBayerClass, SLOT(for_save()));
        QObject::connect(input_z, SIGNAL(clicked()), QtBayerClass, SLOT(inputzoom()));
        QObject::connect(serial_z, SIGNAL(clicked()), QtBayerClass, SLOT(serialzoom()));
        QObject::connect(section_z, SIGNAL(clicked()), QtBayerClass, SLOT(sectionzoom()));
        QObject::connect(for_z, SIGNAL(clicked()), QtBayerClass, SLOT(forzoom()));
        QObject::connect(pushButton_info, SIGNAL(clicked()), QtBayerClass, SLOT(show_info()));
        QObject::connect(checkBox, SIGNAL(toggled(bool)), QtBayerClass, SLOT(check_round()));

        QMetaObject::connectSlotsByName(QtBayerClass);
    } // setupUi

    void retranslateUi(QMainWindow *QtBayerClass)
    {
        QtBayerClass->setWindowTitle(QApplication::translate("QtBayerClass", "Demosaic(8bit->10bit)", Q_NULLPTR));
        label_input->setText(QString());
        label_serial->setText(QString());
        label_section->setText(QString());
        label_for->setText(QString());
        label->setText(QApplication::translate("QtBayerClass", "<html><head/><body><p align=\"center\"><span style=\" font-size:12pt; font-weight:600;\">input</span></p></body></html>", Q_NULLPTR));
        label_2->setText(QApplication::translate("QtBayerClass", "<html><head/><body><p align=\"center\"><span style=\" font-size:12pt; font-weight:600;\">serial :</span></p></body></html>", Q_NULLPTR));
        label_3->setText(QApplication::translate("QtBayerClass", "<html><head/><body><p align=\"center\"><span style=\" font-size:12pt; font-weight:600;\">parallel section :</span></p></body></html>", Q_NULLPTR));
        label_4->setText(QApplication::translate("QtBayerClass", "<html><head/><body><p align=\"center\"><span style=\" font-size:12pt; font-weight:600;\">parallel for :</span></p></body></html>", Q_NULLPTR));
        label_ser->setText(QApplication::translate("QtBayerClass", "<html><head/><body><p align=\"right\"><span style=\" font-size:12pt; font-weight:600;\">ms</span></p></body></html>", Q_NULLPTR));
        label_sec->setText(QApplication::translate("QtBayerClass", "<html><head/><body><p align=\"right\"><span style=\" font-size:12pt; font-weight:600;\">ms</span></p></body></html>", Q_NULLPTR));
        label_for_2->setText(QApplication::translate("QtBayerClass", "<html><head/><body><p align=\"right\"><span style=\" font-size:12pt; font-weight:600;\">ms</span></p></body></html>", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("QtBayerClass", "Demosaicing", Q_NULLPTR));
        pushButton_load->setText(QApplication::translate("QtBayerClass", "RAW image", Q_NULLPTR));
        pushButton_serial->setText(QApplication::translate("QtBayerClass", "serial", Q_NULLPTR));
        pushButton_section->setText(QApplication::translate("QtBayerClass", "section", Q_NULLPTR));
        pushButton_for->setText(QApplication::translate("QtBayerClass", "for", Q_NULLPTR));
        label_6->setText(QApplication::translate("QtBayerClass", "<html><head/><body><p align=\"center\"><span style=\" font-size:12pt; font-weight:600;\">parallel</span></p></body></html>", Q_NULLPTR));
        label_7->setText(QApplication::translate("QtBayerClass", "<html><head/><body><p align=\"center\"><span style=\" font-size:12pt; font-weight:600;\">parallel</span></p></body></html>", Q_NULLPTR));
        pushButton_savebit->setText(QApplication::translate("QtBayerClass", "serial result", Q_NULLPTR));
        pushButton_savebit_2->setText(QApplication::translate("QtBayerClass", "section result", Q_NULLPTR));
        label_8->setText(QApplication::translate("QtBayerClass", "<html><head/><body><p align=\"center\"><span style=\" font-size:12pt; font-weight:600;\">Save</span></p></body></html>", Q_NULLPTR));
        pushButton_savebit_3->setText(QApplication::translate("QtBayerClass", "for result", Q_NULLPTR));
        label_9->setText(QApplication::translate("QtBayerClass", "<html><head/><body><p align=\"center\"><span style=\" font-size:12pt; font-weight:600;\">Load</span></p></body></html>", Q_NULLPTR));
        label_10->setText(QApplication::translate("QtBayerClass", "<html><head/><body><p align=\"center\"><span style=\" font-size:12pt; font-weight:600;\">Demosaic</span></p></body></html>", Q_NULLPTR));
        textBrowser_w->setHtml(QApplication::translate("QtBayerClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Gulim'; font-size:12pt; font-weight:600; font-style:normal;\">\n"
"<p align=\"right\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:9pt; font-weight:400;\"><br /></p></body></html>", Q_NULLPTR));
        textBrowser_h->setHtml(QApplication::translate("QtBayerClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Gulim'; font-size:12pt; font-weight:600; font-style:normal;\">\n"
"<p align=\"right\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:9pt; font-weight:400;\"><br /></p></body></html>", Q_NULLPTR));
        label_ser_2->setText(QApplication::translate("QtBayerClass", "<html><head/><body><p><span style=\" font-size:12pt; font-weight:600;\">width  :</span></p></body></html>", Q_NULLPTR));
        label_ser_3->setText(QApplication::translate("QtBayerClass", "<html><head/><body><p><span style=\" font-size:12pt; font-weight:600;\">height :</span></p></body></html>", Q_NULLPTR));
        pushButton_info->setText(QString());
        checkBox->setText(QApplication::translate("QtBayerClass", "Round", Q_NULLPTR));
        textBrowser_ser->setHtml(QApplication::translate("QtBayerClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Gulim'; font-size:12pt; font-weight:600; font-style:normal;\">\n"
"<p align=\"right\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:9pt; font-weight:400;\"><br /></p></body></html>", Q_NULLPTR));
        textBrowser_sec->setHtml(QApplication::translate("QtBayerClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Gulim'; font-size:12pt; font-weight:600; font-style:normal;\">\n"
"<p align=\"right\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:9pt; font-weight:400;\"><br /></p></body></html>", Q_NULLPTR));
        textBrowser_for->setHtml(QApplication::translate("QtBayerClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Gulim'; font-size:12pt; font-weight:600; font-style:normal;\">\n"
"<p align=\"right\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:9pt; font-weight:400;\"><br /></p></body></html>", Q_NULLPTR));
        input_z->setText(QString());
        serial_z->setText(QString());
        section_z->setText(QString());
        for_z->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class QtBayerClass: public Ui_QtBayerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTBAYER_H
