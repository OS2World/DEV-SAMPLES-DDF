DDF EXAMPLE - HELP.EXE

By request, here is a small example using IPF's DDF (Dynamic Data Facility)
which allows the app to dynamically create help text.  It was modified from
the IPF example in the toolkit.

Run HELP.EXE and click in the window
to get the help screen.  The "Ddf Test Panel" shows examples of using
DdfPara, DdfText, DdfInform and DdfHyperText.  Most of the other Ddf
functions follow easily from this.

Note that the HM_QUERY is not documented correctly by IBM.  Specifically,
the usselectionid parameter should take the place of usreserved, and
usreserved should be removed.

Mat Kramer, 75746.2404@compuserve.com
1/29/94

