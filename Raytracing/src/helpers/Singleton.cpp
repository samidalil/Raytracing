#include "../../headers/helpers/Singleton.h"

#include <memory>

template<typename T>
T& Singleton<T>::getInstance()
{
	static const std::unique_ptr<T> instance(new T(token()));
	return *instance;
}
