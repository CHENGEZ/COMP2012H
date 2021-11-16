#include "menuwindow.h"
#include "ui_menuwindow.h"
#include "mainwindow.h"
#include "City.h"

#include <QPixmap>
#include <QFileDialog>
#include <QMessageBox>

MenuWindow::MenuWindow(QWidget *parent) : QMainWindow(parent),
                                          ui(new Ui::MenuWindow),
                                          selected_grid_size(20)
{
    ui->setupUi(this);

    // Scale label logo pixmap
    const QPixmap *p = ui->label_logo->pixmap();
    const int SCALE = 4;
    ui->label_logo->setPixmap(p->scaled(p->width() * SCALE, p->height() * SCALE));

    // Set pixmap for increase and decrease size buttons
    QPixmap increase{":/resources/images/next.png"};
    QPixmap decrease = increase.transformed(QTransform().rotate(180));
    ui->btn_increase_size->setIcon(increase);
    ui->btn_decrease_size->setIcon(decrease);
}

MenuWindow::~MenuWindow()
{
    delete ui;
}

void MenuWindow::start_game(City *city)
{
    MainWindow *m = new MainWindow{city, nullptr};

    m->setAttribute(Qt::WA_DeleteOnClose);
    m->show();

    close();
}

void MenuWindow::on_btn_load_clicked()
{
    load_game();
}

void MenuWindow::load_game()
{
    // Promt the user to choose a file
    QString file_name = QFileDialog::getOpenFileName(this, "Load Saved City...", "E:/HKUST/yr2_fall/comp2012H/PAs/PA4");

    // If no file is chosen, do nothing
    if (file_name == "")
        return;

    // If a file is chosen, then load the city from the file and start the game.
    City *myCity = new City(file_name.toStdString());
    start_game(myCity);
}

void MenuWindow::on_btn_new_clicked()
{
    new_game();
}

void MenuWindow::new_game()
{
    ui->pages->setCurrentIndex(1);
}

void MenuWindow::on_btn_decrease_size_clicked()
{
    decrease_size_by_2();
}

void MenuWindow::on_btn_increase_size_clicked()
{
    increase_size_by_2();
}

void MenuWindow::decrease_size_by_2()
{
    // QMessageBox::information(this,"..","-2");

    std::string chosen_size_in_string = ui->label_grid_size->text().toStdString();
    int firstDigit = (int)chosen_size_in_string[0] - 48;
    int secondDigit = (int)chosen_size_in_string[1] - 48;
    int chosenSize = firstDigit * 10 + secondDigit;

    if (chosenSize == 10)
        return;

    ui->label_grid_size->setNum(chosenSize - 2);
}

void MenuWindow::increase_size_by_2()
{
    // QMessageBox::information(this,"..","+2");
    std::string chosen_size_in_string = ui->label_grid_size->text().toStdString();
    int firstDigit = (int)chosen_size_in_string[0] - 48;
    int secondDigit = (int)chosen_size_in_string[1] - 48;
    int chosenSize = firstDigit * 10 + secondDigit;

    if (chosenSize == 30)
        return;

    ui->label_grid_size->setNum(chosenSize + 2);
}

void MenuWindow::on_btn_start_game_clicked()
{
    start_new_game();
}

void MenuWindow::start_new_game()
{
    std::string chosen_size_in_string = ui->label_grid_size->text().toStdString();
    int firstDigit = (int)chosen_size_in_string[0] - 48;
    int secondDigit = (int)chosen_size_in_string[1] - 48;
    int chosenSize = firstDigit * 10 + secondDigit;
    City *myCity = new City(chosenSize);
    start_game(myCity);
}
