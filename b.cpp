#include <cctype>
#include <iostream>

using namespace std;

class Alpha {
private:
	unsigned bin;
public:
	Alpha() { bin = 0; };
	Alpha(char*);
	void operator ~(); // перегрузка оператора тильда (операция дополнения)
	Alpha operator ^(Alpha&); // перегрузка оператора циркумфлекс (операция исключения совпадений)
	friend ostream& operator << (ostream&, Alpha&); // дружественная перегрузка оператора << потока ст. вывода
};

Alpha::Alpha(char* s) {
	bin = 0;
	while (*s) {
		bin |= (1 << (tolower(*s) - 'a'));
		s++;
	}
}

Alpha Alpha::operator ^(Alpha& y) {
	Alpha z;
	z.bin = bin ^ y.bin;
	return(z);
}

void Alpha::operator ~() {
	bin = ~bin;
}

ostream & operator << (ostream & out, Alpha & z) {
	unsigned  bit = 1;
	int i;
	for (i=0; i<26; i++) {
		if ((z.bin & bit) > 0)
		out << (char)('a' + i);
		bit = bit << 1;
	}
	return out;
}

int main(int argc, char* argv[]) {
	Alpha x(argv[1]);
	Alpha y(argv[2]);
	Alpha z, w;
	z = x ^ y;
	~z;
	cout << z << " " << endl;
	return (0);
}