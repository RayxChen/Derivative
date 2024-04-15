#  Creational Patterns

 Creation of new objects. Their purpose is to abstract the creation process which helps the system to be developed independently of the types of individual objects. 
## 1 Virtual copy constructor
We need a copy of an object, we do not know its type so we cannot use the copy constructor, so we ask the object to provide a copy of itself. virtual constructors are known as the "Factory Method".
## 2 Factory
The purpose of this pattern is to allow
us to have an object that spits out objects as and when we need them. 
## 3 Singleton

The big advantage of the
singleton pattern is that there is a single copy of the object which is accessible from everywhere, without introducing global variables and all the difficulties they imply.