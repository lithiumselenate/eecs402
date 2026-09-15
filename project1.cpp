#include<iostream>

using namespace std;

// Name: Tianxing(Hank) He, 
// Date: 2026/09/15
// Purpose: This program use Taylor series to approximate sin value
const double PI = 3.14159265359;
double convertDegreesToRadians(const double angleDeg);
//converting degrees to radians
bool toThePower(const double baseVal, const int exponentVal, double& outResult);
//calculate exponential value of baseVal to the power of exponentVal
bool computeFactorial(const int inVal, int& outFactorial);
//calulate factorial of inVal
bool approximateSine(const double angleRad, const int numTerms, double& outSineVal);
//calculate to sine value using Taylor series, 5 terms

#ifdef ANDREW_TEST
#include "andrewTest.h"
#else
int main(){
  cout<<"Would you like to enter angle in degrees (d) or radians (r)? ";
  char format;
  cin>>format;
  if (format == 'd') {
    double angleDeg;
    cout<<"Enter the angle: ";
    cin>>angleDeg;
    cout<<"How many terms to use in the series (1 to 5 inclusive): ";
    int numTerms;
    cin>>numTerms;
    double angleRad = convertDegreesToRadians(angleDeg);
    double sinVal = 0.0;
    if (approximateSine(angleRad, numTerms, sinVal)){
        cout<<"sin(angle) = "<<sinVal<<endl<<endl;
    }
    cout<<"Here are results for other numbers of terms:"<<endl;
    for (int i=1;i<=5;i++){
      double sinVal = 0.0;
      if ( i!=numTerms && approximateSine(angleRad, i, sinVal)){
        cout<<"# terms: "<<i<<" result: "<<sinVal<<endl;
      }
    }
  }
  else if (format)
# endif

double convertDegreesToRadians(const double angleDeg){ 
  return angleDeg * PI / 180.0;
}
bool toThePower(const double baseVal, const int exponentVal, double& outResult){ 
  if (exponentVal < 0) {
    return false; // Return false for negative exponents
  }
  outResult = 1.0;
  for (int i = 0; i < exponentVal; i++) {
    outResult *= baseVal;
  }
  return true; // Return true for successful calculation

}
bool computeFactorial(const int inVal, int& outFactorial){ 
  if (inVal < 0) {
    return false; // Return false for negative input
  }
  outFactorial = 1;
  for (int i = 1; i <= inVal; i++) {
    outFactorial *= i;
  }
  return true; // Return true for successful calculation
}

bool approximateSine(const double angleRad, const int numTerms, double& outSinVal){  
  double radInRange;
  radInRange = angleRad;  
  // add and substract 2*PI to make the angle within range of pi and -pi
  while (radInRange > PI) {
    radInRange -= 2 * PI;
  }
  while (radInRange < -PI) {
    radInRange += 2 * PI;
  }
  for (int i = 1; i <=2*numTerms+1; i += 2) {
    double term;
    if (!toThePower(radInRange, i, term)) {
      return false; // Return false if power calculation fails
    }
    int factorial;
    if (!computeFactorial(i, factorial)) {
      return false; // Return false if factorial calculation fails
    }
    outSinVal += term / factorial;
  }
  return true; // Return true for successful calculation
}
