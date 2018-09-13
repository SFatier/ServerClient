#pragma once
#include "Logger.h"

	template<class Type>
	class Singleton
	{
	public:
		static Type *createInstance()
		{
			releaseInstance();
			_instance = new Type();
			return _instance;
		}
		static bool releaseInstance()
		{
			if (_instance == nullptr)
			{
				return false;
			}
			delete(_instance);
			_instance = nullptr;
			return true;
		}
		static Type *getInstancePtr()
		{
			Logger::log("Attention l'instance n'existe pas.");
			return _instance;
		}
		static Type &getInstanceRef()
		{
			Logger::log("Attention l'instance n'existe pas.");
			return *_instance;
		}
		static bool isInstanciated()
		{
			return (_instance != nullptr);
		}
	protected:
		Singleton() {}
		~Singleton() {}
	private:
		static Type *_instance;
	};
	template<class Type>
	Type *Singleton<Type>::_instance = nullptr;
