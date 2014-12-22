/**
 * ansi.cc
 *  Erik Ginter
 *
 * Date of Last Revision:
 *  December 22nd, 2014
 *
 * Contains some infrastructure for printing to ANSI-color-escape compliant terminals.
 *
 * Changes:
 *  Dec. 22, 2014:
 *    - Removed calls to to_string () from ansiEscapeCode ().
 *        This function is guarded on my MinGW g++ install, and can't be used.
 *        We didn't really need it anyway, it was mostly there for correctness.
 *
 * NOTES:
 *  This will not work in the default Windows terminal.
 *  You'll see something akin to "?[0;0;41m" when running in cmd.exe.
 */
#include <cstdlib>
// using EXIT_SUCCESS

#include <iostream>
using std :: cout;
using std :: endl;

#include <sstream>
using std :: stringstream;

#include <string>
using std :: string;

enum class
TextAttribute
{
  ALL_OFF          = 0,
  BOLD_ON          = 1,
  UNDERSCORE       = 4,
  BLINK_ON         = 5,
  REVERSE_VIDEO_ON = 7,
  CONCEALED_ON     = 8
};

enum class
ForegroundColor
{
  BLACK   = 30,
  RED     = 31,
  GREEN   = 32,
  YELLOW  = 33,
  BLUE    = 34,
  MAGENTA = 35,
  CYAN    = 36,
  WHITE   = 37
};

enum class
BackgroundColor
{
  BLACK   = 40,
  RED     = 41,
  GREEN   = 42,
  YELLOW  = 43,
  BLUE    = 44,
  MAGENTA = 45,
  CYAN    = 46,
  WHITE   = 47
};

string
ansiEscapeCode ( const TextAttribute attr, const ForegroundColor frg, const BackgroundColor bkg )
{
  stringstream stream;
  {
    stream << static_cast < char > ( 27 );
    stream << '[';
    stream << ( static_cast < int > ( attr ) );
    stream << ';';
    stream << ( static_cast < int > ( attr ) );
    stream << ';';
    stream << ( static_cast < int > ( bkg ) );
    stream << 'm';
  }
  return stream.str ();
}

int
main ( int argc, char* args[] )
{
  cout << ansiEscapeCode ( TextAttribute :: ALL_OFF, ForegroundColor :: BLACK, BackgroundColor :: RED );
  cout << "Hello, world!";
  cout << ansiEscapeCode ( TextAttribute :: ALL_OFF, ForegroundColor :: WHITE, BackgroundColor :: BLACK );
  cout << endl;
  return EXIT_SUCCESS;
}
