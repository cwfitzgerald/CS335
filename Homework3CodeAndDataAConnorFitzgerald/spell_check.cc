// YOUR NAME.

#include "quadratic_probing.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;



// Sample main for program spell_check
int main(int argc, char **argv) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <document-file> <dictionary-file>" << endl;
    return 0;
  }
  
  const string document_filename(argv[1]);
  const string dictionary_filename(argv[2]);
  
  cout << "Input document filename is " << document_filename << endl;
  cout << "Input dictionary filename is " << dictionary_filename << endl;

  // Call functions implementing the assignment requirements.

  return 0;
}
