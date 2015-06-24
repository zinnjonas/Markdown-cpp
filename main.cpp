#include <iostream>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

#include "test.h"
#include "file.h"
#include "lib/libmarkdown.h"
#include "lib/htmlParser.h"
#include "lib/latexParser.h"

void show_help(char* s)
{
  cout << "Usage:    " << s << " -h -l level -o file file" << endl;
  cout << "option:   " << "-h      show help information" << endl;
  cout << "          " << "-o file specify an output file" << endl;
  cout << "          " << "file the file to parse" << endl;
}

int main(int argc, char** argv)
{
  char tmp;
  string out_file;
  string in_file;
  int level = 0;
  while( (tmp=getopt(argc,argv,"ho:l:?"))!= -1)
  {
    switch(tmp)
    {
      case 'h':
        show_help(argv[0]);
        break;

      case 'o':
        out_file = optarg;
        break;

      case 'l':
        level = atoi(optarg);
        break;

      default:
        show_help(argv[0]);
        break;
    }
  }


  string content;

  if( argv[optind] == NULL)
  {
    string temp;
    while (getline(cin,temp))
    {
      content += temp + "\n";
    }
  }
  else
  {
    in_file = argv[optind];
    content = get_file_contents(in_file.c_str());
  }

  //HTMLParser* parser = new HTMLParser();
  LaTexParser* parser = new LaTexParser();
  parser->print_headers(true);
  parser->set_ground_level(level);
  string parsed = parse( content, parser);

  if( out_file.empty())
    cout << parsed << endl;
  else
    set_file_contents(out_file.c_str(),parsed);

  return 0;
}
