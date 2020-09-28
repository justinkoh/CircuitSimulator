#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
#include<cassert>
#include "objs/component.hpp"
#include "objs/nodes.hpp"
#include "circuit.hpp"
#include "objs/utils.hpp"
using namespace std;

static double m = 0.001;
static double k = 1000;
static double Meg = 1000000;
static double G = 1000000000;
static double u = 0.000001;
static double n = 0.000000001;
static double p =  0.000000000001;

bool is_num(const string &str){
  int point = 0;
  for(int  i = 0;i<str.length();i++){
    char c = str[i];
    if (!isdigit(c)){
      if (c=='.'&&point==0){
        point+=1;
      }else{
        return false;
      }
    }
  }
  return true;
}

double to_num(string num){
    char c = num.at(num.length()-1);
    double mult = 1;
    double _n;
    if (num.at(0)=='-'){//allow negatives
      mult = -1;
      num = num.substr(1, num.size()-1);
    }
    if (isdigit(c)){
      return stod(num)*mult;
    }
    if(c == 'g'){
       assert(is_num(num.substr(0, num.size()-3)));
      _n = stod(num.substr(0, num.size()-3))* mult;
      return _n*Meg;
    }
    assert(is_num(num.substr(0, num.size()-1)));
     _n = stod(num.substr(0, num.size()-1))* mult;
    if (c == 'm'){
      return _n*m;
    }else if(c == 'k'){
      return _n*k;
    }else if(c == 'G'){
      return _n*G;
    }else if(c == 'u'){
      return _n*u;
    }else if(c == 'n'){
      return _n*n;
    }else if(c == 'p'){
      return _n*p;
    }else{
      cerr<<"unknown quantity";
      return 0;
    }
}

vector<string> check(vector<string> params){
  assert(params.size()==4);
  if (params[3].at(0) =='-'){
      cout<<"Warning: invalid parameters for "<<params[0]<<endl;
      params[3] = params[3].substr(1, params[3].size()-1);
   }
   return params;
}

int main(){
  Circuit circuit;
  string input;
  vector<string> lines;
  vector<Component> components;
  double Tstop,Tstart,Tstep;
  lines.push_back(input);
  while (1){
      getline(cin, input);
      if (input == ".end"){
          break;
      }
     else{
       if (!input.empty()){
         lines.push_back(input);
       }
     }
  }
  for (int i = 1;i<lines.size();i++){
    string line = lines[i];
    if (line.at(0)!='*'&&line!=".backanno"){ //ignore comments and backanno
        istringstream iss(line);//split by spaces
        vector<string> params((istream_iterator<string>(iss)),
                               istream_iterator<string>());

      if ((params.size() == 4)&&(line.at(0)=='R'||line.at(0)=='L'||line.at(0)=='C'||line.at(0)=='V'||line.at(0)=='I')||line.at(0)=='D'){
          circuit.addNode(params[1]);
          circuit.addNode(params[2]);}
      if (line.at(0)=='R'){//add resistor
        params = check(params);
         Resistor *r = new Resistor(params[0],to_num(params[3]));
         circuit.addComponent(r,params[1],params[2]);
       }else if (line.at(0)=='L'){//inductor
         params = check(params);
         Inductor *l = new Inductor(params[0],to_num(params[3]));
         circuit.addComponent(l,params[1],params[2]);
       }else if (line.at(0)=='C'){//capacitor
         params = check(params);
         Capacitor *c = new Capacitor(params[0],to_num(params[3]));
         circuit.addComponent(c,params[1],params[2]);
       }else if (line.at(0)=='D'){//diode must be of type D
         assert(params.size()==4);
         Diode *d = new Diode(params[0]);
         circuit.addComponent(d, params[1], params[2]);
       }else if (line.at(0)=='V'||line.at(0)=='I'){
         if (params.size()==4){
           if (line.at(0)=='V'){
             VoltageSource *v = new VoltageSource(params[0],to_num(params[3]));
             circuit.addComponent(v,params[1],params[2]);
           }else{
             CurrentSource *i = new CurrentSource(params[0],to_num(params[3]));
             circuit.addComponent(i,params[1],params[2]);
           }

         }else{
           circuit.addNode(params[1]);
           circuit.addNode(params[2]);
           string funct = params[3];
           string temp = funct;
           vector<double> f_params;

           int pos = temp.find_first_of('(');
           string first_p = temp.substr(pos+1);
           funct = temp.substr(0,pos);
           f_params.push_back(to_num(first_p));

           for (int i = 4;i<params.size();i++){ //carry on till close bracket
             if (params[i].at(params[i].length()-1)!=')'){
               f_params.push_back(to_num(params[i]));
             }else{
               f_params.push_back(to_num (params[i].substr(0, params[i].size()-1)));
               break;
             }
           }
           if(funct == "SINE"){ //fill up with 0
             for (int i = f_params.size();i<6;i++){
               f_params.push_back(0);
             }
             f_params.push_back(-1);
           }else if (funct == "PULSE"){
               for (int i = f_params.size();i<7;i++){
                 f_params.push_back(0);
           }
           f_params.push_back(-1);
         }

         Funct *comp_funct = new Funct(funct, f_params);
         if (line.at(0)=='V'){
           VoltageSource *v = new VoltageSource(params[0],comp_funct);
           circuit.addComponent(v,params[1],params[2]);
         }else{
           CurrentSource *i = new CurrentSource(params[0],comp_funct);
           circuit.addComponent(i,params[1],params[2]);
         }
       }

       }else if(line.substr(0,5)==".tran"){
         assert(params.size()==5);
         //get transient details, takes latest cmd
         for(int i = 0;i<params.size();i++){
           if (params[i][params[i].size()-1]=='s'){//remove secs
             params[i]=params[i].substr(0, params[i].size()-1);
           }
         }
         Tstop = to_num(params[2]);
         Tstart = to_num(params[3]);
         Tstep = to_num(params[4]);
       }
     }
  }
  cout<<"Time,";
  circuit.outNames();
  //init matrix
  double *eqns = NULL;
  double *vals = NULL;

  for (double i = Tstart; i<=Tstop;i+=Tstep){
    circuit.solve(eqns, vals, i);
    cout<<i<<",";
    circuit.outVals();
    //output all nodes voltages and component currents
  }
}
