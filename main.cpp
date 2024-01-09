#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <unordered_map>
using namespace std;

string numberify(int);
string stringify(string);
string wtf(string);

unordered_map<char, string> mapping;

int main(int argc, char *argv[]) {
  if (argc < 3) {
    cout << "usage: " << argv[0] << " <source> <output>" << endl;
    exit(1);
  }

  ifstream source;
  ofstream output;
  string line, code;
  source.open(argv[1]);
  output.open(argv[2]);
  while (getline(source, line)) {
    code.append(line);
  }
  string wtfed = wtf(code);
  output << wtfed;
  output.close();
  source.close();
  return 0;
}

string wtf(string code) {
  mapping['a'] = "(+{}+[])[" + numberify(1) + "]";
  mapping['b'] = "({}+[])[" + numberify(2) + "]";
  mapping['o'] = "({}+[])[" + numberify(1) + "]";
  mapping['e'] = "({}+[])[" + numberify(4) + "]";
  mapping['c'] = "({}+[])[" + numberify(5) + "]";
  mapping['t'] = "({}+[])[" + numberify(6) + "]";
  mapping[' '] = "({}+[])[" + numberify(7) + "]";
  mapping['f'] = "(![]+[])[" + numberify(0) + "]";
  mapping['s'] = "(![]+[])[" + numberify(3) + "]";
  mapping['r'] = "(!![]+[])[" + numberify(1) + "]";
  mapping['u'] = "(!![]+[])[" + numberify(2) + "]";
  mapping['i'] = "((+!![]/+[])+[])[" + numberify(3) + "]";
  mapping['n'] = "((+!![]/+[])+[])[" + numberify(4) + "]";
  mapping['S'] =
      "([]+([]+[])[" + stringify("constructor") + "])[" + numberify(9) + "]";
  mapping['g'] =
      "([]+([]+[])[" + stringify("constructor") + "])[" + numberify(14) + "]";
  mapping['p'] =
      "([]+(/-/)[" + stringify("constructor") + "])[" + numberify(14) + "]";
  mapping['\\'] = "(/\\\\/+[])[" + numberify(1) + "]";
  mapping['d'] = "(" + numberify(13) + ")[" + stringify("toString") + "](" +
                 numberify(14) + ")";
  mapping['h'] = "(" + numberify(17) + ")[" + stringify("toString") + "](" +
                 numberify(18) + ")";
  mapping['m'] = "(" + numberify(22) + ")[" + stringify("toString") + "](" +
                 numberify(23) + ")";
  mapping['C'] = "((()=>{})[" + stringify("constructor") + "](" +
                 stringify("return escape") + ")()(" + mapping['\\'] + "))[" +
                 numberify(2) + "]";
  return "(()=>{})[" + stringify("constructor") + "](" + stringify(code) +
         ")()";
  ;
}

string stringify(string s) {
  string str;

  for (char &c : s) {
    unordered_map<char, basic_string<char>>::iterator search = mapping.find(c);
    if (search != mapping.end()) {
      str.append(mapping[c]);
    } else {
      str.append("([]+[])[" + stringify("constructor") + "][" +
                 stringify("fromCharCode") + "](" + numberify(c) + ")");
    }
    str.append("+");
  }
  return str.substr(0, str.length() - 1);
}

string numberify(int n) {
  if (n == 0) {
    return "+[]";
  }
  string ret = "+!![]";
  for (int i = 1; i < n; i++) {
    ret.append(" + +!![]");
  }
  return ret;
}
