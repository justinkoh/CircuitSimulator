#ifndef inductor_hpp
#define inductor_hpp
#include "component.hpp"
class Funct;
class Inductor:public Component{
private:
  double m_flux;
  double m_timestep;
  double m_prevT;
public:
  Inductor(string name, double c);
  ~Inductor(){};
  double getVal() const;
  void setVal(double i);
  void setVFunct(Funct *f);
  double getVoltage(double time);//get voltage of component
	double getCurrent(double time);
};
#endif
