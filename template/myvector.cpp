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
		}
		initializeElements(elements, lastPos, curCap);
	}
	
	~vector()	{
		for(auto i = firstPos ;  i<curCap; ++i)
		alloc.destroy(elements+i);
		alloc.deallocate(elements, curCap);
		elements = nullptr;
	}

	const bool reserve() {
		return reserve(defaultIncresement());
	}
	const bool reserve(const size_t cap) {

		T* newElements = alloc.allocate(cap);
		initializeElements(newElements, moveElement(elements, newElements, 0, curCap), cap);
		deleteElements(elements,curCap);
		elements = newElements;
		curCap = cap;
		return true;	
	}
	
	const size_t& start() const {
		return firstPos;
	}
	const size_t& end() const {
		return lastPos;
	}

	const size_t& cap() const {
		return curCap;
	}

	const bool insert(const T& target, const size_t pos) {
		if(pos < firstPos) throw std::length_error("Wrong Position!");
		if (pos >= curCap) reserve(pos + 1);

		if (pos >= lastPos) {
			lastPos = pos;
			elements[lastPos++] = target;
		}
		else {
			if (curCap <= lastPos+1) reserve();
			moveElement(elements, (elements + pos + 1), pos, lastPos++);
			elements[pos] = target;
		}

		return true;
	}

	const bool insert(const T& target) {
		if (curCap <= lastPos) reserve();
		elements[lastPos++] = target;
		return true;
	}


	T& at(const size_t pos){
		checkBound(pos);
		return elements[pos];
	}

	const T& c_at(const size_t pos){
		return at(pos);
	}

	const bool replace(const T& target, const size_t pos) {
		checkBound(pos);
		alloc.destroy(elements+pos);
		elements[pos] = target;
		return true;
	}

	const bool replace(const T&& target, const size_t pos) {
		checkBound(pos);
		alloc.destroy(elements + pos);
		elements[pos] = target;
		return true;
	}

	const bool erase(const size_t pos) {
		checkBound(pos);

		if (pos == lastPos-1) {
			replace(T(), --lastPos);
		}
		else {
			alloc.destroy((elements + pos));
			moveElement(elements, (elements + pos), pos + 1, lastPos--);
		}
		//if pos == last, erase at last, --last
		//if pos < last, destroy at pos, move forward, last--
		return true;
	}

	const bool move(vector& v){
		deleteElements(elements,curCap);
		curCap = v.curCap;
		lastPos = v.lastPos;
		elements = v.elements;
		v.release();
		return true;
	}

	const bool copy(vector& v) {
		deleteElements(elements,curCap);
		this->curCap = v.curCap;
		lastPos = v.lastPos;
		elements = alloc.allocate(curCap);
		copyElements(v.elements, v.curCap);
	}
	
	//copy
	vector<T>& operator = (vector& v) {
		if (this == &v) return *this;
		deleteElements(elements, curCap);
		this->elements = alloc.allocate(curCap);
		initializeElements(elements, copyElements(v.elements, elements, v.lastPos), curCap);
		this->curCap = v.curCap;
		lastPos = v.lastPos;
		return *this;
	}
	//move
	vector<T>& operator = (vector&& v) {
		if (this == &v) return *this;
		deleteElements(elements,curCap);
		this->curCap = v.curCap;
		this->elements = v.elements;
		lastPos = v.lastPos;
		v.release();
		return *this;
	}

private :
	
	static const size_t firstPos = 0;
	const size_t elementSize = sizeof T;
	size_t curSize = 0;
	size_t curCap = 0;
	size_t lastPos = 0;
	T* elements;
	std::allocator<T> alloc;

	const size_t defaultIncresement() {
		return static_cast<size_t>(curCap * 1.5 + 1);
	}

	//only use this for move elements
	const bool release() {
		curCap = 0;
		lastPos = 0;
		elements = nullptr;
		return true;
	}

	const bool checkBound(const size_t pos) {
		if (pos >= curCap || pos < firstPos) throw std::length_error("Wrong Position!");
		return true;
	}

	void destroyElements(T* src,const size_t len) {
		destroyElements(src, firstPos, len);
	}

	void destroyElements(T* src, const size_t start, const size_t end) {
		for (auto i = start; i<end; ++i)
			alloc.destroy(elements + i);
	}

	void deleteElements(T* src, const size_t len) {
		deleteElements(src, firstPos, len);

	}
	void deleteElements(T* src, const size_t start, const size_t end) {
		destroyElements(src, start, end);
		alloc.deallocate((src+start),(end-start));
		src = nullptr;
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


