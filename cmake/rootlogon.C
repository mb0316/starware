{
	TString lib = TString(gSystem -> pwd()) + "/libSTARWARE.dylib";
	cout << lib << endl;
	if (gSystem -> Load(lib) != -1)
	{
		cout << "STAWARE system has been successfully loaded." << endl;
	}
	else
		cout << "Cannot load BMspec" << endl;
}
