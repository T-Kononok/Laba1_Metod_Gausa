#include "pch.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <math.h>
#include "Gaus.h"

using namespace std;

double Neviask(double *, double **, double *, int);

double Pogr(double **, double *, int );

int main()
{
	setlocale(LC_ALL, "rus");

	int n, i, k;

	cout << "Порядок: ";
	cin >> n;

	double **a = new double *[n];
	for (i = 0; i < n; i++)
		a[i] = new double[n + 1];

	double **a1 = new double *[n];
	for (i = 0; i < n; i++)
		a1[i] = new double[n + 1];

	double *x = new double[n];

	double *F = new double[n];

	int *p = new int[n];
	for (i = 0; i < n; i++)
		p[i] = i;

	In(a, n);

	for (i = 0; i < n; i++)
		for (int j = 0; j < n + 1; j++)
			a1[i][j] = a[i][j];

	Out(p, a, n);

	if (!Gaus(p, x, a, n))
		return 0;

	cout << "Норма : " << Neviask(F, a1, x, n) << endl << endl;

	cout << "От. погр : " << Pogr(a1, x, n) << endl;

	for (int i = 0; i < n; i++)
		delete a[i];
	delete[] a;

	for (int i = 0; i < n; i++)
		delete a1[i];
	delete[] a1;

	delete[] x;
	delete[] F;
	delete[] p;
}

double Neviask(double *F, double **a, double *x, int n)
{
	for (int i = 0; i < n; i++)
		F[i] = 0;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			F[i] += a[i][j] * x[j];
			//cout << F[i] << " += " << a[i][j] << " * "<< x[j] << "["<< a[i][j] * x[j] <<"]" << endl;
		}		
	}

	cout << endl;

	double norma = 0;
	for (int i = 0; i < n; i++)
	{
		F[i] -= a[i][n];
		if (abs(F[i]) > norma)
			norma = abs(F[i]);
		cout << "F" << i << " " << setprecision(20) << fixed << F[i] << endl;
	}

	cout << endl;

	return norma;
}

double Pogr(double **a, double *x, int n)
{
	double b = 0;
	double *x1 = new double[n];
	for (int i = 0; i < n; i++)
		x1[i] = 0;

	int *p = new int[n];
	for (int i = 0; i < n; i++)
		p[i] = i;

	for (int i = 0; i < n; i++)
	{
		b = 0;
		for (int j = 0; j < n; j++)
			b += a[i][j] * x[j];
		a[i][n] = b;
	}


	if (!Gaus(p, x1, a, n))
		return 0;

	cout << endl;

	double w = 0;
	for (int i = 0; i < n; i++)
	{
		if (abs(x[i]) > w)
			w = abs(x[i]);
	}

	double w2 = 0;
	for (int i = 0; i < n; i++)
	{
		x1[i] -= x[i];
		if (abs(x1[i]) > w2)
			w2 = abs(x1[i]);
	}

	double pog = w2 / w;


	delete[] x1;
	delete[] p;

	return pog;
}