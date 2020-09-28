#include "capacitor.hpp"

Capacitor::Capacitor(string name, double c){
    m_name = name;
    m_charge = 0;
    m_val = c;
    m_node1 = NULL;
    m_node2=NULL;
    m_voltage = 0;
    m_current = 0;
    m_id = -2;
    m_enabled = true;
    m_timestep = 0;
    m_prevT = 0;
  }
double Capacitor::getVal() const{
    return m_val;
}
void Capacitor::setVal(double c){
    m_val = c;
}

double Capacitor::getCurrent(double time){
  return m_current;
}
double Capacitor::getVoltage(double time){//voltage
  if (m_timestep == 0){
    m_timestep = time;
  }
  if (m_prevT == time){
    return m_voltage;
  }
  m_voltage = m_charge/m_val;
  m_charge += m_timestep*m_current;
  m_prevT = time;
  return m_voltage;
}
