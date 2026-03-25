#include "RadarTestWindow.h"

#include <QDateTime>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QVBoxLayout>

RadarTestWindow::RadarTestWindow(QWidget* parent) : QMainWindow(parent) {
  setupUi();

  m_timer = new QTimer(this);
  connect(m_timer, &QTimer::timeout, this,
          &RadarTestWindow::onUpdateSimulation);
}

void RadarTestWindow::setupUi() {
  this->setWindowTitle("Radar Test Dashboard (WASM)");

  QWidget* centralWidget = new QWidget(this);
  QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);

  // --- Controls Layout ---
  QHBoxLayout* controlsLayout = new QHBoxLayout();

  m_startBtn = new QPushButton("Start", this);
  m_pauseBtn = new QPushButton("Pause", this);
  m_stopBtn = new QPushButton("Stop", this);

  // Timer Interval Input
  QLabel* intervalLabel = new QLabel("Interval (ms):", this);
  m_intervalSpin = new QSpinBox(this);
  m_intervalSpin->setRange(10, 2000);  // Enforce 10ms minimum
  m_intervalSpin->setValue(100);       // Default 10Hz
  m_intervalSpin->setSuffix(" ms");

  controlsLayout->addWidget(m_startBtn);
  controlsLayout->addWidget(m_pauseBtn);
  controlsLayout->addWidget(m_stopBtn);
  controlsLayout->addSpacing(20);
  controlsLayout->addWidget(intervalLabel);
  controlsLayout->addWidget(m_intervalSpin);
  controlsLayout->addStretch();  // Align items to the left

  mainLayout->addLayout(controlsLayout);

  // --- Table Layout ---
  m_table = new QTableWidget(0, 4, this);
  m_table->setHorizontalHeaderLabels(
      {"Timestamp", "Range (m)", "Azimuth", "SNR (dB)"});
  m_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  m_table->setAlternatingRowColors(true);
  mainLayout->addWidget(m_table);

  this->setCentralWidget(centralWidget);
  this->resize(900, 500);

  // Connections
  connect(m_startBtn, &QPushButton::clicked, this, &RadarTestWindow::onStart);
  connect(m_pauseBtn, &QPushButton::clicked, this, &RadarTestWindow::onPause);
  connect(m_stopBtn, &QPushButton::clicked, this, &RadarTestWindow::onStop);
  connect(m_intervalSpin, QOverload<int>::of(&QSpinBox::valueChanged), this,
          &RadarTestWindow::onIntervalChanged);

  m_pauseBtn->setEnabled(false);
  m_stopBtn->setEnabled(false);
}

void RadarTestWindow::onStart() {
  m_timer->start(m_intervalSpin->value());  // Start with user-defined interval
  m_startBtn->setEnabled(false);
  m_pauseBtn->setEnabled(true);
  m_stopBtn->setEnabled(true);
  m_intervalSpin->setEnabled(false);  // Lock interval during active simulation
}

void RadarTestWindow::onIntervalChanged(int ms) {
  if (m_timer->isActive()) {
    m_timer->start(ms);  // Dynamically adjust if running
  }
}

void RadarTestWindow::onPause() {
  m_timer->stop();
  m_startBtn->setEnabled(true);
  m_pauseBtn->setEnabled(false);
  m_intervalSpin->setEnabled(true);
}

void RadarTestWindow::onStop() {
  m_timer->stop();
  m_sim.reset();
  m_table->setRowCount(0);
  m_startBtn->setEnabled(true);
  m_pauseBtn->setEnabled(false);
  m_stopBtn->setEnabled(false);
  m_intervalSpin->setEnabled(true);
}

void RadarTestWindow::onUpdateSimulation() {
  // Calculate delta time (dt) in seconds based on current timer interval
  double dt = m_timer->interval() / 1000.0;
  TargetState data = m_sim.step(dt);

  if (data.snr > 15.0) {
    int row = m_table->rowCount();
    m_table->insertRow(row);

    m_table->setItem(row, 0,
                     new QTableWidgetItem(QDateTime::currentDateTime().toString(
                         "hh:mm:ss.zzz")));
    m_table->setItem(row, 1,
                     new QTableWidgetItem(QString::number(data.range, 'f', 2)));
    m_table->setItem(
        row, 2, new QTableWidgetItem(QString::number(data.azimuth, 'f', 2)));
    m_table->setItem(row, 3,
                     new QTableWidgetItem(QString::number(data.snr, 'f', 1)));

    m_table->scrollToBottom();
    if (m_table->rowCount() > 100) m_table->removeRow(0);
  }
}
