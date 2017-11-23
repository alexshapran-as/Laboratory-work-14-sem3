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
#endif
