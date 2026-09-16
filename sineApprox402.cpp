#include<iostream>

using namespace std;

// Name: Tianxing(Hank) He, 
// Date: 2026/09/15
// Purpose: This program uses Taylor series to approximate sin value
const double PI_VALUE = 3.14159265359;
const int MAX_TERMS = 5;
const int MIN_TERMS = 1;
const int MAX_FACTORIAL_PARAM = 12;
const double PI_RADIAN_DEGREE = 180.0;
double convertDegreesToRadians(const double angleDeg);
//converting degrees to radians
bool toThePower(const double baseVal, const int exponentVal, double& outResult);
//calculate exponential value of baseVal to the power of exponentVal
bool computeFactorial(const int inVal, int& outFactorial);
//calculate factorial of inVal
bool approximateSine(const double angleRad, const int numTerms, 
                     double& outSineVal);
//approximate sine value using Taylor series based on given rad and terms

#ifdef ANDREW_TEST
#include "andrewTest.h"
#else
int main() {
  cout<<"Would you like to enter angle in degrees (d) or radians (r)? ";
  char format;
  cin>>format;
  bool failureFlag = false;
  if (format == 'd' || format == 'r') {
    double angle;
    cout<<"Enter the angle: ";
    cin>>angle;
    double angleRad;
    if (format == 'd') {
      angleRad = convertDegreesToRadians(angle);
    }
    else {
      angleRad = angle;
    }
    cout<<"How many terms to use in the series (1 to 5 inclusive): ";
    int numTerms;
    cin>>numTerms;
    double sinVal = 0.0;
    if (approximateSine(angleRad, numTerms, sinVal)) {
      cout<<"sin(angle) = "<<sinVal<<endl<<endl;
      cout<<"Here are results for other numbers of terms:"<<endl;
      for (int i = MIN_TERMS; i <= MAX_TERMS; i++) {
        double sineVal = 0.0;
        if (i != numTerms && approximateSine(angleRad, i, sineVal)) {
          cout<<"  # terms: "<<i<< " result: "<<sineVal<<endl;
        }
      }
    }
    else {
      //the sine function only returns false when term is out of range
      cout<<"ERROR: Invalid input - must respond with value between 1 and 5!"
          <<endl;
      failureFlag = true;
    }
  }
  else {
    cout<<"ERROR: Invalid input - must respond with either d or r!"<<endl;
    failureFlag = true;
  }
  if (failureFlag) {
    cout<<"Unable to provide results due to invalid inputs!"<<endl;
  }
  return 0;
}
#endif

double convertDegreesToRadians(const double angleDeg) { 
  return angleDeg * PI_VALUE / PI_RADIAN_DEGREE;
}
bool toThePower(const double baseVal, const int exponentVal,
                double& outResult) { 
  if (exponentVal < 0) {
    return false; // Return false for negative exponents
  }
  outResult = 1.0;
  for (int i = 0; i < exponentVal; i++) {
    outResult *= baseVal;
  }
  return true; // Return true for successful calculation

}
bool computeFactorial(const int inVal, int& outFactorial) { 
  if (inVal < 0 || inVal > MAX_FACTORIAL_PARAM) {
    return false; // Return false for negative and too large input
  }
  outFactorial = 1;
  for (int i = 1; i <= inVal; i++) {
    outFactorial *= i;
  }
  return true; // Return true for successful calculation
}

bool approximateSine(const double angleRad, const int numTerms, 
                     double& outSineVal) {
  if (numTerms > MAX_TERMS || numTerms < MIN_TERMS) {
    return false;
  }  
  double radInRange;
  radInRange = angleRad;  
  // add and subtract 2*pi to make the angle within range of -pi to pi
  while (radInRange > PI_VALUE) {
    radInRange -= 2 * PI_VALUE;
  }
  while (radInRange < -PI_VALUE) {
    radInRange += 2 * PI_VALUE;
  }
  outSineVal = radInRange;
  for (int i = 1; i < numTerms; i++) {
    //term: (-1)^i * x^(2*i+1) / (2*i+1)!
    double term;
    if (!toThePower(radInRange, 2 * i + 1, term)) { //calculate x^(2*i+1)
      return false; // Return false if power calculation fails
    }
    int factorial;
    if (!computeFactorial(2 * i + 1, factorial)) { //calculate (2*i+1)!
      return false; // Return false if factorial calculation fails
    }
    double termSign;
    if (!toThePower(-1, i, termSign)) { //calculate (-1)^i
      return false; // Return false if power calculation fails
    }
    outSineVal += term * termSign / factorial;
  }
  return true; // Return true for successful calculation
}
