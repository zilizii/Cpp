#include <iostream>
#include <iomanip>
#include <string>
#include <initializer_list>
#include <cassert>
#include <array>
#include <algorithm>
#include <utility>  	
#include <memory>			// for std::move and std::forward
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

constexpr bool operator==(const Entity &a, const Entity &b) {
	return a.name == b.name && a.x == b.x && a.y == b.y && a.active == b.active;
}
constexpr auto operator<=>(const Entity &a, const Entity &b) {
	if (auto cmp = a.name <=> b.name; cmp != 0) return cmp;
	if (auto cmp = a.x <=> b.x; cmp != 0) return cmp;
	if (auto cmp = a.y <=> b.y; cmp != 0) return cmp;
	return a.active <=> b.active;
}

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
}
{
	std::cout << std::setw(30) << std::setfill('.') << "Test Perfect Forwarding" << std::endl;

	testObject object;
	const testObject const_object;
	PerfectForwardToUseObject(object);
	PerfectForwardToUseObject(const_object);
	PerfectForwardToUseObject(std::move(object));

	std::cout << std::setw(30) << std::setfill('.') << "Test end" << std::endl;
}
	// Test of smart pointer
	// automatic destruction of the object when the pointer goes out of scope
	// no need to call delete
	// no memory leak
	// no dangling pointer
	// no double free
	// no need to implement copy constructor and assignment operator
	std::cout << std::setw(30) << std::setfill('.') << "Test of smart pointer" << std::endl;
	std::unique_ptr<Entity> pEntity (new Entity("Unique",5,6));
	LogEntityForTest(*pEntity);
	// using make_unique is safer because it avoids the possibility of memory leak
	// if an exception is thrown between the new and the assignment to the unique_ptr
	// since C++14
	std::unique_ptr<Entity> pEntity2 = std::make_unique<Entity>( "Unique",5,6);
	LogEntityForTest(*pEntity2);
	std::cout  << std::boolalpha << "(pEntity <=> pEntity2) == 0 : " << ((*pEntity <=> *pEntity2) == 0 ) << std::endl;
	std::cout  << std::boolalpha << "(pEntity <=> pEntity2) < 0 : " << ((*pEntity <=> *pEntity2) < 0) << std::endl;
	// equality operator
	// should be true because the content of the two entities are the same
	// even if they are two different objects in memory
	// beware of the pointer comparison which would be false
	// the value comparison is done by dereferencing the pointers
	std::cout  << std::boolalpha << "(pEntity == pEntity2)  : " << ( *pEntity == *pEntity2 )  << std::endl;

	return 0;
}

void LogEntityForTest(Entity &e)
{
    std::cout << std::setw(30) << std::setfill('*') << "Entity test" << std::endl
    		  << "Name   : "<< e.name << std::endl
    		  << "x      : "   << e.x << std::endl
    		  << "y      : "   << e.y << std::endl
    		  << "Active : " << std::boolalpha << e.active << std::endl;
}
