#include "help.h"

#define IDHT_APPLICATION        100     /* id of HELP TABLE in resource file */

/* GLOBAL DATA */
HAB  hab;
HWND hwndHelp;
HELPTABLE ht = {IDHT_APPLICATION, NULL, 0};
CHAR szClassName[] = "Dummy"; /* window class name            */

/* PROTOTYPES */                         
MRESULT EXPENTRY DummyWndProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);

main( int argc, char *argv[], char *envp[] )
{
   HMQ  hmq;
   HWND hwnd;
   HWND hwndClient;
   QMSG qmsg;
   ULONG flStyle;
   HELPINIT helpinit;
   HWND hwndFrame;         /* handle to the frame                  */
   HMODULE hmod;
   CHAR szBuf[80];
 
   hab = WinInitialize( 0 );
   hmq = WinCreateMsgQueue( hab, 0 );

   flStyle = FCF_STANDARD & (~ (FCF_MENU | FCF_ICON | FCF_ACCELTABLE));
   WinRegisterClass(hab, szClassName, DummyWndProc, 0L, 0);
 
   hwndFrame = WinCreateStdWindow(HWND_DESKTOP,
         WS_VISIBLE,             /* frame-window style            */
         &flStyle,               /* window style                  */
         szClassName,            /* class name                    */
         "Click in window to get Help",    /* window title                  */
         0L,                     /* default client style          */
         NULLHANDLE,             /* resource in executable file   */
         IDHT_APPLICATION,           /* resource id                   */
         &hwndClient);           /* receives client window handle */
 
   /* Setup the help initialization structure */
   helpinit.cb = sizeof( HELPINIT );
   helpinit.ulReturnCode =  0L;
   helpinit.pszTutorialName =  (PSZ)NULL;
   /* Help table  */
   helpinit.phtHelpTable = &ht;
   helpinit.hmodHelpTableModule = NULLHANDLE;
   /* Default action bar and accelerators */
   helpinit.hmodAccelActionBarModule = NULLHANDLE;
   helpinit.idAccelTable = 0;
   helpinit.idActionBar = 0;
   helpinit.pszHelpWindowTitle = "Ddf Test";
   helpinit.fShowPanelId = CMIC_SHOW_PANEL_ID;
   helpinit.pszHelpLibraryName = "HELP.HLP";
   hwndHelp = WinCreateHelpInstance( hab, &helpinit );
   WinAssociateHelpInstance(hwndHelp, hwndFrame);
 
   /* get and dispatch messages from queue */
   while (WinGetMsg(hab, &qmsg, 0, 0, 0))
      WinDispatchMsg(hab, &qmsg);

   /* finish the cleanup and exit */
   WinAssociateHelpInstance(NULLHANDLE, hwndFrame);
   WinDestroyHelpInstance( hwndHelp );
   WinDestroyWindow( hwndFrame );
   WinDestroyMsgQueue( hmq );
   WinTerminate( hab );
}


MRESULT EXPENTRY DummyWndProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
   HWND hwndPanel;
   INT i;
   LONG lb;
   ULONG ul;
   PVOID pfn;
   CLASSINFO clsi;
   HPS hps;
   RECTL  rcl;             /* update region                        */
   USHORT id;
   CHAR sz[80];

   switch (msg) {

   case WM_PAINT:
      hps = WinBeginPaint(hwnd,   /* handle of the window      */
          NULLHANDLE,             /* get a cache presentation space */
          &rcl);                  /* receives update rectangle  */
      WinFillRect(hps, &rcl, CLR_GREEN);
      WinEndPaint(hps);
      return 0L;
      break;
   
   case WM_BUTTON1CLICK:
      /* bring up contents */
      WinSendMsg(hwndHelp, HM_HELP_CONTENTS, 0, 0);
      return (MRESULT) 0;

   case HM_QUERY_DDF_DATA:
      return (MRESULT) Ddf(HWNDFROMMP(mp1), LONGFROMMP(mp2));

   case HM_INFORM:
      sprintf(sz, "Inform message was received, ID = %u (SHORT2 = %u, "
            "MP2SHORT1 = %u, MP2SHORT2 = %u)",
            SHORT1FROMMP(mp1), SHORT2FROMMP(mp1),
            SHORT1FROMMP(mp2), SHORT2FROMMP(mp2));
      WinMessageBox(HWND_DESKTOP, hwnd, sz, "Inform", 0, MB_OK);
      return (MRESULT) 0;

   default:
      return WinDefWindowProc(hwnd, msg, mp1, mp2);

   } /* endswitch */
}

 
