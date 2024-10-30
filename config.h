/* See LICENSE file for copyright and license details. */

#define TERMINAL	"st"
#define TERMCLASS	"St"

/* appearance */
static unsigned int borderpx  = 1;        /* border pixel of windows */
static unsigned int snap      = 32;       /* snap pixel */
static int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static int showbar            = 1;        /* 0 means no standard bar */
static int topbar             = 1;        /* 0 means standard bar at bottom */
static int extrabar           = 1;        /* 0 means no extra bar */
static char statussep         = ';';      /* separator between statuses */
static char font[]          = { "monospace:size=10" };
static char dmenufont[]       = "monospace:size=10";
static unsigned int baralpha        = 0xE6;
static unsigned int borderalpha     = OPAQUE;
static const char *fonts[]          = { font, "NotoColorEmoji:size=10:antialias=true:autohint=true" };
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#005577";
static const char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",    NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "Firefox", NULL,     NULL,           1 << 8,    0,          0,          -1,        -1 },
	{ "St",      NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ NULL,      NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;    /* number of clients in master area */
static int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbordercolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "st", NULL };

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
		{ "font",               STRING,  &font },
		{ "dmenufont",          STRING,  &dmenufont },
		{ "color0",					STRING,  &normbgcolor },
		{ "color0",					STRING,  &normbordercolor },
		{ "color7",					STRING,  &normfgcolor },
		{ "color7",					STRING,  &selbgcolor },
		{ "color8",					STRING,  &selbordercolor },
		{ "color0",					STRING,  &selfgcolor },
		{ "borderpx",          	INTEGER, &borderpx },
		{ "snap",          		INTEGER, &snap },
		{ "showbar",          	INTEGER, &showbar },
		{ "topbar",          	INTEGER, &topbar },
		{ "nmaster",          	INTEGER, &nmaster },
		{ "resizehints",       	INTEGER, &resizehints },
		{ "mfact",      	 	FLOAT,   &mfact },
};

static Key keys[] = {
	/* modifier								key				function				argument */
	{ MODKEY,								XK_Return,		spawn,				{ .v = termcmd } },
	{ MODKEY|ShiftMask,					XK_Return,		spawn,				SHCMD("samedir") },
	{ MODKEY,								XK_r,				spawn,				SHCMD("sb-refresh") },
	{ MODKEY,								XK_p,				spawn,				SHCMD("passmenu") },
	{ MODKEY,								XK_q,				killclient,			{0} },
	{ MODKEY,								XK_d,				spawn,				{.v = dmenucmd } },
	{ MODKEY,								XK_n,				spawn,				SHCMD(TERMINAL" -e newsboat") },
	{ MODKEY,								XK_b,				spawn,				SHCMD("$BROWSER") },
	{ MODKEY|ShiftMask,					XK_b,				spawn,				SHCMD(TERMINAL" -e bookmarkthis") },
	{ MODKEY,								XK_Insert,		spawn,				SHCMD("bookmarkthis -i") },
	{ MODKEY,								XK_e,				spawn,				SHCMD("$EMAIL") },
	{ MODKEY,								XK_w,				spawn,				SHCMD(TERMINAL" -e sudo nmtui") },
	{ MODKEY,								XK_j,				focusstack,			{.i = +1 } },
	{ MODKEY,								XK_k,				focusstack,			{.i = -1 } },
	{ MODKEY,								XK_h,				setmfact,  			{.f = -0.05} },
	{ MODKEY,								XK_l,				setmfact,  			{.f = +0.05} },
	{ MODKEY|ShiftMask,					XK_h,				focusmon,			{.i = -1 } },
	{ MODKEY|ShiftMask,					XK_l,				focusmon,			{.i = +1 } },
	{ MODKEY|ShiftMask,					XK_u,				tagmon,				{.i = -1 } },
	{ MODKEY|ShiftMask,					XK_i,				tagmon,				{.i = +1 } },
	{ MODKEY,								XK_Tab,			view,      			{0} },
	{ MODKEY,								XK_t,				setlayout, 			{.v = &layouts[0]} },
	{ MODKEY,								XK_y,				setlayout, 			{.v = &layouts[1]} },
	{ MODKEY,								XK_u,				setlayout, 			{.v = &layouts[2]} },
	{ MODKEY,								XK_space,		zoom,					{0} },
	{ MODKEY|ShiftMask,					XK_space,		togglefloating,	{0} },
	{ MODKEY,								XK_BackSpace,	spawn,				SHCMD("sysact") },
	{ ShiftMask,							XK_Print,		spawn,				SHCMD("maimpick") },
	{ MODKEY,								XK_Print,		spawn,				SHCMD("dmenurecord") },
	{ MODKEY|ShiftMask,					XK_Print,		spawn,				SHCMD("dmenurecord kill") },
	{ MODKEY,								XK_grave,		spawn,				SHCMD("dmenuunicode") },
	{ MODKEY,								XK_minus,		spawn,				SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%-; kill -37 $(pidof dwmblocks)") },
	{ MODKEY,								XK_equal,		spawn,				SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%+; kill -37 $(pidof dwmblocks)") },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY,								XK_F3,	spawn,				SHCMD("displayselect") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkExBarLeftStatus,   0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkExBarMiddle,       0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkExBarRightStatus,  0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

