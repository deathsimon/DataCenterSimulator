#include <random>
#include <ctime>
#include <iostream>
#include <random>

#define	AVGARRIVAL	60
#define SIMLENGTH	1800	// 30 minutes
#define WORKLOADS	5

int main(){
	int time = 0;

	std::random_device rd;
	std::mt19937 gen(rd());

	std::poisson_distribution<> d(AVGARRIVAL);
	std::uniform_int_distribution<> dis(0, WORKLOADS-1);

	while(time < SIMLENGTH){
		time += d(gen);
		std::cout << time <<'\t'<< dis(gen) << std::endl;
	};

	return 0;
}

