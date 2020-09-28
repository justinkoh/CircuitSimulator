#ifndef component_hpp
#define component_hpp

using namespace std;

#include <string>
#include <iostream>
#include <complex>
#include <vector>
using namespace std;
class Node;

class Component{
protected:
    Node *m_node1;
    Node *m_node2;
    double m_voltage; //voltage going through
    double m_current; //current going through
    double m_source;
    double m_val;//whatever
    string m_name;
    int m_id; //maybe needed for equations
    bool m_enabled; //eroor checking
public:
  //Component(string name);
  virtual ~Component(){};
  Component()=default;
  //getters and setters
	virtual double getVoltage(double time);//get voltage of component
	virtual double getCurrent(double time);//get current
  virtual double getVoltage();//get voltage of component
  virtual double getCurrent();//get current
  virtual double getVal() const;
  virtual void setVal(double x);
  virtual void setVal();
  virtual double getVal_I()const;
	int getId();
	Node* getNode1();
	Node* getNode2();
	string getName();

	void setNode1(Node* node);
	void setNode2(Node* node);
	void setId(int id);
	virtual void setVoltage(double voltage);
	virtual void setCurrent(double current);
	Node* getOtherNode(Node* node);

};

#endif
