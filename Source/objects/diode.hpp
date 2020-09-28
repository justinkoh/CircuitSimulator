#ifndef diode_hpp
#define diode_hpp
#include "component.hpp"
class Funct;
class Diode:public Component{
  private:
    double m_source;
public:
  Diode(string name);
  ~Diode(){};
  double getVal() const;
  void setVal();
  double getVal_I() const;
  double getCurrent(double time);
  double getVoltage(double time);
  double getVoltage();
};
#endif
