#include "component.hpp"
#include "utils.hpp"
#include <string>
#include <cfloat>
#include <cmath>
using namespace std;

void Component::setVoltage(double voltage) {
  m_voltage = voltage;
}
void Component::setCurrent(double current) {
	m_current = current;
}
double Component::getVoltage() {
	return m_voltage;
}
double Component::getCurrent() {
	return m_current;
}
double Component::getVoltage(double time) {
	return m_voltage;
}
double Component::getCurrent(double time) {
	return m_current;
}
double Component::getVal_I() const {
	return m_source;
}

double Component::getVal() const{
  return m_val;
}
void Component::setVal(double x){}

void Component::setVal(){}

int Component::getId() {
	return m_id;
}
Node* Component::getNode1() {
	return m_node1;
}
Node* Component::getNode2() {
	return m_node2;
}

string Component::getName() {
	return m_name;
}
void Component::setNode1(Node* node) {
	m_node1 = node;
}
void Component::setNode2(Node* node) {
	m_node2 = node;
}
void Component::setId(int id) {
	m_id = id;
}

Node* Component::getOtherNode(Node* node) { 
	if (node == m_node1){
		return m_node2;
	}else{
		if (node == m_node2){
			return m_node1;
		}else{
			return NULL;
		}
	}
}
