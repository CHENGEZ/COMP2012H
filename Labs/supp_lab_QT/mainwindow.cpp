#include <iostream>
#include <iterator>
#include <algorithm>
#include <random>
#include <chrono>

#include <QMessageBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;
using std::chrono::system_clock;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    num_cells[0][0] = ui->pushButton_1;
    num_cells[0][1] = ui->pushButton_2;
    num_cells[0][2] = ui->pushButton_3;
    num_cells[1][0] = ui->pushButton_4;
    num_cells[1][1] = ui->pushButton_5;
    num_cells[1][2] = ui->pushButton_6;
    num_cells[2][0] = ui->pushButton_7;
    num_cells[2][1] = ui->pushButton_8;
    num_cells[2][2] = ui->pushButton_9;

    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            num_cells[i][j]->set_row(i);
            num_cells[i][j]->set_col(j);
        }
    }

    generate();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::generate() {
    int temp[9] = {1, 2, 3, 4, 5, 6, 7, 8, 0};
    unsigned int num_reverse_pair = 0;

    do {
        num_reverse_pair = 0;

        unsigned int seed = system_clock::now().time_since_epoch().count();
        shuffle(begin(temp), end(temp), default_random_engine(seed)); // Array Size of 9.

        // Ignore the empty cell 0.
        for (int i = 0; i < 8; ++i) {
            if (temp[i] == 0) {
                continue;
            }

            for (int j = i + 1; j < 9; ++j) {
                if (temp[j] == 0) {
                    continue;
                }

                if (temp[i] > temp[j]) {
                    num_reverse_pair += 1;
                }
            }
        }
    } while (((num_reverse_pair % 2) != 0) || (num_reverse_pair == 0)); // Repeat until non-zero even-number of reverse pairs.

    for (int i = 0; i < 9; i++) {
        num_cells[i/3][i%3]->set_num(temp[i]);
    }
}

void MainWindow::operate(int row, int col) {
    int row0, col0;
    for (int i=0; i<9; i++) {
        if (num_cells[i/3][i%3]->get_num() == 0) {
            row0 = i/3;
            col0 = i%3;
            break;
        }
    }

    if (!( (row==row0) ^ (col==col0) )) return;

    // Swap with the empty cell. If there is a middle cell, swap again with it.
    int temp = num_cells[row][col]->get_num();
    num_cells[row][col]->set_num(num_cells[row0][col0]->get_num());
    num_cells[row0][col0]->set_num(temp);
    if (row == row0) {
        if (((col - col0) == 2) || ((col0 - col) == 2)) {
            int temp = num_cells[row0][1]->get_num();
            num_cells[row0][1]->set_num(num_cells[row0][col0]->get_num());
            num_cells[row0][col0]->set_num(temp);
        }
    }
    else {
        if (((row - row0) == 2) || ((row0 - row) == 2)) {
            int temp = num_cells[1][col0]->get_num();
            num_cells[1][col0]->set_num(num_cells[row0][col0]->get_num());
            num_cells[row0][col0]->set_num(temp);
        }
    }

    if (win()) {
        QMessageBox msg{QMessageBox::Information, QString{"Congratulations"}, QString{"You win!"}, QMessageBox::Ok, this};
        msg.exec();
    }
}

bool MainWindow::win() {
    for (int i = 0; i < 8; i++) {
        if (num_cells[i/3][i%3]->get_num() != i + 1) {
            return false;
        }
    }
    return true;
}
