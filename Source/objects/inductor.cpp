#include "inductor.hpp"

Inductor::Inductor(string name, double i){
    m_name = name;
    m_flux = 0;
    m_val = i;
    m_node1 = NULL;
    m_node2=NULL;
    m_prevT = 0;
    m_voltage = 0;
    m_current = 0;
    m_id = -2;
    m_enabled = true;
  }
double Inductor::getVal() const{
    return m_val;
}
void Inductor::setVal(double i){
    m_val = i;
}

double Inductor::getCurrent(double time){ //current through
  if (m_timestep == 0){
    m_timestep = time;
  }
  if (m_prevT == time){ //only calculate once per timestep
    return m_current;
  }
  m_current+=(m_voltage*m_timestep)/m_val;
  m_prevT = time;
  return m_current;
}
double Inductor::getVoltage(double time){//voltage
  return m_voltage;
}
