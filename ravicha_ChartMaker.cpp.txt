#include "ravicha_ChartMaker.h"
#include <iostream>

Chart ChartMaker::load() {
 
  std::cout << "Enter the filename:";
  std::cin >> fileName;
  Chart current(fileName);
  return current;
}

Chart ChartMaker::add(Chart &current) {
 
  std::cout << "Enter the fileName:";
  std::cin >> fileName;
  Chart other(fileName); //accepts another chart to add data from there to the current point
  Chart result = current + other;
  return result;
}

Chart ChartMaker::subtract(Chart& current) {
 
  std::cout << "Enter the fileName:";
  std::cin >> fileName;
  Chart other(fileName); //removes  another chart to add data from there to the current point
  Chart result = current - other;
  return result;
}

Chart ChartMaker::scaleMultiply(Chart& current) {
	Point scale;
	std::cout << "Enter the Point to be scaled up by: ";
	std::cin >> scale;
	return (current * scale);
}

Chart ChartMaker::scaleDivide(Chart& current) {
	Point scale;
	std::cout << "Enter the Point to be scaled down by: ";
	std::cin >> scale;
	return (current/scale);
}

void ChartMaker::printHistogram(Chart& current) {
  int scale;
  std::cout << "Enter the scale for the histogram: ";
  std::cin >> scale;
  current.analyze(std::cout, scale);
}

Chart ChartMaker::shiftLeft(Chart& current) {
	int value;
	std::cout << "Enter positions to shift left: ";
	std::cin >> value;
	return (current<<value);
}

Chart ChartMaker::shiftRight(Chart& current) {
	int value;
	std::cout << "Enter positions to shift right: ";
	std::cin >> value;
	return (current>>value);
}

void ChartMaker::saveCurrent(Chart& result) {
       std::cout << "Enter path to save file: ";
	std::cin >> fileName;
	std::ofstream destination(fileName);
	destination << result;
	destination.close();
}

void ChartMaker::printCurrent(Chart& result) {
	std::cout << result;
}

void ChartMaker::printHelpMsg(std::ostream& os) {
    os << "All commands are single characters." << std::endl;

    os << "Valid commands are:"<< std::endl;

    os << "l: Load data from file as current set of points" << std::endl;

    os << "+: Add data from another Chart to current points" << std::endl;

    os << "-: Subtract data from another file from current points" << std::endl;

    os << "*: Scale current points by given pair of values" << std::endl;

    os << "/: Scale current points by given pair of values" << std::endl;

    os << "?: Print histogram current point distribution" << std::endl;

    os << "<: Shift points to left by a given value." << std::endl;

    os << ">: Shift points to right by a given value." << std::endl;

    os << "s: Save the current set of points to a given file" << std::endl;

    os << "p: Print current set of points on screen." << std::endl;

    os << "h: Print this message" << std::endl;

    os << "q: Quit" << std::endl;
}

//This calls/implements all the functions that have been declared and defined.
int ChartMaker::run() {
  
	   char choice;
           Chart current;
  do {
	  std::cout<<"Enter command to perform an operation('h' for help):";
	  std::cin>>choice;
	  if(choice == 'l') {
	    current = load();
	  } 

	  else if(choice == '+') {
		current = add(current);
	  }

	  else if(choice == '-') {
		current = subtract(current);
	  }

	  else if(choice == '*') {
		current = scaleMultiply(current);
	  }
	  
	  else if(choice == '/') {
		current = scaleDivide(current);
	  }

	  else if(choice == '?') {
		printHistogram(current);
	  }
	  
	  else if(choice == '<') {
		current = shiftLeft(current);
	  }
	  
	  else if(choice == '>') {
		current = shiftRight(current);
	  }

	  else if(choice == 's') {
		saveCurrent(current);
	  }
	  
	  else if(choice == 'p') {
		printCurrent(current);
	  }

	  else if(choice == 'h') {
		printHelpMsg(std::cout);
	  }
	  
	  else if(choice == 'q') {
		exit(EXIT_FAILURE);
	  }

	  else
		continue;
  }while (choice != 'q');

  return -1;
}
