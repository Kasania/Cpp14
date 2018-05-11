/*	
	vector class

*/
#include <initializer_list>
#include <stdexcept>

template <typename T>
class vector {
public :
	static const size_t defaultCap = 10;

	vector(const size_t cap = defaultCap) {
		curCap = cap;
		curSize = 0;
		lastPos = 0;
		elements = new T[curCap];
		initializeElements(elements, firstPos, curCap);
	}
	vector(const vector& v) {
		copy(v);
	}
	vector(vector&& v) {
		move(v);
	}

	vector(const std::initializer_list<T> values) {
		if (values.size() > defaultCap) {
			curCap = values.size();
		}
		else {
			curCap = defaultCap;
		}
		elements = new T[curCap];
		curSize = 0;
		for (auto i = values.begin(); i < values.end(); ++i) {
			insert(*i);
			++curSize;
		}
		initializeElements(elements, curSize, curCap);
		lastPos = curSize;
	}
	
	~vector()	{
		delete[] elements;
		elements = nullptr;
	}

	const bool reserve(const size_t cap)	{

		T* newElements = new T[cap];
		initializeElements(newElements, copyElements(elements, newElements, curCap), cap);
		curCap = cap;
		delete[] elements;//heap error occur!
		elements = newElements;
		return true;
	}
	
	const size_t& size() const {
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
		if (pos >= curCap) throw std::length_error("Wrong Position!");
		return elements[pos];
	}

	const bool move(vector& v){
		curCap = v.curCap;
		curSize = v.curSize;
		lastPos = v.lastPos;
		delete[] elements;
		elements = v.elements;
		v.release();
		return true;
	}

	const bool copy(vector& v) {
		this->curCap = v.curCap;
		this->curSize = v.curSize;
		lastPos = v.lastPos;
		delete[] elements;
		elements = new T[curCap];
		copyElements(v.elements, v.curCap);
	}
	
	//copy
	vector<T>& operator = (vector& v) {
		if (this == &v) return *this;
		delete[] elements;
		this->elements = new T[curCap];
		initializeElements(elements, copyElements(v.elements, elements, v.curSize), curCap);
		
		this->curSize = v.curSize;
		this->curCap = v.curCap;
		lastPos = v.lastPos;
		return *this;
	}
	//move
	vector<T>& operator = (vector&& v) {
		if (this == &v) return *this;
		delete[] elements;
		this->curSize = v.curSize;
		this->curCap = v.curCap;
		this->elements = v.elements;
		lastPos = v.lastPos;
		v.release();
		return *this;
	}

private :
	
	size_t curSize;
	size_t curCap;
	size_t lastPos;
	size_t firstPos = 0;
	T* elements;
	size_t elementSize = sizeof T;

	//only use this for move elements
	const bool release() {
		curSize = 0;
		curCap = 0;
		lastPos = 0;
		elements = nullptr;
		return true;
	}

	const bool isInBound(const int pos) {
		if (pos < curCap) return true;
		return false;
	}

	const size_t copyElements(const T* src, const size_t len) {
		return copyElements(src, elements, firstPos, len);
	}
	const size_t copyElements(const T* src, T* dst, const size_t len) {
		return copyElements(src, dst, 0, len);
	}
	//end : lastElementPos + 1
	const size_t copyElements(const T* src, T* dst, const size_t start, const size_t end) {
		auto i = start;
		for (; i < end; ++i) {
			*(dst + i) = *(src + i);
		}
		return i;
	}
	//end : lastElementPos + 1
	const bool copyElementsReverse(const T* src, T* dst, const size_t start, const size_t end) {

		for (auto i = end-1; i >= start; --i) {
			dst[i] = src[i];
		}
		return true;
	}

	const size_t initializeElements(T* target, const size_t start, const size_t end) {
		for (auto i = start; i < end; ++i) {
			*(elements + i) = T();
		}
		return end;
	}

	const bool moveElement(T* src, T* dst) {
		dst = src;
		src = nullptr;
		return true;
	}
};

