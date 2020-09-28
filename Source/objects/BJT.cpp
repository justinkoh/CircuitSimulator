#include "BJT.hpp"
#include "utils.hpp"

#include "BJT.hpp"

Diode::Diode(string name){
	m_name = name;
	m_base = 0;
	m_emitter = 0;
	m_collector = 0;
	m_val = 0;
	m_node1 = NULL;
	m_node2 = NULL;
	m_node3 = NULL
	m_voltage = 0;
	m_current = 0;
	m_id = -2;
	m_enabled = true;
}

double BJT::getVal() const{
    return m_val;          //returns conductance?
}


void BJT::setVal(){
	//set current source
	//set resistors

}

double Diode::getCurrent(double time){ //current through C
  return m_current;
}
double Diode::getVoltage(double time){//voltage drop of CE
  return m_voltage;
}

double Diode::getVoltage(){//voltage drop voltage drop of BE
  return m_voltage;
}
