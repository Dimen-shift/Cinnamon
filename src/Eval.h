#ifndef EVAL_H_
#define EVAL_H_

#include "GenMoves.h"
using namespace _board;
using namespace _eval;

class Eval:public GenMoves {
public:
  Eval (  );
  virtual ~ Eval (  );
  int getScore ( const int side, const int alpha, const int beta );

   template < int side > int lazyEval (  ) {
    return lazyEvalSide < side > (  ) - lazyEvalSide < side ^ 1 > (  );
} protected:
#ifdef DEBUG_MODE
  int LazyEvalCuts;
#endif

private:

//    static const int ATTACK_CENTER = 5;
  //static const int ATTACK_F7_F2 = 11;
  static const int ATTACK_KING = 30;
  //static const int BACKWARD_OPEN_PAWN = 4;
  static const int BACKWARD_PAWN = 2;
  static const int BISHOP_ON_QUEEN = 2;
  static const int BISHOP_TRAPPED = 5;
  static const int NO_PAWNS = 15;
  static const int BONUS2BISHOP = 18;
  static const int CONNECTED_ROOKS = 7;
  static const int DOUBLED_ISOLATED_PAWNS = 14;
  static const int DOUBLED_PAWNS = 5;
  static const int END_OPENING = 6;
  static const int ENEMIES_PAWNS_ALL = 8;
  static const int ENEMY_NEAR_KING = 2;
  static const int FRIEND_NEAR_KING = 1;
  static const int HALF_OPEN_FILE_Q = 3;
  static const int KNIGHT_TRAPPED = 5;


//    static const int NEAR_xKING = 2;
  static const int OPEN_FILE = 10;
  static const int OPEN_FILE_Q = 3;
  static const int PAWN_7H = 32;
  static const int PAWN_CENTER = 15;
  static const int PAWN_IN_RACE = 114;
  static const int PAWN_ISOLATED = 3;
  static const int PAWN_NEAR_KING = 2;
  static const int PAWN_BLOCKED = 5;
  //static const int PINNED_PIECE = 20;//TODO
  static const int ROOK_7TH_RANK = 10;
  static const int ROOK_BLOCKED = 13;
  static const int ROOK_TRAPPED = 6;
  static const int UNDEVELOPED = 4;
  static const int UNPROTECTED_PAWNS = 5;
#ifdef DEBUG_MODE
  int evaluationCount[2];
#endif
  void openColumn ( int side );
  template < int side, _Tstatus status > int evaluatePawn (  );
  template < int side, _Tstatus status > int evaluateBishop ( const u64, u64, u64 );
  template < _Tstatus status > int evaluateQueen ( int side, u64 enemies, u64 friends );
  template < int side, _Tstatus status > int evaluateKnight ( const u64, const u64 );
  template < int side, _Tstatus status > int evaluateRook ( const u64, u64 enemies, u64 friends );
  template < _Tstatus status > int evaluateKing ( int side, u64 squares );

  template < int side > int lazyEvalSide (  ) {
    return _bits::bitCount ( chessboard[PAWN_BLACK + side] ) * VALUEPAWN + _bits::bitCount ( chessboard[ROOK_BLACK + side] ) * VALUEROOK + _bits::bitCount ( chessboard[BISHOP_BLACK + side] ) * VALUEBISHOP + _bits::bitCount ( chessboard[KNIGHT_BLACK + side] ) * VALUEKNIGHT + _bits::bitCount ( chessboard[QUEEN_BLACK + side] ) * VALUEQUEEN;
  }
};
#endif
