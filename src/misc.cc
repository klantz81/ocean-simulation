#include "misc.h"

char* loadFile(const char *filename) {
	char* data;
	int len;
	std::ifstream ifs(filename, std::ifstream::in);

	ifs.seekg(0, std::ios::end);
	len = ifs.tellg();

	ifs.seekg(0, std::ios::beg);
	data = new char[len + 1];

	ifs.read(data, len);
	data[len] = 0;

	ifs.close();

	return data;
}

std::string pad(int x) {
	std::stringstream s;
	if      (x < 10)   s << "00" << x;
	else if (x < 100)  s << "0"  << x;
	else if (x < 1000) s << ""   << x;
	return s.str();
}

std::string number_format(int x) {
	std::stringstream s;
	std::vector<int> sep; int t; bool flag = false;
	if (x < 0) { flag = true; x = -x; }
	while (x > 1000) {
		t = x % 1000;
		sep.push_back(t);
		x = x / 1000;
	};
	sep.push_back(x);
	for (int i = sep.size() - 1; i > 0; i--) {
		if (i == sep.size() - 1) s << (flag ? "-" : "") << sep[i] << ",";
		else s << pad(sep[i]) << ",";
	}
	if (sep.size() > 1)
		s << pad(sep[0]);
	else
		s << (flag ? "-" : "") << sep[0];
	return s.str();
}

float uniformRandomVariable() {
	return (float)rand()/RAND_MAX;
}

complex gaussianRandomVariable() {
	float x1, x2, w;
	do {
	    x1 = 2.f * uniformRandomVariable() - 1.f;
	    x2 = 2.f * uniformRandomVariable() - 1.f;
	    w = x1 * x1 + x2 * x2;
	} while ( w >= 1.f );
	w = sqrt((-2.f * log(w)) / w);
	return complex(x1 * w, x2 * w);
}