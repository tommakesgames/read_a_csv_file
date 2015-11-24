//
// How to read a CSV file.
// 
// (C) Andy Thomason 2015
//
// Note CSV files may contain quotes and other complexity, so this
// is not completely general, but it is very simple.

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <ostream>


using namespace std;

vector<string> names;
vector<int> score;



int main() {


  ifstream is("../test.csv");

  if (is.bad()) return 1;

  // store the line here in a character ARRAY called buffer.
  char buffer[2048];

  // loop over lines
  // whilst you haven't encountered the end of file (eof)
  while (!is.eof()) {
	  // take in the next line and store it in the variable 'buffer'.
	  // here the getline is using 2 arguments getline (name of variable, size of stream taken in). A 3rd argument would have specified a custom delimiter)
    is.getline(buffer, sizeof(buffer));

    // loop over columns
	// *b is a pointer to the first VALUE (not address) of the ARRAY buffer.
	// b is set OUTSIDE of the 'for' loop, so scope is bigger than e.
    char *b = buffer;
    for (int col = 0; ; ++col) {
		
		// also, e has local scope in the for loop, b is outside.
		// value of e is b (an address)
      char *e = b;

	
	  // As long as the VALUE of e isn't zero or a comma, increase e itself by 1.
      while (*e != 0 && *e != ',') ++e;

      // now b -> e contains the chars in a column
      if (col == 0) {
		 //This command appends the characters between b and e, as a string, to the end of names.
        names.emplace_back(b, e);
      } else if (col == 1) {
		//This commant appends the characters between b and e, as an integer, to the end of score.
        score.push_back(atoi(b));
      }

      if (*e != ',') break;
	  //this line moves b beyond the comma to the next column. i.e. the next start point.
      b = e + 1;
    }
  }

  //Trying to get names printed to the screen.
  //finally got it, but with warnings - due to extra empty field in names. Why is that?
  //Found extra carraige return in text file. Loop only stops when it reaches end of file, so this was making it add another entry.
  
  for (int i = 0; i < names.size(); i++)
  {
	  cout << names[i].data() << " scored " << score[i] << " in scrabble today." << endl;
  }
  

  
  cout << endl << "Press Enter to finish..." << endl;
  cin.ignore(10, '\n');

  return 0;


}
