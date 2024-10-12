#include<iostream>
#include<vector>
using namespace std;

struct Vector
{
	vector <double> coords;
	void Mult(double alpha)
	{
		vector <double> coords1 = coords;
		for (unsigned i = 0; i < coords1.size(); i++)
		{
			coords1.at(i) = alpha * coords.at(i);
			cout << coords1.at(i) << endl;
		}
		
	}
};
struct Vector Sum(struct Vector V1, struct Vector V2) {
	vector <double> sum ((V1.coords).size());
	for (unsigned i = 0; i < (V1.coords).size(); i++) {
		sum.at(i) = (V1.coords).at(i) + (V2.coords).at(i);
	}
	struct Vector V3 = { sum };
	return V3;
}

double ScPr(struct Vector V1, struct Vector V2) {
	if ((V1.coords).size() != (V2.coords).size()) {
		cout << "Input two vectors with the same dimension" << endl;
		return -100000;
	}
	double scpr = 0;
	for (unsigned i = 0; i < (V1.coords).size(); i++) {
		scpr += (V1.coords).at(i) * (V2.coords).at(i);
	}
	return scpr;
}

int main()
{
	
	int dim;
	cout << "Dimension = ";
	cin >> dim;
	cout << endl;
	vector <double> c1 (dim);
	vector <double> c2 (dim);
	cout << "Coordinates of the 1st vector (input in a column, not in a row): " << endl;
	for (int i = 0; i < dim; i++)
	{
		double a;
		cin >> a;
		c1.at(i) = a;
	}
	cout << "Coordinates of the 2nd vector (input in a column, not in a row): " << endl;
	for (int i = 0; i < dim; i++)
	{
		double a;
		cin >> a;
		c2.at(i) = a;
	}
	struct Vector V1 {{c1}};
	struct Vector V2 {{c2}};

	cout << "(V1, V2) = " << ScPr(V1, V2) << endl;

	struct Vector V3 = Sum(V1, V2);
	vector <double> v = V3.coords;
	cout << "V1+V2 = ";
	std::copy(v.begin(), v.end(), std::ostream_iterator<double>(std::cout, " "));
	cout << endl;

	double alpha;
	cout << "Input a real number: ";
	cin >> alpha;
	cout << endl;
	cout << alpha << "*V1 = ";
	V1.Mult(alpha);
}