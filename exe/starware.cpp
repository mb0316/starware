#include "TROOT.h"
#include "TApplication.h"
#include "TSystem.h"
#include "STAR.h"
#include "STARAnaDC.h"
#include "STARAnaDis.h"
#include "STARAnaGG.h"
#include "STARAnaTG.h"
#include "STARGui.h"
#include "STARCal.h"


int main(int argc, char **argv)
{
  TApplication theApp("STARWARE", &argc, argv);
  new STARGui();
  theApp.Run();

  return 0;
}
