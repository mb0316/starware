{
//	TString lib = TString(gSystem -> Getenv("BMSPECPATH")) + "/libBMspec.dylib";
	TString lib = "/Users/MoonByul/Moon_root/EURICA/BMprogram/starware/cmake/libSTARWARE.dylib";

	if (gSystem -> Load(lib) != -1)
	{
//		new BMgui();
		cout << "STAWARE system starts." << endl;
	}
	else
		cout << "Cannot load BMspec" << endl;
}
