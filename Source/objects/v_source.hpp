#ifndef v_source_hpp
#define v_source_hpp
#include "component.hpp"
#include "utils.hpp"
class Funct;

class VoltageSource:public Component{
private:
  Funct *m_function;
public:
  VoltageSource(string name, Funct *funct);
  VoltageSource(string name, double value);
  ~VoltageSource(){};
  void setVoltage(double v);
  double getVoltage(double time) override;
  double getCurrent(double time);
  double getVal() const;
  void setVal(double x);
  void setId(int x);
  int getId(int x);
};
#endif
