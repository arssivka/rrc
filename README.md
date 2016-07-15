# RRC
RRC(Register Run Comminucate) - is an asynchronous modular system, that developes as a c++ library that must simplify the developing of async systems.

It consists of mechanisms, that allows to create a one-threaded or multi-threaded systems, that represented as a set of seperate modules and provide communications between them.


##The library is currently under developing

**We are now working on:**

* Core architecture:
	* Synchronization mechanisms
	* Mechanisms for concurrency
	* Thread-safe, thread pool based Scheduller
	* Publisher/topic/subscriber
	* Services(request/response mechanism)
	* Settings system
* Set of default additional modules
	* Shared libs loader(*.so ,*.dll)
	* Network
	* Python wrapper(nagrebator)
	* Logger (log4cpp)
 