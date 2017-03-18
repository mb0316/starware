{
	TString lib_MacOS = TString(gSystem -> pwd()) + "/libSTARWARE.dylib";
	TString lib_Linux = TString(gSystem -> pwd()) + "/libSTARWARE.so";
	if (gSystem -> Load(lib_MacOS) != -1)
		cout << "STAWARE system has been successfully loaded." << endl;
	else if (gSystem -> Load(lib_Linux) != -1)
		cout << "STAWARE system has been successfully loaded." << endl;
	else
		cout << "Fail to load STARWARE." << endl;
}
