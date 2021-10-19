
#include "King.h"

namespace Chess
{
  bool King::legal_move_shape(std::pair<char, char> start, std::pair<char, char> end) const{
    char startCol = start.first;
    char startRow = start.second;
    char endCol = end.first;
    char endRow = end.second;
    char testCol;
    char testRow;
    
    
    //Makes sure its actually moving
    if(startCol == endCol && startRow == endRow) {
      return false;
    }

    //Checks a 3x3 square around the King and makes sure the move is within the board
    for(int i = 0; i < 3; i++) {
      testCol = startCol + (i-1);
      for(int j = 0; j < 3; j++) {
	testRow = startRow + (j-1);
	if(testCol == endCol && testRow == endRow) {
	  return true;
	}
      }
    }
    
    return false;
    
    
  }
}
