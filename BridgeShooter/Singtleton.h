#pragma once

template<typename T>
class Singtleton
{
protected:
	static T* myInstance;
	Singtleton();
	~Singtleton();
public:
	
	static T* GetSingtleton(void);
	void ReleaseSingtleton(void);
	
};
template <typename T> T* Singtleton<T>::myInstance = nullptr;

template<typename T>
inline Singtleton<T>::Singtleton()
{
	
}

template<typename T>
inline Singtleton<T>::~Singtleton()
{
}

template<typename T>
inline T* Singtleton<T>::GetSingtleton(void)
{
	if (!myInstance) {
		myInstance = new T;
	}
	return myInstance;
}

template<typename T>
inline void Singtleton<T>::ReleaseSingtleton(void)
{
	if (myInstance) {
		delete myInstance;
		myInstance = nullptr;
	}
}
