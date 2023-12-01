/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 12;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 0;     /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const char *fonts[]          = { "Hurmit Nerd Font Propo:size=12" };
static const char col_black[]       = "#282828";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#eedbad";
static const char col_gray4[]       = "#eeeeee";
static const char col_green[]       = "#9aa75c";
static const char col_red[]         = "#de0102";

// Scratchpad related variables
static const char sp_size[] 	    = "120x28";

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_black, col_gray2 },
	[SchemeSel]  = { col_green, col_black, col_green },
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;

const char *spcmd1[] = {"st", "-n", "spcmd1", "-g", sp_size, NULL }; //0
const char *spcmd2[] = {"st", "-n", "spcmd2", "-g", sp_size, NULL }; //1
const char *spcmd3[] = {"st", "-n", "spcmd3", "-g", sp_size, NULL }; //2
const char *file_manager[] = {"st", "-n", "ranger", "-g", sp_size, "-e", "ranger", NULL }; //3
const char *password_manager[] = {"keepassxc", NULL }; //4
const char *music_player[] = {"st", "-n", "ncmpcpp", "-g", sp_size, "-e", "ncmpcpp", NULL }; //5
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm1",     spcmd1},
	{"spterm2",     spcmd2},
	{"spterm3",     spcmd3},
	{"ranger",      file_manager},
	{"keepassxc",   password_manager},
	{"ncmpcpp",     music_player},
};

/* tagging */
static const char *tags[] = { "", "󰣇", "", "󰙯", ""}; //"", "", "" };
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",	  NULL,			NULL,		0,				1,			 -1 },
	{ "Firefox",  NULL,			NULL,		1 << 8,			0,			 -1 },
	{ NULL,		  "spcmd1",		NULL,		SPTAG(0),		1,			 -1 },
	{ NULL,		  "spcmd2",		NULL,		SPTAG(1),		1,			 -1 },
	{ NULL,		  "spcmd3",		NULL,		SPTAG(2),		1,			 -1 },
	{ NULL,		  "ranger",		NULL,		SPTAG(3),		1,			 -1 },
	{ NULL,		  "keepassxc",		NULL,		SPTAG(4),		1,			 -1 },
	{ NULL,		  "ncmpcpp",		NULL,		SPTAG(5),		1,			 -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */

static const char *dmenucmd[] = { "dmenu_run", "-fn", "Hurmit Nerd Font Propo-16", "-nb", "#282828", "-nf", "#c1b799", "-sb", "#a9b261", NULL };
static const char *termcmd[]  = { "st", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_r,      spawn,          {.v = dmenucmd } },
	{ MODKEY,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ControlMask,		XK_comma,  cyclelayout,    {.i = -1 } },
	{ MODKEY|ControlMask,           XK_period, cyclelayout,    {.i = +1 } },
	//{ MODKEY,                       XK_space,  setlayout,      {0} },
	//{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_End,      quit,           {0} },

	// Scratchpad section
	{ MODKEY,            			XK_a,  	   togglescratch,  {.ui = 0 } },
	{ MODKEY,            			XK_s,	   togglescratch,  {.ui = 1 } },
	{ MODKEY,            			XK_d,	   togglescratch,  {.ui = 2 } },
	{ MODKEY,            			XK_e,	   togglescratch,  {.ui = 3 } },
	{ MODKEY|ShiftMask,            		XK_k,	   togglescratch,  {.ui = 4 } },
	{ MODKEY,            			XK_m,	   togglescratch,  {.ui = 5 } },
	
	// Tag hotkeys section
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

