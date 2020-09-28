#ifndef capacitor_hpp
#define capacitor_hpp
#include "component.hpp"
class Funct;
class Capacitor:public Component{
private:
  //double m_capacitance;
  double m_charge;
  //Funct *m_ifunct;
  double m_prevT;
  double m_timestep;
public:
  Capacitor(string name, double c);
  ~Capacitor(){};
  double getVal() const;
  void setVal(double c);
  void setIFunct(Funct *f);
  double getVoltage(double time);//get voltage of component
	double getCurrent(double time);

};
#endif
