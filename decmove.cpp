// DecMove.cpp
//

#include "DECOR.H"
#include "MISC.H"
#include "DECMOVE.h"

// Mouvement pour secouer un arbre
// (synchrone avec ACTION_PIOCHE).
static short table_move1[] =
{
	9*4,	// nb
	0,0, 0,0, 0,0, 0,0,
	-2,0, +2,0, -1,0, +1,0,
	0,0, 0,0, 0,0, 0,0,
	-2,0, +2,0, -1,0, +1,0,
	0,0, 0,0, 0,0, 0,0,
	0,0, 0,0, 0,0, 0,0,
	-2,0, +2,0, -1,0, +1,0,
	0,0, 0,0, 0,0, 0,0,
	-2,0, +2,0, -1,0, +1,0,
};

// Mouvement pour faire sauter un objet (est) sur blupi
// (synchrone avec ACTION_TAKE).
static short table_move2[] =
{
	9+19,		// nb
	  0,0, 0,0,
	  0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0,
	  0,-10,
	  0,-20,
	  0,-30,
	  0,-40,
	 -1,-50,
	 -3,-60,
	 -7,-70,
	-15,-80,
	-22,-70,
	-30,-56,
	-30,-56,
	-30,-56,
	-30,-56,
	-30,-56,
	-30,-56,
	-30,-56,
	-30,-56,
	-30,-56,
	-30,-56,
};

// Mouvement pour faire sauter un objet (sud) sur blupi
// (synchrone avec ACTION_TAKE2).
static short table_move3[] =
{
	9+19,		// nb
	  0,0, 0,0,
	  0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0,
	  0,-10,
	  0,-20,
	  0,-30,
	  0,-40,
	  1,-50,
	  3,-60,
	  7,-70,
	 15,-80,
	 22,-70,
	 30,-56,
	 30,-56,
	 30,-56,
	 30,-56,
	 30,-56,
	 30,-56,
	 30,-56,
	 30,-56,
	 30,-56,
	 30,-56,
};

// Mouvement pour d�poser un objet (est) sur blupi
// (synchrone avec ACTION_DEPOSE).
static short table_move4[] =
{
	10,		// nb
	-30,-60,
	-22,-70,
	-15,-80,
	 -7,-70,
	 -3,-60,
	 -1,-50,
	  0,-40,
	  0,-30,
	  0,-20,
	  0,-10,
};

// Mouvement pour d�poser un objet (sud) sur blupi
// (synchrone avec ACTION_DEPOSE2).
static short table_move5[] =
{
	10,		// nb
	 30,-60,
	 22,-70,
	 15,-80,
	  7,-70,
	  3,-60,
	  1,-50,
	  0,-40,
	  0,-30,
	  0,-20,
	  0,-10,
};

// Mouvement pour pousser un pont vers l'est.
static short table_move6[] =
{
	40,		// nb
	+2,+1,
	+4,+2,
	+6,+3,
	+8,+4,
	+10,+5,
	+12,+6,
	+14,+7,
	+16,+8,
	+18,+9,
	+20,+10,
	+22,+11,
	+24,+12,
	+26,+13,
	+28,+14,
	+30,+15,
	+32,+16,
	+34,+17,
	+36,+18,
	+38,+19,
	+40,+20,
	+42,+21,
	+44,+22,
	+46,+23,
	+48,+24,
	+50,+25,
	+52,+26,
	+54,+27,
	+56,+28,
	+58,+29,
	+60,+30,
	+60,+30,
	+60,+30,
	+60,+30,
	+60,+30,
	+60,+30,
	+60,+30,
	+60,+30,
	+60,+30,
	+60,+30,
	+60,+30,
};

// Mouvement pour pousser un pont vers l'ouest.
static short table_move7[] =
{
	40,		// nb
	-2,-1,
	-4,-2,
	-6,-3,
	-8,-4,
	-10,-5,
	-12,-6,
	-14,-7,
	-16,-8,
	-18,-9,
	-20,-10,
	-22,-11,
	-24,-12,
	-26,-13,
	-28,-14,
	-30,-15,
	-32,-16,
	-34,-17,
	-36,-18,
	-38,-19,
	-40,-20,
	-42,-21,
	-44,-22,
	-46,-23,
	-48,-24,
	-50,-25,
	-52,-26,
	-54,-27,
	-56,-28,
	-58,-29,
	-60,-30,
	-60,-30,
	-60,-30,
	-60,-30,
	-60,-30,
	-60,-30,
	-60,-30,
	-60,-30,
	-60,-30,
	-60,-30,
	-60,-30,
};

// Mouvement pour pousser un pont vers le sud.
static short table_move8[] =
{
	40,		// nb
	-2,+1,
	-4,+2,
	-6,+3,
	-8,+4,
	-10,+5,
	-12,+6,
	-14,+7,
	-16,+8,
	-18,+9,
	-20,+10,
	-22,+11,
	-24,+12,
	-26,+13,
	-28,+14,
	-30,+15,
	-32,+16,
	-34,+17,
	-36,+18,
	-38,+19,
	-40,+20,
	-42,+21,
	-44,+22,
	-46,+23,
	-48,+24,
	-50,+25,
	-52,+26,
	-54,+27,
	-56,+28,
	-58,+29,
	-60,+30,
	-60,+30,
	-60,+30,
	-60,+30,
	-60,+30,
	-60,+30,
	-60,+30,
	-60,+30,
	-60,+30,
	-60,+30,
	-60,+30,
};

// Mouvement pour pousser un pont vers le nord.
static short table_move9[] =
{
	40,		// nb
	+2,-1,
	+4,-2,
	+6,-3,
	+8,-4,
	+10,-5,
	+12,-6,
	+14,-7,
	+16,-8,
	+18,-9,
	+20,-10,
	+22,-11,
	+24,-12,
	+26,-13,
	+28,-14,
	+30,-15,
	+32,-16,
	+34,-17,
	+36,-18,
	+38,-19,
	+40,-20,
	+42,-21,
	+44,-22,
	+46,-23,
	+48,-24,
	+50,-25,
	+52,-26,
	+54,-27,
	+56,-28,
	+58,-29,
	+60,-30,
	+60,-30,
	+60,-30,
	+60,-30,
	+60,-30,
	+60,-30,
	+60,-30,
	+60,-30,
	+60,-30,
	+60,-30,
	+60,-30,
};

// Mouvement pour secouer le laboratoire.
static short table_move10[] =
{
	16*4,	// nb
	-2,0, +2,0, -2,0, +2,0,
	-2,0, +2,0, -2,0, +2,0,
	-2,0, +2,0, -2,0, +2,0,
	-2,0, +2,0, -2,0, +2,0,
	-1,0, +1,0, -1,0, +1,0,
	-1,0, +1,0, -1,0, +1,0,
	-1,0, +1,0, -1,0, +1,0,
	0,0, 0,0, 0,0, 0,0,
	0,0, 0,0, 0,0, 0,0,
	-2,0, +2,0, -2,0, +2,0,
	-2,0, +2,0, -2,0, +2,0,
	-2,0, +2,0, -2,0, +2,0,
	-2,0, +2,0, -2,0, +2,0,
	-1,0, +1,0, -1,0, +1,0,
	-1,0, +1,0, -1,0, +1,0,
	-1,0, +1,0, -1,0, +1,0,
};

// Mouvement pour secouer la mine.
static short table_move11[] =
{
	20*4,	// nb
	0,-1, 0,+1, 0,-1, 0,+1, 
	0,-1, 0,+1, 0,-1, 0,+1, 
	0,-1, 0,+1, 0,-1, 0,+1, 
	0,0, 0,0, 0,0, 0,0,
	0,0, 0,0, 0,0, 0,0,
	0,-1, 0,+1, 0,-1, 0,+1, 
	0,0, 0,0, 0,0, 0,0,
	0,0, 0,0, 0,0, 0,0,
	0,-1, 0,+1, 0,-1, 0,+1, 
	0,-1, 0,+1, 0,-1, 0,+1, 
	0,-1, 0,+1, 0,-1, 0,+1, 
	0,-1, 0,+1, 0,-1, 0,+1, 
	0,0, 0,0, 0,0, 0,0,
	0,0, 0,0, 0,0, 0,0,
	0,-1, 0,+1, 0,-1, 0,+1, 
	0,-1, 0,+1, 0,-1, 0,+1, 
	0,0, 0,0, 0,0, 0,0,
	0,0, 0,0, 0,0, 0,0,
	0,-1, 0,+1, 0,-1, 0,+1, 
	0,-1, 0,+1, 0,-1, 0,+1, 
};

// Mouvement pour secouer l'usine.
static short table_move12[] =
{
	20*4,	// nb
	-1,0, +1,0, -1,0, +1,0,
	0,-1, 0,+1, 0,-1, 0,+1, 
	-1,0, +1,0, -1,0, +1,0,
	0,0, 0,0, 0,0, 0,0,
	0,0, 0,0, 0,0, 0,0,
	-2,0, +2,0, 0,+1, 0,+1,
	-2,0, +2,0, 0,+1, 0,+1,
	-1,0, +1,0, -1,0, +1,0,
	-2,0, +2,0, 0,+1, 0,+1,
	0,0, 0,0, 0,0, 0,0,
	-1,0, +1,0, -1,0, +1,0,
	-1,0, +1,0, -1,0, +1,0,
	0,-1, 0,+1, 0,-2, 0,+2, 
	-1,0, +1,0, -1,0, +1,0,
	0,0, 0,0, 0,0, 0,0,
	-1,0, +1,0, -1,0, +1,0,
	-2,0, +2,0, 0,+1, 0,+1,
	-2,0, +2,0, 0,+1, 0,+1,
	0,0, 0,0, 0,0, 0,0,
	-2,0, +2,0, 0,+1, 0,+1,
};

short* GetListMoves(int rank)
{
	if ( rank ==  1 )  return table_move1;
	if ( rank ==  2 )  return table_move2;
	if ( rank ==  3 )  return table_move3;
	if ( rank ==  4 )  return table_move4;
	if ( rank ==  5 )  return table_move5;
	if ( rank ==  6 )  return table_move6;
	if ( rank ==  7 )  return table_move7;
	if ( rank ==  8 )  return table_move8;
	if ( rank ==  9 )  return table_move9;
	if ( rank == 10 )  return table_move10;
	if ( rank == 11 )  return table_move11;
	if ( rank == 12 )  return table_move12;

	return NULL;
}


// Petites flammes.
static short table_icon1[] =
{
	8*3,
	49,50,51,52,50,49,51,52,
	49,52,51,50,49,52,50,49,
	52,51,50,49,51,52,49,51,
};

// Grandes flammes.
static short table_icon2[] =
{
	8*3,
	45,46,47,48,46,45,48,47,
	46,45,48,47,45,48,47,48,
	46,45,48,47,45,48,47,46,
};

// Eclairs de la dalle nurserie.
static short table_icon3[] =
{
	4,		// nb
	53,54,55,56,
};

// Eclairs n-s entre les tours.
static short table_icon4[] =
{
	8*4,		// nb
	74,76,78,76,74,78,74,76,
	78,76,74,76,74,76,78,76,
	74,78,76,74,76,78,74,76,
	78,74,76,78,74,76,74,78,
};

// Eclairs e-o entre les tours.
static short table_icon5[] =
{
	8*4,		// nb
	75,77,75,79,75,77,79,75,
	79,77,75,77,75,79,75,79,
	75,77,79,75,75,77,79,75,
	79,75,77,79,75,79,75,79,
};

// Explosion de la dynamite.
static short table_icon6[] =
{
	7+30,	// nb
	91,90,89,88,89,90,91,
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
};

// M�che de la dynamite.
static short table_icon7[] =
{
	12*4,	// nb
	86,87,86,87,86,87,86,87,86,87,86,87,
	86,87,86,87,86,87,86,87,86,87,86,87,
	86,87,86,87,86,87,86,87,86,87,86,87,
	86,87,86,87,86,87,86,87,86,87,86,87,
};

// Rayons de  l'�lectrocuteur.
static short table_icon8[] =
{
	10*10,		// nb
	75,-1,-1,74,-1,75,-1,74,75,-1,
	74,73,-1,75,74,73,72,74,-1,72,
	73,74,72,73,75,73,72,73,74,72,
	75,72,73,72,-1,74,73,72,75,74,
	-1,73,74,75,-1,74,75,-1,75,-1,
	74,75,-1,-1,74,-1,-1,-1,75,-1,
	-1,-1,-1,-1,-1,74,-1,-1,-1,75,
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,75,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1,-1,74,
};

// Blupi �cras�.
static short table_icon9[] =
{
	10*10,		// nb
	76,76,76,76,76,76,76,76,76,76,
	76,76,76,76,76,76,76,76,76,76,
	76,76,76,76,76,76,76,76,76,76,
	76,76,76,76,76,76,76,76,76,76,
	76,76,76,76,76,76,76,76,76,76,
	76,76,76,76,76,76,76,76,76,76,
	76,76,76,76,76,76,76,76,76,76,
	76,76,76,76,76,76,76,76,76,76,
	76,76,76,76,76,76,76,76,76,76,
	76,76,76,76,76,76,76,76,76,76,
};

// Blupi malade �cras�.
static short table_icon10[] =
{
	10*10,		// nb
	77,77,77,77,77,77,77,77,77,77,
	77,77,77,77,77,77,77,77,77,77,
	77,77,77,77,77,77,77,77,77,77,
	77,77,77,77,77,77,77,77,77,77,
	77,77,77,77,77,77,77,77,77,77,
	77,77,77,77,77,77,77,77,77,77,
	77,77,77,77,77,77,77,77,77,77,
	77,77,77,77,77,77,77,77,77,77,
	77,77,77,77,77,77,77,77,77,77,
	77,77,77,77,77,77,77,77,77,77,
};

// Eclairs de la dalle t�l�porteur.
static short table_icon11[] =
{
	4,		// nb
	81,82,83,84,
};

short* GetListIcons(int rank)
{
	if ( rank ==  1 )  return table_icon1;
	if ( rank ==  2 )  return table_icon2;
	if ( rank ==  3 )  return table_icon3;
	if ( rank ==  4 )  return table_icon4;
	if ( rank ==  5 )  return table_icon5;
	if ( rank ==  6 )  return table_icon6;
	if ( rank ==  7 )  return table_icon7;
	if ( rank ==  8 )  return table_icon8;
	if ( rank ==  9 )  return table_icon9;
	if ( rank == 10 )  return table_icon10;
	if ( rank == 11 )  return table_icon11;

	return NULL;
}




// Supprime tous les d�cors anim�s.

void CDecor::MoveFlush()
{
	int		i, x, y;

	for ( i=0 ; i<MAXMOVE ; i++ )
	{
		m_move[i].bExist = false;
	}

	for ( x=0 ; x<MAXCELX/2 ; x++ )
	{
		for ( y=0 ; y<MAXCELY/2 ; y++ )
		{
			m_decor[x][y].rankMove = -1;
		}
	}
}

// Retourne la dur�e du feu.

int CDecor::MoveMaxFire()
{
	if ( m_skill >= 1 )  return (MAXFIRE/4)*3;
	return MAXFIRE;
}

// Initialise tous les mouvements perp�tuels du d�cor.

void CDecor::MoveFixInit()
{
	int		x, y;

	MoveFlush();

	for ( x=0 ; x<MAXCELX ; x+=2 )
	{
		for ( y=0 ; y<MAXCELY ; y+=2 )
		{
			// D�marre le feu.
			if ( m_decor[x/2][y/2].fire > 0 &&
				 m_decor[x/2][y/2].fire < MoveMaxFire() )
			{
				MoveStartFire(GetCel(x,y));
			}

			// D�marre les �clairs entre les tours.
			if ( m_decor[x/2][y/2].objectIcon == 10000 )  // �clair n-s
			{
				if ( MoveCreate(GetCel(x,y), -1, false, CHOBJECT,-1,
								-1,-1, 9999,1,0, true) )
				{
					MoveAddIcons(GetCel(x,y), 4, true);  // �clairs n-s
				}
			}

			if ( m_decor[x/2][y/2].objectIcon == 10001 )  // �clair e-o
			{
				if ( MoveCreate(GetCel(x,y), -1, false, CHOBJECT,-1,
								-1,-1, 9999,1,0, true) )
				{
					MoveAddIcons(GetCel(x,y), 5, true);  // �clairs e-o
				}
			}
		}
	}
}

// Cr�e un nouveau d�cor anim�.
// Si bMisc=true, on garde 10 mouvements en r�serve pour
// des actions importantes (bMisc=false).

bool CDecor::MoveCreate(POINT cel, int rankBlupi, bool bFloor,
						int channel, int icon,
						int maskChannel, int maskIcon,
						int total, int delai, int stepY,
						bool bMisc, bool bNotIfExist)
{
	int		rank, max;

	for ( rank=0 ; rank<MAXMOVE ; rank++ )
	{
		if ( m_move[rank].bExist &&
			 m_move[rank].cel.x == cel.x &&
			 m_move[rank].cel.y == cel.y )
		{
			if ( bNotIfExist )  return false;
			goto create;
		}
	}

	max = 0;
	for ( rank=0 ; rank<MAXMOVE ; rank++ )
	{
		if ( !m_move[rank].bExist )
		{
			if ( bMisc && max > MAXMOVE-10 )  return false;
			goto create;
		}
		max ++;
	}
	return false;

	create:
	m_move[rank].bExist      = true;
	m_move[rank].cel         = cel;
	m_move[rank].rankBlupi   = rankBlupi;
	m_move[rank].bFloor      = bFloor;
	m_move[rank].channel     = channel;
	m_move[rank].icon        = icon;
	m_move[rank].maskChannel = maskChannel;
	m_move[rank].maskIcon    = maskIcon;
	m_move[rank].total       = total;
	m_move[rank].delai       = delai;
	m_move[rank].stepY       = stepY;
	m_move[rank].cTotal      = 0;
	m_move[rank].cDelai      = 0;
	m_move[rank].rankMoves   = 0;
	m_move[rank].rankIcons   = 0;
	m_move[rank].phase       = 0;

	m_decor[cel.x/2][cel.y/2].rankMove = rank;
	return true;
}

// Ajoute un mouvement.

bool CDecor::MoveAddMoves(POINT cel, int rankMoves)
{
	int		rank;

	for ( rank=0 ; rank<MAXMOVE ; rank++ )
	{
		if ( m_move[rank].bExist &&
			 m_move[rank].cel.x == cel.x &&
			 m_move[rank].cel.y == cel.y )
		{
			m_move[rank].rankMoves = rankMoves;
			m_move[rank].phase  = 0;

			return true;
		}
	}

	return false;
}

// Ajoute un mouvement.

bool CDecor::MoveAddIcons(POINT cel, int rankIcons, bool bContinue)
{
	int		rank;

	for ( rank=0 ; rank<MAXMOVE ; rank++ )
	{
		if ( m_move[rank].bExist &&
			 m_move[rank].cel.x == cel.x &&
			 m_move[rank].cel.y == cel.y )
		{
			m_move[rank].rankIcons = rankIcons;
			if ( !bContinue )  m_move[rank].phase = 0;

			if ( rankIcons == 4 || rankIcons == 5 )  // �clairs entre tours ?
			{
				m_move[rank].cTotal = Random(0,10);
			}

			return true;
		}
	}

	return false;
}

// D�marre le feu sur une cellule.
// Retourne true si c'est possible.

bool CDecor::MoveStartFire(POINT cel)
{
	int		channel, icon;

	cel.x = (cel.x/2)*2;
	cel.y = (cel.y/2)*2;

	channel = m_decor[cel.x/2][cel.y/2].objectChannel;
	icon    = m_decor[cel.x/2][cel.y/2].objectIcon;

	if ( channel == CHOBJECT &&
		 ((icon >=   6 && icon <= 11) ||  // arbres ?
		  (icon >=  65 && icon <= 71) ||  // palissade ?
		   icon ==  61 ||                 // cabane ?
		   icon ==  36 ||                 // planches ?
		   icon ==  60 ||                 // tomates ?
		   icon ==  63 ||                 // oeufs ?
		   icon == 113 ||                 // maison ?
		   icon == 121 ||                 // mine de fer ?
		   icon == 122) )                 // mine de fer ?
	{
		if ( !MoveCreate(cel, -1, false, CHOBJECT,-1,
						 -1,-1, 9999,1,0, true) )  return false;
		MoveAddIcons(cel, 1, true);  // petites flammes

		m_decor[cel.x/2][cel.y/2].fire = 2;
		return true;
	}

	// S'il y a un autre objet -> pas de feu !
	if ( channel >= 0 )  return false;

	channel = m_decor[cel.x/2][cel.y/2].floorChannel;
	icon    = m_decor[cel.x/2][cel.y/2].floorIcon;

	if ( channel == CHFLOOR &&
		 (icon == 20 ||    // herbe fonc�e ?
		 (icon >= 59 && icon <= 64)) )  // pont ?
	{
		if ( !MoveCreate(cel, -1, false, CHOBJECT,-1,
						 -1,-1, 9999,1,0, true) )  return false;
		MoveAddIcons(cel, 1, true);  // petites flammes

		m_decor[cel.x/2][cel.y/2].fire = 2;
		return true;
	}

	return false;
}

// D�marre le feu si c'est possible par proximit�.

void CDecor::MoveProxiFire(POINT cel)
{
	int		cx, cy, xx, yy, x, y, channel, icon;

	static short tableInd[5] = {2,1,3,0,4};
	static short tablePos[5*5*2] =
	{
		 0, 0, -1,-2,  0,-2, +1,-2,  0, 0,
		-2,-1, -1,-1,  0,-1, +1,-1, +2,-1,
		-2, 0, -1, 0,  0, 0, +1, 0, +2, 0,
		-2,+1, -1,+1,  0,+1, +1,+1, +2,+1,
		 0, 0, -1,+2,  0,+2, +1,+2,  0, 0,
	};

	for ( cx=0 ; cx<5 ; cx++ )
	{
		for ( cy=0 ; cy<5 ; cy++ )
		{
			xx = tablePos[(tableInd[cx]+tableInd[cy]*5)*2+0];
			yy = tablePos[(tableInd[cx]+tableInd[cy]*5)*2+1];

			if ( xx == 0 && yy == 0 )  continue;

			x = cel.x + xx*2;
			y = cel.y + yy*2;

			if ( x < 0 || x >= MAXCELX ||
				 y < 0 || y >= MAXCELX )  continue;

			if ( m_decor[x/2][y/2].fire != 0 )  continue;  // brule d�j� ?

			x = ((cel.x + xx)/2)*2;
			y = ((cel.y + yy)/2)*2;

			// Mur ou rochers entre le feu et l'objet ?
			channel = m_decor[x/2][y/2].objectChannel;
			icon    = m_decor[x/2][y/2].objectIcon;
			if ( channel == CHOBJECT &&
				 ((icon >= 20 && icon <= 26)||
				  (icon >= 37 && icon <= 43)) )  continue;

			x = cel.x + xx*2;
			y = cel.y + yy*2;

			// Mur ou rochers entre le feu et l'objet ?
			channel = m_decor[x/2][y/2].objectChannel;
			icon    = m_decor[x/2][y/2].objectIcon;
			if ( channel == CHOBJECT &&
				 ((icon >= 20 && icon <= 26)||
				  (icon >= 37 && icon <= 43)) )  continue;

			// D�marre �ventuellement un seul foyer.
			if ( MoveStartFire(GetCel(x,y)) )  return;
		}
	}
}

// Fait �voluer le feu.

void CDecor::MoveFire(int rank)
{
	int		x, y, icon, newIcon;
	POINT	pos;

	x = (m_move[rank].cel.x/2)*2;
	y = (m_move[rank].cel.y/2)*2;

	if ( m_decor[x/2][y/2].fire == 0 ||
		 m_decor[x/2][y/2].fire >= MoveMaxFire() )  return;

	m_decor[x/2][y/2].fire ++;

	pos = ConvCelToPos(GetCel(x,y));
	m_pSound->PlayImage(SOUND_FEU, pos);

	if ( m_decor[x/2][y/2].objectIcon >= 0 )  // objet qui brule ?
	{
		if ( m_decor[x/2][y/2].fire > MoveMaxFire()/2 &&
			 m_decor[x/2][y/2].fire%50 == 0 )  // pas trop souvent !
		{
			MoveProxiFire(GetCel(x,y));  // boutte le feu
		}

		// D�but petites flammes.
		if ( m_decor[x/2][y/2].fire == 2 )
		{
			MoveStartFire(GetCel(x,y));
		}

		// D�but grandes flammes.
		if ( m_decor[x/2][y/2].fire == (MoveMaxFire()-DIMOBJY*2)/2 )
		{
			MoveAddIcons(GetCel(x,y), 2, true);  // grandes flammes
		}

		// D�but objet squelette.
		if ( m_decor[x/2][y/2].fire == MoveMaxFire()-DIMOBJY*2 )
		{
			icon = m_decor[x/2][y/2].floorIcon;
			if ( icon == 20 )  // herbe fonc�e ?
			{
				PutFloor(GetCel(x,y), CHFLOOR, 19);  // herbe brul�e
			}

			icon = m_decor[x/2][y/2].objectIcon;
			newIcon = -1;
			if ( icon >= 6 && icon <= 11 )  newIcon = icon-6+30;  // arbres ?
			if ( icon ==  61 )  newIcon =  62;  // cabane ?
			if ( icon == 113 )  newIcon =  15;  // maison ?
			if ( icon == 121 )  newIcon = 126;  // mine de fer ?
			if ( icon == 122 )  newIcon = 126;  // mine de fer ?
			MoveCreate(GetCel(x,y), -1, false, CHOBJECT,newIcon,
					   -1,-1, DIMOBJY*2,1,-1*50);
			MoveAddIcons(GetCel(x,y), 2, true);  // grandes flammes
		}

		// Fin grandes flammes.
		if ( m_decor[x/2][y/2].fire == MoveMaxFire()-DIMOBJY )
		{
			MoveAddIcons(GetCel(x,y), 1, true);  // petites flammes
		}

		// Fin feu.
		if ( m_decor[x/2][y/2].fire == MoveMaxFire()-1 )
		{
			MoveFinish(GetCel(x,y));
			icon = m_decor[x/2][y/2].objectIcon;
			if (  icon == 36               ||  // planches ?
				  icon == 60               ||  // tomates ?
				  icon == 63               ||  // oeufs ?
				  icon == 113              ||  // maison ?
				 (icon >= 65 && icon <= 71) )  // palissade ?
			{
				m_decor[x/2][y/2].objectChannel = -1;
				m_decor[x/2][y/2].objectIcon    = -1;
			}
			m_decor[x/2][y/2].fire = MoveMaxFire();  // d�j� brul�
		}
	}
	else    // sol qui brule ?
	{
		if ( m_decor[x/2][y/2].fire > DIMOBJY &&
			 m_decor[x/2][y/2].fire%50 == 0 )  // pas trop souvent !
		{
			MoveProxiFire(GetCel(x,y));  // boutte le feu
		}

		// D�but petites flammes.
		if ( m_decor[x/2][y/2].fire == 2 )
		{
			MoveStartFire(GetCel(x,y));
		}

		// Milieu feu.
		if ( m_decor[x/2][y/2].fire == DIMOBJY )
		{
			icon = m_decor[x/2][y/2].floorIcon;
			if ( icon == 20 )  // herbe fonc�e ?
			{
				PutFloor(GetCel(x,y), CHFLOOR, 19);  // herbe brul�e
			}
			if ( icon == 59 )  // pont ?
			{
				PutFloor(GetCel(x,y), CHFLOOR, 2);  // rivage
			}
			if ( icon == 61 )  // pont ?
			{
				PutFloor(GetCel(x,y), CHFLOOR, 4);  // rivage
			}
			if ( icon == 62 )  // pont ?
			{
				PutFloor(GetCel(x,y), CHFLOOR, 3);  // rivage
			}
			if ( icon == 64 )  // pont ?
			{
				PutFloor(GetCel(x,y), CHFLOOR, 5);  // rivage
			}
			if ( icon == 60 || icon == 63 )  // pont ?
			{
				PutFloor(GetCel(x,y), CHFLOOR, 14);  // eau
			}
		}

		// Fin feu.
		if ( m_decor[x/2][y/2].fire == DIMOBJY*2-1 )
		{
			MoveFinish(GetCel(x,y));
			m_decor[x/2][y/2].objectChannel = -1;
			m_decor[x/2][y/2].objectIcon    = -1;
			m_decor[x/2][y/2].fire = MoveMaxFire();  // d�j� brul�
		}
	}
}

// Fait �voluer tous les d�cors anim�s.

void CDecor::MoveStep(bool bFirst)
{
	int		rank, rankBlupi;

	for ( rank=0 ; rank<MAXMOVE ; rank++ )
	{
		if ( m_move[rank].bExist )
		{
			if ( !bFirst &&
				 (m_move[rank].rankIcons == 4 ||  // �clair entre tours ?
				  m_move[rank].rankIcons == 5 ) )
			{
				continue;
			}

			MoveFire(rank);

			// Si le blupi travaillant ici est stopp�, on
			// arr�te aussi la construction.
			rankBlupi = m_move[rank].rankBlupi;
			if ( rankBlupi != -1 )
			{
				if ( m_blupi[rankBlupi].action == ACTION_STOP  ||
					 m_blupi[rankBlupi].action == ACTION_STOPf )  continue;
			}

			m_move[rank].phase ++;
			if ( m_move[rank].phase > 32000 )
			{
				m_move[rank].phase = 0;
			}

			m_move[rank].cDelai ++;
			if ( m_move[rank].cDelai >= m_move[rank].delai )  // d�lai �coul� ?
			{
				m_move[rank].cDelai = 0;

				m_move[rank].cTotal ++;
				if ( m_move[rank].cTotal > 32000 )
				{
					m_move[rank].cTotal = 0;
				}

				if ( m_move[rank].total != 9999 &&
					 m_move[rank].cTotal >= m_move[rank].total )
				{
					MoveFinish(m_move[rank].cel);
				}
			}
		}
	}
}

// Termine un mouvement pour une cellule donn�e.

void CDecor::MoveFinish(POINT cel)
{
	int		rank;

	for ( rank=0 ; rank<MAXMOVE ; rank++ )
	{
		if ( m_move[rank].bExist &&
			 m_move[rank].cel.x == cel.x &&
			 m_move[rank].cel.y == cel.y )
		{
			if ( m_move[rank].channel >= 0 &&
				 m_move[rank].icon    >= 0 )
			{
				if ( m_move[rank].bFloor )
				{
					PutFloor(cel, m_move[rank].channel, m_move[rank].icon);
				}
				else
				{
					PutObject(cel, m_move[rank].channel, m_move[rank].icon);
				}
			}

			m_decor[cel.x/2][cel.y/2].rankMove = -1;
			m_move[rank].bExist = false;
		}
	}
}

// Termine un mouvement, d'apr�s le rang du blupi.

void CDecor::MoveFinish(int rankBlupi)
{
	int		rank;

	for ( rank=0 ; rank<MAXMOVE ; rank++ )
	{
		if ( m_move[rank].bExist &&
			 m_move[rank].rankBlupi == rankBlupi )
		{
			MoveFinish(m_move[rank].cel);
		}
	}
}

// V�rifie si une cellule est d�j� utilis�e.

bool CDecor::MoveIsUsed(POINT cel)
{
	int		rank;

	for ( rank=0 ; rank<MAXMOVE ; rank++ )
	{
		if ( m_move[rank].bExist &&
			 m_move[rank].cel.x == cel.x &&
			 m_move[rank].cel.y == cel.y )
		{
			return true;
		}
	}

	return false;
}

// Retourne l'objet en construction � un endroit donn�.

bool CDecor::MoveGetObject(POINT cel, int &channel, int &icon)
{
	int		rank;

	for ( rank=0 ; rank<MAXMOVE ; rank++ )
	{
		if ( m_move[rank].bExist &&
			 m_move[rank].cel.x == cel.x &&
			 m_move[rank].cel.y == cel.y &&
			 m_move[rank].bFloor == false )
		{
			channel = m_move[rank].channel;
			icon    = m_move[rank].icon;
			return true;
		}
	}

	return false;
}

// Modifie un objet en construction � un endroit donn�.

bool CDecor::MovePutObject(POINT cel, int channel, int icon)
{
	int		rank;

	for ( rank=0 ; rank<MAXMOVE ; rank++ )
	{
		if ( m_move[rank].bExist &&
			 m_move[rank].cel.x == cel.x &&
			 m_move[rank].cel.y == cel.y &&
			 m_move[rank].bFloor == false )
		{
			m_move[rank].channel = channel;
			m_move[rank].icon    = icon;
			return true;
		}
	}

	return false;
}

