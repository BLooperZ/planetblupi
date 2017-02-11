// Obstacle.cpp
//

#include "decor.h"
#include "misc.h"
#include "action.h"

// Cette table indique les obstacles sur les sols.
// 0=passage, 1=obstacle

static char tableObstacleFloor[] =
{
	1,1,1,1,1,		// 0 (noir pour limites)
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,

	0,0,0,0,0,		// 1
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,

	0,1,1,1,1,		// 2
	0,1,1,1,1,
	0,1,1,1,1,
	0,1,1,1,1,
	0,1,1,1,1,

	0,0,0,0,0,		// 3
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,

	1,1,1,1,0,		// 4
	1,1,1,1,0,
	1,1,1,1,0,
	1,1,1,1,0,
	1,1,1,1,0,

	1,1,1,1,1,		// 5
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,
	0,0,0,0,0,

	0,0,0,0,0,		// 6
	0,0,1,1,1,
	0,1,1,1,1,
	0,1,1,1,1,
	0,1,1,1,1,

	0,0,0,0,0,		// 7
	1,1,1,0,0,
	1,1,1,1,0,
	1,1,1,1,0,
	1,1,1,1,0,

	1,1,1,1,0,		// 8
	1,1,1,1,0,
	1,1,1,1,0,
	1,1,1,0,0,
	0,0,0,0,0,

	0,1,1,1,1,		// 9
	0,1,1,1,1,
	0,1,1,1,1,
	0,0,1,1,1,
	0,0,0,0,0,

	0,0,1,1,1,		// 10
	0,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,

	1,1,1,0,0,		// 11
	1,1,1,1,0,
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,

	1,1,1,1,1,		// 12
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,0,
	1,1,1,0,0,

	1,1,1,1,1,		// 13
	1,1,1,1,1,
	1,1,1,1,1,
	0,1,1,1,1,
	0,0,1,1,1,

	1,1,1,1,1,		// 14
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,

	0,0,0,0,0,		// 15
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 16
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 17
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 18
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 19
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 20
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 21
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 22
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 23
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 24
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 25
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 26
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 27
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 28
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 29
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 30
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 31
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 32
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 33
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 34
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 35
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 36
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 37
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 38
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 39
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 40
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 41
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 42
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 43
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 44
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 45
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 46
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 47
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 48
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 49
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 50
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 51
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 52
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 53
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 54
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 55
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 56
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 57
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 58
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 59 (pont e-o)
	0,0,0,0,0,
	0,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,

	0,0,0,0,0,		// 60
	0,0,0,0,0,
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,

	0,0,0,0,0,		// 61
	0,0,0,0,0,
	1,1,1,1,0,
	1,1,1,1,1,
	1,1,1,1,1,

	0,0,0,1,1,		// 62 (pont n-s)
	0,0,1,1,1,
	0,0,1,1,1,
	0,0,1,1,1,
	0,0,1,1,1,

	0,0,1,1,1,		// 63
	0,0,1,1,1,
	0,0,1,1,1,
	0,0,1,1,1,
	0,0,1,1,1,

	0,0,1,1,1,		// 64
	0,0,1,1,1,
	0,0,1,1,1,
	0,0,1,1,1,
	0,0,0,1,1,
};

// Cette table indique les obstacles sur les sols pour le bateau.
// 0=passage, 1=obstacle

static char tableObstacleFloorBateau[] =
{
	1,1,1,1,1,		// 2
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,

	1,1,1,1,1,		// 3
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,

	0,0,1,1,1,		// 4
	0,0,1,1,1,
	0,0,1,1,1,
	0,0,1,1,1,
	0,0,1,1,1,

	0,0,0,0,0,		// 5
	0,0,0,0,0,
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,

	1,1,1,1,1,		// 6
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,

	1,1,1,1,1,		// 7
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,

	0,0,1,1,1,		// 8
	0,0,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,

	1,1,1,1,1,		// 9
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,

	1,1,1,0,0,		// 10
	1,1,1,0,0,
	1,1,1,0,0,
	0,0,0,0,0,
	0,0,0,0,0,

	0,0,1,1,1,		// 11
	0,0,1,1,1,
	0,0,1,1,1,
	0,0,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 12
	0,0,0,0,0,
	0,0,1,1,1,
	0,0,1,1,1,
	0,0,1,1,1,

	0,0,0,0,0,		// 13
	0,0,0,0,0,
	1,1,1,0,0,
	1,1,1,0,0,
	1,1,1,0,0,

	0,0,0,0,0,		// 14
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
};

// Cette table indique les obstacles sur les objets.
// 0=passage, 1=obstacle

static char tableObstacleObject[] =
{
	0,0,0,0,0,		// 0
	0,0,0,0,0,
	0,0,1,0,0,
	0,0,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 1
	0,1,0,0,0,
	0,1,0,0,0,
	0,1,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 2
	0,1,1,1,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 3
	0,1,1,1,0,
	0,1,1,1,0,
	0,1,1,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 4
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,1,0,
	0,0,0,0,0,

	1,1,1,1,1,		// 5
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,

	0,0,0,0,0,		// 6 (arbre)
	0,0,0,0,0,
	0,0,1,0,0,
	0,0,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 7
	0,0,0,0,0,
	0,0,0,1,0,
	0,0,1,1,1,
	0,0,0,1,0,

	0,0,0,0,0,		// 8
	0,1,0,0,0,
	0,1,0,0,0,
	0,1,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 9
	0,0,0,1,0,
	0,0,1,1,0,
	0,1,1,1,0,
	0,0,0,0,0,

	0,1,1,1,1,		// 10
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,
	0,1,1,1,0,

	1,1,1,1,0,		// 11
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,
	0,1,1,1,1,

	0,1,1,1,0,		// 12 (fus�e)
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,
	0,1,1,1,0,

	0,0,0,0,0,		// 13
	0,0,0,0,0,
	0,0,1,0,0,
	0,0,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 14 (m�tal)
	0,0,0,0,0,
	0,0,1,1,1,
	0,0,1,1,1,
	0,0,1,1,1,

	1,1,1,1,1,		// 15 (maison construction)
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,

	0,0,0,0,0,		// 16 (armure)
	0,0,0,0,0,
	0,0,1,1,1,
	0,0,1,1,1,
	0,0,1,1,1,

	1,1,1,1,1,		// 17 (batiment ennemi)
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,

	1,1,1,1,1,		// 18
	1,1,1,1,1,
	1,1,1,1,1,
	1,0,0,0,0,
	1,1,1,1,1,

	0,0,0,0,0,		// 19 (�lectro pi�g�)
	0,0,0,0,0,
	0,0,1,1,1,
	0,0,1,1,1,
	0,0,1,1,1,

	1,1,1,1,1,		// 20 (mur)
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,

	1,1,1,1,1,		// 21
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,

	1,1,1,1,1,		// 22
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,

	1,1,1,1,1,		// 23
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,

	1,1,1,1,1,		// 24
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,

	1,1,1,1,1,		// 25
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,

	1,1,1,1,1,		// 26
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,

	1,1,1,1,1,		// 27 (tour)
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,

	1,1,1,1,1,		// 28 (laboratoire)
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,0,0,
	1,1,1,1,1,
//	1,1,1,1,1,		// 28 (laboratoire)
//	1,1,1,1,1,
//	1,1,1,1,1,
//	1,1,1,1,1,
//	1,1,1,1,1,

	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,

	0,0,0,0,0,		// 30 (arbre sans feuilles)
	0,0,0,0,0,
	0,0,1,0,0,
	0,0,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 31
	0,0,0,0,0,
	0,0,0,1,0,
	0,0,1,1,1,
	0,0,0,1,0,

	0,0,0,0,0,		// 32
	0,1,0,0,0,
	0,1,0,0,0,
	0,1,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 33
	0,0,0,1,0,
	0,0,1,1,0,
	0,1,1,1,0,
	0,0,0,0,0,

	0,1,1,1,1,		// 34
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,
	0,1,1,1,0,

	1,1,1,1,0,		// 35
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,
	0,1,1,1,1,

	0,0,0,0,0,		// 36 (tas de planches)
	0,0,0,0,0,
	0,0,1,1,1,
	0,0,1,1,1,
	0,0,1,1,1,

	1,1,1,1,1,		// 37 (rochers)
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,

	1,1,1,1,1,		// 38
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,

	1,1,1,1,1,		// 39
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,

	1,1,1,1,1,		// 40
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,

	1,1,1,1,1,		// 41
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,

	1,1,1,1,1,		// 42
	1,1,1,1,1,
	1,1,1,1,1,
	0,0,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 43
	0,1,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 44 (tas de pierres)
	0,0,0,0,0,
	0,0,1,1,1,
	0,0,1,1,1,
	0,0,1,1,1,

	0,0,0,0,0,		// 45
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 46
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 47
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 48
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 49
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 50
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 51
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 52
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 53
	0,0,0,0,0,
	0,0,1,1,1,
	0,0,1,1,1,
	0,0,1,1,1,

	0,0,0,0,0,		// 54
	0,0,0,0,0,
	1,1,1,0,0,
	1,1,1,0,0,
	1,1,1,0,0,

	1,1,1,0,0,		// 55
	1,1,1,0,0,
	1,1,1,0,0,
	0,0,0,0,0,
	0,0,0,0,0,

	0,0,1,1,1,		// 56
	0,0,1,1,1,
	0,0,1,1,1,
	0,0,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 57 (plante)
	0,0,0,0,0,
	0,0,1,1,1,
	0,0,1,1,1,
	0,0,1,1,1,

	0,0,0,0,0,		// 58
	0,0,0,0,0,
	0,0,1,1,1,
	0,0,1,1,1,
	0,0,1,1,1,

	0,0,0,0,0,		// 59
	0,0,0,0,0,
	0,0,1,1,1,
	0,0,1,1,1,
	0,0,1,1,1,

	0,0,0,0,0,		// 60 (tomates)
	0,0,0,0,0,
	0,0,1,1,1,
	0,0,1,1,1,
	0,0,1,1,1,

	1,1,1,1,1,		// 61 (cabane)
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,

	1,1,1,1,1,		// 62
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,

	0,0,0,0,0,		// 63 (oeufs)
	0,0,0,0,0,
	0,0,1,1,1,
	0,0,1,1,1,
	0,0,1,1,1,

	1,1,1,1,1,		// 64
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,

	1,1,1,1,0,		// 65 (palissade)
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,0,0,
	0,1,1,0,0,

	1,1,1,1,0,		// 66
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,0,0,
	0,1,1,0,0,

	1,1,1,1,0,		// 67
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,0,0,
	0,1,1,0,0,

	1,1,1,1,0,		// 68
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,0,0,
	0,1,1,0,0,

	1,1,1,1,0,		// 69
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,0,0,
	0,1,1,0,0,

	1,1,1,1,0,		// 70
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,0,0,
	0,1,1,0,0,

	1,1,1,1,0,		// 71
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,0,0,
	0,1,1,0,0,

	0,0,0,0,0,		// 72 (pont en construction)
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 73
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 74 (rayon tour)
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 75
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 76
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 77
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 78
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 79
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 80 (bouteille)
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,1,0,
	0,0,0,0,0,

	0,1,1,1,0,		// 81 (fleurs)
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,
	0,1,1,1,0,

	0,0,0,0,0,		// 82
	0,0,0,0,0,
	0,0,1,1,1,
	0,0,1,1,1,
	0,0,1,1,1,

	0,1,1,1,0,		// 83
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,
	0,1,1,1,0,

	0,0,0,0,0,		// 84
	0,0,0,0,0,
	0,0,1,1,1,
	0,0,1,1,1,
	0,0,1,1,1,

	0,0,0,0,0,		// 85 (dynamite)
	0,0,0,0,0,
	0,0,1,1,1,
	0,0,1,1,1,
	0,0,1,1,1,

	0,0,0,0,0,		// 86
	0,0,0,0,0,
	0,0,1,1,1,
	0,0,1,1,1,
	0,0,1,1,1,

	0,0,0,0,0,		// 87
	0,0,0,0,0,
	0,0,1,1,1,
	0,0,1,1,1,
	0,0,1,1,1,

	0,0,0,0,0,		// 88 (explosion)
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 89
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 90
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 91
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 92 (poison)
	0,0,0,0,0,
	0,0,1,1,1,
	0,0,1,1,1,
	0,0,1,1,1,

	0,0,0,0,0,		// 93 (pi�ge)
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,1,0,
	0,0,0,0,0,

	0,1,1,1,0,		// 94 (fleurs)
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,
	0,1,1,1,0,

	0,0,0,0,0,		// 95
	0,0,0,0,0,
	0,0,1,1,1,
	0,0,1,1,1,
	0,0,1,1,1,

	0,0,0,0,0,		// 96 (araign�e dans pi�ge)
	0,0,0,0,0,
	0,0,1,1,1,
	0,0,1,1,1,
	0,0,1,1,1,

	0,0,0,0,0,		// 97 (tracks dans pi�ge)
	0,0,0,0,0,
	0,0,1,1,1,
	0,0,1,1,1,
	0,0,1,1,1,

	0,0,0,0,0,		// 98 (robot dans pi�ge)
	0,0,0,0,0,
	0,0,1,1,1,
	0,0,1,1,1,
	0,0,1,1,1,

	1,1,1,1,1,		// 99 (recharge)
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,0,0,
	1,1,1,0,0,

	1,1,1,1,1,		// 100 (batiment ennemi)
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,

	1,1,1,1,1,		// 101
	1,1,1,1,1,
	1,1,1,1,1,
	1,0,0,0,0,
	1,1,1,1,1,

	1,1,1,1,1,		// 102
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,

	1,1,1,1,1,		// 103
	1,1,1,1,1,
	1,1,1,1,1,
	1,0,0,0,0,
	1,1,1,1,1,

	1,1,1,1,1,		// 104
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,

	1,1,1,1,1,		// 105
	1,1,1,1,1,
	1,1,1,1,1,
	1,0,0,0,0,
	1,1,1,1,1,

	1,1,1,1,1,		// 106 (barri�re)
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,

	1,1,1,1,1,		// 107
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,

	1,1,1,1,1,		// 108
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,

	1,1,1,1,1,		// 109
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,

	1,1,1,1,1,		// 110
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,

	1,1,1,1,1,		// 111
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,

	1,1,1,1,1,		// 112
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,

	1,1,1,1,1,		// 113 (maison)
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,0,0,
	1,1,1,1,1,

	0,0,0,0,0,		// 114 (bombe dans pi�ge)
	0,0,0,0,0,
	0,0,1,1,1,
	0,0,1,1,1,
	0,0,1,1,1,

	1,1,1,1,1,		// 115 (batiment ennemi)
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,

	1,1,1,1,1,		// 116
	1,1,1,1,1,
	1,1,1,1,1,
	1,0,0,0,0,
	1,1,1,1,1,

	0,0,0,0,0,		// 117 (bateau)
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 118 (jeep)
	0,0,0,0,0,
	0,0,1,1,1,
	0,0,1,1,1,
	0,0,1,1,1,

	1,1,1,1,1,		// 119 (usine)
	1,1,1,1,1,
	1,1,1,1,1,
	1,0,0,0,1,
	1,1,1,1,1,

	1,1,1,1,1,		// 120
	1,1,1,1,1,
	1,1,1,1,1,
	1,0,0,0,0,
	1,1,1,1,1,

	1,1,1,1,1,		// 121 (mine de fer)
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,

	1,1,1,1,1,		// 122
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,0,0,
	1,1,1,1,1,

	0,0,0,0,0,		// 123 (fer)
	0,0,0,0,0,
	0,0,1,1,1,
	0,0,1,1,1,
	0,0,1,1,1,

	0,0,0,0,0,		// 124 (drapeau)
	0,0,0,0,0,
	0,0,1,0,0,
	0,0,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 125 (mine)
	0,0,0,0,0,
	0,0,1,1,1,
	0,0,1,1,1,
	0,0,1,1,1,

	0,0,0,0,0,		// 126 (mine de fer, �chaffaudage)
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,

	0,0,0,0,0,		// 127 (mine)
	0,0,0,0,0,
	0,0,1,1,1,
	0,0,1,1,1,
	0,0,1,1,1,
};

// Retourne les obstacles autour d'une cellule, sous la
// forme d'un tableau de 3x3.

void CDecor::SearchFloor(int rank, int icon, POINT cel, int *pBits)
{
	char*	pTable;
	int		first, last;
	int		dx, dy, x, y, i;
	int		def = 0;

	pTable = tableObstacleFloor;
	first = 0;
	last  = 64;

	if ( rank != -1 && m_blupi[rank].vehicule == 1 )  // en  bateau ?
	{
		pTable = tableObstacleFloorBateau;
		first = 2;
		last  = 14;
		def = 1;
	}

	if ( icon >= first && icon <= last )
	{
		pTable += (icon-first)*5*5;

		if ( cel.x%2 == 0 )  dx = 0;
		else                 dx = 2;

		if ( cel.y%2 == 0 )  dy = 0;
		else                 dy = 2;

		for ( y=dy ; y<dy+3 ; y++ )
		{
			for ( x=dx ; x<dx+3 ; x++ )
			{
				*pBits++ = pTable[x+y*5];
			}
		}
	}
	else
	{
		for ( i=0 ; i<9 ; i++ )
		{
			*pBits++ = def;
		}
	}
}

// Retourne les obstacles autour d'une cellule, sous la
// forme d'un tableau de 3x3.

void CDecor::SearchObject(int rank, int icon, POINT cel, int *pBits)
{
	char*	pTable;
	int		dx, dy, x, y, i;

	if ( icon >= 0 && icon <= 127 )
	{
		pTable = tableObstacleObject+(icon)*5*5;

		if ( cel.x%2 == 0 )  dx = 0;
		else                 dx = 2;

		if ( cel.y%2 == 0 )  dy = 0;
		else                 dy = 2;

		for ( y=dy ; y<dy+3 ; y++ )
		{
			for ( x=dx ; x<dx+3 ; x++ )
			{
				*pBits++ = pTable[x+y*5];
			}
		}
	}
	else
	{
		for ( i=0 ; i<9 ; i++ )
		{
			*pBits++ = 0;
		}
	}
}

// Ajuste un sol en fonction du personnage.

void CDecor::AjustFloor(int rank, int icon, POINT cel, int *pBits)
{
	int		i;

	if ( rank < 0 )  return;

	if ( m_blupi[rank].perso == 0 )  // blupi ?
	{
		if ( m_blupi[rank].interrupt == -1 )  // passe muraille (*) ?
		{
			goto pass;
		}
		if ( m_blupi[rank].vehicule == 1 )  // en bateau ?
		{
			if ( icon >= 59 && icon <= 64 )   goto lock;  // pont ?
		}
		return;
	}

	if ( m_blupi[rank].perso == 2 )  // virus ?
	{
		goto pass;  // le virus peut aller partout (il volle)
		return;
	}

	if ( m_blupi[rank].perso == 3 )  // tracks ?
	{
		if ( icon >= 59 && icon <= 64 )  // ponts ?
		{
			goto lock;  // le tracks ne peut pas aller sur les ponts
		}
		return;
	}

//-	if ( m_blupi[rank].perso == 4 )  // robot ?
//-	{
//-		if ( icon >= 59 && icon <= 64 )  // ponts ?
//-		{
//-			goto lock;  // le robot ne peut pas aller sur les ponts
//-		}
//-		return;
//-	}
	return;

	pass:
	for ( i=0 ; i<9 ; i++ )
	{
		*pBits++ = 0;  // peut passer
	}
	return;

	lock:
	for ( i=0 ; i<9 ; i++ )
	{
		*pBits++ = 1;  // bloqu�
	}
	return;
}

// (*)	Blupi est passe muraille lorsqu'il embarque ou d�barque
//		du bateau. Dans ce cas, tous les sols (rivages) doivent
//		permettre de passer. En revanche, pas les obstacles !

// Ajuste un obstacle en fonction du personnage.

void CDecor::AjustObject(int rank, int icon, POINT cel, int *pBits)
{
	int		i;

	if ( rank < 0 )  return;

	if ( m_blupi[rank].perso == 0 )  // blupi ?
	{
		if ( m_blupi[rank].vehicule != 0 &&  // pas � pied ?
			 cel.x%2 == 1 && cel.y%2 == 1 &&
			 m_decor[cel.x/2][cel.y/2].objectIcon == 117 )  // bateau ?
		{
			goto lock;  // blupi ne peut pas aller dans le bateau
		}
//		if ( m_blupi[rank].interrupt == -1 )  // passe muraille (*) ?
//		{
//			goto pass;
//		}
//		if ( cel.x > 0 && cel.x%2 == 0 && cel.y%2 == 1 &&
//			 (m_decor[(cel.x-2)/2][cel.y/2].objectIcon == 100 ||  // usine ?
//			  m_decor[(cel.x-2)/2][cel.y/2].objectIcon == 102 ||
//			  m_decor[(cel.x-2)/2][cel.y/2].objectIcon == 104 ||
//			  m_decor[(cel.x-2)/2][cel.y/2].objectIcon == 115 ||
//			  m_decor[(cel.x-2)/2][cel.y/2].objectIcon ==  17) )
//		{
//			goto lock;  // blupi ne peut pas bloquer la porte
//		}
		if ( cel.x%2 == 1 && cel.y%2 == 1 &&
			 m_decor[cel.x/2][cel.y/2].objectIcon == 99 )  // recharge ?
		{
			goto lock;  // blupi ne peut pas bloquer la station
		}
		if ( m_blupi[rank].vehicule == 2 &&  // en jeep ?
			 m_decor[cel.x/2][cel.y/2].objectIcon == 113 )  // maison ?
		{
			goto lock;  // blupi ne peut pas aller dans la maison
		}
		return;
	}

	if ( m_blupi[rank].perso == 1 )  // araign�e ?
	{
//		if ( cel.x%2 != 0 && cel.y%2 != 0 &&
		if ( IsSpiderObject(icon) )  // tomate ou poison ?
		{
			goto pass;  // l'araign�e peut aller dans les tomates
		}
		return;
	}

	if ( m_blupi[rank].perso == 2 )  // virus ?
	{
		if ( icon == 81 ||
			 icon == 83 ||
			 icon == 94 ||  // fleurs non-coup�es ?
			 (icon >= 106 && icon <= 112) )  // barri�res ennemies ?
		{
			goto pass;  // le virus peut aller
		}
		return;
	}

	if ( m_blupi[rank].perso == 3 )  // tracks ?
	{
		if ( IsTracksObject(icon) )  // fleurs ou objet ?
		{
			goto pass;  // le tracks peut aller
		}
		if ( icon == 113 ||                 // maison ?
			 icon ==  28 || icon ==  29 ||  // laboratoire ?
			 icon == 119 || icon == 120 ||  // usine ?
			 icon == 121 || icon == 122 )   // mine de fer ?
		{
			goto lock;  // le tracks ne peut pas aller dans la maison
		}
		return;
	}

	if ( m_blupi[rank].perso == 4 )  // robot ?
	{
		if ( IsRobotObject(icon) )  // pi�ge ou dynamite ?
		{
			goto pass;  // le robot peut aller
		}
		return;
	}

	if ( m_blupi[rank].perso == 5 )  // bombe ?
	{
		if ( icon == 93 )	// pi�ge ?
		{
			goto pass;  // la bombe peut aller
		}
		return;
	}

	if ( m_blupi[rank].perso == 7 )  // �lectro ?
	{
		if ( icon ==  93 )  // pi�ge ?
		{
			goto pass;  // l'�lectro peut aller
		}
		if ( icon == 113 ||                 // maison ?
			 icon ==  28 || icon ==  29 ||  // laboratoire ?
			 icon == 119 || icon == 120 ||  // usine ?
			 icon == 121 || icon == 122 )   // mine de fer ?
		{
			goto lock;  // l'�lectro ne peut pas aller dans la maison
		}
		return;
	}

	if ( m_blupi[rank].perso == 8 )  // disciple ?
	{
		if ( cel.x > 0 && cel.x%2 == 0 && cel.y%2 == 1 &&
			 (m_decor[(cel.x-2)/2][cel.y/2].objectIcon == 100 ||  // usine ?
			  m_decor[(cel.x-2)/2][cel.y/2].objectIcon == 102 ||
			  m_decor[(cel.x-2)/2][cel.y/2].objectIcon == 104 ||
			  m_decor[(cel.x-2)/2][cel.y/2].objectIcon == 115) )
		{
			goto lock;  // disciple ne peut pas bloquer la porte
		}
		if ( cel.x%2 == 1 && cel.y%2 == 1 &&
			 m_decor[cel.x/2][cel.y/2].objectIcon == 99 )  // recharge ?
		{
			goto lock;  // disciple ne peut pas bloquer la station
		}
		if ( m_decor[cel.x/2][cel.y/2].objectIcon == 113 )  // maison ?
		{
			goto lock;  // disciple ne peut pas aller dans la maison
		}
		return;
	}
	return;

	pass:
	for ( i=0 ; i<9 ; i++ )
	{
		*pBits++ = 0;  // peut passer
	}
	return;

	lock:
	for ( i=0 ; i<9 ; i++ )
	{
		*pBits++ = 1;  // bloqu�
	}
	return;
}

// Copie un tableau 3x3 dans un tableau 9x9.

void Copy33To99(int *pSrc33, int *pDst99, int dx, int dy)
{
	int		x, y;

	for ( y=0 ; y<3 ; y++ )
	{
		for ( x=0 ; x<3 ; x++ )
		{
			pDst99[(dx+1)*3+x + ((dy+1)*3+y)*9] = pSrc33[x+y*3];
		}
	}
}

// Indique s'il est possible d'avancer dans une direction donn�e.

bool CDecor::IsFreeDirect(POINT cel, int direct, int rank)
{
	int			icon, workBlupi;
	int			bits[3*3], obstacles[9*9];
	POINT		test, vector;

	vector = GetVector(direct);

	test.x = cel.x+vector.x;
	test.y = cel.y+vector.y;

	if ( m_decor[test.x/2][test.y/2].fire > 0 &&
		 m_decor[test.x/2][test.y/2].fire < MoveMaxFire() )  return false;

	// Cellule bloqu�e (un blupi travaille ici) ?
	if ( m_blupi[rank].perso != 3 )  // pas tracks ?
	{
		workBlupi = m_decor[test.x/2][test.y/2].workBlupi;
		if ( workBlupi >= 0 && workBlupi != rank )  return false;
	}

	// D�placement possible par-rapport au sol ?
//	icon = m_decor[cel.x/2][cel.y/2].floorIcon;
//	SearchFloor(rank, icon, cel, bits);
//	AjustFloor(rank, icon, cel, bits);
//	if ( bits[(1+vector.x)+(1+vector.y)*3] == 1 )  return false;

	icon = m_decor[test.x/2][test.y/2].floorIcon;
	SearchFloor(rank, icon, test, bits);
	AjustFloor(rank, icon, test, bits);
	if ( bits[1+1*3] == 1 )  return false;
	if ( bits[(1-vector.x)+(1-vector.y)*3] == 1 )  return false;

	// D�placement possible par-rapport aux obstacles ?
	icon = m_decor[cel.x/2][cel.y/2].objectIcon;
	SearchObject(rank, icon, cel, bits);
	AjustObject(rank, icon, cel, bits);
	if ( bits[(1+vector.x)+(1+vector.y)*3] == 1 )  return false;

	icon = m_decor[test.x/2][test.y/2].objectIcon;
	SearchObject(rank, icon, test, bits);
	AjustObject(rank, icon, test, bits);
	if ( bits[(1-vector.x)+(1-vector.y)*3] == 1 )  return false;
	if ( bits[1+1*3] == 1 )  return false;

	if ( vector.x != 0 && vector.y != 0 )  // d�placement diagonal ?
	{
		test.x = cel.x;
		test.y = cel.y+vector.y;
		icon = m_decor[test.x/2][test.y/2].objectIcon;
		SearchObject(rank, icon, test, bits);
		AjustObject(rank, icon, test, bits);
		Copy33To99(bits, obstacles, 0, vector.y);

		test.x = cel.x+vector.x;
		test.y = cel.y;
		icon = m_decor[test.x/2][test.y/2].objectIcon;
		SearchObject(rank, icon, test, bits);
		AjustObject(rank, icon, test, bits);
		Copy33To99(bits, obstacles, vector.x, 0);

		if ( obstacles[(4+vector.x*1)+(4+vector.y*2)*9] == 1 )  return false;
		if ( obstacles[(4+vector.x*2)+(4+vector.y*1)*9] == 1 )  return false;
	}

	return true;  // pas d'obstacle
}

// Indique si une cellule contient un objet.
// Est utilis� lors du dessin (BuildPutBlupi), pour savoir
// si blupi est devant un objet.

bool CDecor::IsFreeCelObstacle(POINT cel)
{
	int			icon;
	int			bits[9];

	if ( !IsValid(cel) )  return false;

	if ( m_decor[cel.x/2][cel.y/2].fire > 0 &&
		 m_decor[cel.x/2][cel.y/2].fire < MoveMaxFire() )  return false;

	icon = m_decor[cel.x/2][cel.y/2].objectIcon;
	if ( icon != -1 )
	{
		SearchObject(-1, icon, cel, bits);
		if ( bits[1+1*3] == 1 )  return false;
	}

	return true;  // pas d'obstacle
}

// Indique si une cellule contient un sol.
// Est utilis� pour savoir si blupi peut aller sur une cellule
// en tenant compte uniquement des sols.
// Retourne true si blupi peut y aller !

bool CDecor::IsFreeCelFloor(POINT cel, int rank)
{
	int			icon;
	int			bits[9];

	if ( !IsValid(cel) )  return false;

	icon = m_decor[cel.x/2][cel.y/2].floorIcon;
	if ( icon != -1 )
	{
		SearchFloor(rank, icon, cel, bits);
		AjustFloor(rank, icon, cel, bits);
		if ( bits[1+1*3] == 1 )  return false;
	}

	return true;  // pas d'obstacle
}

// Indique si une cellule est libre.
// Est utilis� pour savoir si blupi peut venir ici
// d�barquer en bateau ou monter dans sa jeep.

bool CDecor::IsFreeCelGo(POINT cel, int rank)
{
	bool		bOK;
	POINT		limit;
	int			action, channel, icon;

	if ( rank == -1 )  return IsFreeCel(cel, rank);

	GetObject(cel, channel, icon);

	// Refuse d'aller dans la maison si blupi porte qq chose.
	if ( m_blupi[rank].takeChannel != -1 &&  // porte qq chose ?
		 channel == CHOBJECT &&
		 icon == 113 )  // maison ?
	{
		return false;
	}

	// Refuse d'aller dans le laboratoire (on peut seulement
	// y transformer qq chose).
	if ( channel == CHOBJECT &&
		 (icon ==  28 ||  // laboratoire ?
		  icon == 120 ||  // usine ?
		  icon == 122) )  // mine de fer ?
	{
		return false;
	}

	bOK = IsFreeCel(cel, rank);
	if ( bOK )  return true;

	bOK = IsFreeCelEmbarque(cel, rank, action, limit);
	if ( bOK )  return true;

	bOK = IsFreeCelDebarque(cel, rank, action, limit);
	if ( bOK )  return true;

	if ( !m_blupi[rank].bMalade &&
		 m_blupi[rank].vehicule == 0 &&  // � pied ?
		 m_blupi[rank].perso != 8 &&  // pas le disciple ?
		 channel == CHOBJECT &&
		 icon == 118 )  // jeep ?
	{
		return true;
	}

	if ( !m_blupi[rank].bMalade &&
		 m_blupi[rank].vehicule == 0 &&  // � pied ?
		 m_blupi[rank].perso != 8 &&  // pas le disciple ?
		 m_blupi[rank].energy > MAXENERGY/4 &&  // fort ?
		 m_blupi[rank].takeChannel == -1 &&  // porte rien ?
		 channel == CHOBJECT &&
		 icon == 16 )  // armure ?
	{
		return true;
	}

	return false;
}

// Indique si on peut faire qq chose sur une cellule.
// Est utilis� pour savoir comment est la mise en �vidence (hili)
// � cet endroit.

bool CDecor::IsFreeCelHili(POINT cel, int rank)
{
	bool		bOK;
	POINT		limit;
	int			workBlupi, channel, icon, action;

	if ( IsValid(cel) )
	{
		workBlupi = m_decor[cel.x/2][cel.y/2].workBlupi;
		if ( workBlupi >= 0 && workBlupi != rank )  return false;

		channel = m_decor[cel.x/2][cel.y/2].objectChannel;
		icon    = m_decor[cel.x/2][cel.y/2].objectIcon;

		if ( channel == CHOBJECT &&
			 (icon == 12 ||                    // fus�e ?
			  (icon >=  20 && icon <=  26) ||  // mur ?
			  (icon >= 106 && icon <= 112) ||  // barri�re ?
			  (icon >=  99 && icon <= 105) ||  // batiment ennemi ?
			  (icon >= 115 && icon <= 116) ||  // idem ?
			  (icon >=  17 && icon <=  18)) )  // idem ?
		{
			return false;
		}
	}

	if ( rank == -1 )  return IsFreeCelFloor(cel, rank);

	bOK = IsFreeCelFloor(cel, rank);
	if ( bOK )  return true;

	bOK = IsFreeCelEmbarque(cel, rank, action, limit);
	if ( bOK )  return true;

	bOK = IsFreeCelDebarque(cel, rank, action, limit);
	if ( bOK )  return true;

	return false;
}

// Indique si une cellule est libre.
// Est utilis� pour savoir si blupi peut venir ici.

bool CDecor::IsFreeCel(POINT cel, int rank)
{
	int			icon, workBlupi;
	int			bits[9];

	if ( !IsValid(cel) )  return false;

	if ( m_decor[cel.x/2][cel.y/2].fire > 0 &&
		 m_decor[cel.x/2][cel.y/2].fire < MoveMaxFire() )  return false;

	// Cellule bloqu�e (un blupi travaille ici) ?
	if ( rank != -1 && m_blupi[rank].perso != 3 )  // pas tracks ?
	{
		workBlupi = m_decor[cel.x/2][cel.y/2].workBlupi;
		if ( workBlupi >= 0 && workBlupi != rank )  return false;
	}

	icon = m_decor[cel.x/2][cel.y/2].floorIcon;
	SearchFloor(rank, icon, cel, bits);
	AjustFloor(rank, icon, cel, bits);
	if ( bits[1+1*3] == 1 )  return false;

	icon = m_decor[cel.x/2][cel.y/2].objectIcon;
	SearchObject(rank, icon, cel, bits);
	AjustObject(rank, icon, cel, bits);
	if ( bits[1+1*3] == 1 )  return false;

	return true;  // pas d'obstacle
}

// Indique si blupi peut d�poser un objet ici.

bool CDecor::IsFreeCelDepose(POINT cel, int rank)
{
	int		icon;

	if ( !IsFreeCel(cel, rank) )  return false;

	icon = m_decor[cel.x/2][cel.y/2].objectIcon;
	if ( icon == 10000 || icon == 10001 ||  // �clairs entre tours ?
		 icon == 18 )  // dalle glissante ?
	{
		return false;
	}

	icon = m_decor[cel.x/2][cel.y/2].floorIcon;
	if ( icon == 80 )  // t�l�porteur ?
	{
		return false;
	}

	return true;
}

// Indique s'il est possible d'embarquer ici.
// Le point retourn� dans "limit" indique jusqu'o� il est
// possible de marcher normalement (sans passe muraille).

bool CDecor::IsFreeCelEmbarque(POINT cel, int rank,
							   int &action, POINT &limit)
{
	bool		bOK;
	int			channel, icon;

	// Impossible si blupi n'est pas � pied,
	// ou s'il s'agit d'un disciple.
	if ( rank == -1 || m_blupi[rank].vehicule != 0 ||
		 m_blupi[rank].perso == 8 )  return false;

	// A-t-on cliqu� sur un bateau ?
	if ( cel.x%2 != 1 || cel.y%2 != 1 )  return false;
	GetObject(cel, channel, icon);
	if ( channel != CHOBJECT || icon != 117 )  return false;

	GetFloor(cel, channel, icon);
	if ( channel == CHFLOOR && icon == 2 )
	{
		m_blupi[rank].vehicule = 1;
		bOK = IsFreeCel(GetCel(cel,+1,0), rank);  // libre (en bateau) ?
		m_blupi[rank].vehicule = 0;
		if ( bOK )
		{
			limit = GetCel(cel,-2,0);
			action = WM_ACTION_BATEAUDE;
			return true;
		}
	}

	GetFloor(cel, channel, icon);
	if ( channel == CHFLOOR && icon == 3 )
	{
		m_blupi[rank].vehicule = 1;
		bOK = IsFreeCel(GetCel(cel,0,+1), rank);  // libre (en bateau) ?
		m_blupi[rank].vehicule = 0;
		if ( bOK )
		{
			limit = GetCel(cel,0,-2);
			action = WM_ACTION_BATEAUDS;
			return true;
		}
	}

	GetFloor(cel, channel, icon);
	if ( channel == CHFLOOR && icon == 4 )
	{
		m_blupi[rank].vehicule = 1;
		bOK = IsFreeCel(GetCel(cel,-1,0), rank);  // libre (en bateau) ?
		m_blupi[rank].vehicule = 0;
		if ( bOK )
		{
			limit = GetCel(cel,+1,0);
			action = WM_ACTION_BATEAUDO;
			return true;
		}
	}

	GetFloor(cel, channel, icon);
	if ( channel == CHFLOOR && icon == 5 )
	{
		m_blupi[rank].vehicule = 1;
		bOK = IsFreeCel(GetCel(cel,0,-1), rank);  // libre (en bateau) ?
		m_blupi[rank].vehicule = 0;
		if ( bOK )
		{
			limit = GetCel(cel,0,+1);
			action = WM_ACTION_BATEAUDN;
			return true;
		}
	}

	return false;
}

// Indique s'il est possible de d�barquer ici.
// Le point retourn� dans "limit" indique jusqu'o� il est
// possible de naviguer normalement (sans passe muraille).

bool CDecor::IsFreeCelDebarque(POINT cel, int rank,
							   int &action, POINT &limit)
{
	bool		bOK;
	int			channel1, icon1;
	int			channel2, icon2;

	// Impossible si blupi n'est pas en bateau.
	if ( rank == -1 || m_blupi[rank].vehicule != 1 )  return false;

	m_blupi[rank].vehicule = 0;
	bOK = IsFreeCel(cel, rank);  // libre (� pied) ?
	m_blupi[rank].vehicule = 1;
	if ( !bOK )  return false;

	GetFloor(GetCel(cel,+2,0), channel1, icon1);
	GetObject(GetCel(cel,+2,0), channel2, icon2);
	if ( channel1 == CHFLOOR && icon1 == 2 &&  // rive ?
		 channel2 == -1 && icon2 == -1 &&  // pas de bateau amarr� ?
		 cel.x%2 == 1 && cel.y%2 == 1 )
	{
		limit = GetCel(cel,+3,0);
		action = WM_ACTION_BATEAUAE;
		return true;
	}

	GetFloor(GetCel(cel,0,+2), channel1, icon1);
	GetObject(GetCel(cel,0,+2), channel2, icon2);
	if ( channel1 == CHFLOOR && icon1 == 3 &&  // rive ?
		 channel2 == -1 && icon2 == -1 &&  // pas de bateau amarr� ?
		 cel.x%2 == 1 && cel.y%2 == 1 )
	{
		limit = GetCel(cel,0,+3);
		action = WM_ACTION_BATEAUAS;
		return true;
	}

	GetFloor(GetCel(cel,-2,0), channel1, icon1);
	GetObject(GetCel(cel,-2,0), channel2, icon2);
	if ( channel1 == CHFLOOR && icon1 == 4 &&  // rive ?
		 channel2 == -1 && icon2 == -1 &&  // pas de bateau amarr� ?
		 cel.x%2 == 0 && cel.y%2 == 1 )
	{
		limit = GetCel(cel,-2,0);
		action = WM_ACTION_BATEAUAO;
		return true;
	}

	GetFloor(GetCel(cel,0,-2), channel1, icon1);
	GetObject(GetCel(cel,0,-2), channel2, icon2);
	if ( channel1 == CHFLOOR && icon1 == 5 &&  // rive ?
		 channel2 == -1 && icon2 == -1 &&  // pas de bateau amarr� ?
		 cel.x%2 == 1 && cel.y%2 == 0 )
	{
		limit = GetCel(cel,0,-2);
		action = WM_ACTION_BATEAUAN;
		return true;
	}

	return false;
}

// Indique s'il est possible de sauter dans une direction.

bool CDecor::IsFreeJump(POINT cel, int direct, int rank, int &action)
{
	POINT		depart, vector;
	int			i, icon;
	int			bits[3*3];

	// Refuse de sauter si blupi n'est pas � pied !
	if ( m_blupi[rank].vehicule != 0 )  return false;

	// Refuse de sauter dans les directions se, so, no, ne.
	if ( (direct/16)%2 != 0 )  return false;

	// Refuse de sauter si peu d'�nergie ou si porte qq chose.
	if ( m_blupi[rank].perso != 0 ||
		 m_blupi[rank].energy <= MAXENERGY/4 ||
		 m_blupi[rank].takeChannel != -1 )  return false;

	vector = GetVector(direct);
	depart = cel;

	i = 0;
	while ( true )
	{
		cel.x += vector.x;
		cel.y += vector.y;

		if ( i == 4 )  break;
		if ( IsFreeCelFloor(cel, rank) )  break;
		i ++;
	}
	if ( i == 0 )  return false;

	// D�part possible par-rapport aux obstacles ?
	icon = m_decor[depart.x/2][depart.y/2].objectIcon;
	SearchObject(rank, icon, depart, bits);
	AjustObject(rank, icon, depart, bits);
	if ( bits[(1+vector.x)+(1+vector.y)*3] == 1 )  return false;

	// Arriv�e possible par-rapport aux obstacles ?
	icon = m_decor[cel.x/2][cel.y/2].objectIcon;
	SearchObject(rank, icon, cel, bits);
	AjustObject(rank, icon, cel, bits);
	if ( bits[(1-vector.x)+(1-vector.y)*3] == 1 )  return false;

	if ( !IsFreeCel(cel, rank) ||
		  IsBlupiHere(cel, true) )  return false;

	action = ACTION_SAUTE2+(i-1);
	return true;
}

// Indique s'il est possible de glisser dans une direction.

bool CDecor::IsFreeGlisse(POINT cel, int direct, int rank, int &action)
{
	int			channel, icon;

	// Y'a que blupi qui glisse !
	if ( m_blupi[rank].perso != 0 )  return false;

	GetFloor(GetCel((cel.x/2)*2,(cel.y/2)*2), channel, icon);
	if ( channel != CHFLOOR || icon != 18 )  // pas dalle glissante ?
	{
		return false;
	}

	if ( !IsFreeDirect(cel, direct, rank) )  return false;

	action = ACTION_GLISSE;
	return true;
}


// Cherche la meilleure direction pour atteindre un but.
// Retourne -1 si on est d�j� sur le but.

int CDecor::DirectSearch(POINT cel, POINT goal)
{
	POINT		dir;
	int			direct, tan;

	dir.x = goal.x - cel.x;
	dir.y = goal.y - cel.y;

	if ( dir.x == 0 && dir.y == 0 )  // but atteint ?
	{
		return -1;
	}

#if 0
	if ( dir.x > 0 )
	{
		if ( dir.y >  0 )  direct = DIRECT_SE;
		if ( dir.y == 0 )  direct = DIRECT_E;
		if ( dir.y <  0 )  direct = DIRECT_NE;
	}

	if ( dir.x == 0 )
	{
		if ( dir.y >  0 )  direct = DIRECT_S;
		else               direct = DIRECT_N;
	}

	if ( dir.x < 0 )
	{
		if ( dir.y >  0 )  direct = DIRECT_SO;
		if ( dir.y == 0 )  direct = DIRECT_O;
		if ( dir.y <  0 )  direct = DIRECT_NO;
	}
#endif

	// Cherche le huiti�me de cadrant correspondant �
	// la direction.
	//  41 = 100*tan(22.5)
	// 241 = 100*tan(67.5)
	if ( dir.x == 0 )
	{
		if ( dir.y > 0 )  direct = DIRECT_S;
		else              direct = DIRECT_N;
	}
	else
	{
		tan = abs(100*dir.y/dir.x);  // calcule la tangente*100

		if ( dir.x > 0 )
		{
			if ( dir.y > 0 )
			{
				direct = DIRECT_SE;
				if ( tan <  41 )  direct = DIRECT_E;
				if ( tan > 241 )  direct = DIRECT_S;
			}
			else
			{
				direct = DIRECT_NE;
				if ( tan <  41 )  direct = DIRECT_E;
				if ( tan > 241 )  direct = DIRECT_N;
			}
		}
		else
		{
			if ( dir.y > 0 )
			{
				direct = DIRECT_SO;
				if ( tan <  41 )  direct = DIRECT_O;
				if ( tan > 241 )  direct = DIRECT_S;
			}
			else
			{
				direct = DIRECT_NO;
				if ( tan <  41 )  direct = DIRECT_O;
				if ( tan > 241 )  direct = DIRECT_N;
			}
		}
	}

	return direct;
}


// Vide les positions d�j� essay�es.

void CDecor::FlushUsed(int rank)
{
	m_blupi[rank].nbUsed = 0;
	m_blupi[rank].nextRankUsed = 0;
}

// Ajoute une position d�j� �t� essay�e.

void CDecor::AddUsedPos(int rank, POINT pos)
{
	int		i, j, old;

	// Un virus est b�te.
	if ( m_blupi[rank].perso == 2 )  return;

	// D�j� dans la liste ?
	for ( i=0 ; i<m_blupi[rank].nbUsed ; i++ )
	{
		if ( pos.x == m_blupi[rank].posUsed[i].x &&
			 pos.y == m_blupi[rank].posUsed[i].y )
		{
			m_blupi[rank].rankUsed[i] = m_blupi[rank].nextRankUsed;
			m_blupi[rank].nextRankUsed ++;
			return;
		}
	}

	// Si la liste est pleine, remplace le plus vieux point.
	if ( m_blupi[rank].nbUsed >= MAXUSED )
	{
		old = 10000;
		j = 0;
		for ( i=0 ; i<m_blupi[rank].nbUsed ; i++ )
		{
			if ( m_blupi[rank].rankUsed[i] < old )
			{
				old = m_blupi[rank].rankUsed[i];
				j = i;
			}
		}
		m_blupi[rank].posUsed[j] = pos;
		m_blupi[rank].rankUsed[j] = m_blupi[rank].nextRankUsed;
		m_blupi[rank].nextRankUsed ++;
		return;
	}

	// Ajoute � la suite de la liste.
	i = m_blupi[rank].nbUsed;

	m_blupi[rank].posUsed[i] = pos;
	m_blupi[rank].rankUsed[i] = m_blupi[rank].nextRankUsed;
	m_blupi[rank].nbUsed ++;
	m_blupi[rank].nextRankUsed ++;
	return;
}

// Cherche si une position a d�j� �t� essay�e.

bool CDecor::IsUsedPos(int rank, POINT pos)
{
	int		i;

	for ( i=0 ; i<m_blupi[rank].nbUsed ; i++ )
	{
		if ( pos.x == m_blupi[rank].posUsed[i].x &&
			 pos.y == m_blupi[rank].posUsed[i].y )  return true;
	}

	return false;
}


// Cherche la meilleure direction pour atteindre un but.

bool CDecor::SearchBestBase(int rank, int &action, POINT &newCel, int &direct)
{
	int			searchDirect[8] = {0,1,7,2,6,5,3,4};
	int			tryDirect, workBlupi, i, a;
	POINT		cel, vector;
	bool		bFree;

	cel    = m_blupi[rank].cel;
	direct = DirectSearch(cel, m_blupi[rank].goalCel);

	AddUsedPos(rank, cel);

	for ( i=0 ; i<8 ; i++ )
	{
		tryDirect = ((direct/16+searchDirect[i])%8)*16;

		vector = GetVector(tryDirect);

		bFree = IsFreeGlisse(cel, tryDirect, rank, action);

		if ( !bFree )
		{
			bFree = IsFreeDirect(cel, tryDirect, rank);
			action = ACTION_MARCHE;
		}

		if ( !bFree )
		{
			bFree = IsFreeJump(cel, tryDirect, rank, action);
		}

		a = GetAmplitude(action);

		// Blupi peut aller sur le lieu de la construction.
		if ( m_blupi[rank].passCel.x != -1 )
		{
			newCel = m_blupi[rank].passCel;
			workBlupi = m_decor[newCel.x/2][newCel.y/2].workBlupi;

			if ( m_blupi[rank].passCel.x/2 == (cel.x+vector.x*a)/2 &&
				 m_blupi[rank].passCel.y/2 == (cel.y+vector.y*a)/2 &&
				 (workBlupi < 0 || workBlupi == rank) )
			{
				bFree = true;
			}
		}

		if ( bFree )
		{
			newCel.x = cel.x + vector.x*a;
			newCel.y = cel.y + vector.y*a;

			if ( !IsUsedPos(rank, newCel) )
			{
				if ( m_blupi[rank].perso == 3 )   // tracks ?
				{
					// Le tracks peut aller sur les blupi
					// pour les �craser !
					if ( IsTracksHere(newCel, false) )
					{
						continue;
					}
					else
					{
						AddUsedPos(rank, newCel);
						direct = tryDirect;
						return true;
					}
				}
				else
				{
					if ( IsBlupiHere(newCel, false) )
					{
						// Si blupi immobile, comme si obstacle qq.
						if ( m_blupi[m_blupiHere].goalCel.x == -1 )  continue;
						newCel = cel;
						action = ACTION_STOP;
						direct = tryDirect;
						return true;
					}
					else
					{
						AddUsedPos(rank, newCel);
						direct = tryDirect;
						return true;
					}
				}
			}
		}
	}

	return false;
}

// Cherche la meilleure direction pour atteindre un but.

bool CDecor::SearchBestPass(int rank, int &action)
{
	Blupi		iBlupi;
	int			i, j, direct;
	POINT		iCel, lCel, cel;

	if ( m_blupi[rank].perso == 0 ||   // blupi ?
		 m_blupi[rank].perso == 7 ||   // �lectro ?
		 m_blupi[rank].perso == 8 ||   // disciple ?
		 (m_blupi[rank].perso == 4 &&  // robot ?
		  m_term.bHachRobot ) )        // robot sur dalles hachur�es ?
	{
		if ( m_blupi[rank].busyDelay > 0 )
		{
			m_blupi[rank].busyDelay --;
			if ( m_blupi[rank].busyDelay == 0 &&
				 m_blupi[rank].busyCount > 0 )
			{
				m_blupi[rank].busyCount --;
			}
			return false;
		}
		if ( CheminCherche(rank, action) )  // recherche fut�e selon DD ...
		{
			return true;
		}
		else
		{
			// Si la destination est occup�e pendant une r�p�tition,
			// il faut attendre � l'infini !
			if ( m_blupi[rank].repeatLevel != -1 &&
				 IsBlupiHereEx(m_blupi[rank].goalCel, rank, false) )
			{
				m_blupi[rank].busyCount ++;
			}
			m_blupi[rank].busyDelay = Random(8,12);  // d�lai avant r�essai
			return false;
		}
	}

	for ( j=0 ; j<7 ; j++ )
	{
		iBlupi = m_blupi[rank];  // sauvegarde blupi

		// Essaye 7 coups en avance, pour voir.
		iCel = m_blupi[rank].cel;
		i = 0;
		while ( true )
		{
			if ( !SearchBestBase(rank, action, cel, direct) )  break;
			if ( action == ACTION_STOP )  // collision avec autre blupi ?
			{
				if ( i == 0 )
				{
					m_blupi[rank] = iBlupi;  // restitue blupi
					return false;
				}
				i = 7;  // comme si ok pour 7 coups
				break;
			}
			m_blupi[rank].cel = cel;
			lCel = cel;

			// Est-on revenu juste � c�t� de la position
			// de d�part ? Si oui, simplifie le mouvement.
			if ( i > 1 &&
				 abs(m_blupi[rank].cel.x-iCel.x) <= 1 &&
				 abs(m_blupi[rank].cel.y-iCel.y) <= 1 )
			{
				direct = DirectSearch(iCel, cel);
				if ( IsFreeDirect(iCel, direct, rank) )
				{
					m_blupi[rank].cel = iCel;
					m_blupi[rank].sDirect = direct;
					action = ACTION_MARCHE;
					return true;
				}
			}

			// A-t-on atteint le but ?
			if ( cel.x == m_blupi[rank].goalCel.x &&
				 cel.y == m_blupi[rank].goalCel.y )
			{
				i = 7;  // comme si ok pour 7 coups
				break;
			}

			i ++;
			if ( i >= 7 )  break;
		}

		m_blupi[rank] = iBlupi;  // restitue blupi

		if ( i == 0 )  return false;

		if ( i == 7 )
		{
			SearchBestBase(rank, action, cel, direct);
			m_blupi[rank].sDirect = direct;
			return true;
		}

		AddUsedPos(rank, lCel);  // bloque position ridicule
	}

	return false;
}


// V�rifie si un objet est utilisable pour travailler dessus.
// Le sol doit permettre d'aller aux 4 coins, et il ne doit
// pas y avoir un autre blupi que soi-m�me.

bool CDecor::IsWorkableObject(POINT cel, int rank)
{
	if ( !IsFreeCelFloor(GetCel(cel,0,0), -1) ||
		 !IsFreeCelFloor(GetCel(cel,1,0), -1) ||
		 !IsFreeCelFloor(GetCel(cel,0,1), -1) ||
		 !IsFreeCelFloor(GetCel(cel,1,1), -1) )  return false;

	if ( IsBlupiHereEx(GetCel(cel,0,0), rank, false) ||
		 IsBlupiHereEx(GetCel(cel,1,0), rank, false) ||
		 IsBlupiHereEx(GetCel(cel,0,1), rank, false) ||
		 IsBlupiHereEx(GetCel(cel,1,1), rank, false) )  return false;

	if ( m_decor[cel.x/2][cel.y/2].fire > 0 &&
		 m_decor[cel.x/2][cel.y/2].fire < MoveMaxFire() )  return false;

	return true;
}


// Cherche un autre objet pour continuer une action
// (comme par exemple abatre des arbres).

bool CDecor::SearchOtherObject(int rank, POINT initCel, int action,
							   int distMax, int channel,
							   int firstIcon1, int lastIcon1,
							   int firstIcon2, int lastIcon2,
							   POINT &foundCel, int &foundIcon)
{
	int		startx, starty, endx, endy;
	int		x, y, xx, yy;
	int		dist, min = distMax;
	POINT	cel;
	bool	bOK;

	if ( firstIcon1 == 33 && lastIcon1 == 48 &&
		 firstIcon2 == 71 && lastIcon2 == 71 )  // cherche du fer ?
	{
		return SearchOtherDrapeau(rank, initCel, distMax,
								  foundCel, foundIcon);
	}

	initCel.x = (initCel.x/2)*2;
	initCel.y = (initCel.y/2)*2;

	startx = ((initCel.x-distMax/2)/2)*2;
	endx   = ((initCel.x+distMax/2)/2)*2;
	starty = ((initCel.y-distMax/2)/2)*2;
	endy   = ((initCel.y+distMax/2)/2)*2;

	if ( startx < 0       )  startx = 0;
	if ( endx   > MAXCELX )  endx   = MAXCELX;
	if ( starty < 0       )  starty = 0;
	if ( endy   > MAXCELY )  endy   = MAXCELY;

	if ( firstIcon2 == -1 && lastIcon2 == -1 )
	{
		firstIcon2 = 22222;
		lastIcon2  = 22222;
	}

	for ( y=starty ; y<endy ; y+=2 )
	{
		for ( x=startx ; x<endx ; x+=2 )
		{
			bOK = false;

			if ( channel == CHFLOOR )
			{
				if ( m_decor[x/2][y/2].floorChannel == channel &&
					((m_decor[x/2][y/2].floorIcon >= firstIcon1 &&
					  m_decor[x/2][y/2].floorIcon <= lastIcon1 )||
					 (m_decor[x/2][y/2].floorIcon >= firstIcon2 &&
					  m_decor[x/2][y/2].floorIcon <= lastIcon2 ))&&
					 m_decor[x/2][y/2].objectChannel == -1 )  bOK = true;
			}
			else
			{
				if ( m_decor[x/2][y/2].objectChannel == channel &&
					((m_decor[x/2][y/2].objectIcon >= firstIcon1 &&
					  m_decor[x/2][y/2].objectIcon <= lastIcon1 )||
					 (m_decor[x/2][y/2].objectIcon >= firstIcon2 &&
					  m_decor[x/2][y/2].objectIcon <= lastIcon2 )) ) bOK = true;
			}

			if ( bOK )
			{
				cel.x = x;
				cel.y = y;
				if ( BlupiIsGoalUsed(cel) )  continue;

				if ( action == WM_ACTION_ABAT1    ||
					 action == WM_ACTION_BUILD1   ||
					 action == WM_ACTION_BUILD2   ||
					 action == WM_ACTION_BUILD3   ||
					 action == WM_ACTION_BUILD4   ||
					 action == WM_ACTION_BUILD5   ||
					 action == WM_ACTION_BUILD6   ||
					 action == WM_ACTION_ROC1     ||
					 action == WM_ACTION_MUR      ||
					 action == WM_ACTION_PONTE    ||
					 action == WM_ACTION_TOUR     ||
					 action == WM_ACTION_BATEAUE  ||
					 action == WM_ACTION_CULTIVE2 ||
					 action == WM_ACTION_DRAPEAU2 ||
					 action == WM_ACTION_DEPOSE   )
				{
					if ( !IsWorkableObject(cel, rank) )  continue;
				}

				dist = abs(initCel.x-x) + abs(initCel.y-y);
				if ( dist <= min )
				{
					min = dist;
					xx = x;
					yy = y;
				}
			}
		}
	}

	if ( min == distMax )  return false;

	foundCel.x = xx;
	foundCel.y = yy;

	if ( channel == CHFLOOR )
	{
		foundIcon = m_decor[xx/2][yy/2].floorIcon;
	}
	else
	{
		foundIcon = m_decor[xx/2][yy/2].objectIcon;
	}

	return true;
}

// Cherche un autre sol pouvant contenir du fer, pour y
// planter un drapeau.

bool CDecor::SearchOtherDrapeau(int rank, POINT initCel, int distMax,
								POINT &foundCel, int &foundIcon)
{
	int		startx, starty, endx, endy, icon;
	int		x, y;
	int		dist, min = distMax;
	POINT	cel;

	startx = ((initCel.x-distMax/2)/2)*2;
	endx   = ((initCel.x+distMax/2)/2)*2;
	starty = ((initCel.y-distMax/2)/2)*2;
	endy   = ((initCel.y+distMax/2)/2)*2;

	if ( startx < 0       )  startx = 0;
	if ( endx   > MAXCELX )  endx   = MAXCELX;
	if ( starty < 0       )  starty = 0;
	if ( endy   > MAXCELY )  endy   = MAXCELY;

	for ( y=starty ; y<endy ; y+=2 )
	{
		for ( x=startx ; x<endx ; x+=2 )
		{
			icon = m_decor[x/2][y/2].floorIcon;

			if ( m_decor[x/2][y/2].objectIcon == -1 &&
				 ((icon >= 33 && icon <= 48) ||  // terre ?
				  icon == 71 ) &&
				  !TestDrapeau(GetCel(x,y)) )  // pas encore sond� ?
			{
				cel.x = x;
				cel.y = y;
				if ( BlupiIsGoalUsed(cel) )  continue;
				if ( !IsWorkableObject(cel, rank) )  continue;

				dist = abs(initCel.x-x) + abs(initCel.y-y);
				if ( dist <= min )
				{
					min = dist;
					foundCel.x = x;
					foundCel.y = y;
					foundIcon = icon;
				}
			}
		}
	}

	if ( min == distMax )  return false;
	return true;
}

// Cherche un autre sol permettant de d�poser du bois
// pour construire un bateau.

bool CDecor::SearchOtherBateau(int rank, POINT initCel, int distMax,
							   POINT &foundCel, int &foundIcon)
{
	int		startx, starty, endx, endy;
	int		x, y, direct;
	int		dist, min = distMax;

	startx = ((initCel.x-distMax/2)/2)*2;
	endx   = ((initCel.x+distMax/2)/2)*2;
	starty = ((initCel.y-distMax/2)/2)*2;
	endy   = ((initCel.y+distMax/2)/2)*2;

	if ( startx < 0       )  startx = 0;
	if ( endx   > MAXCELX )  endx   = MAXCELX;
	if ( starty < 0       )  starty = 0;
	if ( endy   > MAXCELY )  endy   = MAXCELY;

	for ( y=starty ; y<endy ; y+=2 )
	{
		for ( x=startx ; x<endx ; x+=2 )
		{
			if ( !IsBuildBateau(GetCel(x,y), direct) )  continue;

			dist = abs(initCel.x-x) + abs(initCel.y-y);
			if ( dist <= min )
			{
				min = dist;
				foundCel.x = x;
				foundCel.y = y;
				foundIcon = m_decor[x/2][y/2].floorIcon;
			}
		}
	}

	if ( min == distMax )  return false;
	return true;
}


// V�rifie si l'objet peut �tre d�truit par l'araign�e.

bool CDecor::IsSpiderObject(int icon)
{
	return ( icon == 60 ||   // tomates ?
			 icon == 92 ||   // poison ?
			 icon == 93 );   // pi�ge ?
}

// Cherche un autre objet pour l'araign�e.

bool CDecor::SearchSpiderObject(int rank, POINT initCel, int distMax,
								POINT &foundCel, int &foundIcon)
{
	int		startx, starty, endx, endy;
	int		x, y;
	int		dist, min = distMax;
	POINT	cel;

	startx = ((initCel.x-distMax/2)/2)*2;
	endx   = ((initCel.x+distMax/2)/2)*2;
	starty = ((initCel.y-distMax/2)/2)*2;
	endy   = ((initCel.y+distMax/2)/2)*2;

	if ( startx < 0       )  startx = 0;
	if ( endx   > MAXCELX )  endx   = MAXCELX;
	if ( starty < 0       )  starty = 0;
	if ( endy   > MAXCELY )  endy   = MAXCELY;

	for ( y=starty ; y<endy ; y+=2 )
	{
		for ( x=startx ; x<endx ; x+=2 )
		{
			if ( IsSpiderObject(m_decor[x/2][y/2].objectIcon) )
			{
				cel.x = x;
				cel.y = y;
				if ( IsBlupiHere(cel, false) )  continue;

				dist = abs(initCel.x-x) + abs(initCel.y-y);

				if ( m_decor[x/2][y/2].objectIcon == 93 &&  //pi�ge ?
					 dist > 4 )  continue;  // si pi�ge loin -> ignore

				if ( dist <= min )
				{
					min = dist;
					foundCel.x = x+1;
					foundCel.y = y+1;  // +1 -> sur l'objet
					foundIcon = m_decor[x/2][y/2].objectIcon;
				}
			}
		}
	}

	if ( min == distMax )  return false;

	return true;
}


// V�rifie si l'objet peut �tre d�truit par le tracks.

bool CDecor::IsTracksObject(int icon)
{
	return ( icon ==  36 ||		// planches ?
			 icon ==  44 ||		// pierres ?
			 icon ==  60 ||		// tomates ?
			 icon ==  63 ||		// oeufs ?
			 icon ==  80 ||		// bouteille ?
			 icon ==  85 ||		// dynamite ?
			 icon ==  92 ||		// poison ?
			 icon ==  93 ||		// pi�ge ?
			 icon == 123 ||		// pi�ge ?
			 icon == 125 ||		// mine ?
			 icon == 127 ||		// mine ?
			 (icon >= 81 && icon <= 84) ||   // fleurs ?
			 (icon >= 94 && icon <= 95) );  // fleurs ?
}

// Cherche un autre objet pour le tracks.

bool CDecor::SearchTracksObject(int rank, POINT initCel, int distMax,
								POINT &foundCel, int &foundIcon)
{
	int		startx, starty, endx, endy, icon;
	int		x, y;
	int		dist, min = distMax;
//?	POINT	cel;

	startx = ((initCel.x-distMax/2)/2)*2;
	endx   = ((initCel.x+distMax/2)/2)*2;
	starty = ((initCel.y-distMax/2)/2)*2;
	endy   = ((initCel.y+distMax/2)/2)*2;

	if ( startx < 0       )  startx = 0;
	if ( endx   > MAXCELX )  endx   = MAXCELX;
	if ( starty < 0       )  starty = 0;
	if ( endy   > MAXCELY )  endy   = MAXCELY;

	for ( y=starty ; y<endy ; y+=2 )
	{
		for ( x=startx ; x<endx ; x+=2 )
		{
			if ( IsTracksObject(m_decor[x/2][y/2].objectIcon) )
			{
//?				cel.x = x;
//?				cel.y = y;
//?				if ( BlupiIsGoalUsed(cel) )  continue;
//?				if ( IsBlupiHere(cel, false) )  continue;

				dist = abs(initCel.x-x) + abs(initCel.y-y);
				if ( dist <= min )
				{
					min = dist;
					foundCel.x = x+1;
					foundCel.y = y+1;  // +1 -> sur l'objet
					foundIcon = m_decor[x/2][y/2].objectIcon;
				}
			}
		}
	}

	// Le tracks peut �craser blupi.
	for ( rank=0 ; rank<MAXBLUPI ; rank++ )
	{
		if ( m_blupi[rank].bExist &&
			 m_blupi[rank].perso == 0 &&  // blupi ?
			 m_blupi[rank].vehicule == 0 )  // � pied ?
		{
//?			if ( BlupiIsGoalUsed(m_blupi[rank].cel) )  continue;

			x = m_blupi[rank].cel.x;
			y = m_blupi[rank].cel.y;

			icon = m_decor[x/2][y/2].objectIcon;
			if ( icon == 113 ||                 // maison ?
				 icon ==  28 || icon ==  29 ||  // laboratoire ?
				 icon == 119 || icon == 120 ||  // usine ?
				 icon == 121 || icon == 122 )   // mine de fer ?
			{
				continue;
			}

			dist = abs(initCel.x-x) + abs(initCel.y-y);
			if ( dist <= min )
			{
				min = dist;
				foundCel.x = x;
				foundCel.y = y;
				foundIcon = -1;  // blupi (pas un objet) !
			}
		}
	}

	if ( min == distMax )  return false;

	return true;
}


// V�rifie si l'objet peut �tre d�truit par le robot.

bool CDecor::IsRobotObject(int icon)
{
	return ( icon ==  85 ||  // dynamite ?
			 icon ==  93 ||  // pi�ge ?
			 icon == 125 ||  // mine ?
			 icon == 127 );  // mine ?
}

// Cherche une autre action pour le robot.
// C'est ici qu'est contenue l'IA du robot !

bool CDecor::SearchRobotObject(int rank, POINT initCel, int distMax,
							   POINT &foundCel, int &foundIcon,
							   int &foundAction)
{
	int		startx, starty, endx, endy;
	int		x, y;
	int		dist, maxUsine, min = distMax;
	int		nbUsine[10];
	int		nbPerso[10];
	int		i, r, d, dd, icon, index, nb;

	if ( m_term.bHachRobot )  // robot sur dalles hachur�es ?
	{
		foundAction = WM_ACTION_GO;
		return SearchOtherObject(rank, initCel, WM_ACTION_GO,
								 200, CHFLOOR,17,17,-1,-1,
								 foundCel, foundIcon);
	}

	initCel.x = (initCel.x/2)*2;
	initCel.y = (initCel.y/2)*2;  // b�timents tr�s espac�s !

	startx = ((initCel.x-distMax/2)/2)*2;
	endx   = ((initCel.x+distMax/2)/2)*2;
	starty = ((initCel.y-distMax/2)/2)*2;
	endy   = ((initCel.y+distMax/2)/2)*2;

	for ( i=0 ; i<10 ; i++ )
	{
		nbUsine[i] = 0;
	}

	if ( startx < 0       )  startx = 0;
	if ( endx   > MAXCELX )  endx   = MAXCELX;
	if ( starty < 0       )  starty = 0;
	if ( endy   > MAXCELY )  endy   = MAXCELY;

	for ( y=starty ; y<endy ; y+=2 )
	{
		for ( x=startx ; x<endx ; x+=2 )
		{
			icon = m_decor[x/2][y/2].objectIcon;

			if ( icon ==  99 )  nbUsine[0] ++;  // recharge ?
			if ( icon == 104 )  nbUsine[1] ++;  // usine tracks ?
			if ( icon == 100 )  nbUsine[2] ++;  // usine araign�e ?
			if ( icon == 102 )  nbUsine[3] ++;  // usine virus ?
			if ( icon == 115 )  nbUsine[4] ++;  // usine bombe ?
			if ( icon ==  17 )  nbUsine[5] ++;  // usine �lectro ?

			dist = abs(initCel.x-x) + abs(initCel.y-y);

			if ( IsRobotObject(icon) &&  // pi�ge/dynamite ?
				 dist <= 4 )             // tr�s proche ?
			{
				if ( dist <= min )
				{
					min = dist;
					foundCel.x = x+1;
					foundCel.y = y+1;  // +1 -> sur l'objet
					foundIcon = m_decor[x/2][y/2].objectIcon;
				}
			}
		}
	}

	if ( min < distMax )
	{
		foundAction = -1;  // robot passe tout pr�t d'un pi�ge/dynamite
		return true;
	}

	// Cherche l'usine la moins construite.
	min = 999;
	maxUsine = 0;
	index = 0;
	for ( i=0 ; i<6 ; i++ )
	{
		if ( nbUsine[i] < min )
		{
			min = nbUsine[i];
			index = i;
		}
		if ( nbUsine[i] > maxUsine )
		{
			maxUsine = nbUsine[i];
		}
	}

//?	if ( nbUsine[0] > 0 &&  // sation de recharge existe ?
//?		 m_blupi[rank].energy <= MAXENERGY/2 )  // peu de forces ?
//?	{
//?		index = 0;  // station de recharge
//?		goto search;
//?	}

	if ( min == 0 )  // encore une usine � construire ?
	{
		// Libre juste ici ?
		if ( IsUsineBuild(rank, initCel) )
		{
			foundCel = initCel;
			build:
			if ( index == 0 )  foundAction = WM_ACTION_R_BUILD1;  // recharge
			if ( index == 1 )  foundAction = WM_ACTION_R_BUILD4;  // tracks
			if ( index == 2 )  foundAction = WM_ACTION_R_BUILD2;  // araign�e
			if ( index == 3 )  foundAction = WM_ACTION_R_BUILD3;  // virus
			if ( index == 4 )  foundAction = WM_ACTION_R_BUILD5;  // bombe
			if ( index == 5 )  foundAction = WM_ACTION_R_BUILD6;  // �lectro
			return true;
		}
		// Cherche un emplacement libre.
		for ( d=1 ; d<distMax/6 ; d++ )
		{
			x = initCel.x + d*6;
			y = initCel.y - d*6;
			for ( i=0 ; i<4 ; i++ )  // 4 directions
			{
				for ( dd=0 ; dd<=d ; dd++ )
				{
					if ( i == 0 )  x -= 6;  // � gauche
					if ( i == 1 )  y += 6;  // descend
					if ( i == 2 )  x += 6;  // � droite
					if ( i == 3 )  y -= 6;  // monte

					if ( IsUsineBuild(rank, GetCel(x,y)) )
					{
						foundCel.x = x;
						foundCel.y = y;
						goto build;
					}
				}
			}
		}
	}

	// Cherche l'ennemi le moins r�pandu.
	for ( i=0 ; i<10 ; i++ )
	{
		nbPerso[i] = 0;
	}
	nb = 0;
	for ( r=0 ; r<MAXBLUPI ; r++ )
	{
		if ( m_blupi[r].bExist )
		{
			nb ++;
			if ( m_blupi[r].perso == 3 )  // tracks ?
			{
				nbPerso[0] += 1;
			}
			if ( m_blupi[r].perso == 1 )  // araign�e ?
			{
				nbPerso[1] += 1;
			}
			if ( m_blupi[r].perso == 2 )  // virus ?
			{
				nbPerso[2] += 1;
			}
			if ( m_blupi[r].perso == 5 )  // bombe ?
			{
				nbPerso[3] += 2;
			}
			if ( m_blupi[r].perso == 7 )  // �lectro ?
			{
				nbPerso[4] += 2;
			}
		}
	}
	if ( nb > MAXBLUPI-10 )  return false;  // rien si trop peupl� !
	// Cherche l'ennemi le moins r�pandu.
	min = 999;
	index = 0;
	for ( i=0 ; i<5 ; i++ )
	{
		if ( nbPerso[i] < min &&
			 nbUsine[i+1] != 0 )  // usine correspondante existe ?
		{
			min = nbPerso[i];
			index = i+1;
		}
	}
	if ( m_blupi[rank].energy <= MAXENERGY/2 )  // peu de forces ?
	{
		index = 0;  // station de recharge
	}
	if ( m_skill >= 1 )  maxUsine *= 2;  // 2 ennemis par batiment
	if ( min >= maxUsine )  // assez peupl� ?
	{
		index = 0;  // station de recharge
	}

	// Cherche l'usine pour fabriquer l'ennemi le moins r�dandu.
//?	search:
	min = distMax;
	for ( y=starty ; y<endy ; y+=2 )
	{
		for ( x=startx ; x<endx ; x+=2 )
		{
			icon = m_decor[x/2][y/2].objectIcon;

			if ( (index == 0 && icon ==  99) ||  // recharge ?
				 (index == 1 && icon == 104) ||  // tracks ?
				 (index == 2 && icon == 100) ||  // araign�e ?
				 (index == 3 && icon == 102) ||  // virus ?
				 (index == 4 && icon == 115) ||  // bombe ?
				 (index == 5 && icon ==  17) )   // �lectro ?
			{
				if ( IsUsineFree(rank, GetCel(x,y)) )
				{
					dist = abs(initCel.x-x) + abs(initCel.y-y);
					if ( dist <= min )
					{
						min = dist;
						foundCel.x = x;
						foundCel.y = y;  // dans l'usine
						foundIcon = icon;
					}
				}
			}
		}
	}
	if ( min < distMax )
	{
		if ( index == 0 )  foundAction = WM_ACTION_R_MAKE1;  // recharge
		if ( index == 1 )  foundAction = WM_ACTION_R_MAKE4;  // tracks
		if ( index == 2 )  foundAction = WM_ACTION_R_MAKE2;  // araign�e
		if ( index == 3 )  foundAction = WM_ACTION_R_MAKE3;  // virus
		if ( index == 4 )  foundAction = WM_ACTION_R_MAKE5;  // bombe
		if ( index == 5 )  foundAction = WM_ACTION_R_MAKE6;  // �lectro
		return true;
	}

	// Cherche l'usine la plus proche.
	min = distMax;
	for ( y=starty ; y<endy ; y+=2 )
	{
		for ( x=startx ; x<endx ; x+=2 )
		{
			icon = m_decor[x/2][y/2].objectIcon;

			if ( (icon == 100 && nbPerso[1] <= maxUsine) ||  // araign�e ?
				 (icon == 102 && nbPerso[2] <= maxUsine) ||  // virus ?
				 (icon == 104 && nbPerso[0] <= maxUsine) ||  // tracks ?
				 (icon == 115 && nbPerso[3] <= maxUsine) ||  // bombe ?
				 (icon ==  17 && nbPerso[4] <= maxUsine) )   // �lectro ?
			{
				if ( IsUsineFree(rank, GetCel(x,y)) )
				{
					dist = abs(initCel.x-x) + abs(initCel.y-y);
					if ( dist <= min )
					{
						min = dist;
						foundCel.x = x;
						foundCel.y = y;  // dans l'usine
						foundIcon = icon;
					}
				}
			}
		}
	}
	if ( min < distMax )
	{
		if ( foundIcon == 100 )  foundAction = WM_ACTION_R_MAKE2;  // araign�e
		if ( foundIcon == 102 )  foundAction = WM_ACTION_R_MAKE3;  // virus
		if ( foundIcon == 104 )  foundAction = WM_ACTION_R_MAKE4;  // tracks
		if ( foundIcon == 115 )  foundAction = WM_ACTION_R_MAKE5;  // bombe
		if ( foundIcon ==  17 )  foundAction = WM_ACTION_R_MAKE6;  // �lectro
		return true;
	}

	return false;
}

// Teste si un emplacement est ok pour b�tir une usine.

bool CDecor::IsUsineBuild(int rank, POINT cel)
{
	int		icon, channel;
	int		x, y;

	// Pas sur les dalles hachur�es !
	GetFloor(cel, channel, icon);
	if ( channel == CHFLOOR &&
		 (icon < 65 || icon > 67) )  return false;

	for ( x=-1 ; x<3 ; x++ )
	{
		for ( y=-1 ; y<3 ; y++ )
		{
			if ( !IsFreeCel(GetCel(cel,x,y), rank) ||
				 IsBlupiHereEx(GetCel(cel,x,y), rank, false) )
			{
				return false;
			}
		}
	}

	return true;
}

// Teste s'il est possible d'entrer dans une usine.
// L'usine doit �tre libre devant (lieu de stationnement
// pour l'ennemi qui sera construit).

bool CDecor::IsUsineFree(int rank, POINT cel)
{
	int		channel, icon;

	GetObject(cel, channel, icon);

	if ( channel == CHOBJECT && icon == 115 )  // usine � bombes ?
	{
		return ( !IsBlupiHereEx(GetCel(cel,0,1), rank, false) &&
				 !IsBlupiHereEx(GetCel(cel,1,1), rank, false) &&
				 !IsBlupiHereEx(GetCel(cel,2,1), rank, false) &&
				 !IsBlupiHereEx(GetCel(cel,3,1), rank, false) );
	}

	return ( !IsBlupiHereEx(GetCel(cel,0,1), rank, false) &&
			 !IsBlupiHereEx(GetCel(cel,1,1), rank, false) &&
			 !IsBlupiHereEx(GetCel(cel,2,0), rank, false) &&
			 !IsBlupiHereEx(GetCel(cel,2,1), rank, false) &&
			 (!IsBlupiHereEx(GetCel(cel,3,0), rank, false)||
			  !IsBlupiHereEx(GetCel(cel,3,1), rank, false)) );
}


// V�rifie si l'objet peut �tre d�truit par une bombe.

bool CDecor::IsBombeObject(int icon)
{
	return ( icon == 36 ||		// planches ?
			 icon == 61 ||		// cabane ?
			 icon == 121 || icon == 122 ||	// mine de fer ?
			 (icon >= 65 && icon <= 71) ||  // palissade ?
			 icon == 93 ||		// pi�ge ?
			 icon == 117 );		// bateau ?
}

// Cherche un autre objet pour une bombe.

bool CDecor::SearchBombeObject(int rank, POINT initCel, int distMax,
							   POINT &foundCel, int &foundIcon)
{
	int		startx, starty, endx, endy;
	int		x, y;
	int		dist, min = distMax;
	POINT	cel;

	startx = ((initCel.x-distMax/2)/2)*2;
	endx   = ((initCel.x+distMax/2)/2)*2;
	starty = ((initCel.y-distMax/2)/2)*2;
	endy   = ((initCel.y+distMax/2)/2)*2;

	if ( startx < 0       )  startx = 0;
	if ( endx   > MAXCELX )  endx   = MAXCELX;
	if ( starty < 0       )  starty = 0;
	if ( endy   > MAXCELY )  endy   = MAXCELY;

	for ( y=starty ; y<endy ; y+=2 )
	{
		for ( x=startx ; x<endx ; x+=2 )
		{
			if ( IsBombeObject(m_decor[x/2][y/2].objectIcon) )
			{
				cel.x = x;
				cel.y = y;
				if ( IsBlupiHere(cel, false) )  continue;

				dist = abs(initCel.x-x) + abs(initCel.y-y);

				if ( m_decor[x/2][y/2].objectIcon == 93 &&  //pi�ge ?
					 dist > 8 )  continue;  // si pi�ge loin -> ignore

				if ( dist <= min )
				{
					min = dist;
					foundCel.x = x+1;
					foundCel.y = y+1;  // +1 -> sur l'objet
					foundIcon = m_decor[x/2][y/2].objectIcon;
				}
			}
		}
	}

	if ( min == distMax )  return false;

	return true;
}

// Cherche un autre objet pour un �lectro.

bool CDecor::SearchElectroObject(int rank, POINT initCel, int distMax,
								 POINT &foundCel, int &foundIcon)
{
	int		startx, starty, endx, endy;
	int		x, y, i, d, dd, r;
	int		dist, min = distMax;
	POINT	cel;

	startx = ((initCel.x-10/2)/2)*2;
	endx   = ((initCel.x+10/2)/2)*2;
	starty = ((initCel.y-10/2)/2)*2;
	endy   = ((initCel.y+10/2)/2)*2;

	if ( startx < 0       )  startx = 0;
	if ( endx   > MAXCELX )  endx   = MAXCELX;
	if ( starty < 0       )  starty = 0;
	if ( endy   > MAXCELY )  endy   = MAXCELY;

	for ( y=starty ; y<endy ; y+=2 )
	{
		for ( x=startx ; x<endx ; x+=2 )
		{
			if ( m_decor[x/2][y/2].objectIcon == 93 )  // pi�ge ?
			{
				cel.x = x;
				cel.y = y;
				if ( IsBlupiHere(cel, false) )  continue;

				dist = abs(initCel.x-x) + abs(initCel.y-y);

				if ( dist <= 4 )
				{
					min = dist;
					foundCel.x = x+1;
					foundCel.y = y+1;  // +1 -> sur l'objet
					foundIcon = m_decor[x/2][y/2].objectIcon;
				}
			}
		}
	}
	if ( min <= 4 )  return true;

	min = distMax;
	for ( r=0 ; r<MAXBLUPI ; r++ )
	{
		if ( m_blupi[r].bExist &&
			 m_blupi[r].perso == 0 &&  // blupi ?
			 m_blupi[r].goalAction != WM_ACTION_ELECTRO )
		{
//?			if ( BlupiIsGoalUsed(m_blupi[r].cel) )  continue;

			x = m_blupi[r].cel.x;
			y = m_blupi[r].cel.y;
			dist = abs(initCel.x-x) + abs(initCel.y-y);
			if ( dist <= distMax/2 && dist <= min )
			{
				min = dist;
				foundCel.x = x;
				foundCel.y = y;
				foundIcon = -1;  // blupi (pas un objet) !
			}
		}
	}
	if ( min == distMax )  return false;

	// Cherche un emplacement libre.
	for ( d=1 ; d<distMax/2 ; d++ )
	{
		x = foundCel.x + d;
		y = foundCel.y - d;
		for ( i=0 ; i<4 ; i++ )  // 4 directions
		{
			for ( dd=0 ; dd<=d ; dd++ )
			{
				if ( i == 0 )  x -= 1;  // � gauche
				if ( i == 1 )  y += 1;  // descend
				if ( i == 2 )  x += 1;  // � droite
				if ( i == 3 )  y -= 1;  // monte

				if ( IsFreeCel(GetCel(x,y), rank) &&
					 !IsBlupiHereEx(GetCel(x,y), rank, false) )
				{
					foundCel.x = x;
					foundCel.y = y;
					return true;
				}
			}
		}
	}

	return false;
}


// Teste si une position est tr�s proche du feu.
// Si oui, retourne true.

bool CDecor::IsFireCel(POINT cel)
{
	int			x, y;
	POINT		test;

	cel.x = (cel.x/2)*2;
	cel.y = (cel.y/2)*2;

	for ( x=-2 ; x<3 ; x+=2 )
	{
		for ( y=-2 ; y<3 ; y+=2 )
		{
			test.x = cel.x + x;
			test.y = cel.y + y;

			if ( !IsValid(test) )  continue;

			if ( m_decor[test.x/2][test.y/2].fire > 0 &&
				 m_decor[test.x/2][test.y/2].fire < MoveMaxFire() )  return true;
		}
	}

	return false;
}

// Teste si une position est tr�s proche d'un virus.
// Si oui, retourne true.

bool CDecor::IsVirusCel(POINT cel)
{
	int		rank;

	for ( rank=0 ; rank<MAXBLUPI ; rank++ )
	{
		if ( m_blupi[rank].bExist &&
			 m_blupi[rank].perso == 2 )  // virus ?
		{
			if ( cel.x >= m_blupi[rank].cel.x-1 &&
				 cel.x <= m_blupi[rank].cel.x+1 &&
				 cel.y >= m_blupi[rank].cel.y-1 &&
				 cel.y <= m_blupi[rank].cel.y+1 )  return true;
		}
	}

	return false;
}


// Regarde s'il est possible de construire un pont � partir
// d'une cellule donn�e (cel).
// Retourne 0 si c'est possible, ou une erreur autrement !

int CDecor::IsBuildPont(POINT &cel, int &iconBuild)
{
	POINT	vector, test;
	int		i, channel, icon, p1, p2, p3, r1, r2, nb, rest;
	int		error = ERROR_MISC;

	for ( i=0 ; i<4 ; i++ )
	{
		vector.x = 0;
		vector.y = 0;

		GetFloor(GetCel(cel,+2,0), channel, icon);
		if ( i == 0 &&
			 channel == CHFLOOR &&
			 (icon == 2 || icon == 59) )  // rivage ?
		{
			vector.x = +1;
			vector.y = 0;
			p1 = 59;
			p2 = 60;
			p3 = 61;
			r1 = 2;
			r2 = 4;
		}

		GetFloor(GetCel(cel,-2,0), channel, icon);
		if ( i == 1 &&
			 channel == CHFLOOR &&
			 (icon == 4 || icon == 61) )  // rivage ?
		{
			vector.x = -1;
			vector.y = 0;
			p1 = 61;
			p2 = 60;
			p3 = 59;
			r1 = 4;
			r2 = 2;
		}

		GetFloor(GetCel(cel,0,+2), channel, icon);
		if ( i == 2 &&
			 channel == CHFLOOR &&
			 (icon == 3 || icon == 62) )  // rivage ?
		{
			vector.x = 0;
			vector.y = +1;
			p1 = 62;
			p2 = 63;
			p3 = 64;
			r1 = 3;
			r2 = 5;
		}

		GetFloor(GetCel(cel,0,-2), channel, icon);
		if ( i == 3 &&
			 channel == CHFLOOR &&
			 (icon == 5 || icon == 64) )  // rivage ?
		{
			vector.x = 0;
			vector.y = -1;
			p1 = 64;
			p2 = 63;
			p3 = 62;
			r1 = 5;
			r2 = 3;
		}

		if ( vector.x == 0 && vector.y == 0 )  continue;

		// Avance tant que le pont existe.
		test = cel;
		nb = 0;
		do
		{
			test.x += vector.x*2;
			test.y += vector.y*2;
			if ( test.x < 0 || test.x >= MAXCELX ||
				 test.y < 0 || test.y >= MAXCELY )  break;

			if ( !GetFloor(test, channel, icon) )  continue;
			nb ++;
		}
		while ( icon == p1 || icon == p2 );
		test.x -= vector.x*2;
		test.y -= vector.y*2;

		if ( icon == p3 )
		{
			error = ERROR_PONTTERM;
			continue;
		}

		if ( nb == 1 )  iconBuild = p1;
		else            iconBuild = p2;

		// Avance jusqu'� la rive oppos�e.
		rest = 0;
		do
		{
			test.x += vector.x*2;
			test.y += vector.y*2;
			if ( test.x < 0 || test.x >= MAXCELX ||
				 test.y < 0 || test.y >= MAXCELY )  break;

			if ( !GetFloor(test, channel, icon) )  continue;
			rest ++;
		}
		while ( icon == r1 || icon == 14 );

		if ( icon == r2 && rest == 1 )  iconBuild = p3;

		if ( icon != r2 && icon != p2 && icon != p3 )
		{
			error = ERROR_PONTOP;
			continue;
		}

		cel.x += vector.x*2*nb;
		cel.y += vector.y*2*nb;

		return 0;  // ok
	}

	return error;
}

// Regarde s'il est possible de construire un bateau � partir
// d'une cellule donn�e (cel).

bool CDecor::IsBuildBateau(POINT cel, int &direct)
{
	int		fChannel, fIcon;
	int		oChannel, oIcon;

	GetFloor (GetCel(cel,+2,0), fChannel, fIcon);
	GetObject(GetCel(cel,+2,0), oChannel, oIcon);
	if ( fChannel == CHFLOOR && fIcon == 2  &&  // rivage ?
		 oChannel == -1      && oIcon == -1 )
	{
		direct = DIRECT_E;
		return true;
	}

	GetFloor (GetCel(cel,-2,0), fChannel, fIcon);
	GetObject(GetCel(cel,-2,0), oChannel, oIcon);
	if ( fChannel == CHFLOOR && fIcon == 4  &&  // rivage ?
		 oChannel == -1      && oIcon == -1 )
	{
		direct = DIRECT_O;
		return true;
	}

	GetFloor (GetCel(cel,0,+2), fChannel, fIcon);
	GetObject(GetCel(cel,0,+2), oChannel, oIcon);
	if ( fChannel == CHFLOOR && fIcon == 3  &&  // rivage ?
		 oChannel == -1      && oIcon == -1 )
	{
		direct = DIRECT_S;
		return true;
	}

	GetFloor (GetCel(cel,0,-2), fChannel, fIcon);
	GetObject(GetCel(cel,0,-2), oChannel, oIcon);
	if ( fChannel == CHFLOOR && fIcon == 5  &&  // rivage ?
		 oChannel == -1      && oIcon == -1 )
	{
		direct = DIRECT_N;
		return true;
	}

	direct = -1;
	return false;
}


// Vide toutes les positions visit�es.

void CDecor::InitDrapeau()
{
	int		i;

	for ( i=0 ; i<MAXLASTDRAPEAU ; i++ )
	{
		m_lastDrapeau[i].x = -1;
		m_lastDrapeau[i].y = -1;
	}
}

// M�morise une cellule visit�e (ne contenant pas de fer).

void CDecor::AddDrapeau(POINT cel)
{
	int		i;

	if ( TestDrapeau(cel) )  return;  // d�j� dans la liste

	for ( i=MAXLASTDRAPEAU-1 ; i>0 ; i-- )
	{
		m_lastDrapeau[i] = m_lastDrapeau[i-1];
	}

	m_lastDrapeau[0] = cel;
}

// Supprime une cellule visit�e (ne contenant pas de fer).

void CDecor::SubDrapeau(POINT cel)
{
	int		i;

	for ( i=0 ; i<MAXLASTDRAPEAU ; i++ )
	{
		if ( cel.x == m_lastDrapeau[i].x &&
			 cel.y == m_lastDrapeau[i].y )
		{
			m_lastDrapeau[i].x = -1;
			m_lastDrapeau[i].y = -1;
		}
	}
}

// Teste si une cellule a d�j� �t� visit�e.

bool CDecor::TestDrapeau(POINT cel)
{
	int		i;

	for ( i=0 ; i<MAXLASTDRAPEAU ; i++ )
	{
		if ( cel.x == m_lastDrapeau[i].x &&
			 cel.y == m_lastDrapeau[i].y )  return true;
	}

	return false;
}

