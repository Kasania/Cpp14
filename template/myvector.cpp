
template <typename T>
class vector {
public :
	vector(const size_t size = defaultSize)
	{
		curSize = size;
	}
	
	~vector()
	{

	}
	
	void setSize(const size_t size)
	{
		curSize = size;
	}
	
	const size_t& size() const
	{
		return curSize;
	}
	static const size_t defaultSize = 10;

private :
	size_t curSize;

};
