//
// Created by Глеб Писарев on 17.12.2023.
//

#include "Controller.h"

#include <QInputDialog>

#include "GraphView.h"

s21::Controller::Controller(s21::CalcModel* model, CalcView* view)
    : model_(model), view_(view) {
  connect(view_, &CalcView::SigExecuteButton, this,
          &Controller::OnExecuteButtonClicked);
  connect(view_, &CalcView::SigGraphButton, this,
          &Controller::OnGraphButtonClicked);
}

void s21::Controller::OnExecuteButtonClicked() {
  if (view_->GetText().contains("X")) {
    auto x = QInputDialog::getDouble(view_, tr("Введите X"), tr("X = "));
    model_->UpdateX(x);
  }
  try {
    auto expr = view_->GetText().toStdString();
    auto result = model_->Calculate(expr);
    view_->SetText(QString::number(result));
  } catch (...) {
    view_->SetText("CALCULATION ERROR");
  }
}
void s21::Controller::OnGraphButtonClicked() {
  auto graph = new GraphView(view_->GetText());
  graph->show();
}
