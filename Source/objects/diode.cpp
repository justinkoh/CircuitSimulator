#include "diode.hpp"
#include "utils.hpp"

#include "diode.hpp"

Diode::Diode(string name){
	m_name = name;
	m_val = 57.85;//initial conductance when assuming V=0.7 is 57.85)
	m_source = -39.049;//assume v=0.7
	m_node1 = NULL;
	m_node2 = NULL;
	m_voltage = 0.7;
	m_current = 0;
	m_id = -2;
	m_enabled = true;
}

double Diode::getVal_I() const{
	return m_source;     //returns value of current source
}
double Diode::getVal() const{
    return m_val;          //returns conductance
}


void Diode::setVal(){     //doesnt require an input value
	if(m_voltage > 1.3){m_voltage = 1.3;}//to avoid exponential overflow

	//if(m_voltage<=0.7){  //iterating on voltage
	double v = m_voltage / (0.025);

	double Id = (0.000000000001) * (series_exp(v)-1 );//Is * e(v/vt)

	m_val = Id/0.025;   //g = (Id/vt)

	m_source = Id - (m_voltage * m_val);  //Ieq = Id - V*Geq
	//else{  m_current  //iterating on current
	m_current = Id;
}



double Diode::getCurrent(double time){ //current through
  return m_current;
}
double Diode::getVoltage(double time){//voltage drop
  return m_voltage;
}

double Diode::getVoltage(){//voltage drop
  return m_voltage;
}
