#include "Igo.h"
int main()
{
        PieceBoard b("A", "B");
        b.SetPiece(Piece(WHITE, 10, 11));
        b.SetPiece(Piece(BLACK, 11, 11));
        b.SetPiece(Piece(WHITE, 10, 10));
        b.SetPiece(Piece(BLACK, 11, 10));

        return 0;
}
