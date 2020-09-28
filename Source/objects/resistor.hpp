#ifndef resistor_hpp
#define resistor_hpp
#include "component.hpp"

class Resistor:public Component{
public:
  Resistor(string name, double r);
  ~Resistor(){};
  double getVal() const;
  void setVal(double r);
  double getVoltage();
  virtual double getVoltage(double time);//get voltage of component
	virtual double getCurrent(double time);

};
#endif
