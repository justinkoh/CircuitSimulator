#ifndef utils_hpp
#define utils_hpp
#include <string>
#include <vector>

class Funct{
private:
  std::string m_funct; //for most components funct = params[0]
  std::vector<double> m_params;
public:
  Funct();
  Funct(std::string funct, std::vector<double> params);
  void Read_Params();
  void Get_Name();
  double getValAt(double time); //if it is sine source, uses the time
};


double series_sin(double x); //sin x is slow
double series_exp(double x);

double integrate(double a, double b, Funct f);


#endif
