
#include "ravicha_chart.h"

//Default constructor
Chart:: Chart(){}//the default constuctor for pointList is automatically called

//copy constructor
Chart:: Chart(const Chart& src): pointList(src.pointList) {}

//move constructor
Chart:: Chart(Chart&& src) : pointList(std::move(src.pointList)) {}

//Constructor to create a chart from filename
Chart::Chart(const std::string& fileName) {
        std::ifstream f1 (fileName);
	std::istream_iterator <Point> pointReader(f1), eof;
	pointList = std::move(std::vector<Point>(pointReader , eof));
      }

// Stream extraction operator for chart
std::ostream& operator<<(std::ostream& os, const Chart& c){
  std::copy(c.pointList.begin(), c.pointList.end(), std::ostream_iterator<Point>(os, "\n"));
  return os;
}

// Stream insertion operator for chart
std::istream& operator>>(std::istream& is, Chart& c){
  std::istream_iterator <Point> pointReader(is), eof;
  std::copy(pointReader, eof, c.pointList.begin());
 return is;
}

 //The assignment operator enables assignment of one chart object to another
Chart& Chart :: operator=(const Chart& src) {
  this->pointList =  src.pointList; 
 return *this;
}

//it is a method that detects if a given point is in this chart. 
bool Chart :: contains(const Point& p ) const {
  return std::find ( pointList.begin(), pointList.end(), p ) != pointList.end(); 
}

Chart Chart :: operator+(const Chart& other) const {
  //when a method is declared with const, then it cannot modify this and its instance variables.
  // it has two vectors, two sets of points, it needs to add those points that are in the one list(that a//re not there in the first list) to the another list without modifying the content.
  Chart result;
  std::copy(pointList.begin(), pointList.end(), std::back_inserter(result.pointList));
  std::copy_if (other.pointList.begin(), other.pointList.end(), std::back_inserter(result.pointList), [&result](const Point& p){return (!result.contains(p));} );
  return result;  
}

//it removes the contents of the list specified
Chart Chart :: operator-(const Chart& other) const {
  Chart result;
  std::copy_if (pointList.begin(), pointList.end(), std::back_inserter(result.pointList),[&other](const Point& p){return (!other.contains(p));} );
  return result;  
}


//This method is used to multiply points in this chart with the x & y values in the supplied scale
 Chart Chart :: operator*(const Point& scale) const {
  Chart result(*this);
  std::transform(result.pointList.begin(),result.pointList.end(), result.pointList.begin(),
		 [&scale](Point& p) {return Point(p.getX() * scale.getX(), p.getY()*scale.getY()); });
  return result;
 }

//This method is used to divide points in this chart with the x & y values in the supplied scale.  
 Chart Chart :: operator/(const Point& scale) const {
  Chart result(*this);
  std::transform(result.pointList.begin(),result.pointList.end(), result.pointList.begin(),
		 [&scale](Point& p) {return Point(p.getX()/scale.getX(), p.getY()/scale.getY()); });
  return result;
 }

//This method shifts the points in this chart to the right by value locations by inserting zeros at the beginning.  
Chart Chart :: operator>>(int value) const{
Chart result;
  result.pointList = std::vector<Point>(value, Point(0,0));
  result.pointList.insert(result.pointList.end(),pointList.begin(), pointList.end());
  return result;
}
 
//This method shifts the points in this chart to the left by removing points at the beginning of the list.
Chart Chart :: operator<<(int value) const{
   Chart result;
   std::copy(pointList.begin()+value, pointList.end(), std::back_inserter(result.pointList));
   return result;
}

//it is a method to display a histogram of distribution of unique points in the 4 quadrants.
void Chart:: analyze(std::ostream& os, const int scale) const {
 Chart unique;
 int maximum  = 0;
 int count[4];
    std::copy_if(pointList.begin(), pointList.end(), std::back_inserter(unique.pointList),
	       [&unique] (const Point& p) { return !(unique.contains(p)); } );
    std::vector<int> quadrants(unique.pointList.size());
    std::transform(unique.pointList.begin(), unique.pointList.end(), quadrants.begin(), std::mem_fun_ref(&Point::getQuadrant));

    for(int i=0; i<4; i++ )
         count[i] = count_if(quadrants.begin(), quadrants.end(), std::bind2nd(std::equal_to<int>(),i+1));
	 maximum = std::max(count[0],std::max(count[1],std::max(count[2],count[3])));
  
  os << "I Quadrant  : " << std::string(count[0] * scale / maximum, '*') << std::endl;
  os << "II Quadrant  : " << std::string(count[1] * scale / maximum, '*') << std::endl;
  os << "III Quadrant : " << std::string(count[2] * scale / maximum, '*') << std::endl;
  os << "IV Quadrant : " << std::string(count[3] * scale / maximum, '*') << std::endl;     
}

