#pragma once
#include <iostream>
#include <iomanip>
#include <math.h>
using namespace std;
class Processor
{
	int number_of_kernels;
	double** lines_of_main_matrix;
	double** A_matrix;
	double** gauss_matrix;
	int second_parameter;
	double* E_parameter;
	double* A_parameter;
	double* L_parameter;
	double* q_parameter;
	double* F_parameter;
	double* d_parameter;
	double* b_parameter;
	bool support_left, support_right;
public:
	Processor();
private:
	void go();
	double b_quadrat(double q, double L, double F);
	double quadrat(double E, double A, double L);
	void building();
	void show_kernels(int choice);
	void node_demonstration();
	void test();
	void show_b_column();
	void show_A_matrix();
	void show_d_column();
	void equating_A_matrix();
	double* gauss(double** buffer_matrix, double* y, int number_of_equations);
	void processor_();
	void postprocessor();
public:
	void start();
	~Processor();
};
