
#pragma once

// traitement d'une liste en fifo


// stucture pour enpiler des positions
// en fonction de leur distance � la cible
typedef struct
{
	long		pos;
	long		dist;
} 
Element;


// traitement d'une pile tri�e

class CPileTriee
{
private:
	long		m_taille;		// nombre de polongs max
	long		m_max;			// position limite
	long		m_out;			// position pour reprendre
	Element*	m_data;			// donn�es
			
public:
	CPileTriee(long taille);
	~CPileTriee();
	
	void		put(long pos, long dist);
	long		get();
};