
#include "Bishop.h"

namespace Chess
{
  bool Bishop::legal_move_shape(std::pair<char, char> start, std::pair<char, char> end) const{
    char startCol = start.first; //column specifiend before row in format A1 - H8
    char startRow = start.second;
    char endCol = end.first;
    char endRow = end.second;
    char colMovement;
    char rowMovement;
    //Not sure if u need to check start but pretty sure it should be good
    if(endCol == startCol && endRow == startRow) {
      return false;
    }
    
    //Making sure the ending is within the board
    if (endCol > startCol) {
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
    
    //Check to see if rowMovement and colMovement are the same signifying a diagonal movement
    if(rowMovement == colMovement) {
      return true;
    }
    
    return false;
  }
}
