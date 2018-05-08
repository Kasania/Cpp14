/*	
	vector class

*/
#include <iostream>

template <typename T>
class vector {
public :
	static const size_t defaultCap = 10;

	vector(vector&& v) {
		this->curCap = v.curCap;
		this->curSize = v.curSize;
		this->elements = v.elements;
		v.release();
		std::cout << "ap" << std::endl;
	}
	vector(const vector& v) {
		this->curCap = v.curCap;
		this->curSize = v.curSize;
		std::cout << "cp" << std::endl;
		copyElements(v.elements, v.curCap);
	}

	vector(const size_t cap = defaultCap)
	{
		curCap = cap;
		elements = new T[curCap];
		curSize = 0;
		std::cout << "dp" << std::endl;
	}
	
	~vector()
	{
		delete[] elements;
		elements = nullptr;
	}

	const bool reserve(const size_t cap)
	{
		T* newElements = new T[cap];
		copyElements(elements, newElements, curCap);
		curCap = cap;
		delete[] elements;
		elements = newElements;
		return true;
	}
	
	const size_t& size() const
	{
		return curSize;
	}

	const size_t& cap() const {
		return curCap;
	}

	const bool insert(const T& target, const size_t pos) {
		//todo : insert method
		return true;
	}

	const bool insert(const T& target) {
		if (curCap <= lastPos) reserve(curCap * 2);
		elements[lastPos++] = target;
		return true;
	}

	T& at(const size_t pos) {
		return elements[pos];
	}

	const bool move(vector& v){
		curCap = v.curCap;
		curSize = v.curSize;
		elements = v.elements;
		v.release();
		return true;
	}
	
	//copy
	vector<T>& operator = (vector& v) {
		if (this == &v) return *this;
		delete[] elements;
		this->elements = new T[curCap];
		copyElements(v.elements, elements, v.curSize);
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
		v.release();
		std::cout << "moved" << std::endl;
		return *this;
	}

private :
	
	size_t curSize;
	size_t curCap;
	size_t lastPos;
	T* elements;

	//only use move Methods
	const bool release() {
		curSize = 0;
		curCap = 0;
		elements = nullptr;
		return true;
	}

	const bool isInBound(const int pos) {
		if (pos < curCap) return true;
		return false;
	}

	const bool copyElements(const T* src, const size_t len) {
		return copyElements(src, elements, 0, len);
	}
	const bool copyElements(const T* src, T* dst, const size_t len) {
		return copyElements(src, dst, 0, len);
	}
	//end : lastElementPos + 1
	const bool copyElements(const T* src, T* dst, const size_t start, const size_t end) {
		for (auto i = start; i < end; ++i) {
			dst[i] = src[i];
			//error!
		}
		return true;
	}
	//end : lastElementPos + 1
	const bool copyElementsReverse(const T* src, T* dst, const size_t start, const size_t end) {

		for (auto i = end-1; i >= start; --i) {
			dst[i] = src[i];
		}
		return true;
	}

	const bool moveElement(T* src, T* dst) {
		dst = src;
		src = nullptr;
		return true;
	}
};

