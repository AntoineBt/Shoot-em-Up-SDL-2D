#ifndef		SHMUPSDL2D_H
#define		SHMUPSDL2D_H

#include	"CList.h"
#include	"data_typedef.h"
#include	"sdldata.h"
#include	"xship.h"
#include	"controls.h"
#include	"menu.h"

struct		Data
{
  SDLData	sdldata;
  Menu		menu;
  Controls	ctrls;
  CList		ships;
  CList		ammos;
  Ship*		player;
};

void		data_init(Data*);

#endif
