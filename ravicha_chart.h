#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <fstream>
#include <cmath>
#include <functional>
#include <string>
#include "Point.h"

using namespace std;

class Chart{

 private:

  std::vector<Point> pointList;

 public:

  //Default constructor
  Chart ();

  //copy constructor
  Chart (const Chart& src);

  //move constructor
  Chart (Chart&& src);

    //Constructor to create a chart from a filename
  Chart ( const std::string& fileName );

  //extraction operator - writes output
    friend std::ostream& operator << ( std::ostream& os, const Chart& c );

    //insertion operator - reads input
    friend std::istream& operator >> ( std::istream& is, Chart& c);

    //Assignment operator - The assignment operator enables assignment of one chart object to another
    Chart& operator = ( const Chart& src);

     //it is a method that detects if a given point is in this chart.
     bool contains(const Point& p) const;

    //it adds the contents of the list specified to the existing list of points(chart)
     Chart operator+(const Chart& other) const;

     //it removes the contents of the list specified
     Chart operator-(const Chart& other) const;

     //This method is used to multiply points in this chart with the x & y values in the supplied scale
     Chart operator*(const Point& scale) const;

      //This method is used to divide points in this chart with the x & y values in the supplied scale. 
     Chart operator/(const Point& scale) const;

     //This method shifts the points in this chart to the right by removing points at the beginning of the list.
     Chart operator>>(int value) const;

     //This method shifts the points in this chart to the left by removing points at the beginning of the list.
     Chart operator<<(int value) const;

     //it is a method to display a histogram of distribution of unique points in the 4 quadrants.
     void analyze(std::ostream& os, const int scale) const;

  };
