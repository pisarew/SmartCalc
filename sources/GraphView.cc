//
// Created by Глеб Писарев on 03.01.2024.
//

#include "GraphView.h"

#include "CalcModel.h"

s21::GraphView::GraphView(const QString& expr)
    : QDialog(nullptr),
      ui_(new Ui::Graph),
      expr_(new QString(expr)),
      plot_(new QCustomPlot) {
  ui_->setupUi(this);
  ui_->graphLayout->addWidget(plot_);
  PlotGraph();
}
void s21::GraphView::PlotGraph() {
  auto x_max = ui_->spinBoxXMax->value();
  auto x_min = ui_->spinBoxXMin->value();
  auto y_max = ui_->spinBoxYMax->value();
  auto y_min = ui_->spinBoxYMin->value();

  plot_->addGraph();
  plot_->xAxis->setLabel("X");
  plot_->yAxis->setLabel("Y");
  plot_->xAxis->setRange(x_max, x_min);
  plot_->yAxis->setRange(y_max, y_min);

  double step = (x_max - x_min) / 999.0;

  QVector<double> x(1000), y(1000);
  x[0] = x_min;

  CalcModel model;
  for (int i = 1; i < 999; ++i) {
    model.UpdateX(x[i - 1]);
    x[i] = x[i - 1] + step;
    y[i] = model.Calculate(expr_->toStdString());
  }
  plot_->graph(0)->addData(x, y);
  plot_->replot();
}
void s21::GraphView::on_plotButton_clicked() { PlotGraph(); }
