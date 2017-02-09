// Button.h

#pragma once

#include <vector>

/////////////////////////////////////////////////////////////////////////////

class CButton
{
public:
	CButton();
	~CButton();

	bool	Create(CPixmap *pPixmap, CSound *pSound,
				   POINT pos, int type, bool bMinimizeRedraw,
				   int *pMenu, int nbMenu,
				   const char **pToolTips,
				   int region, unsigned int message);
	void	Draw();
	void	Redraw();

	int		GetState();
	void	SetState(int state);

	int		GetMenu();
	void	SetMenu(int menu);

	bool	GetEnable();
	void	SetEnable(bool bEnable);

	bool	GetHide();
	void	SetHide(bool bHide);

	bool	TreatEvent(const SDL_Event &event);
	bool	MouseOnButton(POINT pos);
	const char *GetToolTips(POINT pos);

	
protected:
	bool	Detect(POINT pos);
	bool	MouseDown(POINT pos);
	bool	MouseMove(POINT pos);
	bool	MouseUp(POINT pos);

protected:
	CPixmap*	m_pPixmap;
	CDecor*		m_pDecor;
	CSound*		m_pSound;
	int			m_type;			// type de bouton
	bool		m_bEnable;		// true si bouton actif
	bool		m_bHide;		// true si bouton cach�
	unsigned int		m_message;		// message envoy� si bouton actionn�
	POINT		m_pos;			// coin sup/gauche
	POINT		m_dim;			// dimensions
	int			m_state;		// 0=rel�ch�, 1=press�, +2=survoll�
	int			m_mouseState;	// 0=rel�ch�, 1=press�, +2=survoll�
	int			m_iconMenu[20];	// ic�nes du sous-menu
	const char **m_toolTips;	// info-bulles
	int			m_nbMenu;		// nb de case du sous-menu
	int			m_nbToolTips;	// nb d'info-bulles
	int			m_selMenu;		// sous-menu s�lectionn�
	bool		m_bMouseDown;	// true -> bouton souris press�
	bool		m_bMinimizeRedraw;
	bool		m_bRedraw;		// true -> doit �tre redessin�
};

/////////////////////////////////////////////////////////////////////////////
