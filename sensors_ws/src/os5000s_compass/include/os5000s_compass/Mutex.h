/*********************************************************************************************
Mutex.h (There is no coorsponding .cpp file)
This header file contains a ptreads_mutex wrapper and associated protected data types.
namespace Threads 

This header file inculdes:
Mutex		-  Creates a pthread-mutex and gives locking and unlocking functionality
Guard		-  Takes a Mutex object and locks its mutex upon creation and unlocks on destruction

GuardValue	-  A templeted data type that inherits Mutex and provides lock/unlock functionality
GuardVector -  A templeted std::vector data type that inherits Mutex and provides lock/unlock functionality
GuardedData -  A templeted data type that inherits Mutex and provides extensive mutex protection over operations on the data

Author:		Andrew Petruska
Created:	7-11-2012
Last Mod:	7-11-2012
*******************************************************************************************/

#ifndef _MUTEX_H
#define _MUTEX_H

#include <iostream>
#include <vector>
#include <deque>
#include <list>

#include <pthread.h> // for thredding
#ifdef WIN32 // add pthread libraries
#pragma comment(lib, "pthreadVC2.lib")
#pragma comment(lib, "pthreadVCE2.lib")
#pragma comment(lib, "pthreadVSE2.lib")
#endif

using namespace std;

namespace Threads {
/*********************************************************************************************
        Mutex class handels the creation and control of pthread_mutex's.  The
        proper use of this class would be:
        instantiation:	Mutex myMutex();
        locking:		myMutex.lock();
        unlocking:		myMutex.unlock();
        Functions:
        lock()		-	locks the mutex
        unlock()	-	unlocks the mutex
        trylock()	-	atempts to lock the mutex returns true if sucessful and the mutex is locked
        islocked()	-	returns true if the mutex is locked (performes a trylock to determine)
        *******************************************************************************************/
class Mutex {
    pthread_mutex_t* mutex;


public:

    Mutex(bool recursive = true);


    Mutex(const Mutex& baseMutex);
    Mutex(const Mutex* baseMutex);
    Mutex operator =(const Mutex &other);

    ~Mutex();

    int lock();

    bool tryLock(); // returns true if the lock suceeds

    void unlock();

    friend class Guard;
};
/*********************************************************************************************
        Guard takes a Mutex object and locks it upon creation.  When the Guard
        object is deleted the mutex is unlocked.

        Intended Use:
        GuardValue<double> a = 1; // some variable that inhearits Mutex
        GuardValue<double> b = 2; // some other variable that inhearits Mutex
        if(int a > int b){
        Guard a_Protector(a);	// lock the mutex for a
        Guard b_Protector(b);	// lock the mutex for b
        a = b;			// do the operation in a protected state
        } // upon exit from if statement a and b are unlocked as a_Protector and b_Protector are removed from the scope

        *******************************************************************************************/
class Guard {
    pthread_mutex_t* p_mutex;
public:
    Guard(const Mutex* thisMutex);
    Guard(const Mutex& thisMutex);
    ~Guard();
};

/*********************************************************************************************
        GuardValue class, inherates Mutex.  It implements casting and basic constructors.
        Locking and Unlocking is to be handeled by the user.

        Functions:
        lock();		// locks the mutex
        unlock();	// unlockes the mutex
        operator =  // copies a GuardValue (protects other guarded Value before copy) or a type T and retains current mutex

        *******************************************************************************************/
template<class T>
class GuardValue:public Mutex {
public:
    T unprotected;
    operator T()	{return unprotected;}
    GuardValue():Mutex(false) {;}
    GuardValue(T value):Mutex(false) {unprotected = value;}
    GuardValue(const GuardValue& other):Mutex(false) {unprotected = other.unprotected;}

    void operator = (GuardValue& other) {//leaves mutex copies data
        Guard guardOnDuty(other);
        unprotected = other;
    }
    void operator = (T other) {//leaves mutex copies data
        unprotected = other;
    }
};
template<class T>
ostream& operator<< (ostream& out, GuardValue<T>& data) {
    out << data.unprotected();
    return out;
}
template<class T>
istream& operator>> (istream& in, GuardValue<T>& data) {
    cin >> data.unprotected;
    return in;
}

/*********************************************************************************************
        GuardVector class, inherates Mutex and behaves like a stl::vector.
        It implements casting and basic constructors.
        Locking and Unlocking is to be handeled by the user.

        Functions:
        lock();		// locks the mutex
        unlock();	// unlockes the mutex
        operator =  // copies a GuardVector (protects other guarded vector before copy) a std::<vector> and retains current mutex

        *******************************************************************************************/
template<class T>
class GuardVector:public Mutex, public vector<T> {
public:
    GuardVector():Mutex(),vector<T>(){;}
    GuardVector(unsigned int size, T value = T()):Mutex(),vector<T>(size,value) {;}
    template<class InputIterator>
    GuardVector(InputIterator first, InputIterator last):Mutex(),vector<T>(first,last) {;}
    GuardVector(const GuardVector& other):Mutex(),vector<T>(other) {;}
    GuardVector(const vector<T> other):Mutex(),vector<T>(other) {;}

    void operator = (const GuardVector& other) {//leaves mutex copies data
        Guard guardOnDuty(other);
        this->clear();
        this->assign(other.begin(),other.end());
    }
    void operator = (const vector<T>& other) {//leaves mutex copies data
        this->clear();
        this->assign(other.begin(),other.end());
    }

};

/*********************************************************************************************
        GuardedData class, inherates GuardValue and is designed to handel a mutex
        Guarded basic memeber (double, int, long etc.).  It implements casting
        and atherometic operators which, before tuching the base data, locks the data's mutex
        and then unlocks after the operation is performed.

        Proper use of this class treates the object as the templated class.  Direct
        access to the mutex lock/unlock is provided but is discuraged because
        an individual thread could block itself.  If direct access of the lock()/unlock()
        functionality is used the data member MUST be accessed directly through the public
        variable "unprotec {pthread_mutex_unlock(&mutexCopy);}ted".

        Functions:
        set();		// sets the value
        get();		// returns the value
        lock();		// locks the mutex
        unlock();	// unlockes the mutex

        Available mutex Guarded functionality:
        =, *,+,-,/, =, +=, -=, *=, /=, T(), ==, !=, >=, >, <=, <
        ostream operator <<
        istream operator >>

        Example Use 1: Encouraged. lockes and unlocks the data each use
        GuardedData<double> protectedDouble = 1.0; // protectedDouble = 1.0
        double newValue = 2.0;
        protectedDouble = newValue; // protectedDouble = 2.0
        protectedDouble *= newValue; // protectedDouble = 4.0
        newValue = protectedDouble;  // newValue = 4.0; protectedDouble = 4.0
        newValue == protectedDouble; // true
        protectedDouble > newValue;  // false

        Example Use 2:  Discouraged. lock control is by the user
        GuardedData<double> protectedDouble = 1.0; // protectedDouble = 1.0
        double newValue = 2.0;
        protectedDouble.lock();		// locks mutex
        protectedDouble.unprotected = newValue; // protectedDouble = 2.0
        protectedDouble.unprotected *= newValue; // protectedDouble = 4.0
        newValue = protectedDouble.unprotected;  // newValue = 4.0; protectedDouble = 4.0
        newValue == protectedDouble.unprotected; // true
        protectedDouble.unprotected > newValue;  // false
        protectedDouble.unlock();	// dont forget to unlock the mutex

        Example Use 3: UNFUNCTIONAL. lock control is mixed by the user and the code stalls (why example use 2 is discouraged)
        GuardedData<double> protectedDouble = 1.0; // protectedDouble = 1.0
        double newValue = 2.0;
        protectedDouble.lock();		// locks mutex
        protectedDouble = newValue; // Code is locked because the mutex is endlessly waiting to lock.
        ...

        *******************************************************************************************/
template<class T>
class GuardedData:public GuardValue<T> {

public:
    void set( T other) {
        Guard guardOnDuty(this);
        this->unprotected = other;
    }
    T get() {
        Guard guardOnDuty(this);
        T data = this->unprotected;
        return data;
    }

    GuardedData &operator	=	(T other) {set(other);}

    GuardedData &operator	+=	(T other) {
        Guard guardOnDuty(this);
        this->unprotected += other;
    }
    GuardedData &operator	-=	(T other) {
        Guard guardOnDuty(this);
        this->unprotected -= other;
    }
    GuardedData &operator	*=	(T other) {
        Guard guardOnDuty(this);
        this->unprotected *= other;
    }
    GuardedData &operator	/=	(T other) {
        Guard guardOnDuty(this);
        this->unprotected /= other;
    }

    bool operator	==	(T other)	{return (get()==other);}
    bool operator	!=	(T other)	{return (get()!=other);}
    bool operator	<=	(T other)	{return (get()<=other);}
    bool operator	>=	(T other)	{return (get()>=other);}
    bool operator	>	(T other)	{return (get()>other);}
    bool operator	<	(T other)	{return (get()<other);}

    operator T()	{return get();}


    GuardedData():GuardValue<T>() {;}
    GuardedData(T data):GuardValue<T>() {set(data);}
    GuardedData(GuardedData& other):GuardValue<T>() {set(other.get());}
};
template<class T>
ostream& operator<< (ostream& out, GuardedData<T>& data) {
    out << data.get();
    return out;
}
template<class T>
istream& operator>> (istream& in, GuardedData<T>& data) {
    Guard guardOnDuty(data);
    in >> data.unprotected;
    return in;
}

} // end namespace Threads

#ifdef _USE_OPENCV_
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>

namespace Threads {
template<>
class GuardedData<cv::Mat>:public GuardValue<cv::Mat> {

public:
    void set( cv::Mat other);
    cv::Mat get();
    void get(cv::Mat& value);

    GuardedData<cv::Mat> &operator	=	(cv::Mat other);

    GuardedData<cv::Mat> &operator	+=	(cv::Mat other);
    GuardedData<cv::Mat> &operator	-=	(cv::Mat other);
    GuardedData<cv::Mat> &operator	*=	(cv::Mat other);
    GuardedData<cv::Mat> &operator	/=	(cv::Mat other);

    bool operator	==	(cv::Mat other);
    bool operator	!=	(cv::Mat other);
    bool operator	<=	(cv::Mat other);
    bool operator	>=	(cv::Mat other);
    bool operator	>	(cv::Mat other);
    bool operator	<	(cv::Mat other);

    operator cv::Mat();


    GuardedData<cv::Mat>();
    GuardedData<cv::Mat>(cv::Mat data);
    GuardedData<cv::Mat>(GuardedData<cv::Mat>& other);
};

}// end namespace Threads

#endif

#endif
