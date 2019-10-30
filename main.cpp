#include <iostream>
#include <math.h>
using namespace std;

class Polinom {
	int nrElemente;
	float *vectorCoeficienti; //aloc dinamic vectorul de coeficienti ai polinomului
public:
	Polinom(); //constructorul de initializare
	Polinom(int);//constructorul parametrizat
	~Polinom();//destructor
	Polinom(const Polinom&);//constructor de copiere
	Polinom& operator=(const Polinom& ob);//supraincarcare pt atribuire
	friend istream& operator>>(istream&, Polinom&);//supraincarare pt citirea unui polinom de la tastatura
	friend ostream& operator<<(ostream&, Polinom&);//supraincarcare pt scrierea unui polinom in fereastra de executie
	int gradMaxim();//returneaza gradul maxim al polinomului
	float sumaInPunct(float);//calculeaza valoarea intr-un punct al polinomului
	Polinom operator+(const Polinom&);//adunarea a doua polinoame cu supraincarcare ca functie membru
    Polinom operator+(float);//adunarea unui polinom cu un numar; se creste fiecare coeficient cu numarul dat; adunarea e de forma nr + polinom;
	friend Polinom operator+(float, const Polinom&);//adunarea unui polinom cu un numar; se creste fiecare coeficient cu numarul dat; adunarea e de forma polinom + nr
	friend Polinom operator-(const Polinom&,const Polinom&);//scaderea a doua polinoame
	friend Polinom operator*(const Polinom&,const Polinom&);//inmultirea a doua polinoame
	friend Polinom operator/(const Polinom&,const Polinom&);//catul a doua polinoame
	friend Polinom operator%(const Polinom&,const Polinom&);//restul a doua polinoame
	friend int operator==(const Polinom&, const Polinom&);//verificarea egalitatii a doua polinoame; daca au aceiasi coeficienti si acelasi nr de coeficienti, returneaza 0
	friend int operator!=(const Polinom&, const Polinom&);//verificarea inegalitatii a doua polinoame; daca NU au aceiasi coeficienti si acelasi nr de coeficienti, returneaza 0
	friend int operator<(const Polinom&, const Polinom&);//compara gradul maxim a doua polinoame
	Polinom operator++();//preincrementare; creste fiecare coeficient cu 1
	Polinom operator++(int);//postincrementare; creste fiecare coeficient cu 1
	Polinom operator +=(float);//adunarea unui polinom cu un numar
	float& operator[](int);//supraincarcarea operatorului de indexare; echivalenta intre p.vectorCoeficienti[i] si p[i]
	friend class Pereche;
};

class Pereche { //clasa Pereche, care contine un numar real si un polinom
	float n;
	Polinom p;
public:
	Pereche();//constructor initializare
	Pereche(float, Polinom);//constructor parametrizat
	Pereche(const Pereche&);//constructor de copiere
	Pereche& operator=(const Pereche&);//supraincarcarea operatorului de atribuire
	friend istream& operator>>(istream&, Pereche&);//citirea unei perechi de la tastatura
	friend ostream& operator<<(ostream&, Pereche&);//scrierea unei perechi in comanda de executie
	void testRadacina();//apeleaza functia sumaInPunct din clasa Polinom, unde argumentul float din acea functie este data membru
};
Polinom::Polinom() {
	vectorCoeficienti = NULL;
	nrElemente = -1;
}

Polinom::Polinom(int n1) {
	nrElemente = n1;
	vectorCoeficienti = new float[nrElemente + 1];
	for (int i = 1; i <= n1; i++)
		this->vectorCoeficienti[i] = 0;
}

Polinom::~Polinom() {
	if (vectorCoeficienti != NULL) delete[]vectorCoeficienti;
}

Polinom::Polinom(const Polinom &ob) {
	this->nrElemente = ob.nrElemente;
	this->vectorCoeficienti = new float[this->nrElemente + 1];
	for (int i = 1; i <= this->nrElemente; i++)
		this->vectorCoeficienti[i] = ob.vectorCoeficienti[i];
}

Polinom & Polinom::operator=(const Polinom & ob){
	if (this != &ob) {
		this->nrElemente = ob.nrElemente;
		this->vectorCoeficienti = new float[this->nrElemente + 1];
		for (int i = 1; i <= this->nrElemente; i++) {
			this->vectorCoeficienti[i] = ob.vectorCoeficienti[i];
		}
   }
	return *this;
}

int Polinom::gradMaxim() {
	int i = this->nrElemente;
	while (!this->vectorCoeficienti[i] && i > 1) i--;
	return i - 1;
}

float Polinom::sumaInPunct(float valoare){
	float suma = 0;
	for (int i = 1; i <= nrElemente; i++)
		suma += vectorCoeficienti[i] * pow(valoare,nrElemente - 1);
	return suma;
}

Polinom Polinom::operator+=(float f) {
	for (int i = 1; i <= this->nrElemente; i++)
		this->vectorCoeficienti[i] += f;
	return *this;
}

float & Polinom::operator[](int i) {
	if (i > this->nrElemente) {
		cout << "Index prea mare" << endl;
		return this->vectorCoeficienti[1];
	}
	return this->vectorCoeficienti[i];
}

 istream& operator>>(istream &in, Polinom &p) {
	 in>>p.nrElemente;
	 p.vectorCoeficienti = new float[p.nrElemente + 1];
	 for (int i = 1; i <= p.nrElemente; i++)
		 in >> p[i];
	 return in;
}

 ostream & operator<<(ostream &out, Polinom &p) {
	 for (int i = p.nrElemente ; i >= 1; i--) {
		 if (p[i]) {
			 if (i == p.gradMaxim() + 1) out << p[i] << "*X^" << i - 1;
			 else {
				 if (p[i] > 0) out << "+" << p[i] << "*X^" << i - 1;
				 else out << p[i] << "*X^" << i - 1;
			 }
		}
	 }
	 cout << endl;
	 return out;
 }

 Polinom Polinom::operator+(const Polinom& B) {
	 int i;
	 int max = this->nrElemente > B.nrElemente?  this->nrElemente : B.nrElemente;
	 Polinom C(max + 1);
	 if (this->nrElemente <= B.nrElemente) C.nrElemente = this->nrElemente;
	 else C.nrElemente = B.nrElemente;
	 for (i = 1; i <= C.nrElemente; i++)
		 C.vectorCoeficienti[i] = this->vectorCoeficienti[i] + B.vectorCoeficienti[i];
	 while (i <= this->nrElemente) {
		 C.vectorCoeficienti[i] = this->vectorCoeficienti[i];
		 i++;
	 }
	 while (i <= B.nrElemente) {
		 C.vectorCoeficienti[i] = B.vectorCoeficienti[i];
		 i++;
	 }
	 C.nrElemente = max;
	 return C;
 }

 Polinom Polinom::operator+(float f) {
	 for (int i = 1; i <= this->nrElemente; i++) {
		 this->vectorCoeficienti[i] += f;
	 }
	 return *this;
 }

 Polinom operator+(float f, const Polinom &A) {
	 Polinom C(A.nrElemente + 1);
	 for (int i = 1; i <= A.nrElemente; i++)
		 C.vectorCoeficienti[i] = A.vectorCoeficienti[i] + f;
	 return C;
 }

 Polinom operator-(const Polinom &A, const Polinom &B) {
	 int i;
	 int max = A.nrElemente > B.nrElemente? A.nrElemente:  B.nrElemente;
	 Polinom C(max + 1);
	 if (A.nrElemente <= B.nrElemente) C.nrElemente = A.nrElemente;
	 else C.nrElemente = B.nrElemente;
	 for (i = 1; i <= C.nrElemente; i++)
		 C.vectorCoeficienti[i] = A.vectorCoeficienti[i] - B.vectorCoeficienti[i];
	 while (i <= A.nrElemente) {
		 C.vectorCoeficienti[i] = A.vectorCoeficienti[i];
		 i++;
	 }
	 while (i <= B.nrElemente) {
		 C.vectorCoeficienti[i] = (-1)*B.vectorCoeficienti[i];
		 i++;
	 }
	 C.nrElemente = max;
	 return C;
	}

 Polinom operator*(const Polinom &A, const Polinom &B) {
	 int i,j, max = A.nrElemente + B.nrElemente;
	 Polinom C(max + 1);
	 for (i = 1; i <= max; i++)
		 C[i] = 0;
	 for (i = 1; i <= A.nrElemente; i++)
		 for (j = 1; j <= B.nrElemente; j++)
			C[i + j - 1] += A.vectorCoeficienti[i] * B.vectorCoeficienti[j];
	 C.nrElemente = max;
	 return C;
 }

 Polinom operator/(const Polinom &A, const Polinom &B) {                  //in aceasta functie se foloseste algoritmul clasic de impartire a doua polinoame
	 int dimCat = A.nrElemente - B.nrElemente;
	 Polinom C(dimCat + 1);
	 Polinom CopieA(A);
	 Polinom CopieB(B);
	 try {
		 if (!CopieB.gradMaxim() && !CopieB.vectorCoeficienti[1])
			 throw "Eroare: Divizorul este un polinom nul.";
	 }
	 catch (const char* msg) {
		 cerr << msg << endl;
	 }
	 while(CopieA.gradMaxim() >= CopieB.gradMaxim()) {
		 Polinom temp(dimCat + 1);
		 temp.vectorCoeficienti[CopieA.gradMaxim() - CopieB.gradMaxim() + 1] = CopieA.vectorCoeficienti[CopieA.gradMaxim() + 1] / CopieB.vectorCoeficienti[CopieB.gradMaxim() + 1];
		 CopieA = CopieA - (CopieB * temp);
		 C = C + temp;
	 }
	 return C;
 }

 Polinom operator%(const Polinom &A, const Polinom &B) {
	 Polinom C(B.nrElemente - 1);
	 C = A - (B *(A / B));
	 return C;
 }

 int operator==(const Polinom &A, const Polinom &B) {
	 if (A.nrElemente != B.nrElemente) return 0;
	 for (int i = 1; i <= A.nrElemente; i++) {
		 if (A.vectorCoeficienti[i] != B.vectorCoeficienti[i]) return 0;
	 }
	 return 1;
 }

 int operator!=(const Polinom &A, const Polinom &B) {
	 if (A == B) return 0;
	 return 1;
 }

 int operator<(const Polinom &A, const Polinom &B) {
	 Polinom CopieA(A);
	 Polinom CopieB(B);
	 return CopieA.gradMaxim() - CopieB.gradMaxim();
 }

 Polinom Polinom::operator++() {
	 for (int i = 1; i <= this->nrElemente; i++) {
		 this->vectorCoeficienti[i] += 1;
	 }
	 return *this;
 }

 Polinom Polinom::operator++(int f) {
	 for (int i = 1; i <= this->nrElemente; i++) {
		 this->vectorCoeficienti[i] += 1;
	 }
	 return *this;
 }

 istream & operator>>(istream &in, Pereche &per) {
	 in >> per.n;
	 in >> per.p;
	 return in;
 }

 ostream & operator<<(ostream &out, Pereche &per) {
	 out << per.n << endl << per.p << endl;
	 return out;
 }

 Pereche::Pereche() {
	 n = 0;
	 Polinom();
 }

 Pereche::Pereche(float nr, Polinom p1) {
	 this->n = nr;
	 this->p = p1;
 }

 Pereche::Pereche(const Pereche &per) {
	 this->n = per.n;
	 this->p = per.p;
 }

 Pereche & Pereche::operator=(const Pereche &per) {
	 if (this != &per ) {
		 this->n = per.n;
		 this->p = per.p;
	 }
	 return *this;
  }

 void Pereche::testRadacina() {
	 if (!this->p.sumaInPunct(this->n)) cout << "Valoarea " << this->n << " este radacina pentru polinomul dat";
	 else cout << "Valoarea " << this->n << " nu este radacina pentru polinomul dat";
 }

int main() {
	Polinom p,q,r;
	cin >> p >> q;
	cout << p << q;
	r = p / q;
	cout << r;
}
