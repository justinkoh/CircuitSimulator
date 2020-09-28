#ifndef nodes_hpp
#define nodes_hpp
#include <string>
#include <iostream>
#include <complex>
#include <vector>
using namespace std;
class Component;

class Node{
private:
  string m_name;
  int m_id; //easier to use in calcs
  double m_voltage;
  vector<Component*> *m_components; //each node has one or more components
  bool m_isground;
  bool m_containsV;
public:
  Node(string name, int id);
  void addComponent(Component *component);
  double getVoltage();
  double getVoltage(double time);
  void setVoltage(double voltage);
  int getNumOfComponents();
  string getName();
  bool isGround();
  void setGround(bool isground);
  int getId();
  void setId(int id);
  vector<Component*> *getComponents();
  bool hasV();
  };

  #endif
