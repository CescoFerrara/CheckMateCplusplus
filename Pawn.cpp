
#include "Pawn.h"

namespace Chess
{
  bool Pawn::legal_move_shape(std::pair<char, char> start, std::pair<char, char> end) const{
    char startCol = start.first;
    char startRow = start.second;
    char endCol = end.first;
    char endRow = end.second;
    
    //checks if move is vert
    if(startCol != endCol) {
      return false;
    }
    
    //black and white piece separate because pawn can only move toward other side of board
    
    if(is_white()) {
      if(endRow - startRow == 1) {
	return true;
      }
      if(endRow - startRow == 2 && startRow == '2') { //first move only
	return true;
      }
      
    }
    
    else { //black piece
      if(endRow - startRow == -1) {
	return true;
      }
      if(endRow - startRow == -2 && startRow == '7') { //first move only
	return true;
      }
    }
    
    return false;
  }
  
  
  //I believe the Pawn (and maybe Mystery) is the only one we have to implement this function for
  bool Pawn::legal_capture_shape(std::pair<char, char> start, std::pair<char, char> end) const{
    char startCol = start.first; //column specified before row in format A1 - H8
    char startRow = start.second;
    char endCol = end.first;
    char endRow = end.second;
    //black and white piece seperate because pawn can only move towards other side of board
    if (is_white()) {//white piece
      if (startRow + 1 == endRow){ //checks that move is 1 space towards other end
	if (startCol + 1 == endCol || startCol - 1 == endCol) { //checks that move is diagonal
	  return true;
	}
      }
    }
    else { //black piece
      if (startRow - 1 == endRow){ //checks that move is 1 space towards other end
	if (startCol + 1 == endCol || startCol - 1 == endCol) { //checks that move is diagonal
	  return true;
	}
      }
    }
    return false;
  }
}
