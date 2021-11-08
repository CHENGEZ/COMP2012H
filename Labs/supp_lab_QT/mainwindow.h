#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "numcell.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void generate();
    bool win();

    Ui::MainWindow *ui;

    NumCell* num_cells[3][3];
};

#endif // MAINWINDOW_H
