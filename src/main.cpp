#include <iostream>
#include <iomanip>
#include <string>
#include <initializer_list>
#include <cassert>
#include <array>
#include <algorithm>
#include <utility>  				// for std::move and std::forward
#include "FixedSizedArray.hpp"


struct Entity{
	std::string name;
	int x;
	int y;
	bool active;
	Entity():name("Unknown"),x(0),y(0),active{false}{
		std::cout << "Log: Created entity " << name << std::endl;
	}
	Entity(std::string name, int xPos, int yPos):name(name),x(xPos),y(yPos),active{true}{
		std::cout << "Log: Created entity " << name << std::endl;
	}
	~Entity(){
		std::cout << "Log: Destroyed entity " << name << std::endl;
	}

};

void LogEntityForTest(Entity &e);

class testObject{
	public:
		testObject(){
			std::cout << "Log: Created testObject" << std::endl;
		}
		~testObject(){
			std::cout << "Log: Destroyed testObject" << std::endl;
		}

		void setName(const std::string &name) { mName = std::move(name);}
		std::string getName() const { return mName; }

	private:	
		std::string mName;
};

void UsetestObject(testObject &) {
  std::cout << "calling UsetestObject(Object &)" << std::endl;
}

void UsetestObject(const testObject &) {
  std::cout << "calling UsetestObject(const Object &)" << std::endl;
}

void UsetestObject(testObject &&) {
  std::cout << "calling UsetestObject(Object &&)" << std::endl;
}

template <typename T>
void PerfectForwardToUseObject(T&& x) {
  UsetestObject(std::forward<T>(x) );
}

int main()
{

    Entity e{};
	std::array<Entity,2> arr = {Entity("Player",1,2), Entity("Enemy",3,4)};
	
	using T = FixedSizedArray<int>;
	std::cout << std::left << std::setw(30) << std::setfill('.') << "Test FixedSizedArray" << std::endl;
	T c(5);
	T c2 {5};
	

    LogEntityForTest(e);
	for(auto& entity : arr){
		LogEntityForTest(entity);
	}



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

	std::cout << std::setw(30) << std::setfill('.') << "Test Perfect Forwarding" << std::endl;

	testObject object;
	const testObject const_object;
	PerfectForwardToUseObject(object);
	PerfectForwardToUseObject(const_object);
	PerfectForwardToUseObject(std::move(object));

	std::cout << std::setw(30) << std::setfill('.') << "Test end" << std::endl;

	return 0;
}

void LogEntityForTest(Entity &e)
{
    std::cout << std::setw(30) << std::setfill('*') << "Entity test" << std::endl
    		  << e.name << std::endl
    		  << e.x << std::endl
    		  << e.y << std::endl
    		  << std::boolalpha << e.active << std::endl;
}
