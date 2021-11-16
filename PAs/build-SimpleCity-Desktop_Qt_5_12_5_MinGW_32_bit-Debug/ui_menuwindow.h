/********************************************************************************
** Form generated from reading UI file 'menuwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MENUWINDOW_H
#define UI_MENUWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MenuWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_logo;
    QStackedWidget *pages;
    QWidget *page_main;
    QVBoxLayout *verticalLayout;
    QLabel *label_simplecity;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btn_load;
    QPushButton *btn_new;
    QWidget *page_size_selection;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_select_grid_size;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *btn_decrease_size;
    QLabel *label_grid_size;
    QPushButton *btn_increase_size;
    QPushButton *btn_start_game;
    QLabel *label_ack;
    QLabel *label_ack2;

    void setupUi(QMainWindow *MenuWindow)
    {
        if (MenuWindow->objectName().isEmpty())
            MenuWindow->setObjectName(QString::fromUtf8("MenuWindow"));
        MenuWindow->resize(800, 500);
        centralwidget = new QWidget(MenuWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_logo = new QLabel(centralwidget);
        label_logo->setObjectName(QString::fromUtf8("label_logo"));
        label_logo->setPixmap(QPixmap(QString::fromUtf8(":/resources/images/apartment.png")));
        label_logo->setScaledContents(false);
        label_logo->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_logo);

        pages = new QStackedWidget(centralwidget);
        pages->setObjectName(QString::fromUtf8("pages"));
        page_main = new QWidget();
        page_main->setObjectName(QString::fromUtf8("page_main"));
        verticalLayout = new QVBoxLayout(page_main);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_simplecity = new QLabel(page_main);
        label_simplecity->setObjectName(QString::fromUtf8("label_simplecity"));
        QFont font;
        font.setFamily(QString::fromUtf8("Comic Sans MS"));
        font.setPointSize(40);
        font.setBold(true);
        font.setWeight(75);
        label_simplecity->setFont(font);
        label_simplecity->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_simplecity);

        widget = new QWidget(page_main);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        btn_load = new QPushButton(widget);
        btn_load->setObjectName(QString::fromUtf8("btn_load"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btn_load->sizePolicy().hasHeightForWidth());
        btn_load->setSizePolicy(sizePolicy);
        QFont font1;
        font1.setFamily(QString::fromUtf8("Comic Sans MS"));
        font1.setPointSize(30);
        btn_load->setFont(font1);
        btn_load->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);"));

        horizontalLayout_2->addWidget(btn_load);

        btn_new = new QPushButton(widget);
        btn_new->setObjectName(QString::fromUtf8("btn_new"));
        sizePolicy.setHeightForWidth(btn_new->sizePolicy().hasHeightForWidth());
        btn_new->setSizePolicy(sizePolicy);
        btn_new->setFont(font1);
        btn_new->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);"));

        horizontalLayout_2->addWidget(btn_new);


        verticalLayout->addWidget(widget);

        pages->addWidget(page_main);
        page_size_selection = new QWidget();
        page_size_selection->setObjectName(QString::fromUtf8("page_size_selection"));
        verticalLayout_3 = new QVBoxLayout(page_size_selection);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_select_grid_size = new QLabel(page_size_selection);
        label_select_grid_size->setObjectName(QString::fromUtf8("label_select_grid_size"));
        label_select_grid_size->setFont(font1);
        label_select_grid_size->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label_select_grid_size);

        widget_2 = new QWidget(page_size_selection);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        horizontalLayout_3 = new QHBoxLayout(widget_2);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        btn_decrease_size = new QPushButton(widget_2);
        btn_decrease_size->setObjectName(QString::fromUtf8("btn_decrease_size"));
        sizePolicy.setHeightForWidth(btn_decrease_size->sizePolicy().hasHeightForWidth());
        btn_decrease_size->setSizePolicy(sizePolicy);
        QFont font2;
        font2.setFamily(QString::fromUtf8("Comic Sans MS"));
        font2.setPointSize(20);
        btn_decrease_size->setFont(font2);
        btn_decrease_size->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);"));
        btn_decrease_size->setIconSize(QSize(80, 80));

        horizontalLayout_3->addWidget(btn_decrease_size);

        label_grid_size = new QLabel(widget_2);
        label_grid_size->setObjectName(QString::fromUtf8("label_grid_size"));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Comic Sans MS"));
        font3.setPointSize(40);
        label_grid_size->setFont(font3);
        label_grid_size->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(label_grid_size);

        btn_increase_size = new QPushButton(widget_2);
        btn_increase_size->setObjectName(QString::fromUtf8("btn_increase_size"));
        sizePolicy.setHeightForWidth(btn_increase_size->sizePolicy().hasHeightForWidth());
        btn_increase_size->setSizePolicy(sizePolicy);
        btn_increase_size->setFont(font2);
        btn_increase_size->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);"));
        btn_increase_size->setIconSize(QSize(80, 80));

        horizontalLayout_3->addWidget(btn_increase_size);


        verticalLayout_3->addWidget(widget_2);

        btn_start_game = new QPushButton(page_size_selection);
        btn_start_game->setObjectName(QString::fromUtf8("btn_start_game"));
        btn_start_game->setFont(font2);
        btn_start_game->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);"));

        verticalLayout_3->addWidget(btn_start_game);

        pages->addWidget(page_size_selection);

        verticalLayout_2->addWidget(pages);

        label_ack = new QLabel(centralwidget);
        label_ack->setObjectName(QString::fromUtf8("label_ack"));

        verticalLayout_2->addWidget(label_ack);

        label_ack2 = new QLabel(centralwidget);
        label_ack2->setObjectName(QString::fromUtf8("label_ack2"));

        verticalLayout_2->addWidget(label_ack2);

        MenuWindow->setCentralWidget(centralwidget);

        retranslateUi(MenuWindow);

        pages->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MenuWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MenuWindow)
    {
        MenuWindow->setWindowTitle(QApplication::translate("MenuWindow", "Simple City", nullptr));
        label_logo->setText(QString());
        label_simplecity->setText(QApplication::translate("MenuWindow", "Simple City", nullptr));
        btn_load->setText(QApplication::translate("MenuWindow", "Load City", nullptr));
        btn_new->setText(QApplication::translate("MenuWindow", "New City", nullptr));
        label_select_grid_size->setText(QApplication::translate("MenuWindow", "Select Map Size", nullptr));
        btn_decrease_size->setText(QString());
        label_grid_size->setText(QApplication::translate("MenuWindow", "20", nullptr));
        btn_increase_size->setText(QString());
        btn_start_game->setText(QApplication::translate("MenuWindow", "Start City", nullptr));
        label_ack->setText(QApplication::translate("MenuWindow", "Code and UI design by COMP2012H Teaching Team", nullptr));
        label_ack2->setText(QApplication::translate("MenuWindow", "Building icons / images by pixel32@opengameart.org ( https://opengameart.org/content/pixel-city-municipal-buildings )", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MenuWindow: public Ui_MenuWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MENUWINDOW_H
