#include "Processor.h"
Processor::Processor()
{
	number_of_kernels = 0;
	support_left = false, support_right = false;
	E_parameter = NULL; 
	A_parameter = NULL;
	L_parameter = NULL;
	q_parameter = NULL;
	F_parameter = NULL;
	d_parameter = NULL;
	b_parameter = NULL;
	lines_of_main_matrix = NULL;
	A_matrix = NULL;
	second_parameter = 0;
	gauss_matrix = NULL;
}
void Processor::go()
{
	int choice = 0;
	cout << "Hello, input value:\n\n1 - to start a task(2 test examples);\n2 - to build a new task.\ninput: ";
	cin >> choice;
	if (choice == 1)
	{
		system("cls");
		test();
		processor_();
	}
	if (choice == 2)
		building();
}
double Processor::b_quadrat(double q, double L, double F) { return ((q * L) / 2) + F; }
double Processor::quadrat(double E, double A, double L) { return (E * A) / L; }
void Processor::building()
{
	int choice = 0;
	do {
		cout << "1 - add number of kernels;\n2 - finish building.\ninput: ";
		cin >> choice;

		if (choice == 1)
		{
			system("cls");
			cout << "Input number of kernels: ";
			cin >> number_of_kernels;
			E_parameter = new double[number_of_kernels];
			A_parameter = new double[number_of_kernels];
			L_parameter = new double[number_of_kernels];

			for (int i = 0; i < number_of_kernels; i++)
				E_parameter[i] = A_parameter[i] = L_parameter[i] = 0;

			system("cls");
			cout << "If parameters A are unknown in the task, then calculate them yourself and enter them\n";
			for (int i = 0; i < number_of_kernels; i++)
			{
				cout << "\n" << i + 1 << " kernel:\nInput A for " << i + 1 << " kernel(please, input dimensionless values): ";
				cin >> A_parameter[i];
				cout << "Input E for " << i + 1 << " kernel(please, input dimensionless values): ";
				cin >> E_parameter[i];
				cout << "Input L for " << i + 1 << " kernel(please, input dimensionless values): ";
				cin >> L_parameter[i];
			}
			int choice_support = 0;
			cout << endl << "Add supports:\n1 - add support on the left;\n2 - add support on the right;\n3 - add supports on the left and on the right;\n4 - do not add supports;\n";
			cin >> choice_support;

			if (choice_support == 1)
			{
				show_kernels(2);
				support_left = true;
			}
			if (choice_support == 2)
			{
				show_kernels(3);
				support_right = true;
			}
			if (choice_support == 3)
			{
				show_kernels(4);
				support_left = true;
				support_right = true;
			}
			if (choice_support == 4)
				show_kernels(1);

			q_parameter = new double[number_of_kernels + 1];
			F_parameter = new double[number_of_kernels + 1];

			for (int i = 0; i < number_of_kernels + 1; i++)
				q_parameter[i] = F_parameter[i] = 0;

			double buff1 = 0, buff2 = 0;
			int iter = 0;

			b_parameter = new double[number_of_kernels + 1];
			for (int i = 0; i < number_of_kernels + 1; i++)
				b_parameter[i] = 0;

			cout << "\nYour construction has " << number_of_kernels + 1 << " nodes, please, input q and F parameters on the nodes(please, input dimensionless values).\n\n";
			for (int i = 0; i < number_of_kernels + 1; i++)
			{
				cout << i + 1 << " node, q(if it is missing, then put 0): ";
				cin >> buff1;
				q_parameter[i] = buff1;
				cout << i + 1 << " node, F(if it is missing, then put 0): ";
				cin >> buff2;
				F_parameter[i] = buff2;

				b_parameter[i] = b_quadrat(q_parameter[i], L_parameter[iter], F_parameter[i]);
				if (i > 0)
					iter++;

				cout << endl;
			}
			cout << endl;

			if (choice_support == 1)
			{
				show_kernels(2);
				support_left = true;
			}
			if (choice_support == 2)
			{
				show_kernels(3);
				support_right = true;
			}
			if (choice_support == 3)
			{
				show_kernels(4);
				support_left = true;
				support_right = true;
			}
			if (choice_support == 4)
				show_kernels(1);

			node_demonstration();
			cout << endl << endl;
		}
	} while (choice != 2);
	processor_();
}
void Processor::show_kernels(int choice)
{
	cout << "\nConditional scheme\nThe picture shows up to a maximum of four kernels(if there are more kernels,\nthen everything will be calculate without a picture),\nThe scheme is arbitrary, does not show arrows q and F:\n";
	if (number_of_kernels == 2)
	{
		if (choice == 1)
		{
			cout << "                   __________\n";
			cout << "        __________|          |\n";
			cout << "       |          |          |\n";
			cout << "       |          |          |\n";
			cout << "       |__________|          |\n";
			cout << "                  |__________|\n\n";
			cout << "       |          |          |\n";
			cout << "       1          2          3\n";
		}
		if (choice == 2)
		{
			cout << "                    __________\n";
			cout << "         __________|          |\n";
			cout << "       \\|          |          |\n";
			cout << "       \\|          |          |\n";
			cout << "       \\|__________|          |\n";
			cout << "                   |__________|\n\n";
			cout << "        |          |          |\n";
			cout << "        1          2          3\n";
		}
		if (choice == 3)
		{
			cout << "                   __________\n";
			cout << "        __________|          |/\n";
			cout << "       |          |          |/\n";
			cout << "       |          |          |/\n";
			cout << "       |__________|          |/\n";
			cout << "                  |__________|/\n\n";
			cout << "       |          |          |\n";
			cout << "       1          2          3\n";
		}
		if (choice == 4)
		{
			cout << "                    __________\n";
			cout << "         __________|          |/\n";
			cout << "       \\|          |          |/\n";
			cout << "       \\|          |          |/\n";
			cout << "       \\|__________|          |/\n";
			cout << "                   |__________|/\n\n";
			cout << "        |          |          |\n";
			cout << "        1          2          3\n";
		}
	}
	if (number_of_kernels == 3)
	{
		if (choice == 1)
		{
			cout << "                   __________\n";
			cout << "        __________|          |__________\n";
			cout << "       |          |          |          |\n";
			cout << "       |          |          |          |\n";
			cout << "       |__________|          |__________|\n";
			cout << "                  |__________|\n\n";
			cout << "       |          |          |          |\n";
			cout << "       1          2          3          4\n";
		}
		if (choice == 2)
		{
			cout << "                    __________\n";
			cout << "         __________|          |__________\n";
			cout << "       \\|          |          |          |\n";
			cout << "       \\|          |          |          |\n";
			cout << "       \\|__________|          |__________|\n";
			cout << "                   |__________|\n\n";
			cout << "        |          |          |          |\n";
			cout << "        1          2          3          4\n";
		}
		if (choice == 3)
		{
			cout << "                   __________\n";
			cout << "        __________|          |__________\n";
			cout << "       |          |          |          |/\n";
			cout << "       |          |          |          |/\n";
			cout << "       |__________|          |__________|/\n";
			cout << "                  |__________|\n\n";
			cout << "       |          |          |          |\n";
			cout << "       1          2          3          4\n";
		}
		if (choice == 4)
		{
			cout << "                    __________\n";
			cout << "         __________|          |__________\n";
			cout << "       \\|          |          |          |/\n";
			cout << "       \\|          |          |          |/\n";
			cout << "       \\|__________|          |__________|/\n";
			cout << "                   |__________|\n\n";
			cout << "        |          |          |          |\n";
			cout << "        1          2          3          4\n";
		}
	}
	if (number_of_kernels == 4)
	{
		if (choice == 1)
		{
			cout << "                   __________            __________\n";
			cout << "        __________|          |__________|          |\n";
			cout << "       |          |          |          |          |\n";
			cout << "       |          |          |          |          |\n";
			cout << "       |__________|          |__________|          |\n";
			cout << "                  |__________|          |__________|\n\n";
			cout << "       |          |          |          |          |\n";
			cout << "       1          2          3          4          5\n";
		}
		if (choice == 2)
		{
			cout << "                    __________            __________\n";
			cout << "         __________|          |__________|          |\n";
			cout << "       \\|          |          |          |          |\n";
			cout << "       \\|          |          |          |          |\n";
			cout << "       \\|__________|          |__________|          |\n";
			cout << "                   |__________|          |__________|\n\n";
			cout << "        |          |          |          |          |\n";
			cout << "        1          2          3          4          5\n";
		}
		if (choice == 3)
		{
			cout << "                   __________            __________\n";
			cout << "        __________|          |__________|          |/\n";
			cout << "       |          |          |          |          |/\n";
			cout << "       |          |          |          |          |/\n";
			cout << "       |__________|          |__________|          |/\n";
			cout << "                  |__________|          |__________|/\n\n";
			cout << "       |          |          |          |          |\n";
			cout << "       1          2          3          4          5\n";
		}
		if (choice == 4)
		{
			cout << "                    __________            __________\n";
			cout << "         __________|          |__________|          |/\n";
			cout << "       \\|          |          |          |          |/\n";
			cout << "       \\|          |          |          |          |/\n";
			cout << "       \\|__________|          |__________|          |/\n";
			cout << "                   |__________|          |__________|/\n\n";
			cout << "        |          |          |          |          |\n";
			cout << "        1          2          3          4          5\n";
		}
	}
}
void Processor::node_demonstration()
{
	//cout << "        |";
	//for (int i = 0; i < number_of_kernels + 1; i++)
	//{
	//	if (i == 0)
	//	{
	//		if (q_parameter[i] != 0)
	//		{
	//			if (q_parameter[i] > 0)
	//				cout << ">>>>>>>>>>|";
	//			if (q_parameter[i] < 0)
	//				cout << "<<<<<<<<<<|";
	//		}
	//	}
	//	if (i > 0)
	//	{
	//		if (q_parameter[i - 1] == 0 && q_parameter[i] != 0)
	//		{
	//			if (q_parameter[i] > 0)
	//				cout << ">>>>>>>>>>|";
	//			if (q_parameter[i] < 0)
	//				cout << "<<<<<<<<<<|";
	//		}
	//	}
	//	/*if (F_parameter[i] != 0 && i != number_of_kernels)
	//	{
	//		if (F_parameter[i] > 0)
	//			cout << "----->    |";
	//		if (F_parameter[i] > 0)
	//			cout << "<-----    |";
	//	}*/
	//	else if (i != number_of_kernels)
	//		cout << "          |";
	//}
	//cout << "\n\n     ";
	cout << "     ";
	for (int i = 0; i < number_of_kernels + 1; i++)
		cout << "q=" << q_parameter[i] << ",F=" << F_parameter[i] << setw(6);
	cout << "\n\n";
	for (int i = 0; i < number_of_kernels; i++)
		cout << setw(4) << "kernel " << i + 1 << ": E = " << E_parameter[i] << ", A = " << A_parameter[i] << ", L = " << L_parameter[i] << endl;
}
void Processor::test()
{
	int choice = 0;
	cout << "\nExample with 2 kernels - 2, example with 3 kernels - 3: ";
	cin >> choice;
	cout << endl;
	if (choice == 2)
	{
		number_of_kernels = 2;
		E_parameter = new double[number_of_kernels];
		A_parameter = new double[number_of_kernels];
		L_parameter = new double[number_of_kernels];

		for (int i = 0; i < number_of_kernels; i++)
			E_parameter[i] = A_parameter[i] = L_parameter[i] = 0;
		E_parameter[0] = 1, A_parameter[0] = 1, L_parameter[0] = 2;
		E_parameter[1] = 1, A_parameter[1] = 2, L_parameter[1] = 1;
		support_left = true;
		support_right = true;
		show_kernels(4);
		b_parameter = new double[number_of_kernels + 1];
		for (int i = 0; i < number_of_kernels + 1; i++)
			b_parameter[i] = 0;

		q_parameter = new double[number_of_kernels + 1];
		F_parameter = new double[number_of_kernels + 1];
		for (int i = 0; i < number_of_kernels + 1; i++)
			q_parameter[i] = F_parameter[i] = 0;

		q_parameter[0] = 1, F_parameter[0] = 0;
		q_parameter[1] = 1, F_parameter[1] = -4;
		q_parameter[2] = 0, F_parameter[2] = 0;

		b_parameter[0] = b_quadrat(q_parameter[0], L_parameter[0], F_parameter[0]);
		b_parameter[1] = b_quadrat(q_parameter[1], L_parameter[0], F_parameter[1]);
		b_parameter[2] = b_quadrat(q_parameter[2], L_parameter[1], F_parameter[2]);
		node_demonstration();
	}
	if (choice == 3)
	{
		number_of_kernels = 3;
		E_parameter = new double[number_of_kernels];
		A_parameter = new double[number_of_kernels];
		L_parameter = new double[number_of_kernels];

		for (int i = 0; i < number_of_kernels; i++)
			E_parameter[i] = A_parameter[i] = L_parameter[i] = 0;
		E_parameter[0] = 1, A_parameter[0] = 3, L_parameter[0] = 1;
		E_parameter[1] = 1, A_parameter[1] = 2, L_parameter[1] = 2;
		E_parameter[2] = 1, A_parameter[2] = 1, L_parameter[2] = 1;
		support_left = true;
		support_right = true;
		show_kernels(4);
		b_parameter = new double[number_of_kernels + 1];
		for (int i = 0; i < number_of_kernels + 1; i++)
			b_parameter[i] = 0;

		q_parameter = new double[number_of_kernels + 1];
		F_parameter = new double[number_of_kernels + 1];
		for (int i = 0; i < number_of_kernels + 1; i++)
			q_parameter[i] = F_parameter[i] = 0;

		q_parameter[0] = 0, F_parameter[0] = 0;
		q_parameter[1] = 0, F_parameter[1] = 3;
		q_parameter[2] = 0, F_parameter[2] = 1;
		q_parameter[3] = 0, F_parameter[4] = 0;

		b_parameter[0] = b_quadrat(q_parameter[0], L_parameter[0], F_parameter[0]);
		b_parameter[1] = b_quadrat(q_parameter[1], L_parameter[0], F_parameter[1]);
		b_parameter[2] = b_quadrat(q_parameter[2], L_parameter[1], F_parameter[2]);
		node_demonstration();
	}

}
void Processor::show_b_column()
{
	cout << endl;
	int int_number = number_of_kernels + 1;
	for (int i = 0; i < number_of_kernels + 1; i++)
	{
		if (i == int_number / 2)
			cout << "b = {" << setw(4) << b_parameter[i] << setw(4) << " }" << endl;
		else cout << "    {" << setw(4) << b_parameter[i] << setw(4) << " }" << endl;
	}
}
void Processor::show_A_matrix()
{
	cout << endl;
	int int_number = number_of_kernels + 1;
	for (int i = 0; i < number_of_kernels + 1; i++)
	{
		if (i != int_number / 2)
			cout << "    {";
		if (i == int_number / 2)
			cout << "A = {";
		for (int j = 0; j < second_parameter - 2; j++)
			cout << setw(7) << A_matrix[i][j];
		cout << setw(5) << "}\n";
	}
}
void Processor::show_d_column()
{
	cout << endl;
	int int_number = number_of_kernels + 1;
	for (int i = 0; i < number_of_kernels + 1; i++)
	{
		if (i == int_number / 2)
		{
			if (d_parameter[i] == 9)
				cout << "d = {" << setw(3) << "d" << i + 1 << setw(4) << " }" << endl;
			else cout << "d = {" << setw(4) << d_parameter[i] << setw(4) << " }" << endl;
		}
		else
		{
			if (d_parameter[i] == 9)
				cout << "    {" << setw(3) << "d" << i + 1 << setw(4) << " }" << endl;
			else cout << "    {" << setw(4) << d_parameter[i] << setw(4) << " }" << endl;
		}
	}
}
void Processor::equating_A_matrix()
{
	for (int i = 0; i < number_of_kernels + 1; i++)
		for (int j = 0; j < second_parameter - 2; j++)
			A_matrix[i][j] = lines_of_main_matrix[i][j];
}
double* Processor::gauss(double** buffer_matrix, double* y, int number_of_equations)
{
	double* x, max;
	int k, index;
	const double eps = 0.00001;  // точность
	x = new double[number_of_equations];
	k = 0;
	while (k < number_of_equations)
	{
		// Поиск строки с максимальным a[i][k]
		max = abs(buffer_matrix[k][k]);
		index = k;
		for (int i = k + 1; i < number_of_equations; i++)
		{
			if (abs(buffer_matrix[i][k]) > max)
			{
				max = abs(buffer_matrix[i][k]);
				index = i;
			}
		}
		// Перестановка строк
		if (max < eps)
		{
			// нет ненулевых диагональных элементов
			cout << "Решение получить невозможно из-за нулевого столбца ";
			cout << index << " матрицы A" << endl;
			return 0;
		}
		for (int j = 0; j < number_of_equations; j++)
		{
			double temp = buffer_matrix[k][j];
			buffer_matrix[k][j] = buffer_matrix[index][j];
			buffer_matrix[index][j] = temp;
		}
		double temp = y[k];
		y[k] = y[index];
		y[index] = temp;
		// Нормализация уравнений
		for (int i = k; i < number_of_equations; i++)
		{
			double temp = buffer_matrix[i][k];
			if (abs(temp) < eps) continue; // для нулевого коэффициента пропустить
			for (int j = 0; j < number_of_equations; j++)
				buffer_matrix[i][j] = buffer_matrix[i][j] / temp;
			y[i] = y[i] / temp;
			if (i == k)  continue; // уравнение не вычитать само из себя
			for (int j = 0; j < number_of_equations; j++)
				buffer_matrix[i][j] = buffer_matrix[i][j] - buffer_matrix[k][j];
			y[i] = y[i] - y[k];
		}
		k++;
	}
	// обратная подстановка
	for (k = number_of_equations - 1; k >= 0; k--)
	{
		x[k] = y[k];
		for (int i = 0; i < k; i++)
			y[i] = y[i] - buffer_matrix[i][k] * x[k];
	}
	return x;
}
void Processor::processor_()
{
	d_parameter = new double[number_of_kernels + 1];
	for (int i = 0; i < number_of_kernels + 1; i++)
		d_parameter[i] = 9;
	int buf_parameter = number_of_kernels;
	if (support_left == true)
		d_parameter[0] = 0;
	if (support_right == true)
		d_parameter[buf_parameter] = 0;

	lines_of_main_matrix = new double* [number_of_kernels + 1];
	second_parameter = (4 + (number_of_kernels - 1));
	for (int i = 0; i < number_of_kernels + 1; i++)
		lines_of_main_matrix[i] = new double[second_parameter];
	for (int i = 0; i < number_of_kernels + 1; i++)
		for (int j = 0; j < second_parameter; j++)
			lines_of_main_matrix[i][j] = 0;
	A_matrix = new double* [number_of_kernels + 1];
	for (int i = 0; i < number_of_kernels + 1; i++)
		A_matrix[i] = new double[second_parameter - 2];
	for (int i = 0; i < number_of_kernels + 1; i++)
		for (int j = 0; j < second_parameter - 2; j++)
			A_matrix[i][j] = 0;

	int j_buffer = 0, iter = 0;
	double buffer_for = 0, new_buffer = 0;
	for (int i = 0; i < number_of_kernels + 1; i++)
		if (j_buffer < second_parameter)
		{
			lines_of_main_matrix[i][j_buffer] = quadrat(E_parameter[iter], A_parameter[iter], L_parameter[iter]);
			if (i == 0)
				buffer_for = lines_of_main_matrix[i][j_buffer];
			if (i > 0 && i < number_of_kernels)
			{
				new_buffer = lines_of_main_matrix[i][j_buffer];
				lines_of_main_matrix[i][j_buffer] = lines_of_main_matrix[i][j_buffer] + buffer_for;
				buffer_for = new_buffer;
			}
			if (i < number_of_kernels)
			{
				lines_of_main_matrix[i][j_buffer + 1] = -quadrat(E_parameter[iter], A_parameter[iter], L_parameter[iter]);
				lines_of_main_matrix[i + 1][j_buffer] = -quadrat(E_parameter[iter], A_parameter[iter], L_parameter[iter]);
			}
			if (iter < number_of_kernels - 1)
				iter++;
			j_buffer++;
		}
	equating_A_matrix();

	for (int i = 0; i < number_of_kernels + 1; i++)
		for (int j = 0; j < second_parameter - 2; j++)
		{
			if (support_left == true && i == 0 && j == 0)
				lines_of_main_matrix[i][j] = 1;
			if (support_right == true && i == number_of_kernels && j == second_parameter - 3)
				lines_of_main_matrix[i][j] = 1;
			if (support_left == true && i == 0 && j > 0)
				lines_of_main_matrix[i][j] = 0;
			if (support_right == true && i == number_of_kernels && j < second_parameter - 3)
				lines_of_main_matrix[i][j] = 0;
			if (support_right == true && j == second_parameter - 3 && i < number_of_kernels)
				lines_of_main_matrix[i][j] = 0;
			if (support_left == true && i > 0 && j == 0)
				lines_of_main_matrix[i][j] = 0;
		}

	cout << "\n\nMatrix A:";
	show_A_matrix();
	cout << "Use supports and get a new matrix A";
	equating_A_matrix();
	show_A_matrix();
	cout << "Column b:";
	show_b_column();
	cout << "Column d";
	show_d_column();
	cout << "\n[A] * {d} = {b} and taking into account those d_parameters that are equal to 0:\n";

	int for_b_column_buffer = 0;
	int for_d_column_buffer = 0;
	for (int i = 0; i < number_of_kernels + 1; i++)
		for (int j = 0; j < second_parameter; j++)
		{
			if (j == second_parameter - 1)
				lines_of_main_matrix[i][j] = b_parameter[for_b_column_buffer++];
			if (j == second_parameter - 2)
				lines_of_main_matrix[i][j] = d_parameter[for_d_column_buffer++];
		}
	// zero d
	for (int i = 0; i < number_of_kernels + 1; i++)
		if (d_parameter[i] == 0)
			lines_of_main_matrix[i][second_parameter - 1] = 0;
	cout << setw(6);
	for (int i = 0; i < number_of_kernels + 1; i++)
	{
		for (int j = 0; j < second_parameter; j++)
		{
			if (lines_of_main_matrix[i][j] == 9 && j == second_parameter - 2)
				cout << " *  d" << i + 1 << setw(6);
			else
				cout << lines_of_main_matrix[i][j] << setw(6);
		}
		cout << endl;
	}

	cout << "Preparation for the Gauss method:" << endl;
	gauss_matrix = new double* [number_of_kernels + 1];
	for (int i = 0; i < number_of_kernels + 1; i++)
		gauss_matrix[i] = new double[second_parameter - 1];
	for (int i = 0; i < number_of_kernels + 1; i++)
		for (int j = 0; j < second_parameter - 1; j++)
		{
			gauss_matrix[i][j] = 0;
			if (j == second_parameter - 2)
				gauss_matrix[i][j] = lines_of_main_matrix[i][second_parameter - 1];
		}
	for (int i = 0; i < number_of_kernels + 1; i++)
		for (int j = 0; j < second_parameter - 2; j++)
		{
			gauss_matrix[i][j] = lines_of_main_matrix[i][j];
			if (lines_of_main_matrix[j][second_parameter - 2] != 9)
				gauss_matrix[i][j] = gauss_matrix[i][j] * lines_of_main_matrix[j][second_parameter - 2];
		}
	int zero_iterator = 0;
	int zero_and_last_column_iterator = 0;
	int no_zero = 0;

	cout << setw(7);
	for (int i = 0; i < number_of_kernels + 1; i++)
	{
		for (int j = 0; j < second_parameter - 1; j++)
		{
			if (gauss_matrix[i][j] == 0)
				zero_iterator++;
			if (gauss_matrix[i][j] == 0 && j == second_parameter - 2)
				zero_and_last_column_iterator++;
			if (gauss_matrix[i][j] != 0 && j != second_parameter - 2)
				no_zero++;
			if (gauss_matrix[i][j] != 0 && j != second_parameter - 2)
				cout << gauss_matrix[i][j] << "*d" << j + 1 << setw(4);
			if (j == second_parameter - 3)
				cout << gauss_matrix[i][j] << "   =   ";
			else if (gauss_matrix[i][j] == 0 && j != second_parameter - 3 || (gauss_matrix[i][j] != 0 && j == second_parameter - 2))
				cout << gauss_matrix[i][j] << setw(7);
		}
		cout << endl;
	}
	cout << "Calculation...\n";
	int difference = (number_of_kernels + 1) * (second_parameter - 1);
	double d_solution1 = 0;
	double* d_solution;/*
	cout << difference - zero_iterator << endl;
	cout << "no_zero = " << no_zero << ",   zero_and_last_column_iterator = " << zero_and_last_column_iterator << endl;*/
	if ((no_zero % 2) != 0)
		no_zero++;
	if ((difference - zero_iterator) == 2)
	{
		for (int i = 0; i < number_of_kernels + 1; i++)
			for (int j = 0; j < second_parameter - 1; j++)
				if (gauss_matrix[i][j] != 0 && gauss_matrix[i][j] != 9 && j != second_parameter - 2)
					d_solution1 = gauss_matrix[i][second_parameter - 2] / gauss_matrix[i][j];
		cout << "Result:\n";
		for (int i = 0; i < number_of_kernels + 1; i++)
		{
			if (d_parameter[i] != 0)
			{
				d_parameter[i] = d_solution1;
				cout << "d" << i + 1 << " = " << d_parameter[i];
			}
		}
	}
	if ((difference - zero_iterator) > 2)
	{
		double* y = new double[no_zero / 2];
		double** for_method_gauss = new double* [no_zero / 2];
		int y_iterator = 0;
		for (int i = 0; i < number_of_kernels + 1; i++)
			if (gauss_matrix[i][second_parameter - 2] != 0)
				y[y_iterator++] = gauss_matrix[i][second_parameter - 2];

		for (int i = 0; i < (no_zero / 2); i++)
		{
			for_method_gauss[i] = new double[no_zero / 2];
			for (int j = 0; j < (no_zero / 2); j++)
				for_method_gauss[i][j] = 0;
		}
		int x_g = 0, y_g = 0;

		double* array_for_gauss_matrix = new double[no_zero];
		for (int i = 0; i < no_zero; i++)
			array_for_gauss_matrix[i] = 0;
		int iterator_for_array = 0;
		for (int i = 0; i < number_of_kernels + 1; i++)
			for (int j = 0; j < second_parameter - 2; j++)
				if (gauss_matrix[i][j] != 0)
					array_for_gauss_matrix[iterator_for_array++] = gauss_matrix[i][j];

		for (int i = 0; i < no_zero; i++)
		{
			for_method_gauss[x_g][y_g++] = array_for_gauss_matrix[i];
			if (i == ((no_zero / 2) - 1))
			{
				x_g++;
				y_g = 0;
			}
		}
		for (int i = 0; i < (no_zero / 2); i++)
		{
			for (int j = 0; j < (no_zero / 2); j++)
				cout << setw(4) << for_method_gauss[i][j];
			cout << "  =  " << y[i] << endl;
		}
		d_solution = gauss(for_method_gauss, y, (no_zero / 2));
		cout << "Result:\n";
		iterator_for_array = 0;
		for (int i = 0; i < number_of_kernels + 1; i++)
		{
			if (d_parameter[i] != 0)
			{
				d_parameter[i] = d_solution[iterator_for_array++];
				cout << setw(3) << "d" << i + 1 << " = " << d_parameter[i];
			}
		}

		delete[] y;
		delete[] array_for_gauss_matrix;
		for (int i = 0; i < (no_zero / 2); i++)
			delete[] for_method_gauss[i];
	}
	postprocessor();
}
void Processor::postprocessor()
{
	double* U1 = new double[number_of_kernels];
	double* UL = new double[number_of_kernels];
	for (int i = 0; i < number_of_kernels; i++)
	{
		U1[i] = 0;
		UL[i] = 0;
	}

	int no_zero_elements = 0;
	for (int i = 0; i < number_of_kernels + 1; i++)
		if (d_parameter[i] != 0)
			no_zero_elements++;
	double* no_zero_array = new double[no_zero_elements];
	for (int i = 0; i < no_zero_elements; i++)
		no_zero_array[i] = 0;
	int iterator_no_zero_elements = 0;
	for (int i = 0; i < number_of_kernels + 1; i++)
		if (d_parameter[i] != 0)
			no_zero_array[iterator_no_zero_elements++] = d_parameter[i];

	iterator_no_zero_elements = 0;
	for (int i = 0; i < number_of_kernels; i++)
	{
		/*if (i == 0 && q_parameter[0] != 0 || F_parameter[0] != 0 && i == 0)
			U1[i] = no_zero_array[iterator_no_zero_elements++];*/
		if (i > 0)
			U1[i] = no_zero_array[iterator_no_zero_elements++];
		/*if (i == number_of_kernels - 1 && q_parameter[number_of_kernels] != 0 || i == number_of_kernels - 1 && F_parameter[number_of_kernels] != 0)
			UL[i] = no_zero_array[no_zero_elements-1];*/
		if (i < number_of_kernels - 1)
			UL[i] = no_zero_array[iterator_no_zero_elements];
	}
	cout << "\nPostprocessor:\n";
	for (int i = 0; i < number_of_kernels; i++)
	{
		cout << "U" << i + 1 << ",0 = " << U1[i] << setw(7) << "U" << i + 1 << ",L = " << UL[i] << endl;
	}

	/*double* qF_parameter = new double[number_of_kernels];
	for (int i = 0; i < number_of_kernels; i++)
		qF_parameter[i] = 0;

	if (F_parameter[0] != 0 && q_parameter[0] == 0)
		qF_parameter[0] = F_parameter[0];
	else if (F_parameter[0] == 0)
		qF_parameter[0] = q_parameter[0];*/

	cout << "Sorry, parameters Nx and sigma not implemented:\nNx = ...\nsigma = ...";

	delete[] U1;
	delete[] UL;
}
void Processor::start()
{
	go();
}
Processor::~Processor()
{
	delete[] E_parameter;
	delete[] A_parameter;
	delete[] L_parameter;
	delete[] q_parameter;
	delete[] F_parameter;
	delete[] d_parameter;
	delete[] b_parameter;
	for (int i = 0; i < number_of_kernels + 1; i++)
	{
		delete[] lines_of_main_matrix[i];
		delete[] A_matrix;
		delete[] gauss_matrix;
	}
}
