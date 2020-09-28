#include "resistor.hpp"

Resistor::Resistor(string name, double r){
    m_name = name;
    m_val = r;
    m_node1 = NULL;
    m_node2=NULL;
    m_voltage = 0;
    m_current = 0;
    m_id = -2;
    m_enabled = true;
  }
double Resistor::getVal() const{
    return m_val;
}
void Resistor::setVal(double r){
    m_val = r;
}

double Resistor::getCurrent(double time){ //current through
  return m_current;
}
double Resistor::getVoltage(double time){//voltage drop
  return m_voltage;
}

double Resistor::getVoltage(){//voltage drop
  return m_voltage;
}
