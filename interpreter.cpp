#include <bits/stdc++.h>
 
using namespace std;
 
#define REP(c, it)   for( typeof( (c).begin()) it = (c).begin();  it != (c).end(); ++it)

string line;
bool start = false;
map<string, string> M;

int main() {
   M["pushl"]  = "pushq";
   M["%rbp"]   = "%ebp";
   M["8"]      = "16";
   M["-8"]     = "-16";
   M["5"]      = "6";
   M["5,"]      = "6,";
   M["movl"]   = "movq";
   M["%esp,"]   = "%rsp,";
   M["%ebp"]   = "%rbp";
   M["$.LC0,"] = "$0,";
   M["(%esp)"] = "%eax";
   M["leave"]  = "popq  %rbp";
   M["4,"]     = "7,";
   M["4"]      = "8";
   
   // Input file
   ifstream infile("hello_32bit.asm");
   // Generated Output file
   ofstream opfile("output_64bit.s");

   while ( getline(infile, line) ) {
      if ( line.find(".cfi_startproc") != std::string::npos ) {
         opfile << line << '\n';
         start = true;
      } else if ( line.find("andl") != std::string::npos ) {
         opfile << "\tmovl   $.LC0, %edi" << "\n";
      } else if ( line.find("subl") != std::string::npos || line.find(".cfi_restore") != std::string::npos ) {
         continue;
      } else if ( line.find("call") != std::string::npos ) {
         opfile << line << '\n';         
      } else {
         if ( start ) {
            vector<string> tokens;
            istringstream iss(line);
            copy(istream_iterator<string>(iss),
                 istream_iterator<string>(),
                 back_inserter(tokens));

            REP(tokens, it) {
               if ( M.count(*it) ) {
                  line.replace(line.find(*it), (*it).length(), M[*it]);
                  if ( (*it) == "movl" )
                     M[*it] = (*it);
               }
            }
         }
         opfile << line << "\n";
      }
   }
   return 0;
}