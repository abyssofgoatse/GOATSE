
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>

char sanitize_char( char ch ) {
  if( ('A' <= ch && ch <= 'Z') ||
      ('a' <= ch && ch <= 'z') ||
      ('0' <= ch && ch <= '9') ) {
    return ch;
  }
  return '_';
}

std::string sanitize( std::string s ) {
  if( s.length() == 0 ) {
    return "data";
  }

  std::transform( s.begin(), s.end(), s.begin(), sanitize_char );
  if( '0' <= s[0] && s[0] <= '9' ) {
    s = "_" + s;
  }

  return s;
}

void include_bin( std::istream& in, std::ostream& out, std::string name ) {
  int b = 0, count = 0;
  name = sanitize(name);

  out << "unsigned char " << name << "[] = {\n  ";

  while( (b = in.get()) != std::istream::traits_type::eof() ) {
    std::stringstream stream;
    stream << std::setfill('0') << std::setw(2) << std::hex << b;
    if( count > 0 ) {
      if( count%12 == 0 ) {
        out << ",\n  ";
      } else {
        out << ", ";
      }
    }
    out << "0x" << stream.str();
    count++;
  }

  out << "\n};\nunsigned int " << name << "_len = " << count << ";\n";
  out << std::flush;
}

int main( int argc, char* argv[] ) {

  if( argc < 1 || argc > 3 ) {
    std::cerr << "Usage: include-bin [infile [outfile]]" << argc << std::endl;
    return 1;
  }

  if( argc > 1 ) {
    std::ifstream fin( argv[1], std::ios_base::binary );
    if( argc > 2 ) {
      std::ofstream fout( argv[2] );
      include_bin( fin, fout, std::string(argv[1]) );
      fout.close();
    } else {
      include_bin( fin, std::cout, std::string(argv[1]) );
    }
    fin.close();
  } else {
    include_bin( std::cin, std::cout, "data" );
  }

  return 0;
}
