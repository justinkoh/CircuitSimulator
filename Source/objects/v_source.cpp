#include "v_source.hpp"

VoltageSource::VoltageSource(string name, double v){
    m_name = name;
    m_voltage = v;
    m_function = new Funct(to_string(v),vector<double>{v});
    m_node1 = NULL;
    m_node2=NULL;
    m_current = 0;
    m_id = -2;
    m_enabled = true;
  };
VoltageSource::VoltageSource(string name, Funct *f){
      m_name = name;
      m_function = f;
      m_node1 = NULL;
      m_node2=NULL;
      m_current = 0;
      m_voltage = f->getValAt(0);
      m_id = -2;
      m_enabled = true;
    };
void VoltageSource::setVoltage(double v) {
    m_voltage = v;
}

double VoltageSource::getCurrent(double time){ //current through
  return m_current;
}
double VoltageSource::getVoltage(double time){//voltage drop
  return m_function->getValAt(time);
}
double VoltageSource::getVal() const{
  return m_voltage;
}

void VoltageSource::setVal(double x){
  m_voltage = x;
}

void VoltageSource::setId(int x){
  m_id = x;
}

int VoltageSource::getId(int x){
  return m_id;
}
