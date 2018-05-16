/*	
	vector class

*/
#include <initializer_list>
#include <stdexcept>
#include <memory>

template <typename T>
class vector {
public :
	static const size_t defaultCap = 10;

	

	vector(const size_t cap = defaultCap) {
		curCap = cap;
		elements = alloc.allocate(curCap);
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
		elements = alloc.allocate(curCap);
		for (auto i = values.begin(); i < values.end(); ++i) {
			insert(*i);
			++curSize;
		}
		initializeElements(elements, curSize, curCap);
		lastPos = curSize;
	}
	
	~vector()	{
		for(auto i = firstPos ;  i<curCap; ++i)
		alloc.destroy(elements+i);
		alloc.deallocate(elements, curCap);
		elements = nullptr;
	}

	const bool reserve(const size_t cap)	{

		T* newElements = new T[cap];
		initializeElements(newElements, moveElement(elements, newElements, 0, curCap), cap);
		delete[] elements;
		elements = newElements;
		curCap = cap;
		return true;	
	}
	
	const size_t& size() const {
		return curSize;
	}

	const size_t& cap() const {
		return curCap;
	}

	const bool insert(const T& target, const size_t pos) {
		if(pos < firstPos) throw std::length_error("Wrong Position!");
		if (pos > curCap) reserve(pos + 1);

		if (pos >= lastPos) {
			lastPos = pos;
			elements[lastPos++];
		}
		else {
			
			size_t oldLastPos = lastPos;
			//moveElement()
		}

		//todo : insert method
		//if pos >= last insert at pos, last = pos
		//else move back pos~last to pos+1~last+1 , insert at pos
		return true;
	}

	const bool insert(const T& target) {
		
		if (curCap <= lastPos) reserve(static_cast<int>(curCap * 1.5 + 1));
		elements[lastPos++] = target;
		return true;
	}

	T& at(const size_t pos) {
		if (pos >= curCap || pos < firstPos) throw std::length_error("Wrong Position!");
		return elements[pos];
	}

	const T& c_at(const size_t pos) {
		return at(pos);
	}

	const bool remove(const size_t pos) {
		if (pos >= curCap || pos < firstPos) throw std::length_error("Wrong Position!");
		~elements[pos];
		elements[pos] = T();
		return true;
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
	
	size_t curSize = 0;
	size_t curCap = 0;
	size_t lastPos = 0;
	size_t firstPos = 0;
	size_t elementSize = sizeof T;
	T* elements;
	std::allocator<T> alloc;

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
			*(dst + i) = *(src + i);
		}
		return true;
	}

	const size_t initializeElements(T* target, const size_t start, const size_t end) {
		for (auto i = start; i < end; ++i) {
			*(target + i) = T();
		}
		return end;
	}

	const size_t moveElement(T* src, T* dst, const size_t start, const size_t end) {
		std::_Uninitialized_move((src + start), (src + end + 1), dst, alloc); 
		return end;
	}
};


