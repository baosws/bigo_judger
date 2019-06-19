#ifndef CONFIGER
#define CONFIGER
#include <bits/stdc++.h>
#include "definitions.h"

namespace configer {
	struct base_config_object {
		void* data = nullptr;
		virtual ~base_config_object() {}
	};

	template <class T>
	struct config_obj: base_config_object {
		void set(const T& data) {
			this->data = new T(data);
		}

		T get() const {
			return *(T*)data;
		}

		~config_obj() {
			delete (T*)data;
		}
	};

	class configer {
		std::map<std::string, base_config_object*> configs;
	public:
		template <class T>
			void set(const std::string& key, const T& value) {
				if (configs.count(key) == 0) {
					configs[key] = new config_obj<T>();
				}
				((config_obj<T>*)configs[key])->set(value);
			}

		template <class T>
			T get(const std::string& key) {
				if (configs.count(key) == 0) {
					throw std::runtime_error("keyerror: " + key);
				}
				return ((config_obj<T>*)(configs[key]))->get();
			}
	};
}

#endif
