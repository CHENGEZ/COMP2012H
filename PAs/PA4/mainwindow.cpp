#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "City.h"

#include <QString>
#include <QTimer>
#include <QFileDialog>
#include <QMainWindow>
#include <QtDebug>

const QString BTN_RELEASED_STYLE = "background-color: rgba(50, 127, 127, 255);";
const QString BTN_SELECTED_STYLE = "background-color: rgba(255, 255, 255, 255);";

MainWindow::MainWindow(City *const city, QWidget *parent) : QMainWindow(parent),
                                                            ui(new Ui::MainWindow),
                                                            city(city),
                                                            selected_side_menu_button(SideMenuButton::NAVIGATE),
                                                            selected_overlay_button(OverlayButton::NORMAL),
                                                            side_menu_status(SideMenuStatus::HIDDEN)
{
    ui->setupUi(this);

    initialize_overlay_buttons();
    initialize_side_menu_buttons();

    // Run main loop
    loop_timer = new QTimer{this};
    connect(loop_timer, &QTimer::timeout, this, &MainWindow::main_loop);
    // 50 updates per second
    loop_timer->start(20);

    ui->side_menu_move->move(400, 0);
    ui->side_menu->setMaximumWidth(0);
}

void MainWindow::initialize_side_menu_buttons()
{
    ui->btn_clinic->setText(ui->btn_clinic->text() + " $" + QString::number(Clinic::cost));
    ui->btn_hospital->setText(ui->btn_hospital->text() + " $" + QString::number(Hospital::cost));
    ui->btn_silver->setText(ui->btn_silver->text() + " $" + QString::number(SilverMine::cost));
    ui->btn_gold->setText(ui->btn_gold->text() + " $" + QString::number(GoldMine::cost));
    ui->btn_house->setText(ui->btn_house->text() + " $" + QString::number(House::cost));
    ui->btn_apartment->setText(ui->btn_apartment->text() + " $" + QString::number(Apartment::cost));

    // START OF YOUR IMPLEMENTATION
    ui->btn_navigate->setStyleSheet(BTN_SELECTED_STYLE);
    ui->btn_apartment->setStyleSheet(BTN_RELEASED_STYLE);
    ui->btn_house->setStyleSheet(BTN_RELEASED_STYLE);
    ui->btn_hospital->setStyleSheet(BTN_RELEASED_STYLE);
    ui->btn_clinic->setStyleSheet(BTN_RELEASED_STYLE);
    ui->btn_gold->setStyleSheet(BTN_RELEASED_STYLE);
    ui->btn_silver->setStyleSheet(BTN_RELEASED_STYLE);
    ui->btn_destruct->setStyleSheet(BTN_RELEASED_STYLE);
    // END OF YOUR IMPLEMENTATION
}

void MainWindow::on_btn_next_clicked()
{
    go_to_next_step();
}

void MainWindow::on_btn_save_game_clicked()
{
    save_current_game();
}

void MainWindow::go_to_next_step()
{
    city->move_to_next_turn();
}

void MainWindow::save_current_game()
{
    QString file_to_save = QFileDialog::getSaveFileName(this, "Choose a file to save", "E:/HKUST/yr2_fall/comp2012H/PAs/PA4");

    city->save(file_to_save.toStdString());
}

void MainWindow::initialize_overlay_buttons()
{
    // START OF YOUR IMPLEMENTATION
    ui->btn_overlay_normal->setStyleSheet(BTN_SELECTED_STYLE);
    ui->btn_overlay_neighbor->setStyleSheet(BTN_RELEASED_STYLE);
    ui->btn_overlay_type->setStyleSheet(BTN_RELEASED_STYLE);
    // END OF YOUR IMPLEMENTATION
}

MainWindow::~MainWindow()
{
    delete ui;
    loop_timer->stop();
    delete loop_timer;
    delete city;
}

MainWindow::SideMenuButton MainWindow::get_selected_side_menu_button()
{
    return selected_side_menu_button;
}

MainWindow::OverlayButton MainWindow::get_selected_overlay_button()
{
    return selected_overlay_button;
}

MainWindow::SideMenuStatus MainWindow::get_side_menu_status()
{
    return side_menu_status;
}

void MainWindow::set_side_menu_status(SideMenuStatus status)
{
    side_menu_status = status;
}

void MainWindow::on_side_menu_button_clicked(SideMenuButton button)
{
    // START OF YOUR IMPLEMENTATION
    switch (button)
    {
    case SideMenuButton::NAVIGATE:
        ui->btn_navigate->setStyleSheet(BTN_SELECTED_STYLE);
        ui->btn_apartment->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_house->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_hospital->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_clinic->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_gold->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_silver->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_destruct->setStyleSheet(BTN_RELEASED_STYLE);
        selected_side_menu_button = SideMenuButton::NAVIGATE;
        break;
    case SideMenuButton::DEMOLISH:
        ui->btn_navigate->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_apartment->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_house->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_hospital->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_clinic->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_gold->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_silver->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_destruct->setStyleSheet(BTN_SELECTED_STYLE);
        selected_side_menu_button = SideMenuButton::DEMOLISH;
        break;
    case SideMenuButton::APARTMENT:
        ui->btn_house->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_hospital->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_clinic->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_gold->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_silver->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_destruct->setStyleSheet(BTN_RELEASED_STYLE);

        if (city->can_construct(Building::Type::APARTMENT))
        {
            ui->btn_navigate->setStyleSheet(BTN_RELEASED_STYLE);
            ui->btn_apartment->setStyleSheet(BTN_SELECTED_STYLE);
            selected_side_menu_button = SideMenuButton::APARTMENT;
        }
        else
        {
            ui->btn_navigate->setStyleSheet(BTN_SELECTED_STYLE);
            ui->btn_apartment->setStyleSheet(BTN_RELEASED_STYLE);
            selected_side_menu_button = SideMenuButton::NAVIGATE;
        }

        break;
    case SideMenuButton::HOUSE:

        ui->btn_apartment->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_hospital->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_clinic->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_gold->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_silver->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_destruct->setStyleSheet(BTN_RELEASED_STYLE);
        if (city->can_construct(Building::Type::HOUSE))
        {
            ui->btn_navigate->setStyleSheet(BTN_RELEASED_STYLE);
            ui->btn_house->setStyleSheet(BTN_SELECTED_STYLE);
            selected_side_menu_button = SideMenuButton::HOUSE;
        }
        else
        {
            ui->btn_navigate->setStyleSheet(BTN_SELECTED_STYLE);
            ui->btn_house->setStyleSheet(BTN_RELEASED_STYLE);
            selected_side_menu_button = SideMenuButton::NAVIGATE;
        }

        break;
    case SideMenuButton::HOSPITAL:
        ui->btn_apartment->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_house->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_clinic->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_gold->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_silver->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_destruct->setStyleSheet(BTN_RELEASED_STYLE);
        if (city->can_construct(Building::Type::HOSPITAL))
        {
            ui->btn_navigate->setStyleSheet(BTN_RELEASED_STYLE);
            ui->btn_hospital->setStyleSheet(BTN_SELECTED_STYLE);
            selected_side_menu_button = SideMenuButton::HOSPITAL;
        }
        else
        {
            ui->btn_navigate->setStyleSheet(BTN_SELECTED_STYLE);
            ui->btn_hospital->setStyleSheet(BTN_RELEASED_STYLE);
            selected_side_menu_button = SideMenuButton::NAVIGATE;
        }

        break;
    case SideMenuButton::CLINIC:
        ui->btn_apartment->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_house->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_hospital->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_gold->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_silver->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_destruct->setStyleSheet(BTN_RELEASED_STYLE);
        if (city->can_construct(Building::Type::CLINIC))
        {
            ui->btn_navigate->setStyleSheet(BTN_RELEASED_STYLE);
            ui->btn_clinic->setStyleSheet(BTN_SELECTED_STYLE);
            selected_side_menu_button = SideMenuButton::CLINIC;
        }
        else
        {
            ui->btn_navigate->setStyleSheet(BTN_SELECTED_STYLE);
            ui->btn_clinic->setStyleSheet(BTN_RELEASED_STYLE);
            selected_side_menu_button = SideMenuButton::NAVIGATE;
        }

        break;

    case SideMenuButton::GOLD_MINE:
        ui->btn_apartment->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_house->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_hospital->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_clinic->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_silver->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_destruct->setStyleSheet(BTN_RELEASED_STYLE);
        if (city->can_construct(Building::Type::GOLD_MINE))
        {
            ui->btn_navigate->setStyleSheet(BTN_RELEASED_STYLE);
            ui->btn_gold->setStyleSheet(BTN_SELECTED_STYLE);
            selected_side_menu_button = SideMenuButton::GOLD_MINE;
        }
        else
        {
            ui->btn_navigate->setStyleSheet(BTN_SELECTED_STYLE);
            ui->btn_gold->setStyleSheet(BTN_RELEASED_STYLE);
            selected_side_menu_button = SideMenuButton::NAVIGATE;
        }

        break;

    case SideMenuButton::SILVER_MINE:
        ui->btn_apartment->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_house->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_hospital->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_clinic->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_gold->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_destruct->setStyleSheet(BTN_RELEASED_STYLE);
        if (city->can_construct(Building::Type::SILVER_MINE))
        {
            ui->btn_navigate->setStyleSheet(BTN_RELEASED_STYLE);
            ui->btn_silver->setStyleSheet(BTN_SELECTED_STYLE);
            selected_side_menu_button = SideMenuButton::SILVER_MINE;
        }
        else
        {
            ui->btn_navigate->setStyleSheet(BTN_SELECTED_STYLE);
            ui->btn_silver->setStyleSheet(BTN_RELEASED_STYLE);
            selected_side_menu_button = SideMenuButton::NAVIGATE;
        }

        break;

    default:
        break;
    }

    // END OF YOUR IMPLEMENTATION
}

void MainWindow::on_overlay_button_clicked(OverlayButton button)
{
    // START OF YOUR IMPLEMENTATION
    switch (button)
    {
    case OverlayButton::NORMAL:
        ui->btn_overlay_normal->setStyleSheet(BTN_SELECTED_STYLE);
        ui->btn_overlay_neighbor->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_overlay_type->setStyleSheet(BTN_RELEASED_STYLE);
        break;
    case OverlayButton::NEIGHBOR:
        ui->btn_overlay_normal->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_overlay_neighbor->setStyleSheet(BTN_SELECTED_STYLE);
        ui->btn_overlay_type->setStyleSheet(BTN_RELEASED_STYLE);
        break;
    case OverlayButton::TYPE:
        ui->btn_overlay_normal->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_overlay_neighbor->setStyleSheet(BTN_RELEASED_STYLE);
        ui->btn_overlay_type->setStyleSheet(BTN_SELECTED_STYLE);
        break;

    default:
        break;
    }

    selected_overlay_button = button;

    // END OF YOUR IMPLEMENTATION
}

// This is called 50 times per second
void MainWindow::main_loop()
{
    int current_x = ui->side_menu_move->x();
    int current_y = ui->side_menu_move->y();
    switch (side_menu_status)
    {
    case SideMenuStatus::HIDDEN:
        // qDebug()<<"Hidden"<<current_x;
        break;

    case SideMenuStatus::HIDDEN_TO_VISIBLE:
        ui->side_menu->setMaximumWidth(400);
        if (current_x - 10 <= 0)
        {
            side_menu_status = SideMenuStatus::VISIBLE;
        }
        else
        {
            /*decrease the x-coordinate of MainWindow::ui->side_menu_move by fixed steps (e.g. 10), to a minimum of 0. */
            ui->side_menu_move->move(current_x - 10, current_y);
        }
        // qDebug()<< "Hidden -> Visible" << current_x;
        break;

    case SideMenuStatus::VISIBLE:
        // qDebug()<<"Visible"<<current_x;
        break;

    case SideMenuStatus::VISIBLE_TO_HIDDEN:
        if (current_x + 10 >= 400)
        {
            side_menu_status = SideMenuStatus::HIDDEN;
            ui->side_menu->setMaximumWidth(0);
        }
        else
        {
            /* increase the x-coordinate of MainWindow::ui->side_menu_move by fixed steps (e.g. 10), to a maximum of 400. */
            ui->side_menu_move->move(current_x + 10, current_y);
        }
        // qDebug()<<"Visible -> Hidden"<<current_x;
        break;

    default:
        break;
    }
    ui->side_menu_move->setFixedWidth(ui->side_menu->width());
    ui->side_menu_move->setFixedHeight(ui->side_menu->height());

    ui->widget->loop();
}
