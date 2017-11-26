#include "timer.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <boost/lexical_cast.hpp>
#include <ctime>
#include <vector>
#include <deque>
#include <map>
#include <set>
#include <unordered_map>
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
	vector<CopiedObjects<int>> v_copy;
	vector<MovableObjects<int>> v_move;
	deque<int> d;
	deque<CopiedObjects<int>> d_copy;
	deque<MovableObjects<int>> d_move;
	string results;
	clock_t start;
	clock_t end;
	double cpu_time_used;
	// Вычисляем сложность алгоритма доступа к элементу вектора
	cout << endl << "Vector" << endl << endl << "Complexity of operation \"at()\":" << endl;
	for (unsigned int count = { 0 }; count < count_of_tests; ++count)
	{
		amount_of_elements = get_amount_of_elements(count);
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
	// Вычисляем сложность добавления элемента в конец вектора
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
	number_of_measurements = { 10 };
	// Вычисляем сложность добавления элемента в конец вектора (копируемые объекты)
	cout << endl << "Complexity of operation \"push_back()\" for copied objects:" << endl;
	for (unsigned int count = { 0 }; count < count_of_tests; ++count)
	{
		amount_of_elements = get_amount_of_elements(count);
		for (unsigned int i = { 0 }; i < number_of_measurements; ++i)
		{
			CopiedObjects<int> copied_object(i);
			start = clock();
			for (unsigned int i = { 0 }; i < amount_of_elements; ++i)
			{
				v_copy.push_back(copied_object);
			}
			end = clock();
			cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
			calc_time.push_back(cpu_time_used);
		}
		average_time.push_back(average(calc_time));
		cout << endl << "Average time(amount of elements " << amount_of_elements << "): " << average_time[count] << endl;
		v_copy.clear();
		calc_time.clear();
	}
	results = "Results for operation \"push_back()\" for copied objects in vector\n";
	for (const auto it : average_time)
	{
		results += boost::lexical_cast<string>(it);
		results += "\n";
	}
	write_to_file(results);
	results.clear();
	average_time.clear();
	v_copy.clear();
	// Вычисляем сложность добавления элемента в конец вектора (перемещаемые объекты)
	cout << endl << "Complexity of operation \"push_back()\" for moveable objects:" << endl;
	for (unsigned int count = { 0 }; count < count_of_tests; ++count)
	{
		amount_of_elements = get_amount_of_elements(count);
		for (unsigned int i = { 0 }; i < number_of_measurements; ++i)
		{
			MovableObjects<int> movable_object(i);
			start = clock();
			for (unsigned int i = { 0 }; i < amount_of_elements; ++i)
			{
				v_move.push_back(std::move(movable_object));
			}
			end = clock();
			cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
			calc_time.push_back(cpu_time_used);
		}
		average_time.push_back(average(calc_time));
		cout << endl << "Average time(amount of elements " << amount_of_elements << "): " << average_time[count] << endl;
		v_move.clear();
		calc_time.clear();
	}
	results = "Results for operation \"push_back()\" for movable objects in vector\n";
	for (const auto it : average_time)
	{
		results += boost::lexical_cast<string>(it);
		results += "\n";
	}
	write_to_file(results);
	results.clear();
	average_time.clear();
	v_move.clear();

	cout << endl << endl << "Deque" << endl;
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
	// Вычисляем сложность добавления элемента в конец deque
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
	// Вычисляем сложность добавления элемента в конец deque (копируемые объекты)
	cout << endl << "Complexity of operation \"push_back()\" for copied objects:" << endl;
	for (unsigned int count = { 0 }; count < count_of_tests; ++count)
	{
		amount_of_elements = get_amount_of_elements(count);
		for (unsigned int i = { 0 }; i < number_of_measurements; ++i)
		{
			CopiedObjects<int> copied_object(i);
			start = clock();
			for (unsigned int i = { 0 }; i < amount_of_elements; ++i)
			{
				d_copy.push_back(copied_object);
			}
			end = clock();
			cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
			calc_time.push_back(cpu_time_used);
		}
		average_time.push_back(average(calc_time));
		cout << endl << "Average time(amount of elements " << amount_of_elements << "): " << average_time[count] << endl;
		d_copy.clear();
		calc_time.clear();
	}
	results = "Results for operation \"push_back()\" for copied objects in deque\n";
	for (const auto it : average_time)
	{
		results += boost::lexical_cast<string>(it);
		results += "\n";
	}
	write_to_file(results);
	results.clear();
	average_time.clear();
	d_copy.clear();
	// Вычисляем сложность добавления элемента в конец deque (перемещаемые объекты)
	cout << endl << "Complexity of operation \"push_back()\" for moveable objects:" << endl;
	for (unsigned int count = { 0 }; count < count_of_tests; ++count)
	{
		amount_of_elements = get_amount_of_elements(count);
		for (unsigned int i = { 0 }; i < number_of_measurements; ++i)
		{
			MovableObjects<int> movable_object(i);
			start = clock();
			for (unsigned int i = { 0 }; i < amount_of_elements; ++i)
			{
				d_move.push_back(std::move(movable_object));
			}
			end = clock();
			cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
			calc_time.push_back(cpu_time_used);
		}
		average_time.push_back(average(calc_time));
		cout << endl << "Average time(amount of elements " << amount_of_elements << "): " << average_time[count] << endl;
		d_move.clear();
		calc_time.clear();
	}
	results = "Results for operation \"push_back()\" for movable objects in deque\n";
	for (const auto it : average_time)
	{
		results += boost::lexical_cast<string>(it);
		results += "\n";
	}
	write_to_file(results);
	results.clear();
	average_time.clear();
	d_move.clear();

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
	cout << endl << endl << "Multimap" << endl;
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
	using std::cout;
	using std::endl;
	using std::set;
	using std::string;
	set<int> s;
	string results;
	clock_t start;
	clock_t end;
	double cpu_time_used;
	cout << endl << endl << "Set" << endl;
	// Вычисляем время работы поиска при использовании метода класса
	cout << endl << "Complexity of operation \"find()\" in set:" << endl;
	for (unsigned int count = { 0 }; count < count_of_tests; ++count)
	{
		amount_of_elements = get_amount_of_elements(count);
		for (unsigned int i = { 0 }; i < amount_of_elements; ++i)
		{
			s.insert(i);
		}
		int element = amount_of_elements - rand() % (1 + amount_of_elements);
		for (unsigned int i = { 0 }; i < number_of_measurements; ++i)
		{
			start = clock();
			s.find(element);
			end = clock();
			cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
			calc_time.push_back(cpu_time_used);
		}
		average_time.push_back(average(calc_time));
		cout << endl << "Average time(amount of elements " << amount_of_elements << "): " << average_time[count] << endl;
		s.clear();
		calc_time.clear();
	}
	results = "Results for operation \"find()\" in set (Complexity: Logarithmic in size/O(log(n)))\n";
	for (const auto it : average_time)
	{
		results += boost::lexical_cast<string>(it);
		results += "\n";
	}
	write_to_file(results);
	results.clear();
	average_time.clear();
	s.clear();
	// Вычисляем время работы поиска при использовании внешней функции из <algorithm> для set
	cout << endl << "Complexity of operation \"std::find()\" from <algorithm> for set:" << endl;
	for (unsigned int count = { 0 }; count < count_of_tests; ++count)
	{
		amount_of_elements = get_amount_of_elements(count);
		for (unsigned int i = { 0 }; i < amount_of_elements; ++i)
		{
			s.insert(i);
		}
		int element = amount_of_elements - rand() % (1 + amount_of_elements);
		for (unsigned int i = { 0 }; i < number_of_measurements; ++i)
		{
			start = clock();
			std::find(s.begin(), s.end(),element);
			end = clock();
			cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
			calc_time.push_back(cpu_time_used);
		}
		average_time.push_back(average(calc_time));
		cout << endl << "Average time(amount of elements " << amount_of_elements << "): " << average_time[count] << endl;
		s.clear();
		calc_time.clear();
	}
	results = "Results for operation \"std::find()\" from <algorithm> for set (Complexity: Up to linear in the distance between first and last: Compares elements until a match is found/O(n))\n";
	for (const auto it : average_time)
	{
		results += boost::lexical_cast<string>(it);
		results += "\n";
	}
	write_to_file(results);
	results.clear();
	average_time.clear();
	s.clear();
}

void unorderedmap_timer()
{
	using std::cout;
	using std::endl;
	using std::unordered_map;
	using std::string;
	unordered_map<int, int> u_m;
	string results;
	clock_t start;
	clock_t end;
	double cpu_time_used;
	cout << endl << endl << "Unordered map" << endl;
	// Отслеживание попадания элементов в конкретный bucket (например, в bucket #1) и фиксирование размеров всех bucket
	number_of_measurements = { 1 }; // Очень долгие вычисления, поэтому уменьшаем количество пересчетов
	cout << endl << "Tracking of falling of elements in a concrete bucket and fixing of the sizes of all buckets (using from 10 to 50000 elements)" << endl;
	results = "Results for Tracking of falling of elements in a concrete bucket and fixing of the sizes of all buckets\n";
	for (unsigned int count = { 0 }; count < count_of_tests; ++count)
	{
		amount_of_elements = get_amount_of_elements(count);
		if (amount_of_elements == 100000)
			break;
		unsigned int size = { 0 };
		unsigned int count_of_buckets = { 0 };
		for (unsigned int i = { 0 }; i < number_of_measurements; ++i)
		{
			size = { 0 };
			for (unsigned int i = { 0 }; i < amount_of_elements; ++i)
			{
				u_m.insert(std::pair<int,int>(i,i));
				auto it = u_m.begin();
				for (unsigned int step = { 0 }; step != i; ++step)
				{
					++it;
				}
				if (u_m.bucket(it->first) == 1)
				{
					cout << endl << "Element [" << it->first << "," << it->second << "] is in bucket #"
					<< u_m.bucket(it->first);
					results += "\nElement [";
					results += boost::lexical_cast<string>(it->first);
					results += ",";
					results += boost::lexical_cast<string>(it->second);
					results += "] is in bucket #";
					results += boost::lexical_cast<string>(u_m.bucket(it->first));
					results += "\n";
				}
			}
			count_of_buckets = u_m.bucket_count();
			for (unsigned int j = { 0 }; j < count_of_buckets; ++j)
			{
				size += u_m.bucket_size(j);
			}
			u_m.clear();
		}
		cout << endl << "Count of buckets is " << count_of_buckets;
		cout << endl << "Size of all buckets is " << size;
		results += "Count of buckets is ";
		results += boost::lexical_cast<string>(count_of_buckets);
		results += "\nSize of all buckets is ";
		results += boost::lexical_cast<string>(size);
		u_m.clear();
	}
	u_m.clear();
	number_of_measurements = { 10 };
	write_to_file(results);
	results.clear();
	u_m.clear();
	// Оценка сложности поиска для unordered_map
	cout << endl << "Complexity of operation \"find()\" in unordered_map (standart hash_function):" << endl;
	for (unsigned int count = { 0 }; count < count_of_tests; ++count)
	{
		amount_of_elements = get_amount_of_elements(count);
		for (unsigned int i = { 0 }; i < amount_of_elements; ++i)
		{
			u_m.insert(std::pair<int,int>(i,i));
		}
		int element = amount_of_elements - rand() % (1 + amount_of_elements);
		for (unsigned int i = { 0 }; i < number_of_measurements; ++i)
		{
			start = clock();
			u_m.find(element);
			end = clock();
			cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
			calc_time.push_back(cpu_time_used);
		}
		average_time.push_back(average(calc_time));
		cout << endl << "Average time(amount of elements " << amount_of_elements << "): " << average_time[count] << endl;
		u_m.clear();
		calc_time.clear();
	}
	results = "Results for operation \"find()\" in unordered_map with standart hash_function (Complexity: Average case: constant. Worst case: linear in container size./O(1) or O(n)\n";
	for (const auto it : average_time)
	{
		results += boost::lexical_cast<string>(it);
		results += "\n";
	}
	write_to_file(results);
	results.clear();
	average_time.clear();
	u_m.clear();
    // Оценка сложности поиска в случае "плохой" функции хэширования для пользовательского типа
	number_of_measurements = { 1 };
	unordered_map<CustomType<int>, int> u_m_custom;
	cout << endl << "Complexity of operation \"find()\" in unordered_map (custom hash_function):" << endl;
	for (unsigned int count = { 0 }; count < count_of_tests; ++count)
	{
		amount_of_elements = get_amount_of_elements(count);
		// Из-за очень длинного периода вставки элементов необходимо уменьшить их кол-во
		if (amount_of_elements > 50000)
			break;
		for (unsigned int i = { 0 }; i < amount_of_elements; ++i)
		{
			CustomType<int> custom_elem(i,i);
			u_m_custom.insert(std::pair<CustomType<int>, int>(custom_elem, i));
		}
		CustomType<int> element (10, 10);
		for (unsigned int i = { 0 }; i < number_of_measurements; ++i)
		{
			start = clock();
			u_m_custom.find(element);
			end = clock();
			cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
			calc_time.push_back(cpu_time_used);
		}
		average_time.push_back(average(calc_time));
		cout << endl << "Average time(amount of elements " << amount_of_elements << "): " << average_time[count] << endl;
		u_m_custom.clear();
		calc_time.clear();
	}
	results = "Results for operation \"find()\" in unordered_map with custom hash_function\n";
	for (const auto it : average_time)
	{
		results += boost::lexical_cast<string>(it);
		results += "\n";
	}
	write_to_file(results);
	results.clear();
	average_time.clear();
	u_m_custom.clear();
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

template<class T>
CopiedObjects<T>::CopiedObjects(const CopiedObjects<T> & other)
{
	if (this == &other)
		return;
	data = other.data;
}

template<class T>
CopiedObjects<T> CopiedObjects<T>::operator=(const CopiedObjects<T> & other)
{
	if (this == &other)
		return *this;
	data = other.data;
}

template<class T>
MovableObjects<T>::MovableObjects(const MovableObjects<T> && other)
{
	if (this == &other)
		return;
	data = std::move(other.data);
}

template<class T>
MovableObjects<T> MovableObjects<T>::operator=(const MovableObjects<T> && other)
{
	if (this == &other)
		return *this;
	data = std::move(other.data);
}

template <class T>
bool operator==(const CustomType<T>& obj1, const CustomType<T>& obj2)
{
	return obj1.first == obj2.first && obj1.second == obj2.second;
}
