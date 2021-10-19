
#include "Queen.h"
namespace Chess
{
  bool Queen::legal_move_shape(std::pair<char, char> start, std::pair<char, char> end) const{
    char startCol = start.first;
    char startRow = start.second;
    char endCol = end.first;
    char endRow = end.second;
    char colMovement;
    char rowMovement;
    
    
    //checking if its standing still
    if(endCol == startCol && endRow == startRow) {
      return false;
    }
    
    
    //check vert/horizontal move
    if(startCol == endCol || startRow == endRow) {
      return true;
    }
    
    //check diagonal move
    if(endCol > startCol) {
      colMovement = endCol - startCol;
    }
    else {
      colMovement = startCol - endCol;
    }
    if(endRow > startRow) {
      rowMovement = endRow - startRow;
    }
    else {
      rowMovement = startRow - endRow;
    }
    
    //if they the same that means diagonal move occurred
    if(rowMovement == colMovement) {
      return true;
    }
    return false;
  }
}
