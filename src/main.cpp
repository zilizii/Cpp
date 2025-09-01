#include <iostream>
#include <string>
#include <initializer_list>
#include <cassert>

struct Entity{
	std::string name;
	int x;
	int y;
};

template<typename T>
class FixedSizedArray{
private:
	/*Implement Iterator here*/
	struct iterator{
		
		// Properties of the iterator
		using Category		= std::forward_iterator_tag;
		using Distance		= std::ptrdiff_t;
		// Shorthand, reduce chance of mistakes
		using value_type	= T;
		using Pointer		= T*;
		using Reference		= T&;

		//Constructor
		iterator(T* ptr): mPtr(ptr){}

		//++it
		iterator operator++(){
			++mPtr;
			return *this;
		}
		
		//it++
		iterator operator++(T){
			iterator tmp = *this;
			++(*this);
			return  tmp;
		}
		// Dereference the unary operator
		// get back the item (actual data)
		// where the iterator is pointing to
		Reference operator*() const{
			return *mPtr;
		}

		Pointer operator->(){
			return mPtr;
		}

		friend bool operator==(const iterator& lhs, const iterator& rhs){
			return lhs.mPtr == rhs.mPtr;
		}
		friend bool operator!=(const iterator& lhs, const iterator& rhs){
			return lhs.mPtr != rhs.mPtr;
		}



	private:
			Pointer mPtr;
	};


private:
	T* 	mData; 		//Underlying Data
	size_t 	mCapacity;	//Capacity of the data structure

public:
	//Constructor
	//Initialize memory
	FixedSizedArray(int capacity) : mCapacity(capacity){
		mData = new T[mCapacity];
	}
/*
	template <typename... _Rest>
	FixedSizedArray(T _first, _Rest... _rest)
	: mData(new T[sizeof...(_rest) + 1]{_first, _rest...}), 
          mCapacity(sizeof...(_rest) + 1) {}
*/


	//Constructor for initializer list
	//Init and copy data to the string
	FixedSizedArray(std::initializer_list<T> l) 
	:  mCapacity(l.size()) {
		mData = new T[mCapacity];
		std::copy(l.begin(), l.end(), mData);
	}
	   


	//Destructor
	~FixedSizedArray(){
		if(nullptr != mData){
			delete[] mData;
			mData = nullptr;
		}
	}

	T& operator[](size_t indexOf){
		assert(indexOf<mCapacity && "Address Overflow detected");
		return mData[indexOf];
	}

	size_t capacity(){
		return mCapacity;
	}
	
	iterator begin(){
		return iterator(&mData[0]);
	}

	iterator end(){
		return iterator(&mData[mCapacity]);
	}
};


int main(){

	Entity e{};
	using T = FixedSizedArray<int>;
	
	T c(5);
	T c2 {5};
	std::cout << e.name << std::endl;
	std::cout << e.x << std::endl;
	std::cout << e.y << std::endl;
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
