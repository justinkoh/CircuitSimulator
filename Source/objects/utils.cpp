#include "utils.hpp"
#include <cmath>
#include <string>
#include <iostream>
#include <cassert>
double pi = 3.14159265358979323846;
//note need to make more efficient without cmath
double series_sin(double x){
  return sin(x);
}
double series_exp(double x){
  return exp(x);
}

bool is_number(const std::string& s)
{
    char* end = nullptr;
    double val = strtod(s.c_str(), &end);
    return end != s.c_str() && *end == '\0' && val != HUGE_VAL;
}

Funct::Funct(std::string funct, std::vector<double> params){
	m_funct = funct; //assume input is correct
	m_params= params;
}
void Funct::Read_Params(){
  for (int i = 0;i<m_params.size();i++){
    std::cout<<m_params[i]<<" ";
  }
}
void Funct::Get_Name(){
    std::cout<<m_funct<<" ";
}
double Funct::getValAt(double time){ //calculate value at time
  if(is_number(m_funct)){
    double temp_num = std::stod(m_funct);
    assert(m_params[0]==temp_num);
    return m_params[0];
  }
	if(m_funct == "SINE"){
			double offset = m_params[0];
			double amp = m_params[1];
			double Freq = m_params[2];
			double Td= m_params[3]; //tdelay
			double Theta = m_params[4];
			double Phi = m_params[5];
			double Ncycles =m_params[6];
      if (Ncycles <0){
        Ncycles = ceil((time-Td)*Freq)+1;
      }
			if ((time<Td)||((time-Td)*Freq>Ncycles)){
				return offset+amp*series_sin(pi*Phi/180);
			}else{
        return offset+amp*series_exp(-(time-Td)*Theta)*series_sin(2*pi*Freq*(time-Td)+pi*Phi/180);
			}
	}else if(m_funct == "PULSE"){
    double Voff = m_params[0]; // initval
    double Von = m_params[1];//on val
    double Td = m_params[2]; //delay
    double Tr= m_params[3];//rise time
    double Tf= m_params[4];//fall time
    double Ton = m_params[5]; //on time
    double Tperiod = m_params[6];//time for 1
    double Ncycles =m_params[7];//cycles

    if (Tperiod <=0){
      Tperiod = Ton+Tr+Tf;
    }
    double T1Frac = Tr/Tperiod;
    double T2Frac =(Tr+Ton)/Tperiod;
    double T3Frac =(Tr+Ton+Tf)/Tperiod;
    if (Ncycles <0){
      Ncycles = 1;
    }
    if (time<Td||((time-Td)/Tperiod)>Ncycles){ //or enough cycles have elapsed
      return Voff;
    }else{
      double temp = (time-Td)/Tperiod;
      double pos = (temp)-floor(temp);
      if(pos<=T1Frac){
        double grad = (Von-Voff)/Tr;
        return Voff+(grad*pos*Tperiod);
      }
      if (pos<T2Frac){
        return Von;
      }
      if (pos<T3Frac){
        double grad = (Voff-Von)/Tf;
        return Von+(grad*(pos-T2Frac)*Tperiod);
      }else{
        return Voff;
      }

    }
  }else{
    return -100;
  }
}
