#include <stdlib.h>
#include <malloc.h>
#include "help.h"

/* MACROS */
#define PFROMOFF(pBase, off) (PVOID)((PBYTE)(pBase) + (off))

/* PROTOTYPES */
void ShowErrorInfo(HWND hwnd);


/* Ddf(): called to process HM_QUERY_DDF_DATA message */
/* returns ahandle to the Ddf instance (or NULLHANDLE) */
HDDF Ddf(HWND hwndPage, LONG id)
{
   HWND hwndPageFrame, hwndCoverpage, hwndInstance;
   HDDF hddf;
   CHAR szDdf[300];
   LONG i;
   APIRET rc;
   PERRINFO perri;

   hwndPageFrame = WinQueryWindow(hwndPage, QW_PARENT);  /* page frame */
   hwndCoverpage = WinQueryWindow(hwndPageFrame, QW_PARENT);  /* coverpage */
   hwndInstance = (HWND)WinSendMsg(hwndCoverpage, HM_QUERY,
         MPFROM2SHORT(0, HMQW_INSTANCE), NULL);

   hddf = DdfInitialize(
                   hwndInstance,  /* Handle of help instance */
                   0L,            /* Default buffer size     */
                   0L             /* Default increment       */
                   );
   if (hddf == NULLHANDLE)       /* Check return code       */
       return hddf;

   /* initial text */
   DdfPara(hddf);
   sprintf(szDdf, "Ddf data was requested from the application.  "
         "The ID is %ld", id);
   DdfText(hddf, szDdf);

   /* test DdfInform */
   DdfPara(hddf);                          
   DdfText(hddf, "The following links are 'inform' links that should "
         "cause the app to bring up a confirming message box.  The ID "
         "in the confirmation dialog should match the link number:  ");
   DdfInform(hddf, "Link 1", 1);
   DdfText(hddf, ", ");
   sprintf(szDdf, "Link %ld", id);
   DdfInform(hddf, szDdf, id);
   DdfText(hddf, ", ");
   DdfInform(hddf, "Link 64000", 64000);

   /* test DdfHyperText */
   DdfPara(hddf);
   DdfText(hddf, "This [");
   if (! DdfHyperText(hddf, "link", "12", REFERENCE_BY_RES))
      ShowErrorInfo(hwndCoverpage);
   DdfText(hddf, "] attempts to link to Panel 12 by resource id.  This [");
   if (! DdfHyperText(hddf, "link", "TWELVE", REFERENCE_BY_ID))
      ShowErrorInfo(hwndCoverpage);
   DdfText(hddf, "] attempts to link to Panel 12 by name.");

   return hddf;
}


/* ShowErrorInfo(): displays error info for the current thread in */
/* a PM message window. */
void ShowErrorInfo(HWND hwnd)
{
   PERRINFO perri;
   CHAR szMsg[256];
   CHAR szAll[1024];
   PULONG poffsz;
   PSZ psz;
   ULONG ul;

   perri = WinGetErrorInfo(hab);
   if (perri == NULL) {
      strcpy(szAll, "No Error Info Available");
   } else {
      sprintf(szAll, "Error %04X, Severity %d", ERRORIDERROR(perri->idError),
            ERRORIDSEV(perri->idError));
      poffsz = PFROMOFF(perri, perri->offaoffszMsg);
      for (ul = 0; ul < perri->cDetailLevel; ul++) {
         psz = PFROMOFF(perri, *(poffsz++));
         sprintf(szMsg, ", (%d) %s", ul, psz);
         strcat(szAll, szMsg);
      } /* endfor */
   } /* endif */
   WinFreeErrorInfo(perri);
   WinMessageBox(HWND_DESKTOP, hwnd, szAll, NULL, 0, MB_OK);
}

