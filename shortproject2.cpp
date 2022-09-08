// Author: Erick Damian Cabrera
// Course: CSCI-135
// Instructor: Gennadiy Maryash
// Assignment: Project 2 Phase 4.
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
using namespace std;

class same
{
  public: 
    string line;
    string before;
    string after;
    string newline;
    string space();
    string lastline;
};
string same::space()
{
  return " ";
}
 void splitOnSpace(string s, string & before, string & after) 
 {
    before="";
    after="";
    int i = 0;
    while (i < s.size() && not isspace(s[i])) // loops through strings that dont have spaces.
    { 
        before = before + s[i];               
        i++; 
    }
    i++;
    while (i < s.size()) 
    { 
        after = after + s[i]; 
        i++; 
    }
}
string theword(string theinput)
{   
    char c = (int)theinput[0] - 32;
    return theinput.empty()? "": isalpha(c)? c+ theword(theinput.substr(1)): theinput[0] + theword(theinput.substr(1));
}
string findbefore(string flowers)
{
  ifstream read("cmudict.0.7a"); // uploads the file to the program. 
  same sc;
  int i = 0;   // starts at index zero. class this too
  if (!isdigit(sc.before[0]))
    {
        while (!read.eof()) // reads until the end of the file. 
        {   
            splitOnSpace(sc.line,sc.before,sc.after);
            getline(read, sc.line);
            if (sc.before==flowers || sc.before==theword(flowers)) // if its all uppercase from the getgo or its changed into uppercase. 
                {
                    return sc.after;
                }
                i++; // Continously runs the whole program. 
        }
    }
    return "Not found"; // I could also make it into a string and report that.  reports error message if the input doesnt match before which is before the space.
    read.close();  // closes file.
}

 string findafter (string sound)
{
    string previous= findbefore (sound); // stores output from the previous one. 
    ifstream read("cmudict.0.7a");
    same sc;
    int i = 0;
    if (previous != "Not found")
    {
      while (!read.eof()) // reads until the end of the file. 
        {   
          splitOnSpace(sc.line,sc.before,sc.after);
          getline(read,sc.line);
          previous==sc.after && theword(sound)!=sc.before? sc.newline+=sc.before+sc.space():sc.newline;
                  i++; // Continously runs the whole program. 
          }
    return sc.newline;
    read.close();  // closes file.
    }
    return "Not found";
}
// ------------------------------------ passed here is old code ----------------------------------------------
string positions(string other)
{   
    int counter= 0;
    same sc;
    for (int i =0 ; i < other.length(); i++)
    {   
        if (isspace(other[i])) 
        {   
            counter++;
            int indexes = counter; // proper conversion from int datatype to string datatype.
            string str = to_string(indexes); // converstion is set for integers.
            sc.newline+= sc.space()+str;// + anothersp;  // conversion is stored into an empty string for further manipulation.
        }
    }
    return sc.newline; // returns string with amount of spaces. 
}
int spacescount(string other)
{
    int counter= 0;
    for (int i =0 ; i < other.length(); i++)
    {   
        isspace(other[i])?counter++:counter;
    }
    return counter; // returns total amount of spaces
}

string chunks(string str, int num)
{
    isspace(str[0])?str.erase(0,1):str; 
    stringstream name(str); // Used after the first space is taken out of the string. 
    same sc;
    vector <string> x;
    int i = 0;
    while (getline (name, sc.newline,' ')) // stream in getline, empty string , delimeter
    {
        x.push_back(sc.newline); // vector pushing back in empty string

           if (i + 1 == num) // num starts at 1, not zero , thus we need to add one to have an offset. 
          {
            sc.before += x[i];  // adding endlines.
            return sc.before;
          }
        i++;
    }
    return "";
}
string nospaces(string other, int erasenum, char let)
{
        string newline = positions(other);
        same sc;
        string revert;
        int spacescounter = spacescount(other);
// ----------------- Gets single digits from strings and streams it into the letters function. -------------------------------
        for (int i =0; i < newline.length() ; i++ ) // basically gets single digit numbers from string of num.
        {  
            int ic = newline[i] - '0'; // this is like mod 48 that converts char to num. Converts char to num.= 
            !isdigit(newline[i-1]) && !isdigit(newline[i+1])? ic!=erasenum?revert+=sc.space() + chunks(other,ic):revert+=sc.space() + let: !isspace(newline[i])? sc.line+=newline[i]:"";
        }
// ------------------------------ Creates double digits---------------------------------------------------
        for (int i=0; i < sc.line.length(); i++) // this dictates why it goes up by 3. 
        {                                     // however we need to fix this to make it go up by 4 and it would work. 
            i%2==1?sc.lastline +=sc.line[i] + sc.space():sc.lastline+=sc.line[i];
        }
        int temp;
        int counter=0;

        spacescounter>=10 && sc.lastline.length()>9?counter=sc.lastline.length()/3 - 3:counter;
//------------------------------- streams second digit numbers to the letters function------------------------------------------
         for (int i = 0; i < sc.lastline.length()+ counter; i++) 
        {
            stringstream number(sc.lastline);
            number >> temp;
            temp!=erasenum?revert+= sc.space() + chunks(other,temp):revert+= sc.space() + let;
            sc.lastline.erase(0,3);
        }
        return revert;
}
string first(string other , int position, char letter)
{   
    string newline= nospaces(other, 1 + position,letter); 
    newline.erase(remove(newline.begin(), newline.end(), '\0'), newline.end());
    return newline;
}
bool digit(string s)
{
  return isdigit(s[s.length()-2])?1:0;
}
 string samepro (string sound)
{
    string previous= findbefore (sound); // stores output from the previous one. 
    ifstream read("cmudict.0.7a");
    same sc;
    int spaces = spacescount(previous);
    int i = 0;
  if (previous != "Not found")
  {
    while (!read.eof()) // reads until the end of the file. 
      {   
          splitOnSpace(sc.line,sc.before,sc.after);
          getline(read, sc.line);
        if (spacescount(sc.after)==spacescount(previous)) // counts the spaces which shuld give you amount of chunks.
          {
            for (int j=0; j < spaces; j++)  // from index 0 to the amount of spaces. if spaces=5 then its, 0,1,2,3,4.
              {
                first(sc.after,j,' ') == first(previous,j,' ') && theword(sound)!=sc.before && previous!=sc.after && digit(sc.before)==false? sc.newline+= sc.before + sc.space():sc.newline;
              }
          }
                    i++; // Continously runs the whole program. 
        }
      return sc.newline;
      read.close();  // closes file.
  }
    return "Not found";
}
string removeslash(string word) 
{
 for (int i = 0; i < word.length(); i++) 
 {
    word.substr(i,2)==" /"? word.erase(i,2):word;
 }
 return word;
}
string onemore (string sound)
{
  // this could essentially look for all words that have the same after as the previous function.
    string previous= findbefore (sound); // stores output from the previous one. 
    ifstream read("cmudict.0.7a");
    same sc;
    int spaces = spacescount(previous);
    int i = 0;
  if (previous != "Not found" )
  {
    while (!read.eof()) // reads until the end of the file. 
    {   
      splitOnSpace(sc.line,sc.before,sc.after);
      getline(read,sc.line);
      string one;
      string astro;
          if (spacescount(sc.after)==spacescount(previous)+1)  
        { 
            for (int g =0; g < spaces + 1; g++)
            {
              one = first(sc.after,g,'/');
              astro = removeslash(one);   
              astro == previous && theword(sound)!=sc.before && previous!=sc.after && digit(sc.before)==false? sc.newline+=sc.before+sc.space():sc.newline;             
              }   
          }
            i++; // Continously runs the whole program. 
    }  // connects the while loop
        return sc.newline;
        read.close();  // closes file.
  }
      return "Not found";
}
string lastonebaby (string sound)
{   // this could essentially look for all words that have the same after as the previous function.
    string previous= findbefore (sound); // stores output from the previous one. 
    ifstream read("cmudict.0.7a");
    same sc;
    int spaces = spacescount(previous);
    int i = 0;
  if (previous != "Not found" )
  {
    while (!read.eof()) // reads until the end of the file. 
    {   
      splitOnSpace(sc.line,sc.before,sc.after);
      getline(read,sc.line);
      string one;
      string astro;
        if (spacescount(sc.after)==spacescount(previous)-1)  
        { 
            for (int g =0; g < spaces + 1; g++)
            {
              one = first(previous,g,'/');
              astro = removeslash(one);  
              astro==sc.after && theword(sound)!=sc.before && previous!=sc.after && digit(sc.before)==false? sc.newline+=sc.before+sc.space():sc.newline;     
            }   
        }
            i++; // Continously runs the whole program. 
    }  // connects the while loop
        return sc.newline;
        read.close();  // closes file.
  }
    return "Not found";
}
int main()
{   
    string flowers;  // what is being inputted from the main. 
    cin >> flowers;
    cout << "Pronounciation:" << findbefore(flowers) << endl;
    cout << "Identical:" << findafter(flowers) << endl;

    cout << "Remove Phoneme :" << lastonebaby(flowers) << endl;
    cout << "Add Phoneme :" << onemore(flowers) << endl;
    cout << "Replace Phoneme :" << samepro(flowers) << endl;
}