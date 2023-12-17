/* user functions */

#include "toggle.h"
void
tester(const Arg *arg)
{
}


void
FocusMonitor(const Arg *arg)
{
    Monitor *m;

    if (!mons->next) return;
    if ((m = dirtomon(arg->i)) == selmon) return;
    unfocus(selmon->sel, 0);
    selmon = m;
    focus(NULL);
}
void
FocusNextWindow(const Arg *arg) {
	Monitor *m;
	Client *c;
	m = selmon;
	c = m->sel;

	if (arg->i) {
		if (c->next)
			c = c->next;
		else
			c = m->clients;
	} else {
		Client *last = c;
		if (last == m->clients)
			last = NULL;
		for (c = m->clients; c->next != last; c = c->next);
	}; /* prevent 0 division errors */
	focus(c);
}

void
ChangeMasterWindow(const Arg *arg)
{
    selmon->nmaster = MAX(selmon->nmaster + arg->i, 0);
    arrange(selmon);
}

void
KillWindow(const Arg *arg)
{
    killclient(selmon->sel, GRACEFUL);
}
void
TerminateWindow(const Arg *arg)
{
    killclient(selmon->sel, SAFEDESTROY);
}
void
DragWindow(const Arg *arg) /* move mouse */
{
    int x, y, ocx, ocy, nx, ny;
    Client *c;
    Monitor *m;
    XEvent ev;
    Time lasttime;

    float frametime;

    c = selmon->sel;
    if (!c) return;
    if (c->isfullscreen) return; /* no support moving fullscreen windows by mouse */
    restack(selmon);
    if (!c->isfloating || selmon->lt[selmon->sellt]->arrange) ToggleFloating(NULL);
    if (XGrabPointer(dpy, root, False, MOUSEMASK, GrabModeAsync, GrabModeAsync,
                     None, cursor[CurMove]->cursor, CurrentTime) != GrabSuccess) return;
    if (!getrootptr(&x, &y)) return;
    frametime = 1000 / (cfg.windowrate + !cfg.windowrate); /* prevent 0 division errors */
    lasttime = 0;
    ocx = c->x;
    ocy = c->y;
    do {
        XMaskEvent(dpy, MOUSEMASK|ExposureMask|SubstructureRedirectMask, &ev);
        switch(ev.type) {
        case ConfigureRequest:
        case Expose:
        case MapRequest:
            handler[ev.type](&ev);
            break;
        case MotionNotify:
            if(cfg.windowrate != 0)
            {
                if ((ev.xmotion.time - lasttime) <= frametime) continue;
                lasttime = ev.xmotion.time;
            }
            nx = ocx + (ev.xmotion.x - x);
            ny = ocy + (ev.xmotion.y - y);
            if (abs(selmon->wx - nx) < cfg.snap)
                nx = selmon->wx;
            else if (abs((selmon->wx + selmon->ww) - (nx + WIDTH(c))) < cfg.snap)
                nx = selmon->wx + selmon->ww - WIDTH(c);
            if (abs(selmon->wy - ny) < cfg.snap)
                ny = selmon->wy;
            resize(c, nx, ny, c->w, c->h, 1);
            break;
        }
    } while (ev.type != ButtonRelease);
    if(dockablewindow(c))
    {
        /* workaround as setting c->isfloating c->ismax 0|1 doesnt work properly */
        c->ismax = 0;
        maximize(selmon->wx, selmon->wy, selmon->ww - 2 * cfg.borderpx, selmon->wh - 2 * cfg.borderpx);
        c->isfloating = 0;
        c->oldx+=cfg.snap;
        c->oldy+=cfg.snap;
    }
    else c->ismax = 0;
    XUngrabPointer(dpy, CurrentTime);
    if ((m = recttomon(c->x, c->y, c->w, c->h)) != selmon) {
        sendmon(c, m);
        selmon = m;
        focus(NULL);
    }
    restack(selmon);
}


void 
Restart(const Arg *arg)
{
    savesession();
    restart();
}
void
Quit(const Arg *arg)
{
    savesession();
    quit();
}

void
ResizeWindow(const Arg *arg) /* resizemouse */
{
    /* rcurx, rcury     old x/y Pos for root cursor
     * ocw/och          old client width/height
     * prev (w/h)       Previous iteration width/height
     * nw/nh            new width/height
     * ocx/ocy          old client posX/posY
     * nx/ny            new posX/posY
     * horiz/vert       check if top left/bottom left of screen
     * di,dui,dummy     holder vars to pass check (useless aside from check)
     * basew            Minimum client request size (wont go smaller)
     * baseh            See above
     * rszbase(w/h)     base window (w/h) when resizing assuming resize hints wasnt set / too small
     */
    int rcurx, rcury;
    int ocw, och;
    int prevw, prevh;
    int nw, nh;
    int ocx, ocy;
    int nx, ny;
    int horizcorner, vertcorner;
    int basew, baseh;
    float frametime;

    int di;
    unsigned int dui;
    Window dummy;

    Client *c;
    Monitor *m;
    XEvent ev;
    Time lasttime = 0;
    c = selmon->sel;

    /* client checks */
    if (!c || c->isfullscreen) return;/* no support resizing fullscreen windows by mouse */
    if (XGrabPointer(dpy, root, False, MOUSEMASK, GrabModeAsync, GrabModeAsync,
                     None, cursor[CurResize]->cursor, CurrentTime) != GrabSuccess) return;
    if (!XQueryPointer (dpy, c->win, &dummy, &dummy, &di, &di, &nx, &ny, &dui)) return;
    if(!getrootptr(&rcurx, &rcury)) return;
    if (!c->isfloating || selmon->lt[selmon->sellt]->arrange) ToggleFloating(NULL);
    restack(selmon);

    frametime = 1000 / (cfg.windowrate + !cfg.windowrate); /*prevent 0 division errors */
    ocw = c->w;
    och = c->h;
    ocx = c->x;
    ocy = c->y;

    horizcorner = nx < c->w >> 1;
    vertcorner  = ny < c->h >> 1;

    basew = MAX(c->basew, cfg.rszbasew);
    baseh = MAX(c->baseh, cfg.rszbaseh);
    do {
        XMaskEvent(dpy, MOUSEMASK|ExposureMask|SubstructureRedirectMask, &ev);
        switch(ev.type)
        {
        case ConfigureRequest:
        case Expose:
        case MapRequest: handler[ev.type](&ev); break;
        case MotionNotify:
            if(cfg.windowrate != 0)
            {
                if ((ev.xmotion.time - lasttime) <= frametime)
                    continue;
                lasttime = ev.xmotion.time;
            }
            nw = horizcorner ? MAX(ocw - (ev.xmotion.x - rcurx), basew) : MAX(ocw + (ev.xmotion.x - rcurx), basew);
            nh = vertcorner  ? MAX(och - (ev.xmotion.y - rcury), baseh) : MAX(och + (ev.xmotion.y - rcury), baseh);
            nx = horizcorner ? ocx + ocw - nw : c->x;
            ny = vertcorner  ? ocy + och - nh : c->y;

            resize(c, nx, ny, nw, nh, 1);
            break;
        }
    } while (ev.type != ButtonRelease);
    /* add if w + x > monx || w + x < 0 resize */
    if(c->w > c->mon->ww)
        MaximizeWindowHorizontal(NULL);
    if(c->h > c->mon->wh)
        MaximizeWindowVertical(NULL);
    if(dockablewindow(c))
    {
        c->isfloating = 0;
        c->ismax = 1;
        c->oldx+=cfg.snap;
        c->oldy+=cfg.snap;
    }
    else c->ismax = 0;

    XUngrabPointer(dpy, CurrentTime);
    while (XCheckMaskEvent(dpy, EnterWindowMask, &ev));
    if ((m = recttomon(c->x, c->y, c->w, c->h)) != selmon) {
        sendmon(c, m);
        selmon = m;
        focus(NULL);
    }
    restack(selmon);
}

void
SetWindowLayout(const Arg *arg)
{
    Monitor *m;
    m = selmon;

    if(!m) return;
    setclientlayout(m, arg->i);
    if (m->sel) arrange(m);
    else drawbar(m);
}

/* arg > 1.0 will set mfact absolutely */
void
SetMonitorFact(const Arg *arg)
{
    float f;

    if (!arg || !selmon->lt[selmon->sellt]->arrange) return;
    f = arg->f < 1.0 ? arg->f + selmon->mfact : arg->f - 1.0;
    if (f < 0.05 || f > 0.95) return;
    selmon->mfact = f;
    arrange(selmon);
}

void
SpawnWindow(const Arg *arg)
{
    if (fork() == 0) {
        if (dpy)
            close(ConnectionNumber(dpy));
        setsid();
        execvp(((char **)arg->v)[0], (char **)arg->v);
        die("FATAL ERROR: EXECVP '%s' FAILED:", ((char **)arg->v)[0]);
    }
}
void
MaximizeWindow(const Arg *arg) 
{
    maximize(selmon->wx, selmon->wy, selmon->ww - 2 * cfg.borderpx, selmon->wh - 2 * cfg.borderpx);
    selmon->sel->isfloating = 0;
}


void
MaximizeWindowVertical(const Arg *arg) {
    maximize(selmon->sel->x, selmon->wy, selmon->sel->w, selmon->wh - 2 * cfg.borderpx);
    selmon->sel->ismax = 0; /* no such thing as vertmax being fully maxed */
}

void
MaximizeWindowHorizontal(const Arg *arg) {
    maximize(selmon->wx, selmon->sel->y, selmon->ww - 2 * cfg.borderpx, selmon->sel->h);
    selmon->sel->ismax = 0; /* no such thing as horzmax being fully maxed */
}
void
AltTab(const Arg *arg)
{
    Monitor *m;
    Client *c;
    int grabbed;
    int listindex;
    struct timespec ts = { .tv_sec = 0, .tv_nsec = 1000000 };

    m = selmon;
    m->altsnext = NULL;
    m->altTabN = 0;
    m->nTabs = 0;
    grabbed = 0;
    listindex = 0;

    for(c = m->clients; c; c = c->next) m->nTabs += !!ISVISIBLE(c);
    if(!(m->nTabs > 0)) return;

    m->altsnext = (Client **) malloc(m->nTabs * sizeof(Client *));
    /* add clients to list */
    for(c = m->stack; c; c = c->snext) !!ISVISIBLE(c) ? m->altsnext[listindex++] = c : NULL;

    drawtab(m->nTabs, 1, m);
    for (int i = 0; i < 1000; i++) 
    {
        if (XGrabKeyboard(dpy, DefaultRootWindow(dpy), True, GrabModeAsync, GrabModeAsync, CurrentTime) == GrabSuccess)
        {
            grabbed = 1;
            break;
        }
        nanosleep(&ts, NULL);
    }
    XEvent event;
    alttab();

    while (grabbed) 
    {
        XNextEvent(dpy, &event);
        switch(event.type)
        {case KeyPress:   if(event.xkey.keycode == cfg.tabcyclekey) alttab();    break;
         case KeyRelease: if(event.xkey.keycode == cfg.tabmodkey)   grabbed = 0; break;
        }
    }

    alttabend(); /* end the alt-tab functionality */
    XUngrabKeyboard(dpy, CurrentTime);
}

void
TagWindow(const Arg *arg)
{
    if (selmon->sel && arg->ui & TAGMASK) 
    {
        selmon->sel->tags = arg->ui & TAGMASK;
        focus(NULL);
        arrange(selmon);
    }
}

void
TagMonitor(const Arg *arg)
{
    if (!selmon->sel || !mons->next) return;
    sendmon(selmon->sel, dirtomon(arg->i));
}

void
ToggleStatusBar(const Arg *arg)
{
    selmon->showbar = !selmon->showbar;
    updatebarpos(selmon);
    XMoveResizeWindow(dpy, selmon->barwin, selmon->wx, selmon->by, selmon->ww, bh);
    arrange(selmon);
}

void
ToggleFloating(const Arg *arg)
{
    Client *c; 
    int togglefloat;

    c = selmon->sel;
    togglefloat = 0;
    if (!c) return;
    if (c->isfullscreen) return; /* no support for fullscreen windows */
    togglefloat = !selmon->sel->isfloating || selmon->sel->isfixed;
    if(togglefloat)
    {
        c->isfloating = togglefloat;
        resize(c, c->x, c->y, c->w, c->h, 0);
    }
    arrange(selmon);
}

void
ToggleFullscreen(const Arg *arg)
{
    Client *c;
    Monitor *m;
    int winmode; /* if fullscreen or not */

    m = selmon;
    if(!m->sel) return; /* no client focused */
    m->isfullscreen = !m->isfullscreen;
    winmode = m->isfullscreen;
    for (c = m->clients; c; c = c->next)
    {
        if(!ISVISIBLE(c)) continue;
        setfullscreen(c, winmode);
    }
    focus(m->sel);
    restack(m);
}

void
ToggleTag(const Arg *arg)
{
    unsigned int newtags;

    if (!selmon->sel) return;
    newtags = selmon->sel->tags ^ (arg->ui & TAGMASK);
    if (newtags) {
        selmon->sel->tags = newtags;
        focus(NULL);
        arrange(selmon);
    }
}

void
ToggleView(const Arg *arg)
{
    unsigned int newtagset = selmon->tagset[selmon->seltags] ^ (arg->ui & TAGMASK);

    if (newtagset) {
        selmon->tagset[selmon->seltags] = newtagset;
        focus(NULL);
        arrange(selmon);
    }
}

void
View(const Arg *arg)
{
    if ((arg->ui & TAGMASK) == selmon->tagset[selmon->seltags]) return;
    selmon->seltags ^= 1; /* toggle sel tagset */
    if (arg->ui & TAGMASK)
        selmon->tagset[selmon->seltags] = arg->ui & TAGMASK;
    focus(NULL);
    arrange(selmon);
}

void
Zoom(const Arg *arg)
{
    Client *c = selmon->sel;

    if (!selmon->lt[selmon->sellt]->arrange || !c || c->isfloating) return;
    if (c == nexttiled(selmon->clients) && !(c = nexttiled(c->next))) return;
    pop(c);
}
