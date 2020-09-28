#include "nodes.hpp"
#include "component.hpp"
#include <string>

using namespace std;

Node::Node(string name, int id){
	m_name = name; //unique
	m_id = id;//equations
	m_voltage = 0;
	m_components = new vector<Component*>(0);
	if (name == "0"){
		m_isground = true;
	}else{
		m_isground = false;
	}
	m_containsV = false;

}
// add component to node
void Node::addComponent(Component* component) {
	m_components->push_back(component);
	if (component->getName().at(0)=='V'||component->getName().at(0)=='C'){
		m_containsV = true;
	}
}
// getters and setters
double Node::getVoltage(){
	return m_voltage;
}
double Node::getVoltage(double time){
	return m_voltage;
}
void  Node::setVoltage(double voltage){
	m_voltage = voltage;
}
int Node::getNumOfComponents(){
	return m_components->size();
}
string Node::getName(){
	return m_name;
}
bool Node::isGround(){
	return m_isground;
}
void Node::setGround(bool isground){
	m_isground = isground;
}
int Node::getId(){
	return m_id;
}
void Node::setId(int id){
	m_id = id;
}
vector<Component*>* Node::getComponents() {
	return m_components;
}
bool Node::hasV(){
	return m_containsV;
}
