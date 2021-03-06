#include "defs.h"

// Returns true if the given square is attacked by any piece of the given side.
inline bool squareAttacked(const unsigned sq, const unsigned side,
                           const S_BOARD *pos) {

  static const int RkDir[4] = {-1, -10, 1, 10};
  static const int BiDir[4] = {-9, -11, 11, 9};
  static const int KnDir[8] = {-8, -21, 8, 21, 19, -19, 12, -12};
  static const int KiDir[8] = {-1, -10, 1, 10, -9, -11, 11, 9};

  unsigned piece, t_sq;

  const unsigned king = side == WHITE ? wK : bK;   // wK + side * 6;
  const unsigned knight = side == WHITE ? wN : bN; // wN + side * 6;

  ASSERT(squareOnBoard(sq));
  ASSERT(sideValid(side));
  ASSERT(checkBoard(pos));

  for (int i = 0; i < 8; i++) {
    if (pos->pieces[sq + KiDir[i]] == king ||
        pos->pieces[sq + KnDir[i]] == knight) {
      return true;
    }
  }

  if (side == WHITE) {
    if (pos->pieces[sq - 11] == wP || pos->pieces[sq - 9] == wP) {
      return true;
    }
  } else {
    if (pos->pieces[sq + 11] == bP || pos->pieces[sq + 9] == bP) {
      return true;
    }
  }

  for (unsigned i = 0; i < 4; i++) {
    t_sq = sq + RkDir[i];
    while (squareOnBoard(t_sq)) {
      piece = pos->pieces[t_sq];
      if (piece != EMPTY) {
        if (pieceCol[piece] == side && IsRQ(piece)) {
          return true;
        }
        break;
      }
      t_sq += RkDir[i];
    }

    t_sq = sq + BiDir[i];
    while (squareOnBoard(t_sq)) {
      piece = pos->pieces[t_sq];
      if (piece != EMPTY) {
        if (pieceCol[piece] == side && IsBQ(piece)) {
          return true;
        }
        break;
      }
      t_sq += BiDir[i];
    }
  }

  return false;
}
