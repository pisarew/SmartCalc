//
// Created by Глеб Писарев on 03.01.2024.
//

#ifndef CPP3_SMARTCALC_V2_0_1_GRAPHVIEW_H
#define CPP3_SMARTCALC_V2_0_1_GRAPHVIEW_H

#include <QDialog>

#include "qcustomplot.h"
#include "ui_graph.h"

namespace s21 {
class GraphView : public QDialog {
  Q_OBJECT

 public:
  explicit GraphView(const QString& expr);

 private:
  Ui::Graph* ui_;
  QCustomPlot* plot_;
  QString* expr_;
  void PlotGraph();

 private slots:
  void on_plotButton_clicked();
};
}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_1_GRAPHVIEW_H
