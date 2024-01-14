//
// Created by Глеб Писарев on 17.12.2023.
//

#ifndef CPP3_SMARTCALC_V2_0_1_CONTROLLER_H
#define CPP3_SMARTCALC_V2_0_1_CONTROLLER_H

#include <QObject>

#include "CalcModel.h"
#include "CalcView.h"

namespace s21 {
class Controller : public QObject {
  Q_OBJECT

 public:
  Controller(CalcModel& model, CalcView& view);

 private slots:
  void OnExecuteButtonClicked();
  void OnGraphButtonClicked();

 private:
  CalcModel& model_;
  CalcView& view_;
};
}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_1_CONTROLLER_H
