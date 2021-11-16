/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "graphics.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    GameWidget *widget;
    QVBoxLayout *verticalLayout;
    QWidget *top_menu;
    QHBoxLayout *horizontalLayout_4;
    QToolButton *btn_next;
    QPushButton *btn_overlay_normal;
    QPushButton *btn_overlay_type;
    QPushButton *btn_overlay_neighbor;
    QWidget *side_menu;
    QFrame *side_menu_move;
    QVBoxLayout *verticalLayout_2;
    QFrame *side_menu_innermost;
    QGridLayout *gridLayout;
    QToolButton *btn_clinic;
    QToolButton *btn_apartment;
    QToolButton *btn_gold;
    QToolButton *btn_destruct;
    QToolButton *btn_silver;
    QToolButton *btn_house;
    QToolButton *btn_navigate;
    QToolButton *btn_hospital;
    QPushButton *btn_save_game;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1528, 948);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        widget = new GameWidget(MainWindow);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setStyleSheet(QString::fromUtf8("QWidget#centralwidget{\n"
"background-image: url(:/resources/images/stripes.png);\n"
"};"));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        top_menu = new QWidget(widget);
        top_menu->setObjectName(QString::fromUtf8("top_menu"));
        top_menu->setMinimumSize(QSize(0, 35));
        top_menu->setMaximumSize(QSize(16777215, 40));
        QFont font;
        font.setFamily(QString::fromUtf8("Comic Sans MS"));
        font.setPointSize(14);
        top_menu->setFont(font);
        horizontalLayout_4 = new QHBoxLayout(top_menu);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        btn_next = new QToolButton(top_menu);
        btn_next->setObjectName(QString::fromUtf8("btn_next"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btn_next->sizePolicy().hasHeightForWidth());
        btn_next->setSizePolicy(sizePolicy);
        btn_next->setMinimumSize(QSize(0, 30));
        btn_next->setFont(font);
        btn_next->setLayoutDirection(Qt::LeftToRight);
        btn_next->setStyleSheet(QString::fromUtf8("background-color: rgb(234, 234, 234);"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/resources/images/next.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_next->setIcon(icon);
        btn_next->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        horizontalLayout_4->addWidget(btn_next);

        btn_overlay_normal = new QPushButton(top_menu);
        btn_overlay_normal->setObjectName(QString::fromUtf8("btn_overlay_normal"));
        btn_overlay_normal->setMinimumSize(QSize(0, 30));
        btn_overlay_normal->setFont(font);

        horizontalLayout_4->addWidget(btn_overlay_normal);

        btn_overlay_type = new QPushButton(top_menu);
        btn_overlay_type->setObjectName(QString::fromUtf8("btn_overlay_type"));
        btn_overlay_type->setMinimumSize(QSize(0, 30));
        btn_overlay_type->setFont(font);

        horizontalLayout_4->addWidget(btn_overlay_type);

        btn_overlay_neighbor = new QPushButton(top_menu);
        btn_overlay_neighbor->setObjectName(QString::fromUtf8("btn_overlay_neighbor"));
        btn_overlay_neighbor->setMinimumSize(QSize(0, 30));
        btn_overlay_neighbor->setFont(font);

        horizontalLayout_4->addWidget(btn_overlay_neighbor);


        verticalLayout->addWidget(top_menu);

        side_menu = new QWidget(widget);
        side_menu->setObjectName(QString::fromUtf8("side_menu"));
        side_menu->setMaximumSize(QSize(400, 16777215));
        side_menu->setFont(font);
        side_menu->setLayoutDirection(Qt::RightToLeft);
        side_menu_move = new QFrame(side_menu);
        side_menu_move->setObjectName(QString::fromUtf8("side_menu_move"));
        side_menu_move->setGeometry(QRect(9, 9, 378, 831));
        side_menu_move->setLayoutDirection(Qt::LeftToRight);
        side_menu_move->setStyleSheet(QString::fromUtf8("background-color:rgba(255, 255, 255, 0);"));
        side_menu_move->setFrameShape(QFrame::StyledPanel);
        side_menu_move->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(side_menu_move);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        side_menu_innermost = new QFrame(side_menu_move);
        side_menu_innermost->setObjectName(QString::fromUtf8("side_menu_innermost"));
        side_menu_innermost->setMinimumSize(QSize(100, 0));
        side_menu_innermost->setMaximumSize(QSize(400, 16777215));
        side_menu_innermost->setFont(font);
        side_menu_innermost->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);"));
        side_menu_innermost->setFrameShape(QFrame::StyledPanel);
        side_menu_innermost->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(side_menu_innermost);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setHorizontalSpacing(6);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        btn_clinic = new QToolButton(side_menu_innermost);
        btn_clinic->setObjectName(QString::fromUtf8("btn_clinic"));
        btn_clinic->setMinimumSize(QSize(175, 0));
        btn_clinic->setFont(font);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/resources/images/clinic.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_clinic->setIcon(icon1);
        btn_clinic->setIconSize(QSize(150, 150));
        btn_clinic->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        gridLayout->addWidget(btn_clinic, 0, 0, 1, 1);

        btn_apartment = new QToolButton(side_menu_innermost);
        btn_apartment->setObjectName(QString::fromUtf8("btn_apartment"));
        btn_apartment->setMinimumSize(QSize(175, 0));
        btn_apartment->setFont(font);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/resources/images/apartment.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_apartment->setIcon(icon2);
        btn_apartment->setIconSize(QSize(150, 150));
        btn_apartment->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        gridLayout->addWidget(btn_apartment, 2, 2, 1, 1);

        btn_gold = new QToolButton(side_menu_innermost);
        btn_gold->setObjectName(QString::fromUtf8("btn_gold"));
        btn_gold->setMinimumSize(QSize(175, 0));
        btn_gold->setFont(font);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/resources/images/gold_mine.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_gold->setIcon(icon3);
        btn_gold->setIconSize(QSize(150, 150));
        btn_gold->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        gridLayout->addWidget(btn_gold, 1, 2, 1, 1);

        btn_destruct = new QToolButton(side_menu_innermost);
        btn_destruct->setObjectName(QString::fromUtf8("btn_destruct"));
        btn_destruct->setMinimumSize(QSize(175, 0));
        btn_destruct->setFont(font);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/resources/images/destruct.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_destruct->setIcon(icon4);
        btn_destruct->setIconSize(QSize(150, 150));
        btn_destruct->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        gridLayout->addWidget(btn_destruct, 3, 0, 1, 1);

        btn_silver = new QToolButton(side_menu_innermost);
        btn_silver->setObjectName(QString::fromUtf8("btn_silver"));
        btn_silver->setMinimumSize(QSize(175, 0));
        btn_silver->setFont(font);
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/resources/images/silver_mine.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_silver->setIcon(icon5);
        btn_silver->setIconSize(QSize(150, 150));
        btn_silver->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        gridLayout->addWidget(btn_silver, 1, 0, 1, 1);

        btn_house = new QToolButton(side_menu_innermost);
        btn_house->setObjectName(QString::fromUtf8("btn_house"));
        btn_house->setMinimumSize(QSize(175, 0));
        btn_house->setFont(font);
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/resources/images/house.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_house->setIcon(icon6);
        btn_house->setIconSize(QSize(150, 150));
        btn_house->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        gridLayout->addWidget(btn_house, 2, 0, 1, 1);

        btn_navigate = new QToolButton(side_menu_innermost);
        btn_navigate->setObjectName(QString::fromUtf8("btn_navigate"));
        btn_navigate->setMinimumSize(QSize(175, 0));
        btn_navigate->setFont(font);
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/resources/images/navigation.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_navigate->setIcon(icon7);
        btn_navigate->setIconSize(QSize(150, 150));
        btn_navigate->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        gridLayout->addWidget(btn_navigate, 3, 2, 1, 1);

        btn_hospital = new QToolButton(side_menu_innermost);
        btn_hospital->setObjectName(QString::fromUtf8("btn_hospital"));
        btn_hospital->setMinimumSize(QSize(175, 0));
        btn_hospital->setFont(font);
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/resources/images/hospital.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_hospital->setIcon(icon8);
        btn_hospital->setIconSize(QSize(150, 150));
        btn_hospital->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        gridLayout->addWidget(btn_hospital, 0, 2, 1, 1);


        verticalLayout_2->addWidget(side_menu_innermost);


        verticalLayout->addWidget(side_menu);

        btn_save_game = new QPushButton(widget);
        btn_save_game->setObjectName(QString::fromUtf8("btn_save_game"));
        btn_save_game->setFont(font);
        btn_save_game->setStyleSheet(QString::fromUtf8("background-color: rgb(234, 234, 234);"));

        verticalLayout->addWidget(btn_save_game);

        MainWindow->setCentralWidget(widget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Simple City", nullptr));
        btn_next->setText(QApplication::translate("MainWindow", "Next", nullptr));
        btn_overlay_normal->setText(QApplication::translate("MainWindow", "Normal Overlay", nullptr));
        btn_overlay_type->setText(QApplication::translate("MainWindow", "Type Overlay", nullptr));
        btn_overlay_neighbor->setText(QApplication::translate("MainWindow", "Neighbor Effects Overlay", nullptr));
        btn_clinic->setText(QApplication::translate("MainWindow", "Clinic", nullptr));
        btn_apartment->setText(QApplication::translate("MainWindow", "Apartment", nullptr));
        btn_gold->setText(QApplication::translate("MainWindow", "Gold Mine", nullptr));
        btn_destruct->setText(QApplication::translate("MainWindow", "Remove", nullptr));
        btn_silver->setText(QApplication::translate("MainWindow", "Silver Mine", nullptr));
        btn_house->setText(QApplication::translate("MainWindow", "House", nullptr));
        btn_navigate->setText(QApplication::translate("MainWindow", "Navigate", nullptr));
        btn_hospital->setText(QApplication::translate("MainWindow", "Hospital", nullptr));
        btn_save_game->setText(QApplication::translate("MainWindow", "Save City", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
