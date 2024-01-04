//
// Created by Глеб Писарев on 17.12.2023.
//

#include "CalcView.h"
s21::CalcView::CalcView() : QMainWindow(nullptr), ui(new Ui::SmartCalc) {
  ui->setupUi(this);
  connect(ui->equalButton, &QPushButton::clicked, this,
          &CalcView::SigExecuteButton);
  connect(ui->graphButton, &QPushButton::clicked, this,
          &CalcView::SigGraphButton);
}
void s21::CalcView::on_enterButtonGroup_buttonClicked(QAbstractButton *button) {
  if (GetText() == "0" || GetText() == "CALCULATION ERROR")
    SetText(button->text());
  else
    SetText(GetText() + button->text());
}
void s21::CalcView::SetText(const QString &text) {
  ui->lineEdit->setText(text);
}
QString s21::CalcView::GetText() { return ui->lineEdit->text(); }

void s21::CalcView::on_ACButton_clicked() { SetText("0"); }
void s21::CalcView::on_divButton_clicked() { SetText(GetText() + "/"); }
void s21::CalcView::on_mulButton_clicked() { SetText(GetText() + "*"); }
