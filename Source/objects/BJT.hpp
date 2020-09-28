#ifndef diode_hpp
#define diode_hpp
#include "component.hpp"
class Funct;
class Node;
class BJT:public Component{
  private:
    double m_base;
    double m_emitter;
    double m_collector;
    Node *m_node3;
public:
  BJT(string name);
  ~BJT(){};
  double getVal() const;
  void setVal();
  double getCurrent(double time);
  double getVoltage(double time);
  double getVoltage();
  Node* getNode3();
  void setNode3();
};
#endif
