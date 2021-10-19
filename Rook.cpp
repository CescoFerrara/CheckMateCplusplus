
#include "Rook.h"

namespace Chess
{
  bool Rook::legal_move_shape(std::pair<char, char> start, std::pair<char, char> end) const{
    
    char startCol = start.first;
    char startRow = start.second;
    char endCol = end.first;
    char endRow = end.second;
    
    //checking if it didn't move
    if(startCol == endCol && startRow == endRow) {
      return false;
    }
    
    //Making sure its within the board
    if (startCol == endCol || startRow == endRow) {
      return true;
    }
    
    return false;
  }
}
