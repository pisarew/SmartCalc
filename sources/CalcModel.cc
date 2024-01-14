//
// Created by Глеб Писарев on 01.12.2023.
//

#include "CalcModel.h"

#include <cmath>
#include <regex>

s21::CalcModel::CalcModel() : x_(0) {}

double s21::CalcModel::Calculate(const std::string &expr) const {
  try {
    auto postfix_expr = GetPostfixExpr(expr);
    std::stack<double> result;

    for (const auto &token : postfix_expr) {
      if (token == "X") {
        result.push(x_);
      } else if (IsDouble(token)) {
        result.push(stof(token));
      } else if (IsOperator(token)) {
        double b = result.top();
        result.pop();
        double a = result.top();
        result.pop();
        result.push(Execute(token, a, b));
      } else {
        double x = result.top();
        result.pop();
        result.push(Execute(token, x));
      }
    }
    return result.top();
  } catch (std::exception &ex) {
    throw ex;
  }
}

std::list<std::string> s21::CalcModel::GetPostfixExpr(
    const std::string &expr) const {
  auto list_expr = Parse(expr);
  try {
    ValidateExpr(list_expr);
  } catch (std::invalid_argument &ex) {
    throw ex;
  }
  std::list<std::string> output_list;
  std::stack<std::string> tmp_stack;

  for (const auto &token : list_expr) {
    if (IsDouble(token) || token == "X") {
      output_list.push_back(token);
    } else if (token == "(") {
      tmp_stack.push(token);
    } else if (token == ")") {
      while (!tmp_stack.empty() && tmp_stack.top() != "(") {
        output_list.push_back(tmp_stack.top());
        tmp_stack.pop();
      }
      tmp_stack.pop();
    } else if (IsOperator(token)) {
      while (!tmp_stack.empty() && token != "(" &&
             GetPriority(token) <= GetPriority(tmp_stack.top())) {
        output_list.push_back(tmp_stack.top());
        tmp_stack.pop();
      }
      tmp_stack.push(token);
    } else if (IsFunction(token)) {
      tmp_stack.push(token);
    }
  }

  while (!tmp_stack.empty()) {
    output_list.push_back(tmp_stack.top());
    tmp_stack.pop();
  }
  return output_list;
}

std::list<std::string> s21::CalcModel::Parse(const std::string &expr) noexcept {
  std::list<std::string> output_expr;

  std::regex pattern(
      R"(\d+(\.\d+)?|[+\-*/^%()]|asin|atan|acos|sin|cos|tan|X|log|ln|sqrt)");

  std::regex_token_iterator<std::string::const_iterator> end;
  std::regex_token_iterator<std::string::const_iterator> it(
      expr.begin(), expr.end(), pattern);
  for (; it != end; ++it) {
    output_expr.push_back(it->str());
  }

  return output_expr;
}

bool s21::CalcModel::IsDouble(const std::string &str) noexcept {
  try {
    std::stod(str);
    return true;
  } catch (...) {
    return false;
  }
}

bool s21::CalcModel::IsOperator(const std::string &str) const noexcept {
  return op_priority_.find(str) != op_priority_.end();
}

bool s21::CalcModel::IsFunction(const std::string &str) const noexcept {
  return func_priority_.find(str) != func_priority_.end();
}

int s21::CalcModel::GetPriority(const std::string &str) const noexcept {
  return IsOperator(str) ? op_priority_.find(str)->second
                         : func_priority_.find(str)->second;
}

double s21::CalcModel::Execute(const std::string &op, double a, double b) {
  std::unordered_map<std::string, int> op_map{{"+", 1}, {"-", 2}, {"*", 3},
                                              {"/", 4}, {"^", 5}, {"%", 6}};

  switch (op_map[op]) {
    case 1:
      return a + b;
    case 2:
      return a - b;
    case 3:
      return a * b;
    case 4:
      return a / b;
    case 5:
      return pow(a, b);
    case 6:
      return (double)((int)a % (int)b);
    default:
      throw std::invalid_argument("Execution error. Invalid operator");
  }
}
double s21::CalcModel::Execute(const std::string &func, double x) {
  std::unordered_map<std::string, int> func_map{
      {"sin", 1},  {"cos", 2},  {"tan", 3}, {"asin", 4}, {"acos", 5},
      {"atan", 6}, {"sqrt", 7}, {"ln", 8},  {"log", 9}};

  switch (func_map[func]) {
    case 1:
      return sin(x);
    case 2:
      return cos(x);
    case 3:
      return tan(x);
    case 4:
      return asin(x);
    case 5:
      return acos(x);
    case 6:
      return atan(x);
    case 7:
      return sqrt(x);
    case 8:
      return log(x);
    case 9:
      return log10(x);
    default:
      throw std::invalid_argument("Execution error. Invalid operator");
  }
}
void s21::CalcModel::UpdateX(double new_x) noexcept { x_ = new_x; }

void s21::CalcModel::ValidateExpr(std::list<std::string> &expr) {
  int left_bracket = 0;
  int right_bracket = 0;
  if (*(expr.begin()) == "-" || *(expr.begin()) == "+") expr.emplace_front("0");
  auto it = expr.begin();
  while (it != expr.end()) {
    if (*it == "(") ++left_bracket;
    if (*it == ")") ++right_bracket;
    if (*it == "-" || *it == "+") {
      if ((*(--it) == "("))
        it = expr.insert(++it, "0");
      else
        ++it;
    }
    ++it;
  }
  if (left_bracket != right_bracket)
    throw std::invalid_argument("Left bracket != right bracket");
}