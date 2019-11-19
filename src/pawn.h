#ifndef pawn_H
#define pawn_H


class pawn
{
    private:
		int XPos;
		int YPos;
		bool HasOrb;

    public:
        pawn();
		virtual ~pawn();

		virtual bool setPosition(int x, int y);
		virtual int getXPos(){return XPos;}
		virtual int getYPos(){return YPos;}
		
		virtual bool hasOrb(){return HasOrb;}
		virtual void toggleOrb();
};
#endif
