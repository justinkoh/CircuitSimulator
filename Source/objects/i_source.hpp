#ifndef i_source_hpp
#define i_source_hpp
#include "component.hpp"
#include "utils.hpp"
class Funct;

class CurrentSource:public Component{
private:
  Funct *m_function;
public:
  CurrentSource(string name, Funct *funct);
  CurrentSource(string name, double value);
  ~CurrentSource(){};
  void setCurrent(double i);
  double getVoltage(double time);
  double getCurrent(double time);
  double getVal() const;
  double getVal(double time);
  void setVal(double x);
};
#endif
