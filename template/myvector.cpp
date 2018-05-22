#include <initializer_list>
#include <stdexcept>
#include <memory>
#include <string>

template <typename T, class allocator = std::allocator<T>>
class vector {
public :
	static const size_t defaultCap = 10;
	
	vector(const size_t cap = defaultCap) noexcept;
	vector(const std::initializer_list<T> values); 
	vector(const vector& v);
	vector(vector&& v);
	
	~vector(); 

	const size_t& start() const; 
	const size_t& end() const; 
	const size_t& cap() const; 

	const bool reserve(); 
	const bool reserve(const size_t cap); 

	const bool resize(); 
	const bool resize(const size_t cap); 

	const bool insert(const T& target, const size_t pos); 
	const bool insert(const T& target); 

	T& at(const size_t pos); 
	const T& c_at(const size_t pos); 

	const bool replace(const T& target, const size_t pos); 
	const bool replace(const T&& target, const size_t pos); 

	const bool erase(const size_t pos); 

	vector<T>& move(vector& v); 

	vector<T>& copy(vector& v); 
	
	//copy
	vector<T>& operator = (vector& v); 
	//move
	vector<T>& operator = (vector&& v); 

	T& operator[](size_t pos); 
	const T& operator[](size_t pos) const; 

private :
	static const size_t firstPos = 0;
	const size_t elementSize = sizeof T;
	size_t curSize = 0;
	size_t curCap = 0;
	size_t lastPos = 0;
	T* elements;
	allocator alloc;
	size_t reservedCount = 0;

	const size_t defaultIncresement(); 

	//only use this for move elements
	const bool release(); 

	const bool checkBound(const size_t pos);
	void outOfBoundException();

	void destroyElements(T* src, const size_t len); 
	void destroyElements(T* src, const size_t start, const size_t end); 

	void deleteElements(T* src, const size_t len);
	void deleteElements(T* src, const size_t start, const size_t end); 

	const size_t copyElements(const T* src, const size_t len); 
	const size_t copyElements(const T* src, T* dst, const size_t len); 
	const size_t copyElements(const T* src, T* dst, const size_t start, const size_t end); 

	const size_t initializeElements(T* target, const size_t start, const size_t end); 

	const size_t moveElement(T* src, T* dst, const size_t start, const size_t end); 
	
};

template<typename T, class allocator>
vector<T, allocator>::vector(const size_t cap) noexcept
{
	curCap = cap;
	elements = alloc.allocate(curCap);
}

template<typename T, class allocator>
vector<T, allocator>::vector(const std::initializer_list<T> values)
{
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
}

template<typename T, class allocator>
vector<T, allocator>::vector(const vector & v)
{
	copy(v);
}

template<typename T, class allocator>
vector<T, allocator>::vector(vector && v)
{
	move(v);
}

template<typename T, class allocator>
vector<T, allocator>::~vector()
{
	for (auto i = firstPos; i<curCap; ++i)
		alloc.destroy(elements + i);

	alloc.deallocate(elements, curCap);

	elements = nullptr;
}

template<typename T, class allocator>
const size_t & vector<T, allocator>::start() const
{
	return firstPos;
}

template<typename T, class allocator>
const size_t & vector<T, allocator>::end() const
{
	return lastPos;
	//next insert position
}

template<typename T, class allocator>
const size_t & vector<T, allocator>::cap() const
{
	return curCap;
}

template<typename T, class allocator>
const bool vector<T, allocator>::reserve()
{
	return reserve(defaultIncresement());
}

template<typename T, class allocator>
const bool vector<T, allocator>::reserve(const size_t cap)
{
	if (cap == curCap) return true;
	T* newElements = alloc.allocate(cap);

	moveElement(elements, newElements, 0, curCap);
	deleteElements(elements, curCap);
	elements = newElements;
	curCap = cap;
	++reservedCount;
	return true;
}

template<typename T, class allocator>
const bool vector<T, allocator>::resize()
{
	return resize(curCap);
}

template<typename T, class allocator>
const bool vector<T, allocator>::resize(const size_t cap)
{
	if (cap >= lastPos) {
		reserve(cap);
	}
	initializeElements(elements, lastPos, cap);
	return true;
}

template<typename T, class allocator>
const bool vector<T, allocator>::insert(const T & target, const size_t pos)
{
	if (pos < firstPos) outOfBoundException();
	if (pos >= curCap) reserve(pos + 1);

	if (pos >= lastPos) {
		lastPos = pos;
		elements[lastPos++] = target;
	}
	else {
		if (curCap <= lastPos + 1) reserve();
		moveElement(elements, (elements + pos + 1), pos, lastPos++);
		elements[pos] = target;
	}
	return true;
}

template<typename T, class allocator>
const bool vector<T, allocator>::insert(const T & target)
{
	if (curCap <= lastPos) reserve();
	elements[lastPos++] = target;
	return true;
}

template<typename T, class allocator>
T & vector<T, allocator>::at(const size_t pos)
{
	checkBound(pos);
	return elements[pos];
}

template<typename T, class allocator>
const T & vector<T, allocator>::c_at(const size_t pos)
{
	return at(pos);
}

template<typename T, class allocator>
const bool vector<T, allocator>::replace(const T & target, const size_t pos)
{
	checkBound(pos);
	alloc.destroy(elements + pos);
	elements[pos] = target;
	return true;
}

template<typename T, class allocator>
const bool vector<T, allocator>::replace(const T && target, const size_t pos)
{
	checkBound(pos);
	alloc.destroy(elements + pos);
	elements[pos] = target;
	return true;
}

template<typename T, class allocator>
const bool vector<T, allocator>::erase(const size_t pos)
{
	checkBound(pos);
	//if pos >= lastpos throw Exception
	if (pos >= lastPos) {
		outOfBoundException();
	}
	//if pos == last-1, erase at --last
	else if (pos == lastPos - 1) {
		replace(T(), --lastPos);
	}
	//if pos < last, destroy at pos, move forward, last--
	else {
		alloc.destroy((elements + pos));
		moveElement(elements, (elements + pos), pos + 1, lastPos--);
	}
	return true;
}

template<typename T, class allocator>
vector<T>& vector<T, allocator>::move(vector & v)
{
	deleteElements(elements, curCap);
	curCap = v.curCap;
	lastPos = v.lastPos;
	elements = v.elements;
	v.release();
	return *this;
}

template<typename T, class allocator>
vector<T>& vector<T, allocator>::copy(vector & v)
{
	deleteElements(elements,curCap);
	this->curCap = v.curCap;
	lastPos = v.lastPos;
	elements = alloc.allocate(curCap);
	copyElements(v.elements, v.curCap);
	return *this;
}

template<typename T, class allocator>
vector<T>& vector<T, allocator>::operator=(vector & v)
{
	if (this == &v) return *this;
	deleteElements(elements, curCap);
	this->elements = alloc.allocate(curCap);
	copyElements(v.elements, elements, v.lastPos);
	this->curCap = v.curCap;
	lastPos = v.lastPos;
	return *this;
}

template<typename T, class allocator>
vector<T>& vector<T, allocator>::operator=(vector && v)
{
	if (this == &v) return *this;
	deleteElements(elements, curCap);
	this->curCap = v.curCap;
	this->elements = v.elements;
	lastPos = v.lastPos;
	v.release();
	return *this;
}

template<typename T, class allocator>
T & vector<T, allocator>::operator[](size_t pos)
{
	return *(elements + pos);
}

template<typename T, class allocator>
const T & vector<T, allocator>::operator[](size_t pos) const
{
	return *(elements + pos);
}

template<typename T, class allocator>
const size_t vector<T, allocator>::defaultIncresement()
{
	return static_cast<size_t>(curCap * (1.5 + (reservedCount / 10.0)) + 1);
}

template<typename T, class allocator>
const bool vector<T, allocator>::release()
{
	curCap = 0;
	lastPos = 0;
	elements = nullptr;
	return true;
}

template<typename T, class allocator>
const bool vector<T, allocator>::checkBound(const size_t pos)
{
	if (pos >= curCap || pos < firstPos) outOfBoundException();

	return true;
}

template<typename T, class allocator>
void vector<T, allocator>::outOfBoundException()
{
	std::string message = std::string("out of bound Exception, \n pos : ") + std::to_string(pos);
	throw std::length_error(message);
}

template<typename T, class allocator>
void vector<T, allocator>::destroyElements(T * src, const size_t len)
{
	destroyElements(src, firstPos, len);
}

template<typename T, class allocator>
void vector<T, allocator>::destroyElements(T * src, const size_t start, const size_t end)
{
	for (auto i = start; i<end; ++i)
		alloc.destroy(elements + i);
}

template<typename T, class allocator>
void vector<T, allocator>::deleteElements(T * src, const size_t len)
{
	deleteElements(src, firstPos, len);
}

template<typename T, class allocator>
void vector<T, allocator>::deleteElements(T * src, const size_t start, const size_t end)
{
	destroyElements(src, start, end);
	alloc.deallocate((src + start), (end - start));
	src = nullptr;
}

template<typename T, class allocator>
const size_t vector<T, allocator>::copyElements(const T * src, const size_t len)
{
	return copyElements(src, elements, firstPos, len);
}

template<typename T, class allocator>
const size_t vector<T, allocator>::copyElements(const T * src, T * dst, const size_t len)
{
	return copyElements(src, dst, 0, len);
}

template<typename T, class allocator>
const size_t vector<T, allocator>::copyElements(const T * src, T * dst, const size_t start, const size_t end)
{
	auto i = start;
	for (; i < end; ++i) {
		*(dst + i) = *(src + i);
	}
	return i;
}

template<typename T, class allocator>
const size_t vector<T, allocator>::initializeElements(T * target, const size_t start, const size_t end)
{
	for (auto i = start; i < end; ++i, ++lastPos) {
		*(target + i) = T();
	}
	return end;
}

template<typename T, class allocator>
const size_t vector<T, allocator>::moveElement(T * src, T * dst, const size_t start, const size_t end)
{
	std::_Uninitialized_move((src + start), (src + end + 1), dst, alloc);
	return end;
}
