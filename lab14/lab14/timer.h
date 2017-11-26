#ifndef TIMER_H
#define TIMER_H
#include <string>
#include <vector>
void vector_deque_timer();
void multimap_timer();
void set_timer();
void unorderedmap_timer();
void write_to_file(const std::string&);
double average(const std::vector<double>&);
unsigned int get_amount_of_elements(const unsigned int&);
static unsigned int number_of_measurements = { 10 };
static unsigned int amount_of_elements = { 10 };
const unsigned int count_of_tests = { 7 };
template <class T>
class CopiedObjects
{
	T data;
public:
	CopiedObjects(T data_) : data(data_) {}
	CopiedObjects(const CopiedObjects<T>& other);
	CopiedObjects<T> operator=(const CopiedObjects<T>& other);
	CopiedObjects(const CopiedObjects<T>&& other) = delete;
	CopiedObjects<T> operator=(const CopiedObjects&& other) = delete;
};
template <class T>
class MovableObjects
{
	T data;
public:
	MovableObjects(T data_) : data(data_) {}
	MovableObjects(const MovableObjects&& other);
	MovableObjects<T> operator=(const MovableObjects<T>&& other);
	MovableObjects(const MovableObjects<T>& other) = delete;
	MovableObjects<T> operator=(const MovableObjects<T>& other) = delete;
};
// Реализация функции хеширования для пользовательского типа
template <class T>
struct CustomType
{
	T first;
	T second;
	CustomType(T first_, T second_)
	{
		first = first_;
		second = second_;
	}
};
// Специализация уже существующих сущностей (это является разрешенным в стандарте C++)
namespace std
{
	template <class T>
	struct hash<CustomType<T>>
	{
		size_t operator()(const CustomType<T>& obj) const
		{
			hash<T> h;
			return h(obj.first) ^ h(obj.second);
		}
	};
}
#endif