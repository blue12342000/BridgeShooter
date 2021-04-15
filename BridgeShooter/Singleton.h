#pragma once

template <typename T>
class Singleton
{
	static T* instance;

	Singleton() {};
	~Singleton() {};

public:
	static T* GetSingleton();
	void ReleaseSingleton();
};

template <typename T>
T* Singleton<T> ::instance = nullptr;

template<typename T>
inline T* Singleton<T> ::GetSingleton()
{
	if (instance == nullptr)
	{
		instance = new T;
	}
	return instance;
}

template<typename T>
inline void Singleton<T>::ReleaseSingleton()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}