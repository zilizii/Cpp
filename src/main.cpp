#include <iostream>
#include <string>
#include <initializer_list>
#include <cassert>
#include "FixedSizedArray.hpp"


struct Entity{
	std::string name;
	int x;
	int y;
};




int main(){

	Entity e{};
	using T = FixedSizedArray<int>;
	std::cout << "Test FixedSizedArray" << std::endl;
	T c(5);
	T c2 {5};
	std::cout << "Entity test" << std::endl;
	std::cout << e.name << std::endl;
	std::cout << e.x << std::endl;
	std::cout << e.y << std::endl;


	std::cout << "Test of the FixedSizedArray" << std::endl;
	c[4]=-15;

	std::cout<< "c : " << std::endl;
	for(const auto& e : c){
		std::cout<< e << std::endl;
	}
	
	std::cout<< "c2 : " << std::endl;
	for(const auto& e : c2){
		std::cout<< e << std::endl;
	}

	

	return 0;
}
