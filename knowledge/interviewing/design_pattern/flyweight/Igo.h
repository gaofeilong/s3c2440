#ifndef _IGO_H_
#define _IGO_H_
#include <stdio.h>
#include <string>
#include <vector>

enum PieceColor { WHITE, BLACK };
struct PiecePos { 
        PiecePos(int x, int y): x(x), y(y) {}
        int x; 
        int y; 
};
struct Piece { 
        Piece(const enum PieceColor &c, int x, int y): 
                m_Color(c), m_Pos(x, y) {}
        PieceColor m_Color; 
        PiecePos m_Pos; 
};


class PieceBoard {
public:
        PieceBoard(const std::string &black, const std::string white):
                m_BlackName(black), m_WhiteName(white) 
        {
                m_BlackPiece = NULL;
                m_WhitePiece = NULL;
        }
        ~PieceBoard() { delete m_WhitePiece; delete m_BlackPiece; }

public:
        void SetPiece(Piece p)
        {
                if (p.m_Color == WHITE) {
                        if (!m_WhitePiece) {
                                m_WhitePiece = new Piece(p); 
                        }
                        m_WhitePos.push_back(p.m_Pos);
                        printf("write on pos: x(%d), y(%d)\n", 
                                                p.m_Pos.x, p.m_Pos.y);
                } else {
                        if (!m_BlackPiece) {
                                m_BlackPiece = new Piece(p); 
                        }
                        m_BlackPos.push_back(p.m_Pos);
                        printf("black on pos: x(%d), y(%d)\n", 
                                                p.m_Pos.x, p.m_Pos.y);
                }
                return;
        }
private:
        Piece *m_WhitePiece;
        Piece *m_BlackPiece;
        std::string m_WhiteName;
        std::string m_BlackName;
        std::vector<PiecePos> m_WhitePos;
        std::vector<PiecePos> m_BlackPos;
};

#endif  //_IGO_H_
