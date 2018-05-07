/*	
	vector class

*/
#include <iostream>

template <typename T>
class vector {
public :
	static const size_t defaultCap = 10;

	vector(vector&& v) {
		this->curCap = v.cap;
		this->curSize = v.size;
		this->elements = v.elements;
	}

	vector(const size_t cap = defaultCap)
	{
		curCap = cap;
		elements = new T[curCap];
		curSize = 0;
	}
	
	~vector()
	{
		delete[] elements;
		elements = nullptr;
	}

	const bool reserve(const size_t cap)
	{
		curSize = size;
		//todo : moveElements and extends Vector
		return true;
	}
	
	const size_t& size() const
	{
		return curSize;
	}

	const size_t& cap() const {
		return curCap;
	}

	const bool insert(const T& target, const int pos) {
		//todo : insert method
		return true;
	}

	const bool move(vector& v){
		this = v;
		return true;
	}
	
	//copy
	vector<T>& operator = (vector& v) {
		if (this == &v) return *this;
		delete[] elements;
		this->elements = new T[curCap];
		copyElements(v.elements,v.curSize);
		this->curSize = v.curSize;
		this->curCap = v.curCap;
		std::cout << "copied" << std::endl;
		return *this;
	}
	//move
	vector<T>& operator = (vector&& v) {
		if (this == &v) return *this;
		//delete[] elements;
		this->curSize = v.curSize;
		this->curCap = v.curCap;
		this->elements = v.elements;
		v.curSize = 0;
		v.curCap = 0;
		v.elements = nullptr;
		std::cout << "moved" << std::endl;
		return *this;
	}

private :
	
	size_t curSize;
	size_t curCap;
	T* elements;

	const bool isInBound(const int pos) {
		if (pos < curCap) return true;
		return false;
	}

	const bool copyElements(const T* src,const size_t len) {

		for (auto i = 0; i < len; ++i) {
			elements[i] = src[i];
		}
		return true;
	}


};

