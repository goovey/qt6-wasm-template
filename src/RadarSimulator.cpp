#include "RadarSimulator.h"

RadarSimulator::RadarSimulator() : m_gen(m_rd()), m_dist(-1.0, 1.0) {
  // Start target at 5km, closing at 250 m/s
  m_state = {5000.0, 250.0, 45.0, 22.0};
}

void RadarSimulator::reset() {
  // Initial state: 5km range, 250 m/s closing velocity
  m_state = {5000.0, 250.0, 45.0, 22.0};
}

TargetState RadarSimulator::step(double dt) {
  // Constant Velocity Update
  m_state.range -= m_state.velocity * dt;

  // Create detection with synthetic Gaussian-like jitter
  TargetState detection = m_state;
  detection.range += m_dist(m_gen) * 2.0;
  detection.azimuth += m_dist(m_gen) * 0.05;
  detection.snr += m_dist(m_gen) * 0.3;

  return detection;
}
