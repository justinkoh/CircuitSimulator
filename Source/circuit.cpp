#include "circuit.hpp"
#include "objs/utils.hpp"
#include <cfloat>
#include <cstdlib>
#include <iostream>
#include "objs/component.hpp"
#include "objs/nodes.hpp"
#include "Eigen/Dense"
#include <algorithm>
using namespace std;
using namespace Eigen;

Circuit::Circuit() {

	m_nodes = new vector<Node*>(0);
	m_components = new vector<Component*>(0);
	m_voltageSources = new vector<Component*>(0);
	m_diodes= new vector<Component*>(0);
	m_id = 0;
	m_cap= 0;

}


bool Circuit::equalNodes(Node *a, Node *b) {
  return (a->getName()==b->getName());
}
Node* Circuit::getNode(string name) {
	for (vector<Node*>::iterator it = m_nodes->begin(); it != m_nodes->end(); it++) {
		if ((*it)->getName() == name) return (*it);
	}
	return NULL;
}
Node* Circuit::getNode(int id) {
	for (vector<Node*>::iterator it = m_nodes->begin(); it != m_nodes->end(); it++) {
		if ((*it)->getId() == id) return (*it);
	}
	return NULL;
}
Component* Circuit::getComponent(int id) {
	for (vector<Component*>::iterator it = m_components->begin(); it != m_components->end(); it++) {
		if ((*it)->getId() == id) return (*it);
	}
	return NULL;
}

Component* Circuit::getComponent(string name) {
	for (vector<Component*>::iterator it = m_components->begin(); it != m_components->end(); it++) {
		if ((*it)->getName() == name) {
			return (*it);};
	}
	return NULL;
}

bool Circuit::addNode(string name) {
	bool addingG = false;
	if (getNode(name) != NULL){
		return false;
	}
	int temp = m_id;
	if (name == "0") {
		addingG=true;
		m_id = -1;
	}
	Node* tNode = new Node(name, m_id);
	if (addingG){
		m_id = temp;
	}else{
		m_id++;
	};
	m_nodes->push_back(tNode);
	return true;
}

double Circuit::getCurrent(string name, double time) { 
	Component* tComponent = getComponent(name);
	if (tComponent == NULL)
		return DBL_MAX;
	return tComponent->getCurrent(time);
}

double Circuit::getVoltage(string name, double time) {
	Component* tComponent = getComponent(name);
	if (tComponent == NULL) {
		Node* node = getNode(name);
		if (node != NULL)
			return node->getVoltage(time);
		else return DBL_MAX;
	}
	else {
		return tComponent->getVoltage(time);
	}
}

void Circuit::getNodeNames (string componentName, string& node1, string& node2) {
	Component* temp = this->getComponent(componentName);
	if (temp == NULL) {
		node1 = "0";
		node2 = "0";
		return;
	}
	node1 = (temp->getNode1())->getName();
	node2 = (temp->getNode2())->getName();
}

int Circuit::getNumVoltageSources() {
	return m_voltageSources->size();
}
int Circuit::getNumNodes() {
	return m_nodes->size();
}

bool Circuit::containsC(){
	return (m_cap>0);
}

// adds component to node
bool Circuit::addComponent(Resistor *r, string nodename1, string nodename2){
	//check nodes are valid, check component doesnt already exist
	Node* n1 = getNode(nodename1);
	Node* n2 = getNode(nodename2);
	Component *e = getComponent(r->getName());
	if (e == NULL){
		m_components->push_back(r);
	}
	if (r->getNode1() == NULL) {
		r->setNode1(n1);
	}
	if (r->getNode2() == NULL) {
		r->setNode2(n2);
	}
	n1->addComponent(r);
	n2->addComponent(r);
}
bool Circuit::addComponent(Inductor *l, string nodename1, string nodename2){
	//check nodes are valid, check component doesnt already exist
	Node* n1 = getNode(nodename1);
	Node* n2 = getNode(nodename2);
	Component *e = getComponent(l->getName());
	if (e == NULL){
		m_components->push_back(l);
	}
	if (l->getNode1() == NULL) {
		l->setNode1(n1);
	}
	if (l->getNode2() == NULL) {
		l->setNode2(n2);
	}
	n1->addComponent(l);
	n2->addComponent(l);
}
bool Circuit::addComponent(Capacitor *c, string nodename1, string nodename2){
	Node* n1 = getNode(nodename1);
	Node* n2 = getNode(nodename2);
	Component *e = getComponent(c->getName());
	if (e == NULL){
		m_voltageSources->push_back(c);
	}
	if (c->getNode1() == NULL) {
		c->setNode1(n1);
	}
	if (c->getNode2() == NULL) {
		c->setNode2(n2);
	}
	n1->addComponent(c);
	n2->addComponent(c);
	m_cap +=1;
}
bool Circuit::addComponent(VoltageSource *v, string nodename1, string nodename2){
	Node* pnode = getNode(nodename1);
	Node* nnode = getNode(nodename2);
	Component *e = getComponent(v->getName());
	if (e == NULL){
			m_voltageSources->push_back(v);
	}
	if (v->getNode1() == NULL) {
		v->setNode1(pnode);
	}
	if (v->getNode2() == NULL) {
		v->setNode2(nnode);
	}
	pnode->addComponent(v);
	nnode->addComponent(v);
}
bool Circuit::addComponent(CurrentSource *i, string nodename1, string nodename2){
	Node* inode = getNode(nodename1);
	Node* onode = getNode(nodename2);
	Component *e = getComponent(i->getName());
	if (e == NULL){
		m_components->push_back(i);
	}
	if (i->getNode1() == NULL) {
		i->setNode1(inode);
	}
	if (i->getNode2() == NULL) {
		i->setNode2(onode);
	}
	inode->addComponent(i);
	onode->addComponent(i);
}
bool Circuit::addComponent(Diode *d, string nodename1, string nodename2){
	Node* anode = getNode(nodename1);
	Node* cathode = getNode(nodename2);
	Component *e = getComponent(d->getName());
	if (e == NULL){
		m_components->push_back(d);
		m_diodes->push_back(d);
	}
	if (d->getNode1() == NULL) {
		d->setNode1(anode);
	}
	if (d->getNode2() == NULL) {
		d->setNode2(cathode);
	}
	anode->addComponent(d);
	cathode->addComponent(d);
}

void Circuit::outNames(){
	vector<string> names;
	for (vector<Node*>::iterator it = m_nodes->begin(); it != m_nodes->end(); it++){
		if ((*it)->getName()!="0"){
		names.push_back("V("+(*it)->getName()+")");}
	}
	for (vector<Component*>::iterator it = m_components->begin(); it != m_components->end(); it++){
		names.push_back("I("+(*it)->getName()+")");
	}
	for (vector<Component*>::iterator it = m_voltageSources->begin(); it != m_voltageSources->end(); it++){
		names.push_back("I("+(*it)->getName()+")");
	}
	for (int i =0;i<names.size()-1;i++){
		cout<<names[i]<<",";
	}
	cout<<names[names.size()-1]<<endl;
}
//output the numerical values
void Circuit::outVals(){
	vector<double> vals;
	for (vector<Node*>::iterator it = m_nodes->begin(); it != m_nodes->end(); it++){
		if ((*it)->getName()!="0"){
		vals.push_back((*it)->getVoltage());}
	}
	for (vector<Component*>::iterator it = m_components->begin(); it != m_components->end(); it++){
		vals.push_back((*it)->getCurrent());
	}
	for (vector<Component*>::iterator it = m_voltageSources->begin(); it != m_voltageSources->end(); it++){
		vals.push_back((*it)->getCurrent());
	}
	for (int i =0;i<vals.size()-1;i++){
		cout<<vals[i]<<",";
	}
	cout<<vals[vals.size()-1]<<endl;
}

void Circuit::setResults(double* vals) {
	int n = getNumNodes() - 1;
	for (int i = 0; i < n; i++) {
		Node* tNode = getNode(i);
		if (tNode != NULL){
			tNode->setVoltage(vals[i]);
		}else{
			Component* comp = getComponent(i);
			if (comp != NULL && comp->getName().at(0)!='L') {
				comp->setCurrent(vals[i]);
			}
		}
	}
	//resistor current
	for (vector<Component*>::iterator it = m_components->begin(); it != m_components->end(); it++){
		double voltageDrop = ((*it)->getNode1()->getVoltage())-((*it)->getNode2()->getVoltage());
		if ((*it)->getName().at(0)=='R'){
			(*it)->setCurrent(voltageDrop/(*it)->getVal());
		}else if ((*it)->getName().at(0)=='L'||(*it)->getName().at(0)=='D'){
			(*it)->setVoltage(voltageDrop);
		}
	}
	//v source currents
	for (vector<Component*>::iterator it = m_voltageSources->begin(); it != m_voltageSources->end(); it++){
			Node *posn = (*it)->getNode1();
			Node *negn = (*it)->getNode2();
			bool reverse = false;
			KCL((*it),posn, reverse);//recursively find node without voltage source to get current
	}

}
//perform KCL on supernodes
void Circuit::KCL(Component *vsrc, Node *node, bool reverse){

	double current=0;
	for(vector<Component*>::iterator itc = node->getComponents()->begin(); itc != node->getComponents()->end(); itc++){
		if ((*itc)!=vsrc){
			if ((*itc)->getName().at(0)=='V'){
				KCL(*itc, ((*itc)->getOtherNode(node)), (!reverse));
			}
			if((*itc)->getName().at(0)=='C'){
				KCL(*itc, ((*itc)->getOtherNode(node)), reverse);
			}
			if (((*itc)->getNode1()==node&&(!reverse))||((*itc)->getNode2()==node&&(reverse))){
				current-=(*itc)->getCurrent();
			}else{
				current+=(*itc)->getCurrent();
			}
		}
	}
	vsrc->setCurrent(current);
}
//create solve and set new equation values
bool Circuit::solve(double *eqn, double *vals, double time){
	createEquations(eqn, vals, time);
	solveEquations(eqn, vals);
	setResults(vals);
	ApproxDiodes(eqn,vals,time);
	return true;
}


void Circuit::ApproxDiodes(double *eqn, double *vals, double time){
	double x,y;
	int solved = 0;
	while (solved != m_diodes->size()){ //all diodes must be solved
		solved = 0;
		for (vector<Component*>::iterator it = m_diodes->begin(); it != m_diodes->end(); it++){
			x = 0;
			y = 0.11;
			while (abs(y-x)>0.00001){ //require small difference
				x = (*it)->getVal();
				(*it)->setVal();
				y = (*it)->getVal();

				createEquations(eqn, vals, time);
				solveEquations(eqn, vals);
				setResults(vals);
			}
			solved++;
		}

	}
}
//creates eqns Ax = B, a is eqns
bool Circuit::createEquations(double*& eqs, double*& vals, double time){

	int n = getNumNodes()-1;
	eqs = new double[n*n];
	vals = new double[n];
	for (int i = 0; i < n; i++) { //init matrix
		vals[i] = 0;
		for (int j = 0; j < n; j++) {
			eqs[i + n*j] = 0;
		}
	}
	int i = 0;//rows
	vector<vector<Node*>>supernodes;
	vector<Node*> groundedNodes;
	//v equations
	for (vector<Component*>::iterator it = m_voltageSources->begin(); it != m_voltageSources->end(); it++) {
			createEquation((*it), (eqs + n*i), vals[i], time); //voltage source eqns
			Node* posn = (*it)->getNode1();
			Node *negn=(*it)->getNode2();
			bool pexists = false;
			bool nexists = false;
			if(posn->isGround()){
				groundedNodes.push_back(negn);
			}
			if(negn->isGround()){
				groundedNodes.push_back(posn);
			}
			if(!(posn->isGround())&&!(negn->isGround())){ //add to supernodes
				for(int k = 0;k<supernodes.size();k++){
					for (int l = 0;l<supernodes[k].size();l++){
						if (equalNodes(posn, supernodes[k][l])){
							pexists = true;
						}else if(equalNodes(negn, supernodes[k][l])){
							nexists = true;
						}
						if (pexists&&nexists){
							break;
						}
					}
					if(pexists&&!nexists){
							supernodes[k].push_back(negn);
					}else if(!pexists&&nexists){
							supernodes[k].push_back(posn);
					}
				}

				if(!pexists&&!nexists){
					supernodes.push_back(vector<Node*>{posn, negn});
				}
			}
			i++;
	}
	//node equations
	for (vector<Node*>::iterator it = m_nodes->begin(); it != m_nodes->end(); it++){
		if (!(*it)->hasV()&&!(*it)->isGround()){ //non voltage source eqns
			createEquation((*it), (eqs + n*i), vals[i], time);
			i++;
		}

	}
	//supernode equations
	for (int j = 0; j<supernodes.size();j++){
		bool grounded = false;
		for (int k = 0;k<supernodes[j].size();k++){
			for(int l = 0;l<groundedNodes.size();l++){
				if (supernodes[j][k]==groundedNodes[l]){
					grounded = true;
					break;
				}
			}
		}
		if(!grounded){
			createEquation(supernodes[j], (eqs + n*i), vals[i], time);
			i++;
		}

		}


	return true;
}
//eqn for specific Node
bool Circuit::createEquation(Node* node, double* eqn, double& val, double time){
	for (vector<Component*>::iterator it = node->getComponents()->begin(); it != node->getComponents()->end(); it++) {
			double x;
			switch ((*it)->getName().at(0)) {
			case 'R':
				x = 1 / (*it)->getVal(); //conductance
				eqn[node->getId()] += x; //set value of combined node
				if (!(*it)->getOtherNode(node)->isGround()){
					eqn[(*it)->getOtherNode(node)->getId()] -= x;//offset
				}
				break;
			case 'L':
				if ((*it)->getNode1() == node) {
					x = -(*it)->getCurrent(time);
				}
				else {
					x = (*it)->getCurrent(time);
				}
				val+= x;
				break;
			case 'I':
				if ((*it)->getNode1() == node) {
					x = -(*it)->getCurrent(time);
				}
				else {
					x = (*it)->getCurrent(time);
				}
				val += x;
				break;
			case 'D':
				x = (*it)->getVal();//conductance
				eqn[node->getId()] += x;
				if (!(*it)->getOtherNode(node)->isGround()){
					eqn[(*it)->getOtherNode(node)->getId()] -= x;
				}
				if ((*it)->getNode1() == node) {//source current
					x =-(*it)->getVal_I();
				}
				else {
					x =(*it)->getVal_I();
				}
				val+= x;

				break;
			}
		}
}
//eqn for vsources
bool Circuit::createEquation(Component* vsrc, double* eqn, double& val, double time){
	if(!vsrc->getNode1()->isGround()){
		eqn[vsrc->getNode1()->getId()] = 1;}
	if (!vsrc->getNode2()->isGround()){
		eqn[vsrc->getNode2()->getId()] = -1;}
	val = vsrc->getVoltage(time);
}
//eqn for supernodes
bool Circuit::createEquation(vector<Node*>nodes, double* eqn, double& vals, double time){
	for (int i = 0;i<nodes.size();i++){//create new eqn for all nodes
		createEquation(nodes[i], eqn, vals, time);
	}
}

//solve Ax=B
bool Circuit::solveEquations(double* eqns, double* vals){
	int numofeqs = getNumNodes() - 1;
	Map <Matrix<double,Dynamic,Dynamic,RowMajor>> A(eqns, numofeqs, numofeqs);
	Map<VectorXd> b(vals, numofeqs);
	VectorXd x = A.colPivHouseholderQr().solve(b);
	for (int i = 0; i < numofeqs; i++){
	vals[i] = x[i];}

	return true;
}
