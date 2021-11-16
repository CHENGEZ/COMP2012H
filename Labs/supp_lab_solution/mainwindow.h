#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>

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

protected:
    void keyPressEvent(QKeyEvent *e);

private slots:
    void operate(int row, int col);

    void on_generate_clicked();

private:
    void generate();
    bool win();
    void operate_dir(int d_row, int d_col);

    Ui::MainWindow *ui;

    NumCell* num_cells[3][3];
};

#endif // MAINWINDOW_H
