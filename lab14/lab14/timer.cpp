#include "timer.h"
#include <iostream>
#include <fstream>
#include <boost/lexical_cast.hpp>
#include <ctime>
#include <vector>
#include <deque>
#include <map>
#include <set>
#include <iomanip>

std::vector<double> calc_time;
std::vector<double> average_time;

void vector_deque_timer()
{
	using std::cout;
	using std::endl;
	using std::vector;
	using std::deque;
	using std::string;
	vector<int> v;
	deque<int> d;
	string results;
	clock_t start;
	clock_t end;
	double cpu_time_used;
	// Вычисляем сложность алгоритма доступа к элементу вектора
	cout << endl << "Vector" << endl << "Complexity of operation \"at()\":" << endl;
	for (unsigned int count = { 0 }; count < count_of_tests; ++count)
	{
		amount_of_elements = get_amount_of_elements(count);
		/*cout << endl << "Amount of elements = " << amount_of_elements << endl;*/
		for (unsigned int i = { 0 }; i < amount_of_elements; ++i)
		{
			v.push_back(i);
		}
		for (unsigned int i = { 0 }; i < number_of_measurements; ++i)
		{
			start = clock();
			v.at(i);
			end = clock();
			cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
			calc_time.push_back(cpu_time_used);
		}
		/*cout << endl << "Calc_time:" << endl;
		for (const auto it : calc_time)
		{
			cout << std::fixed << std::setprecision(5) << it << " ";
		}*/
		average_time.push_back(average(calc_time));
		cout << endl << "Average time(amount of elements " << amount_of_elements << "): " << average_time[count] << endl;
		v.clear();
		calc_time.clear();
	}
	results = "Results for operation \"at()\" in vector (Complexity: constant/O(1))\n";
	for (const auto it : average_time)
	{
		results += boost::lexical_cast<string>(it);
		results += "\n";
	}
	write_to_file(results);
	results.clear();
	average_time.clear();
	v.clear();
	// Вычисляем сложность добавления элемента в конец вектора (копируемые объекты)
	cout << endl << "Complexity of operation \"push_back()\":" << endl;
	for (unsigned int count = { 0 }; count < count_of_tests; ++count)
	{
		amount_of_elements = get_amount_of_elements(count);
		for (unsigned int i = { 0 }; i < number_of_measurements; ++i)
		{
			start = clock();
			for (unsigned int i = { 0 }; i < amount_of_elements; ++i)
			{
				v.push_back(i);
			}
			end = clock();
			cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
			calc_time.push_back(cpu_time_used);
		}
		average_time.push_back(average(calc_time));
		cout << endl << "Average time(amount of elements " << amount_of_elements << "): " << average_time[count] << endl;
		v.clear();
		calc_time.clear();
	}
	results = "Results for operation \"push_back()\" in vector (Complexity: Constant (amortized time, reallocation may happen)/O(1))\n";
	for (const auto it : average_time)
	{
		results += boost::lexical_cast<string>(it);
		results += "\n";
	}
	write_to_file(results);
	results.clear();
	average_time.clear();
	v.clear();
	// Вычисляем сложность добавления элемента в начало вектора
	cout << endl << "Complexity of operation \"insert(v.begin(),value)\":" << endl;
	number_of_measurements = { 1 }; // Очень длительный процесс при 500000 эл-ов
	for (unsigned int count = { 0 }; count < count_of_tests; ++count)
	{
		amount_of_elements = get_amount_of_elements(count);
		for (unsigned int i = { 0 }; i < number_of_measurements; ++i)
		{
			start = clock();
			for (unsigned int i = { 0 }; i < amount_of_elements; ++i)
			{
				v.insert(v.begin(),i);
			}
			end = clock();
			cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
			calc_time.push_back(cpu_time_used);
		}
		average_time.push_back(average(calc_time));
		cout << endl << "Average time(amount of elements " << amount_of_elements << "): " << average_time[count] << endl;
		v.clear();
		calc_time.clear();
	}
	results = "Results for operation \"insert(v.begin(),value)\" in vector (Complexity: Linear on the number of elements inserted/O(n))\n";
	for (const auto it : average_time)
	{
		results += boost::lexical_cast<string>(it);
		results += "\n";
	}
	write_to_file(results);
	results.clear();
	average_time.clear();
	v.clear();
	// Вычисляем сложность добавления элемента в конец вектора (перемещаемые объекты)
	number_of_measurements = { 10 };
	cout << endl << "Complexity of operation \"push_back(move())\":" << endl;
	for (unsigned int count = { 0 }; count < count_of_tests; ++count)
	{
		amount_of_elements = get_amount_of_elements(count);
		for (unsigned int i = { 0 }; i < number_of_measurements; ++i)
		{
			start = clock();
			for (unsigned int i = { 0 }; i < amount_of_elements; ++i)
			{
				v.push_back(std::move(i));
			}
			end = clock();
			cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
			calc_time.push_back(cpu_time_used);
		}
		average_time.push_back(average(calc_time));
		cout << endl << "Average time(amount of elements " << amount_of_elements << "): " << average_time[count] << endl;
		v.clear();
		calc_time.clear();
	}
	results = "Results for operation \"push_back(move())\" in vector (Complexity: Constant (amortized time, reallocation may happen)/O(1))\n";
	for (const auto it : average_time)
	{
		results += boost::lexical_cast<string>(it);
		results += "\n";
	}
	write_to_file(results);
	results.clear();
	average_time.clear();
	v.clear();

	cout << endl << "Deque" << endl;
	// Вычисляем сложность алгоритма доступа к элементу deque
	for (unsigned int count = { 0 }; count < count_of_tests; ++count)
	{
		amount_of_elements = get_amount_of_elements(count);
		for (unsigned int i = { 0 }; i < amount_of_elements; ++i)
		{
			d.push_back(i);
		}
		for (unsigned int i = { 0 }; i < number_of_measurements; ++i)
		{
			start = clock();
			d.at(i);
			end = clock();
			cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
			calc_time.push_back(cpu_time_used);
		}
		average_time.push_back(average(calc_time));
		cout << endl << "Average time(amount of elements " << amount_of_elements << "): " << average_time[count] << endl;
		d.clear();
		calc_time.clear();
	}
	results = "Results for operation \"at()\" in deque (Complexity: constant/O(1))\n";
	for (const auto it : average_time)
	{
		results += boost::lexical_cast<string>(it);
		results += "\n";
	}
	write_to_file(results);
	results.clear();
	average_time.clear();
	d.clear();
	// Вычисляем сложность добавления элемента в конец deque (копируемые объекты)
	cout << endl << "Complexity of operation \"push_back()\":" << endl;
	for (unsigned int count = { 0 }; count < count_of_tests; ++count)
	{
		amount_of_elements = get_amount_of_elements(count);
		for (unsigned int i = { 0 }; i < number_of_measurements; ++i)
		{
			start = clock();
			for (unsigned int i = { 0 }; i < amount_of_elements; ++i)
			{
				d.push_back(i);
			}
			end = clock();
			cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
			calc_time.push_back(cpu_time_used);
		}
		average_time.push_back(average(calc_time));
		cout << endl << "Average time(amount of elements " << amount_of_elements << "): " << average_time[count] << endl;
		d.clear();
		calc_time.clear();
	}
	results = "Results for operation \"push_back()\" in deque (Complexity: Constant/O(1))\n";
	for (const auto it : average_time)
	{
		results += boost::lexical_cast<string>(it);
		results += "\n";
	}
	write_to_file(results);
	results.clear();
	average_time.clear();
	d.clear();
	// Вычисляем сложность добавления элемента в начало deque
	cout << endl << "Complexity of operation \"push_front()\":" << endl;
	for (unsigned int count = { 0 }; count < count_of_tests; ++count)
	{
		amount_of_elements = get_amount_of_elements(count);
		for (unsigned int i = { 0 }; i < number_of_measurements; ++i)
		{
			start = clock();
			for (unsigned int i = { 0 }; i < amount_of_elements; ++i)
			{
				d.push_front(i);
			}
			end = clock();
			cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
			calc_time.push_back(cpu_time_used);
		}
		average_time.push_back(average(calc_time));
		cout << endl << "Average time(amount of elements " << amount_of_elements << "): " << average_time[count] << endl;
		d.clear();
		calc_time.clear();
	}
	results = "Results for operation \"push_front()\" in deque (Complexity: Constant/O(1))\n";
	for (const auto it : average_time)
	{
		results += boost::lexical_cast<string>(it);
		results += "\n";
	}
	write_to_file(results);
	results.clear();
	average_time.clear();
	d.clear();
	// Вычисляем сложность добавления элемента в конец deque (перемещаемые объекты)
	cout << endl << "Complexity of operation \"push_back(move())\":" << endl;
	for (unsigned int count = { 0 }; count < count_of_tests; ++count)
	{
		amount_of_elements = get_amount_of_elements(count);
		for (unsigned int i = { 0 }; i < number_of_measurements; ++i)
		{
			start = clock();
			for (unsigned int i = { 0 }; i < amount_of_elements; ++i)
			{
				d.push_back(std::move(i));
			}
			end = clock();
			cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
			calc_time.push_back(cpu_time_used);
		}
		average_time.push_back(average(calc_time));
		cout << endl << "Average time(amount of elements " << amount_of_elements << "): " << average_time[count] << endl;
		d.clear();
		calc_time.clear();
	}
	results = "Results for operation \"push_back(move())\" in deque (Complexity: Constant/O(1))\n";
	for (const auto it : average_time)
	{
		results += boost::lexical_cast<string>(it);
		results += "\n";
	}
	write_to_file(results);
	results.clear();
	average_time.clear();
	d.clear();

	// Вычисляем динамику изменения capacity при добавлении элементов в вектор
	cout << endl << "Dynamics of \"capacity\" changes when adding elements to the vector:" << endl;
	for (unsigned int count = { 0 }; count < count_of_tests; ++count)
	{
		amount_of_elements = get_amount_of_elements(count);
		for (unsigned int i = { 0 }; i < number_of_measurements; ++i)
		{
			for (unsigned int i = { 0 }; i < amount_of_elements; ++i)
			{
				v.push_back(i);
			}
			double cap = double(v.capacity());
			calc_time.push_back(cap);
		}
		average_time.push_back(average(calc_time));
		cout << endl << "Average capacity(amount of elements " << amount_of_elements << "): " << average_time[count] << endl;
		v.clear();
		calc_time.clear();
	}
	results = "Results for Dynamics of \"capacity\" changes when adding elements to the vector\n";
	for (const auto it : average_time)
	{
		results += boost::lexical_cast<string>(it);
		results += "\n";
	}
	write_to_file(results);
	results.clear();
	average_time.clear();
	v.clear();
	// Вычисляем динамику изменения capacity при удалении элементов из вектора
	cout << endl << "Dynamics of \"capacity\" changes when deleting elements from the vector:" << endl;
	for (unsigned int count = { 0 }; count < count_of_tests; ++count)
	{
		amount_of_elements = get_amount_of_elements(count);
		for (unsigned int i = { 0 }; i < number_of_measurements; ++i)
		{
			for (unsigned int i = { 0 }; i < amount_of_elements; ++i)
			{
				v.push_back(i);
			}
			for (unsigned int i = { 0 }; i < amount_of_elements; ++i)
			{
				v.pop_back();
			}
			double cap = double(v.capacity());
			calc_time.push_back(cap);
		}
		average_time.push_back(average(calc_time));
		cout << endl << "Average capacity(amount of elements " << amount_of_elements << "): " << average_time[count] << endl;
		v.clear();
		calc_time.clear();
	}
	results = "Results for Dynamics of \"capacity\" changes when deleting elements from the vector\n";
	for (const auto it : average_time)
	{
		results += boost::lexical_cast<string>(it);
		results += "\n";
	}
	write_to_file(results);
	results.clear();
	average_time.clear();
	v.clear();
}

void multimap_timer()
{
	using std::cout;
	using std::endl;
	using std::multimap;
	using std::string;
	multimap<unsigned int, unsigned int> m;
	string results;
	clock_t start;
	clock_t end;
	double cpu_time_used;
	// Вычисляем изменение времени добавления элемента с одним и тем же ключом
	cout << endl << "Change the time to add an element with the same key to multimap:" << endl;
	for (unsigned int count = { 0 }; count < count_of_tests; ++count)
	{
		amount_of_elements = get_amount_of_elements(count);
		for (unsigned int i = { 0 }; i < number_of_measurements; ++i)
		{
			start = clock();
			for (unsigned int i = { 0 }; i < amount_of_elements; ++i)
			{
				m.insert(std::pair<unsigned int,unsigned int>(count,i));
			}
			end = clock();
			cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
			calc_time.push_back(cpu_time_used);
		}
		average_time.push_back(average(calc_time));
		cout << endl << "Average time(amount of elements " << amount_of_elements << "): " << average_time[count] << endl;
		m.clear();
		calc_time.clear();
	}
	results = "Results for Change the time to add an element with the same key to multimap (Complexity: If a single element is inserted, "
	"logarithmic in size in general, but amortized constant if a hint is given and the position given is the optimal.)\n";
	for (const auto it : average_time)
	{
		results += boost::lexical_cast<string>(it);
		results += "\n";
	}
	write_to_file(results);
	results.clear();
	average_time.clear();
	m.clear();

}

void set_timer()
{
}

void unorderedmap_timer()
{
}

void write_to_file(const std::string & str)
{
	std::ofstream fout;
	fout.open("C:\\cpp\\baumanclasses\\results_for_lab14\\results.txt", std::ios_base::app);
	if (!fout.is_open())
	{
		std::cout << std::endl << "[-] Error! File wasn't opened." << std::endl;
		return;
	}
	fout << str;
}

double average(const std::vector<double>& time_)
{
	double sum = { 0.0 };
	for (const auto it : time_)
	{
		sum += it;
	}
	return sum / time_.size();
}

unsigned int get_amount_of_elements(const unsigned int& index)
{
	if (index == 0)
	{
		return 10;
	}
	else if (index == 1)
	{
		return 100;
	}
	else if (index == 2)
	{
		return 1000;
	}
	else if (index == 3)
	{
		return 10000;
	}
	else if (index == 4)
	{
		return 50000;
	}
	else if (index == 5)
	{
		return 100000;
	}
	else if (index == 6)
	{
		return 500000;
	}
}
