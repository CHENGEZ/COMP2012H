#include "numcell.h"

NumCell::NumCell(QWidget *parent)
        :QPushButton(parent), row(0), col(0), num(0) {
    connect(this, &NumCell::clicked, this, &NumCell::on_clicked);
}

int NumCell::get_row() {
    return row;
}

void NumCell::set_row(int row) {
    this->row = row;
}

int NumCell::get_col() {
    return col;
}

void NumCell::set_col(int col) {
    this->col = col;
}

int NumCell::get_num() {
    return num;
}

void NumCell::set_num(int num) {
    this->num = num;
    setText(num!=0 ? QString::number(num) : " ");
}

void NumCell::on_clicked() {
    emit operate_signal(row, col);
}
