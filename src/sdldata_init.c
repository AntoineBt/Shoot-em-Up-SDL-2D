#include	"sdldata.h"

static char const* spr = "img/sprites.png";

static void	load_bgs(SDLData* d)
{
  d->srf_bg[BG0] = SDLazy_SurfaceLoad("img/bg.jpg", NULL);
}

static void	load_ship(SDLData* d)
{
  d->srf_ship[SRF_SHIP_NO]	= SDLazy_SurfaceLoad(spr, SDLazy_Rect(20, 20, 23, 23));
  d->srf_ship[SRF_SHIP_NE]	= SDLazy_SurfaceLoad(spr, SDLazy_Rect(43, 20, 23, 23));
  d->srf_ship[SRF_SHIP_SO]	= SDLazy_SurfaceLoad(spr, SDLazy_Rect(20, 43, 23, 23));
  d->srf_ship[SRF_SHIP_SE]	= SDLazy_SurfaceLoad(spr, SDLazy_Rect(43, 43, 23, 23));

  SDLazy_SetCenterAlign(d->srf_ship[SRF_SHIP_NO], ALIGN_BOTTOM | ALIGN_RIGHT);
  SDLazy_SetCenterAlign(d->srf_ship[SRF_SHIP_NE], ALIGN_BOTTOM | ALIGN_LEFT);
  SDLazy_SetCenterAlign(d->srf_ship[SRF_SHIP_SO], ALIGN_TOP | ALIGN_RIGHT);
  SDLazy_SetCenterAlign(d->srf_ship[SRF_SHIP_SE], ALIGN_TOP | ALIGN_LEFT);

  d->srf_ship[SRF_SHIP_AN_TURRET]	= SDLazy_SurfaceLoad(spr, SDLazy_Rect(100, 70, 11, 10));
}

static void	load_ammo(SDLData* d)
{
  unsigned	u;

  d->srf_ammo[AMMO_BULLET]	= SDLazy_SurfaceLoad(spr, SDLazy_Rect(200, 30,  4, 4));
  d->srf_ammo[AMMO_ROCKET]	= SDLazy_SurfaceLoad(spr, SDLazy_Rect(200, 20, 14, 4));
  for (u = 0; u < NB_AMMOS; ++u)
    SDLazy_SetCenterAlign(d->srf_ammo[u], ALIGN_CENTER | ALIGN_CENTER);
}

void		sdldata_init(SDLData* d)
{
  d->cam.x = d->cam.y = 0;
  load_bgs(d);
  load_ship(d);
  load_ammo(d);
}