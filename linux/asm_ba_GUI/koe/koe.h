class tietue
{
public:
	int r_indeksi=0;
	std::string bin;
	std::vector<int> tunnus;
	
	tietue() {}
	tietue(int r_id, std::vector<int> t,  std::string s) {
		r_indeksi = r_id;
		bin = s;
		tunnus = t;
		
	}	
};