/*
 * Mutex
 *
 *  Created on: Feb 8, 2013
 *      Author: Adnrew Petruska
 */
#include "os5000s_compass/Mutex.h"
//#include "../../CodeBase/Utilities/Mutex.h"


Threads::Mutex::Mutex(bool recursive)
{
    mutex = new pthread_mutex_t();
    pthread_mutexattr_t Attr;
    pthread_mutexattr_init(&Attr);

    if ( recursive )
        pthread_mutexattr_settype(&Attr, PTHREAD_MUTEX_RECURSIVE); // make it recursive
    else {
        //cout << "error type" <<endl;
        pthread_mutexattr_settype(&Attr, PTHREAD_MUTEX_ERRORCHECK); // make it check for errors
    }

    pthread_mutex_init(mutex, &Attr);

}

Threads::Mutex::Mutex(const Mutex& baseMutex)
{
    mutex = baseMutex.mutex;
}

Threads::Mutex::Mutex(const Mutex* baseMutex)
{
    mutex = baseMutex->mutex;
}

Threads::Mutex::~Mutex()
{
    pthread_mutex_destroy(mutex);
}

int Threads::Mutex::lock()
{
    return pthread_mutex_lock(mutex);
}

bool Threads::Mutex::tryLock()
{
    return !pthread_mutex_trylock(mutex);
}

void Threads::Mutex::unlock()
{
    pthread_mutex_unlock(mutex);
}

Threads::Mutex Threads::Mutex::operator =(const Threads::Mutex& other) {
    this->mutex = other.mutex;
    return *this;
}

Threads::Guard::Guard(const Mutex* p_thisMutex)
{
    p_mutex = (p_thisMutex->mutex);
    pthread_mutex_lock(p_mutex);
}

Threads::Guard::Guard(const Mutex& thisMutex)
{

    p_mutex = (thisMutex.mutex);
    pthread_mutex_lock(p_mutex);
}

Threads::Guard::~Guard()
{
    pthread_mutex_unlock(p_mutex);
}


#ifdef _USE_OPENCV_
void Threads::GuardedData<cv::Mat>::set( cv::Mat other)
{
    Threads::Guard guardOnDuty(this);
    this->unprotected = other.clone();
}

cv::Mat Threads::GuardedData<cv::Mat>::get()
{
    Threads::Guard guardOnDuty(this);
    cv::Mat data = this->unprotected.clone();
    return data;
}

void Threads::GuardedData<cv::Mat>::get(cv::Mat& value)
{
    this->unprotected.copyTo(value);
    return;
}

Threads::GuardedData<cv::Mat>& Threads::GuardedData<cv::Mat>::operator	=	(cv::Mat other)
{
    set(other);
    return *this;
}

Threads::GuardedData<cv::Mat>& Threads::GuardedData<cv::Mat>::operator	+=	(cv::Mat other)
{
    Threads::Guard guardOnDuty(this);
    this->unprotected += other;
    return *this;
}

Threads::GuardedData<cv::Mat>& Threads::GuardedData<cv::Mat>::operator	-=	(cv::Mat other)
{
    Threads::Guard guardOnDuty(this);
    this->unprotected -= other;
    return *this;
}

Threads::GuardedData<cv::Mat>& Threads::GuardedData<cv::Mat>::operator	*=	(cv::Mat other)
{
    Threads::Guard guardOnDuty(this);
    this->unprotected *= other;
    return *this;
}

Threads::GuardedData<cv::Mat>& Threads::GuardedData<cv::Mat>::operator	/=	(cv::Mat other) {
    Threads::Guard guardOnDuty(this);
    this->unprotected /= other;
    return *this;
}

bool Threads::GuardedData<cv::Mat>::operator	==	(cv::Mat other)
{
    assert (("Cannot Compare cv::Mats" , false) );
    return false;
}
bool Threads::GuardedData<cv::Mat>::operator	!=	(cv::Mat other)
{
    assert (("Cannot Compare cv::Mats" , false) );
    return false;
}
bool Threads::GuardedData<cv::Mat>::operator	<=	(cv::Mat other)
{
    assert (("Cannot Compare cv::Mats" , false) );
    return false;
}
bool Threads::GuardedData<cv::Mat>::operator	>=	(cv::Mat other)
{
    assert (("Cannot Compare cv::Mats" , false) );
    return false;
}
bool Threads::GuardedData<cv::Mat>::operator	>	(cv::Mat other)
{
    assert (("Cannot Compare cv::Mats" , false) );
    return false;
}
bool Threads::GuardedData<cv::Mat>::operator	<	(cv::Mat other)
{
    assert (("Cannot Compare cv::Mats" , false) );
    return false;
}

Threads::GuardedData<cv::Mat>::operator cv::Mat()	{return get();}


Threads::GuardedData<cv::Mat>::GuardedData() {;}
Threads::GuardedData<cv::Mat>::GuardedData(cv::Mat data) {set(data);}
Threads::GuardedData<cv::Mat>::GuardedData(Threads::GuardedData<cv::Mat>& other) {set(other.get());}


ostream& operator<< (ostream& out, Threads::GuardedData<cv::Mat>& data) {
    out << data.get();
    return out;
}

istream& operator>> (istream& in, Threads::GuardedData<cv::Mat>& data) {
    assert (("Cannot >> cv::Mats" , false) );
    //Threads::Guard guardOnDuty(data);
    //in >> data.unprotected;
    return in;
}
#endif

