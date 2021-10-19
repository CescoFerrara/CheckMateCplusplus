
#include "Knight.h"

namespace Chess
{
  bool Knight::legal_move_shape(std::pair<char, char> start, std::pair<char, char> end) const{
    
    char startCol = start.first;
    char startRow = start.second;
    char endCol = end.first;
    char endRow = end.second;
    char testCol;
    char testRow;
    
    //Make sure piece moves
    if(endCol == startCol && endRow == startRow) {
      return false;
    }
    
    //Not entirely sure if this next part is right
    for(int i = -1; i <= 1; i+=2) { //each for loop should run twice, checking all combinations of +/- 1/2 for Rows and Cols
      for(int j = -1; j <= 1; j+=2) {
	testCol = startCol + i*1;
	testRow = startRow + j*2;
	if(testCol == endCol && testRow == endRow) {
	  return true;
	}
	testCol = startCol + i*2;
	testRow = startRow + j*1;
	if(testCol == endCol && testRow == endRow) {
	  return true;
	}
      }
    }
    return false;
  }
}
