#ifndef circuit_hpp
#define circuit_hpp
#include "objs/utils.hpp"
#include "objs/component.hpp"
#include "objs/capacitor.hpp"
#include "objs/inductor.hpp"
#include "objs/resistor.hpp"
#include "objs/v_source.hpp"
#include "objs/i_source.hpp"
#include "objs/diode.hpp"
#include <vector>


class Circuit {

private:

	vector<Node*> *m_nodes;
	vector<Component*> *m_components;
	vector<Component*> *m_voltageSources; //need to be separate
	vector<Component*> *m_diodes;

	int m_id;
	int m_cap;

	Node* getNode(string name);
	Node* getNode(int id);
	Component* getComponent(string name);
	Component* getComponent(int id);


  //creates eqns Ax = B, a is eqns
	bool createEquations(double*& eqns, double*& vals, double time);
	//update all vals
	bool updateEquations(double*& eqns, double*& vals, double time);
  //eqn for specific Node
	bool createEquation(Node* node, double* eqns, double& vals, double time);
	//eqn for voltage sources
	bool createEquation(Component* vsrc, double* eqn, double& vals, double time);
	//supernode
	bool createEquation(vector<Node*> nodes, double* eqn, double& vals, double time);
  //solve Ax=B
	bool solveEquations(double* eqns, double* vals);

	void setResults(double* vals);
	//apply KCL to find current
	void KCL(Component* vsrc, Node *node, bool reverse);


public:

	Circuit();
	bool solve(double *eqn, double *vals, double time);

	void ApproxDiodes(double *eqn, double *vals, double time);
	// add components to node
	bool addComponent(Resistor *r, string nodename1, string nodename2);
	bool addComponent(Inductor *l, string nodename1, string nodename2);
	bool addComponent(Capacitor *c, string nodename1, string nodename2);
	bool addComponent(VoltageSource *v, string nodename1, string nodename2);
	bool addComponent(CurrentSource *i, string nodename1, string nodename2);
	bool addComponent(Diode *d, string nodename1, string nodename2);

	// adds a node with name
	bool addNode(string name);
	bool equalNodes(Node *a, Node *b);
	// getters
	double getCurrent(string name, double time);
	double getVoltage(string name, double time);
	double getConductance(string name);
	void getNodeNames (string componentName, string& node1, string& node2);
	int getNumVoltageSources();
	int getNumNodes();
	int getNumGroundedV();
	// checks if circuit works --not sure how to implement
	bool checkCircuit();
	bool containsC();
	void outNames();
	void outVals();
};



#endif
