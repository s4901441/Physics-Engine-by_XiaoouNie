/********************************************************************************
** Form generated from reading UI file 'MainWindow_copy.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_COPY_H
#define UI_MAINWINDOW_COPY_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QOpenGLWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_XiaouLibrary
{
public:
    QWidget *centralwidget;
    QOpenGLWidget *openGLWidget;
    QFrame *line;
    QLabel *label;
    QTextEdit *textEdit;
    QLineEdit *lineEdit;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_3;
    QCheckBox *checkBox_4;
    QSlider *horizontalSlider;
    QSlider *horizontalSlider_2;
    QTextEdit *textEdit_2;
    QSlider *horizontalSlider_3;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QMenuBar *menubar;
    QMenu *menuMain_Window;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *XiaouLibrary)
    {
        if (XiaouLibrary->objectName().isEmpty())
            XiaouLibrary->setObjectName(QStringLiteral("XiaouLibrary"));
        XiaouLibrary->resize(1175, 686);
        XiaouLibrary->setMouseTracking(true);
        centralwidget = new QWidget(XiaouLibrary);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        openGLWidget = new QOpenGLWidget(centralwidget);
        openGLWidget->setObjectName(QStringLiteral("openGLWidget"));
        openGLWidget->setGeometry(QRect(320, 30, 811, 591));
        line = new QFrame(centralwidget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(290, 20, 20, 601));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(40, 200, 111, 21));
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(150, 200, 131, 21));
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(200, 260, 81, 21));
        checkBox = new QCheckBox(centralwidget);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(30, 230, 91, 31));
        checkBox_2 = new QCheckBox(centralwidget);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));
        checkBox_2->setGeometry(QRect(30, 300, 161, 31));
        checkBox_3 = new QCheckBox(centralwidget);
        checkBox_3->setObjectName(QStringLiteral("checkBox_3"));
        checkBox_3->setGeometry(QRect(30, 390, 211, 31));
        checkBox_4 = new QCheckBox(centralwidget);
        checkBox_4->setObjectName(QStringLiteral("checkBox_4"));
        checkBox_4->setGeometry(QRect(30, 160, 171, 31));
        horizontalSlider = new QSlider(centralwidget);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(110, 240, 160, 16));
        horizontalSlider->setOrientation(Qt::Horizontal);
        horizontalSlider_2 = new QSlider(centralwidget);
        horizontalSlider_2->setObjectName(QStringLiteral("horizontalSlider_2"));
        horizontalSlider_2->setGeometry(QRect(110, 340, 160, 16));
        horizontalSlider_2->setOrientation(Qt::Horizontal);
        textEdit_2 = new QTextEdit(centralwidget);
        textEdit_2->setObjectName(QStringLiteral("textEdit_2"));
        textEdit_2->setGeometry(QRect(200, 360, 81, 21));
        horizontalSlider_3 = new QSlider(centralwidget);
        horizontalSlider_3->setObjectName(QStringLiteral("horizontalSlider_3"));
        horizontalSlider_3->setGeometry(QRect(110, 430, 160, 16));
        horizontalSlider_3->setOrientation(Qt::Horizontal);
        widget = new QWidget(centralwidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(30, 580, 241, 31));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(widget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);

        XiaouLibrary->setCentralWidget(centralwidget);
        openGLWidget->raise();
        line->raise();
        pushButton->raise();
        pushButton_2->raise();
        label->raise();
        textEdit->raise();
        pushButton_2->raise();
        lineEdit->raise();
        checkBox->raise();
        checkBox_2->raise();
        checkBox_3->raise();
        checkBox_4->raise();
        horizontalSlider->raise();
        horizontalSlider_2->raise();
        textEdit_2->raise();
        horizontalSlider_3->raise();
        menubar = new QMenuBar(XiaouLibrary);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1175, 26));
        menuMain_Window = new QMenu(menubar);
        menuMain_Window->setObjectName(QStringLiteral("menuMain_Window"));
        XiaouLibrary->setMenuBar(menubar);
        statusbar = new QStatusBar(XiaouLibrary);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        XiaouLibrary->setStatusBar(statusbar);
#ifndef QT_NO_SHORTCUT
        label->setBuddy(textEdit);
#endif // QT_NO_SHORTCUT

        menubar->addAction(menuMain_Window->menuAction());

        retranslateUi(XiaouLibrary);

        QMetaObject::connectSlotsByName(XiaouLibrary);
    } // setupUi

    void retranslateUi(QMainWindow *XiaouLibrary)
    {
        XiaouLibrary->setWindowTitle(QApplication::translate("XiaouLibrary", "MainWindow", Q_NULLPTR));
        label->setText(QApplication::translate("XiaouLibrary", "Particle Count", Q_NULLPTR));
        checkBox->setText(QApplication::translate("XiaouLibrary", "Gravity", Q_NULLPTR));
        checkBox_2->setText(QApplication::translate("XiaouLibrary", "Collide with Object", Q_NULLPTR));
        checkBox_3->setText(QApplication::translate("XiaouLibrary", "Collide with Particles", Q_NULLPTR));
        checkBox_4->setText(QApplication::translate("XiaouLibrary", "Enable Particles", Q_NULLPTR));
        pushButton->setText(QApplication::translate("XiaouLibrary", "Reset", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("XiaouLibrary", "Simulate", Q_NULLPTR));
        menuMain_Window->setTitle(QApplication::translate("XiaouLibrary", "RigidBody", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class XiaouLibrary: public Ui_XiaouLibrary {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_COPY_H
