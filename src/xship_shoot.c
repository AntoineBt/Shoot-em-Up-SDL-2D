#include	"xship.h"
#include	"data.h"

#define		BULLET_SPD	650
#define		FREQ_FACT	1.1
#define		RECOIL		120.0

/*
x 0001  1 UP
x 0010  2 RIGHT
x 0100  4 DOWN
x 1000  8 LEFT

x 0011  3 UP   | RIGHT
x 1001  9 UP   | LEFT
x 0110  6 DOWN | RIGHT
x 1100 12 DOWN | LEFT

? 0101  5 DOWN  | UP
? 1010 10 LEFT | RIGHT
*/

static void	ammoUp(XShip* s, v2f* vp, v2f* vd, float* pan)
{
  vd->x += 0;
  vd->y += -BULLET_SPD;
  vp->x += (6 + SDLazy_GetCenterX(s->bases_sprite[SRF_SHIP_NO])) * (s->turret_shoot[0] ? 1 : -1);
  vp->y -= 33 + (s->turret_shoot[0] ?
		 SDLazy_GetCenterY(s->bases_sprite[SRF_SHIP_NE]) :
		 SDLazy_GetCenterY(s->bases_sprite[SRF_SHIP_NO]));
  ship_recoil((Ship*)s, RECOIL, SHIP_AXE_Y);
  *pan = s->turret_shoot[0] ? .5 : -.5;
}

static void	ammoRight(XShip* s, v2f* vp, v2f* vd, float* pan)
{
  vd->x += BULLET_SPD;
  vd->y += 0;
  vp->y += (6 + SDLazy_GetCenterY(s->bases_sprite[SRF_SHIP_NE])) * (s->turret_shoot[1] ? 1 : -1);
  vp->x += 33 - (s->turret_shoot[1] ?
		 SDLazy_GetCenterX(s->bases_sprite[SRF_SHIP_SE]) :
		 SDLazy_GetCenterX(s->bases_sprite[SRF_SHIP_NE]));
  ship_recoil((Ship*)s, -RECOIL, SHIP_AXE_X);
  *pan = .5;
}

static void	ammoDown(XShip* s, v2f* vp, v2f* vd, float* pan)
{
  vd->x += 0;
  vd->y += BULLET_SPD;
  vp->x += (6 + SDLazy_GetCenterX(s->bases_sprite[SRF_SHIP_SO])) * (s->turret_shoot[2] ? -1 : 1);
  vp->y += 33 + (s->turret_shoot[2] ?
		 SDLazy_GetCenterY(s->bases_sprite[SRF_SHIP_NO]) :
		 SDLazy_GetCenterY(s->bases_sprite[SRF_SHIP_NE]));
  ship_recoil((Ship*)s, -RECOIL, SHIP_AXE_Y);
  *pan = s->turret_shoot[2] ? -.5 : .5;
}

static void	ammoLeft(XShip* s, v2f* vp, v2f* vd, float* pan)
{
  vd->x += -BULLET_SPD;
  vd->y += 0;
  vp->y += (6 + SDLazy_GetCenterY(s->bases_sprite[SRF_SHIP_NO])) * (s->turret_shoot[3] ? -1 : 1);
  vp->x -= 33 + (s->turret_shoot[3] ?
		 SDLazy_GetCenterX(s->bases_sprite[SRF_SHIP_NO]) :
		 SDLazy_GetCenterX(s->bases_sprite[SRF_SHIP_SO]));
  ship_recoil((Ship*)s, RECOIL, SHIP_AXE_X);
  *pan = -.5;
}

static void	ammoUpRight(XShip* s, v2f* vp, v2f* vd, float* pan)
{
  vd->x +=  BULLET_SPD * 0.7071;
  vd->y += -BULLET_SPD * 0.7071;

  vp->y -= SDLazy_GetCenterY(s->bases_sprite[SRF_SHIP_NE]);
  vp->x -= SDLazy_GetCenterX(s->bases_sprite[SRF_SHIP_NE]);

  ship_recoil((Ship*)s, -RECOIL, SHIP_AXE_X);
  ship_recoil((Ship*)s, +RECOIL, SHIP_AXE_Y);

  *pan = .5;
}

static void	ammoUpLeft(XShip* s, v2f* vp, v2f* vd, float* pan)
{
  ammoUp(s, vp, vd, pan);
  ammoLeft(s, vp, vd, pan);
}

static void	ammoDownRight(XShip* s, v2f* vp, v2f* vd, float* pan)
{
  ammoDown(s, vp, vd, pan);
  ammoRight(s, vp, vd, pan);
}

static void	ammoDownLeft(XShip* s, v2f* vp, v2f* vd, float* pan)
{
  ammoDown(s, vp, vd, pan);
  ammoLeft(s, vp, vd, pan);
}

static void	null(){}

void		(*ammo[])() =
/*0     1       2          3            4         (5)   6              7     8         9           (10)  11    12         */
{ null, ammoUp, ammoRight, ammoUpRight, ammoDown, null, ammoDownRight, null, ammoLeft, ammoUpLeft, null, null, ammoDownLeft,
  null, null,   null };
/*13    14      15 */

static void	create_ammo(Data* d, XShip* p)
{
  Ammo		b;
  v2f		vd = {0, 0};
  v2f		vp = p->ship.pos;
  float		pan;

  ammo[p->ship.shoot_dir](p, &vp, &vd, &pan);
  b.type = AMMO_BULLET;
  b.from_who = (Ship*)p;
  b.duration_time = 1.;
  b.rad = 0.;
  b.pos = vp;
  b.dir = vd;
  ammo_push(d, &b);
  sound_play(SND_XHSIP_SHOOT, .8, pan, 60000 + rand() % 20000);
}

void            xship_shoot(Data* d, XShip* p)
{
  unsigned	u = 1, v = 0;

  for (; v < 4; ++v, u <<= 1)
    if (p->ship.shoot_dir & u &&
        SDLazy_GetTotalTime() > p->time_last_turret_shoot + p->ship.shoot_freq)
      {
	p->time_last_turret_shoot = SDLazy_GetTotalTime();
        p->turret_shoot[v] = !p->turret_shoot[v];
        p->ship.shoot_freq *= FREQ_FACT;
        SDLazy_AnimReplay(p->turret_anim[v * 2 + p->turret_shoot[v]]);
        create_ammo(d, p);
      }
}
