#ifndef RADARSIMULATOR_H
#define RADARSIMULATOR_H

#include <random>

struct TargetState {
  double range;     // meters
  double velocity;  // m/s
  double azimuth;   // degrees
  double snr;       // dB
};

class RadarSimulator {
 public:
  RadarSimulator();
  TargetState step(double dt);
  void reset();

 private:
  TargetState m_state;
  std::random_device m_rd;
  std::mt19937 m_gen;
  std::uniform_real_distribution<> m_dist;
};

#endif  // RADARSIMULATOR_H
