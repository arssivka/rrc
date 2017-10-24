# RRC

[![Build Status](https://travis-ci.org/arssivka/rrc.svg?branch=master)](https://travis-ci.org/arssivka/rrc)

RRC(Register Run Comminucate) - is an asynchronous modular system, that developes as a c++ library that must simplify the developing of async systems.

It consists of mechanisms, that allows to create a one-threaded or multi-threaded systems, that represented as a set of seperate modules and provide communications between them.


Development of the library has been discontinued. I don't have enough time and resources to develop all my ideas. Basic mechanisms of synchronization was implemented, but usability leaves much to be desired. Main problem is the development an elegant and lightweight way to store and share data between modules both within single process and through network without external librariy dependencies.

Last realization of the library is completely asynchonous and lock-free. All modules are divided into tasks like in boost::asio. Communication between modules is done by providing API for passing data in searelized way with using zero-copy deserialization algorithms. 

In [this repo](https://github.com/arssivka/masters-work) you can read the paper about this library.
 
