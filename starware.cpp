#include "TROOT.h"
#include "TApplication.h"
#include "TSystem.h"
#include "include/STARGui.h"
/*
int main(int argc, char **argv)
{
	TApplication theApp("STARWARE", &argc, argv);
	gSystem->Load("build/libSTARWARE.dylib");
	new STARGui();
	theApp.Run();

	return 0;
}
*/
   void starware()
   {
   new STARGui();
   }
