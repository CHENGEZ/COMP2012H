#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "City.h"

#include <QMainWindow>

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    enum class SideMenuButton
    {
        CLINIC = 1,
        HOSPITAL = 2,
        SILVER_MINE = 3,
        GOLD_MINE = 4,
        HOUSE = 5,
        APARTMENT = 6,
        DEMOLISH = 7,
        NAVIGATE = 8
    };

    enum class OverlayButton
    {
        NORMAL,
        TYPE,
        NEIGHBOR
    };

    enum class SideMenuStatus
    {
        HIDDEN,
        HIDDEN_TO_VISIBLE,
        VISIBLE,
        VISIBLE_TO_HIDDEN
    };

    MainWindow(City *const city, QWidget *parent = nullptr);
    ~MainWindow();

    MainWindow(const MainWindow &) = delete;
    MainWindow &operator=(const MainWindow &) = delete;

    SideMenuButton get_selected_side_menu_button();
    OverlayButton get_selected_overlay_button();
    SideMenuStatus get_side_menu_status();
    void set_side_menu_status(SideMenuStatus status);
private slots:
    void on_btn_next_clicked();
    void on_btn_save_game_clicked();
    void on_btn_overlay_neighbor_clicked() { on_overlay_button_clicked(OverlayButton::NEIGHBOR); }
    void on_btn_overlay_normal_clicked() { on_overlay_button_clicked(OverlayButton::NORMAL); }
    void on_btn_overlay_type_clicked() { on_overlay_button_clicked(OverlayButton::TYPE); }

    void on_btn_apartment_clicked() { on_side_menu_button_clicked(SideMenuButton::APARTMENT); }
    void on_btn_clinic_clicked() { on_side_menu_button_clicked(SideMenuButton::CLINIC); }
    void on_btn_house_clicked() { on_side_menu_button_clicked(SideMenuButton::HOUSE); }
    void on_btn_hospital_clicked() { on_side_menu_button_clicked(SideMenuButton::HOSPITAL); }
    void on_btn_gold_clicked() { on_side_menu_button_clicked(SideMenuButton::GOLD_MINE); }
    void on_btn_silver_clicked() { on_side_menu_button_clicked(SideMenuButton::SILVER_MINE); }
    void on_btn_navigate_clicked() { on_side_menu_button_clicked(SideMenuButton::NAVIGATE); }
    void on_btn_destruct_clicked() { on_side_menu_button_clicked(SideMenuButton::DEMOLISH); }

private:
    void go_to_next_step();
    void save_current_game();
    // Initialization functions, called in constructor
    void initialize_overlay_buttons();
    void initialize_side_menu_buttons();

    void on_overlay_button_clicked(OverlayButton button);
    void on_side_menu_button_clicked(SideMenuButton button);

    void main_loop();

    Ui::MainWindow *ui;

    City *const city;

    QTimer *loop_timer;

    SideMenuButton selected_side_menu_button;
    OverlayButton selected_overlay_button;
    SideMenuStatus side_menu_status;

    friend class GameWidget;
};
#endif // MAINWINDOW_H
