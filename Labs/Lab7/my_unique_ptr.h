#ifndef MY_UNIQUE_PTR_H_
#define MY_UNIQUE_PTR_H_

#include <utility>

template <typename T>
class my_unique_ptr
{
private:
	T *p;

public:
	/*******************************
	 * Constructors and Destructor *
	 *******************************/

	// Default Constructor, p is empty.
	my_unique_ptr()
	{
		this->p = nullptr;
	}

	// Parameterized Constructor, takes ownership of p.
	/*
	 * Note: There exists the issue of 2 my_unique_ptrs thinking they have single and separate ownership of the same object.
	 * We ignore this for the sake of lab simplicity, as it is a complex problem to solve.
	 */
	my_unique_ptr(T *p)
	{
		this->p = p;
	}

	// Copy Constructor - transfers ownership of object from u to this pointer
	my_unique_ptr(my_unique_ptr<T> &x)
	{
		if (x.p != nullptr)
		{
			this->p = x.p;
			x.p = nullptr;
		}
		else
		{
			this->p = nullptr;
		}
	}

	// Destructor - deallocate p if it is not a nullptr.
	~my_unique_ptr()
	{
		// TODO
		if (this->p != nullptr)
		{
			delete p;
			p = nullptr;
		}
	}

	/************************
	 * Operator Overloading *
	 ************************/

	// Copy Assignment Operator.
	my_unique_ptr &operator=(my_unique_ptr<T> &x)
	{
		if (p != nullptr)
		{
			delete p;
			p == nullptr;
		}

		p = x.p;
		x.p = nullptr;

		return *this;
	}

	// Dereference Operators.
	T &operator*() const
	{
		// TODO
		return *p;
	}

	T *operator->() const
	{
		// TODO
		return p;
	}

	/*********************
	 * Utility Functions *
	 *********************/

	T *get_pointer() const { return p; }
	bool is_empty() const { return p == nullptr; }

	T *release()
	{
		// TODO
		T *temp = p;
		p = nullptr;
		return temp;
	}

	void reset()
	{
		// TODO
		delete p;
		p = nullptr;
	}

	void reset(T *p)
	{
		// TODO
		delete this->p;
		this->p = p;
	}

	void swap(my_unique_ptr<T> &x)
	{
		//
		T *temp = x.p;
		x.p = this->p;
		this->p = temp;
	}
};

#endif /* MY_UNIQUE_PTR_H_ */
