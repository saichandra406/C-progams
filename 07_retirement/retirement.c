#include <stdio.h>
#include <stdlib.h>

struct retire_info_t {
	int months;
	double contribution;
	double rate_of_return;
};
typedef	struct retire_info_t retire_info;

void print_line(int age, double balance) {
	printf("Age %3d month %2d you have $%.2f\n", age/12, age%12, balance);
}

double compute_balance(double initial, retire_info status) {
	return initial + (initial * status.rate_of_return / 12)
			+ status.contribution;
}

void retirement (int startAge,   //in months
                 double initial, //initial savings in dollars
                 retire_info working, //info about working
                 retire_info retired) //info about being retired
{
	int age = startAge;
	double balance = initial;
	for( int i = 1; i <= working.months; i++) {
		print_line(age, balance);
		age++;
		balance = compute_balance(balance, working);
	}
	for( int i = 1; i <= retired.months; i++) {
		print_line(age, balance);
		age++;
		balance = compute_balance(balance, retired);
	}
}

int main(void) {
	retire_info working = {489, 1000, 0.045}; 
	retire_info retired = {384, -4000, 0.01};
	int age = 327;
    double savings = 21345;
	retirement(age, savings, working, retired);
	
	return 0;
}

 
