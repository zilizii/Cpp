#include <iostream>
#include <iomanip>
#include <string>
#include <initializer_list>
#include <cassert>
#include <array>
#include <algorithm>
#include "FixedSizedArray.hpp"


struct Entity{
	std::string name;
	int x;
	int y;
	Entity():name("Unknown"),x(0),y(0){}
	Entity(std::string name, int xPos, int yPos):name(name),x(xPos),y(yPos){
		std::cout << "Log: Created entity " << name << std::endl;
	}
	~Entity(){
		std::cout << "Log: Destroyed entity " << name << std::endl;
	}

};




int main(){

	Entity e{};
	std::array<Entity,2> arr = {Entity("Player",1,2), Entity("Enemy",3,4)};
	
	using T = FixedSizedArray<int>;
	std::cout << std::left << std::setw(30) << std::setfill('.') << "Test FixedSizedArray" << std::endl;
	T c(5);
	T c2 {5};
	std::cout << std::setw(30) << std::setfill('*') << "Entity test" << std::endl;
	std::cout << e.name << std::endl;
	std::cout << e.x << std::endl;
	std::cout << e.y << std::endl;


	std::cout << std::setw(30) << std::setfill('.') << "Test of the FixedSizedArray" << std::endl;
	c[4]=-15;

	std::cout << std::setw(30) << std::setfill('.') << "c : " << std::endl;
	for(const auto& e : c){
		std::cout<< e << std::endl;
	}
	
	std::cout << std::setw(30) << std::setfill('.') << "c2 : " << std::endl;
	for(const auto& e : c2){
		std::cout<< e << std::endl;
	}

	

	return 0;
}
