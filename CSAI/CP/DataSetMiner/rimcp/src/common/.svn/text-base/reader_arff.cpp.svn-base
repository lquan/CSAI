/*
 *  Main authors:
 *      Siegfried Nijssen <siegfried.nijssen@cs.kuleuven.be>
 *
 *  Revision information:
 *
 *  This file is part of Fim_cp, Frequent Itemset Mining using
 *  Constraint Programming, and uses Gecode.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining
 *  a copy of this software and associated documentation files (the
 *  "Software"), to deal in the Software without restriction, including
 *  without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to
 *  permit persons to whom the Software is furnished to do so, subject to
 *  the following conditions:
 *
 *  The above copyright notice and this permission notice shall be
 *  included in all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 *  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 *  LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 *  OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 *  WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */
#ifndef __FIMCP_COMMON_READERARFF__
#define __FIMCP_COMMON_READERARFF__

#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <algorithm>
#include <string>
#include <stdlib.h>

using namespace std;

template <class Type>
class Reader_Arff {
  public:
    vector <vector<bool> > data;
    vector <Type> labels;
    Reader_Arff () { }
    ~Reader_Arff () { }
    void add ( vector<string> row );
    void read ( string filename );
};


template <class Type>
void Reader_Arff<Type>::add ( vector<string> row ) {
  vector<bool> newrow;
  int pos = 0;
  vector<string>::iterator i, j = row.begin ();
  ++j;
  for ( i = row.begin (); j != row.end (); ++i, ++pos, ++j ) 
    newrow.push_back ( atoi ( i->c_str () ) );
  data.push_back ( newrow );
  labels.push_back ( atof ( i->c_str() ) );
}

bool is_space_arff ( char pos ) {
  return pos == ' ' || pos == '\n' || pos == '\t' || pos == ',' || pos == '\r';
}

char *read_spaces ( char *pos ) {
  while ( is_space_arff ( *pos ) )
    if ( *pos == 0 )
      return pos;
    else
      ++pos;
  return pos;
}

char *get_attribute ( char *&pos ) {
  static char attribute[1000]; 
  char *pos2 = attribute;
  pos = read_spaces ( pos );
  if ( *pos == 0 )
    return NULL;
  while ( !is_space_arff ( *pos ) && *pos != 0 ) {
    *pos2 = *pos;
    ++pos2;
    ++pos;
  }
  *pos2 = 0;
  return attribute;
}

bool label_compare ( pair<int,float> a, pair<int,float> b ) {
  return a.second < b.second;
}

template <class Type>
void Reader_Arff<Type>::read ( string filename ) {
  ifstream input ( filename.c_str () );
  char line[10000];
  input.getline ( line, 10000 );
  while ( !input.eof () ) {
    char *pos = line;
    pos = read_spaces ( pos );
    if ( *pos != '@' && *pos != '%' && *pos != 0 ) {
      vector<string> row;
      while ( *pos != 0 ) {
        char *p = get_attribute ( pos );
        if ( p )
          row.push_back ( p );
      }
      add ( row );
    }
    input.getline ( line, 10000 );
  }
  
  vector<pair<int,float> > v;
  // sort the examples in increasing order of label
  for ( unsigned i = 0; i < labels.size (); ++i )
    v.push_back ( make_pair ( i, labels[i] ) );
  
  sort ( v.begin (), v.end (), label_compare );
  
  vector<vector<bool> > data2; // sorted copy of the data
  for ( unsigned i = 0; i < v.size (); ++i ) 
    data2.push_back ( data[v[i].first] );
  
  data.swap ( data2 ); // make new data true data
  sort ( labels.begin (), labels.end () ); // update corresponding labels
}

#endif
