#include "i_source.hpp"

CurrentSource::CurrentSource(string name, double i){
    m_name = name;
    m_current = i;
    m_function = new Funct(to_string(i),vector<double>{i});
    m_node1 = NULL;
    m_node2=NULL;
    m_voltage = 0;
    m_id = -2;
    m_enabled = true;
  };
CurrentSource::CurrentSource(string name, Funct *f){
      m_name = name;
      m_function = f;
      m_current = f->getValAt(0);
      m_node1 = NULL;
      m_node2=NULL;
      m_voltage = 0;
      m_id = -2;
      m_enabled = true;
    };
void CurrentSource::setCurrent(double i) {
    m_current = i;
}

double CurrentSource::getCurrent(double time){ //current through
  m_current = m_function->getValAt(time);
  return m_current;
}
double CurrentSource::getVoltage(double time){//voltage drop
  return m_voltage;
}
double CurrentSource::getVal() const{
  return m_current;
}

void CurrentSource::setVal(double x){
  m_current = x;
}
