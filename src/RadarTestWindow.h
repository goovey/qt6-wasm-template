#ifndef RADARTESTWINDOW_H
#define RADARTESTWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QSpinBox>
#include <QTableWidget>
#include <QTimer>

#include "RadarSimulator.h"

class RadarTestWindow : public QMainWindow {
  Q_OBJECT
 public:
  explicit RadarTestWindow(QWidget* parent = nullptr);

 private slots:
  void onUpdateSimulation();
  void onStart();
  void onPause();
  void onStop();
  void onIntervalChanged(int ms);  // Slot to update timer frequency dynamically

 private:
  QTableWidget* m_table;
  QPushButton* m_startBtn;
  QPushButton* m_pauseBtn;
  QPushButton* m_stopBtn;
  QSpinBox* m_intervalSpin;
  QTimer* m_timer;
  RadarSimulator m_sim;

  void setupUi();
};

#endif
