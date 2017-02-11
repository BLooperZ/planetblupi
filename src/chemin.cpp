// chemin.cpp

// (c) 1997, Denis Dumoulin

#include "decor.h"
#include "fifo.h"
#include "action.h"

// M�morise toutes les positions des blupi.

void CDecor::CheminMemPos(int exRank)
{
	int		rank, index;

	m_cheminNbPos = 0;
	index = 0;
	for ( rank=0 ; rank<MAXBLUPI ; rank++ )
	{
		if ( m_blupi[rank].bExist &&
			 m_blupi[rank].perso != 6 &&  // pas le d�tonnateur de mine
			 rank != exRank )
		{
			m_cheminPos[index]  = m_blupi[rank].cel;
			m_cheminRank[index] = rank;
			m_cheminNbPos ++;
			index ++;

			if ( m_blupi[rank].destCel.x != m_blupi[rank].cel.x ||
				 m_blupi[rank].destCel.y != m_blupi[rank].cel.y )
			{
				m_cheminPos[index]  = m_blupi[rank].destCel;
				m_cheminRank[index] = rank;
				m_cheminNbPos ++;
				index ++;
			}
		}
	}
}

// Teste si une positiion est occup�e par un blupi.

bool CDecor::CheminTestPos(POINT pos, int &rank)
{
	int		i;

	for ( i=0 ; i<m_cheminNbPos ; i++ )
	{
		if ( pos.x == m_cheminPos[i].x &&
			 pos.y == m_cheminPos[i].y )
		{
			rank = m_cheminRank[i];
			return true;
		}
	}

	return false;
}


// une fois le but trouv�, reprend en arri�re
// � la recherche du chemin le plus court

// retourne la direction � prendre
int CDecor::CheminARebours(int rank)
{
	int		pos, rebours, last, dir, set;
	POINT	v;
	
	pos = m_blupi[rank].goalCel.y*MAXCELX + m_blupi[rank].goalCel.x;
	
	rebours = m_cheminWork[pos];
	
	if ( rebours == 0 )  return -1;

	while ( true )
	{	
	bis:
		for ( set=0 ; set<2 ; set++ )
		{
			for ( dir=set ; dir<8 ; dir+=2 )
			{
				v = GetVector(dir*16);
				last = pos + v.y*MAXCELX+v.x;
				
				if ( m_cheminWork[last] > 0 &&
					 m_cheminWork[last] < rebours )
				{
					pos = last;
					rebours = m_cheminWork[pos];
					if (rebours==1) return (dir>=4) ? dir-4 : dir+4;
					goto bis; // interrompt le for...
				}
			}
		}
		
		// ne devrait jamais arriver !
		return -1;
	}	
}


// troisi�me m�thode de recherche
// semblable � la pr�c�dente,
// mais les points � explorer sont class�s selon leur distance � la cible

void CDecor::CheminFillTerrain(int rank)
{
	long	pos, last, dest, dist;
	int		step, dir, cout, action, max, next, ampli;
	int		dx, dy;
	int		but = 1000;
	
	if ( m_blupi[rank].cel.x == m_blupi[rank].goalCel.x &&
		 m_blupi[rank].cel.y == m_blupi[rank].goalCel.y )  return;
	
	pos = m_blupi[rank].cel.y*MAXCELX + m_blupi[rank].cel.x;
	dest = m_blupi[rank].goalCel.y*MAXCELX + m_blupi[rank].goalCel.x;
	
	CPileTriee fifo(2*MAXCELX+2*MAXCELY);  // les variantes possibles
	
	fifo.put(pos, 0);  					// position de d�part
	m_cheminWork[pos] = 1;  			// premi�re position

	// r�p�te jusqu'� trouv� ou plus de possibilit�s
	max = 500;
	while ( max-- > 0 )
	{
		// reprend une variante de chemin
		pos = fifo.get();
		if ( pos < 0 )  break;

		step = m_cheminWork[pos];
		
		// on est arriv� au but ?
//?		if ( pos == dest )  return;
		if ( pos == dest )
		{
			but = step;  // h�las trop lent !
			max = 50;
		}
		
		// est-ce vraiment trop loin ?
		if ( step > 200 )  return;
			
		// marque les cases autour du point
		if ( step < but )  for ( dir=0 ; dir<8 ; dir++ )
		{
			if ( CheminTestDirection(rank, pos, dir, next, ampli, cout, action) )
			{
				last = pos + ampli*next;
				if ( last<0 || last>=MAXCELX*MAXCELY )  continue;

				if ( m_cheminWork[last] == 0 ||
					 m_cheminWork[last] > step+cout )
				{
					// marque les cases saut�es
					for (int i=1; i<ampli;i++)
					{
						m_cheminWork[pos+i*next] = step+cout-ampli+i;
					}

					m_cheminWork[last] = step+cout;
//?			char buffer[50];
//?			sprintf(buffer, "word = %d;%d  %d\n", last%200, last/200, step+cout);
//?			OutputDebug(buffer);
					dx = m_blupi[rank].goalCel.x - last%MAXCELX;
					dy = m_blupi[rank].goalCel.y - last/MAXCELX;
//?					dist = dy*dy + dx*dx;
					dist = (long)(dy*dy) + (long)(dx*dx);
					fifo.put(last, dist);
				}
			}
		}
	}
}


// routine d�terninant si une direction est possible
// retourne l'incr�ment pour passer � la nouvelle case
// et le "prix � payer" pour aller dans cette direction
// co�t doit �tre d�termin� en sortie

bool CDecor::CheminTestDirection(int rank, int pos, int dir,
								 int &next, int &ampli,
								 int &cout, int &action)
{
	POINT		cel, vector, newCel;
	bool		bFree;
	int			tryDirect, workBlupi, rankHere;

	cel.x = pos%MAXCELX;
	cel.y = pos/MAXCELX;

	tryDirect = dir*16;
	vector = GetVector(tryDirect);

	// Peut-on glisser dans cette direction ?
	bFree = IsFreeGlisse(cel, tryDirect, rank, action);
	cout = 5;  // co�t �lev�

	if ( !bFree )
	{
		// Peut-on marcher normalement ?
		bFree = IsFreeDirect(cel, tryDirect, rank);
		action = ACTION_MARCHE;
		cout = 1;  // co�t minimal
	}

	if ( !bFree )
	{
		// Peut-on sauter ?
		bFree = IsFreeJump(cel, tryDirect, rank, action);
		cout = 3;  // co�t �lev�
	}

	ampli = GetAmplitude(action);  	// a <- amplitude (1..5)
	cout *= ampli; 					// co�t plus �lev� si grande amplitude

	// Blupi peut aller sur le lieu de la construction.
	if ( !bFree && m_blupi[rank].passCel.x != -1 )
	{
		newCel = m_blupi[rank].passCel;
		workBlupi = m_decor[newCel.x/2][newCel.y/2].workBlupi;

		if ( m_blupi[rank].passCel.x/2 == (cel.x+vector.x*ampli)/2 &&
			 m_blupi[rank].passCel.y/2 == (cel.y+vector.y*ampli)/2 &&
			 (workBlupi < 0 || workBlupi == rank) )
		{
			bFree = true;
			cout = 1;
		}
	}

	if ( bFree )  // chemin libre (sans tenir compte des perso) ?
	{
		newCel.x = cel.x + vector.x*ampli;
		newCel.y = cel.y + vector.y*ampli;  // newCel <- arriv�e supos�e

		if ( m_blupi[rank].perso == 3 )   // tracks ?
		{
			// Le tracks peut aller sur les blupi
			// pour les �craser !
			if ( IsTracksHere(newCel, false) )  // autre perso ici ?
			{
				return false;
			}
		}
		else
		{
//?			if ( IsBlupiHere(newCel, false) )  // autre perso ici ?
			if ( CheminTestPos(newCel, rankHere) )  // autre perso ici ?
			{
				// Si blupi immobile, comme si obstacle qq.
//?				if ( m_blupi[m_blupiHere].goalCel.x == -1 )  return false;
				if ( m_blupi[rankHere].goalCel.x == -1 )  return false;

				// Si blupi mobile, possible mais co�t �lev�.
				cout = 20;
			}
		}
		next = vector.y*MAXCELX + vector.x;
		return true;
	}

	return false;
}



// Retourne true si on a assign� une nouvelle direction � blupi.
bool CDecor::CheminCherche(int rank, int &action)
{
	int 	cout;		// prix pour aller dans une direction
	int		pos, dir, next, ampli;

	// D�j� � destination ?
	if ( m_blupi[rank].cel.x == m_blupi[rank].goalCel.x &&
		 m_blupi[rank].cel.y == m_blupi[rank].goalCel.y )
	{
		return false;
	}

	// Destination occup�e ?
	if ( IsBlupiHereEx(m_blupi[rank].goalCel, rank, false) )
	{
		return false;
	}

	memset(m_cheminWork, 0, (Uint8)MAXCELX*(Uint8)MAXCELY);
	CheminMemPos(rank);
	
	// fait un remplissage du map de travail
	// autour du point de d�part
	CheminFillTerrain(rank);
    
    // cherche le chemin � partir de la destination
	dir = CheminARebours(rank);
	if ( dir < 0 )  return false;

	pos = m_blupi[rank].cel.y*MAXCELX + m_blupi[rank].cel.x;
	if ( CheminTestDirection(rank, pos, dir, next, ampli, cout, action) &&
		 cout < 20 )
	{
		m_blupi[rank].sDirect = 16*dir;
		return true;
	}

	// ne devrait jamais arriver !	
	return false;			
}


// Teste s'il est possible de se rendre � un endroit donn�.

bool CDecor::IsCheminFree(int rank, POINT dest, int button)
{
	int		action, sDirect;
	POINT	goalCel, passCel, limit;
	bool	bOK;

	if ( button == BUTTON_STOP )  return true;

	goalCel = m_blupi[rank].goalCel;
	passCel = m_blupi[rank].passCel;
	sDirect = m_blupi[rank].sDirect;

	if ( IsFreeCelEmbarque(dest, rank, action, limit) )
	{
		dest = limit;
	}
	if ( IsFreeCelDebarque(dest, rank, action, limit) )
	{
		dest = limit;
	}
	if ( button == BUTTON_GO &&
		 m_decor[dest.x/2][dest.y/2].objectChannel == CHOBJECT &&
		 (m_decor[dest.x/2][dest.y/2].objectIcon == 118 ||    // jeep ?
		  m_decor[dest.x/2][dest.y/2].objectIcon == 16  ) &&  // armure ?
		 dest.x%2 == 1 && dest.y%2 == 1 )
	{
		dest.y --;  // va � c�t� jeep/armure
	}
	if ( button == BUTTON_GO &&
		 m_decor[dest.x/2][dest.y/2].objectChannel == CHOBJECT &&
		 m_decor[dest.x/2][dest.y/2].objectIcon == 113 )  // maison ?
	{
		dest.x = (dest.x/2)*2+1;
		dest.y = (dest.y/2)*2+1;  // sous la porte
	}

	if ( m_blupi[rank].cel.x == dest.x &&
		 m_blupi[rank].cel.y == dest.y )  return true;

	m_blupi[rank].goalCel = dest;
	if ( m_decor[dest.x/2][dest.y/2].objectChannel == CHOBJECT &&
		 button != BUTTON_GO )
	{
		m_blupi[rank].passCel = dest;  // si arbres/fleurs/bateau/etc.
	}

	bOK = CheminCherche(rank, action);

	m_blupi[rank].goalCel = goalCel;
	m_blupi[rank].passCel = passCel;
	m_blupi[rank].sDirect = sDirect;

	return bOK;
}

