#include "ravicha_chart.h"
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <fstream>
#include <cmath>
#include <functional>
#include <string>

class ChartMaker {

private:
   std::string fileName;
   
public:
	ChartMaker() : fileName() {}

	  Chart load(); //Loads data from file as current set of point

	  Chart add(Chart& other); //Adds data from another Chart to current point

	  Chart subtract(Chart& other); //Subtracts data from another file from current points

	  Chart scaleMultiply(Chart& current);//Scales by multiplying  current points by given pair of values

	  Chart scaleDivide(Chart& current);//Scales by dividing  current points by given pair of values
  
	  void printHistogram(Chart& current);//Prints histogram current point distribution

	  Chart shiftLeft(Chart& current);// Shifts points to left by a given value

	  Chart shiftRight(Chart& current); //Shifts points right by a given value

	  void saveCurrent(Chart& result);// Saves the current set of points by a given file

	  void printCurrent(Chart& result); //Prints the current set of points on the screen

	  void printHelpMsg(std::ostream& os);//Prints this whole message for the user to read

	  int run(); //This function implements all the operations.

};
