#include <cstdio>
#include <vector>
#include <math.h>

int getRandom(int min, int max);
typedef std::vector<double> vect;

// input data
double beta = (double)getRandom(1, 99) / 100;
int M = 300;
double t = 10;
double R = 5;
int N = 1000;
// double q0[] = { 240, 160, 80, 110, 47 }; // expected result
double q0[] = { 100, 100, 100, 100, 100 };
double k[] = { 120, 160, 130, 140, 110 };
double v[] = { 48000, 22400, 6400, 8600, 2460 };
double s[] = { 200, 280, 260, 200, 250 };
int size = 5;

int getRandom(int min, int max)
{
	//srand(rand());
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
	return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

double norma(vect vector) {
	double sum = 0;
	for (int i = 0; i < vector.size(); i++) {
		sum += vector[i] * vector[i];
	}
	return sqrt(sum);
}

vect norm(vect vector) {
	vect result;
	result.resize(size);
	double n = norma(vector);
	for (int i = 0; i < vector.size(); i++) {
		result[i] = vector[i] / n;
	}
	return result;
}

void fillVector(vect& vector, double* arr, int size) {
	//vector.resize(size);
	for (int i = 0; i < size; i++) {
		vector[i] = arr[i];
	}
}

vect generateVector() {
	vect result;
	for (int i = 0; i < size; i++) {
		double r = (double)getRandom(-100, 100);
		r = r / 100;
		result.push_back(r);
	}
	return result;
}

vect newVect(vect x, vect e) {
	vect eNorm = norm(e);
	vect result;
	result.resize(size);
	for (int i = 0; i < size; i++) {
		result[i] = x[i] + t * eNorm[i];
	}
	return result;
}

double func(vect x) {
	double result = 0;
	for (int i = 0; i < size; i++) {
		result += k[i] * v[i] / x[i] + s[i] * x[i] / 2;
	}
	return result;
}

void printVector(vect x) {
	for (int i = 0; i < size; i++) {
		printf("\t%f", x[i]);
	}
	printf("\n");
	printf("L = %f\n", func(x));
}

int main()
{
	int k = 0;
	int j = 1;
	vect y;
	vect x, e;
	x.resize(size);
	e.resize(size);
	fillVector(x, q0, size);
	do {
		e = generateVector();
		y = newVect(x, e);

		double funcY = func(y);
		double funcX = func(x);
		printf("\ny:\n");
		printVector(y);
		printf("x:\n");
		printVector(x);
		if (funcY < funcX) {
			// step is successful
			x = y;
			k++;
			if (k < N) {
				j = 1;
			}
			if (k == N) {
				break;
			}

		}
		else {
			// step isn't successful
			if (j < M) {
				j++;
			}
			if (j == M) {
				if (t <= R) {
					break;
				}
				else {
					t = t * beta;
					j = 1;
				}
			}
		}
	} while (true);
	printf("RESULTS:\n");
	printVector(x);
}
