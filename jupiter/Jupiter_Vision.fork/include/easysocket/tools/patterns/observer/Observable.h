#ifndef __EASYSOCKET_OBSERVABLE_H__
#define __EASYSOCKET_OBSERVABLE_H__

#include "ObserverInterface.h"

#include <assert.h>
#include <semaphore.h>
#include <set>

class IObserver ;

/**
 * @brief Abstract class based on the Java implementation of the IObserver
 *        pattern design.
 *        An observable object can notify its IObservers in order to make them
 *        update data of the observable object itself : they can handle
 *        inaccessible data to the observable object.
 */
class Observable {
    private:
        /** @brief To know if the observable object has changed. */
        bool m_hasChanged ;

        /** @brief List of IObservers. */
        std::set<IObserver*> m_Observers ;

        /**
         * @brief Regulate the access to the object to avoid concurrency
         *        problems.
         */
        sem_t m_access ;

    public:
                                                            /** CONSTRUCTORS **/
        /** @brief Create the Observable object. */
        Observable() {
            assert(sem_init(&m_access, 0, 1) == 0) ;
        }

        /** @brief Destroy the Observable object. */
        virtual ~Observable() {}

                                                               /** UTILITIES **/
        /**
         * @brief Add an IObserver.
         * @param o     The IObserver of the current object.
         */
        virtual void addObserver(IObserver* o) {
            sem_wait(&m_access) ;

            if (o == 0) {
                sem_post(&m_access) ;
                assert(false) ;
            }

            if (m_Observers.count(o) == 0)
                m_Observers.insert(o) ;
            
            sem_post(&m_access) ;
        }

        /**
         * @brief Remove an IObserver.
         * @param o     The IObserver to remove.
         */
        virtual void removeObserver(IObserver* o) {
            sem_wait(&m_access) ;
            // Safely delete from the set...
            m_Observers.erase(o) ;
            sem_post(&m_access) ;
        }

        /**
         * @brief Clear the list of IObservers.
         */
        virtual void removeObservers() {
            sem_wait(&m_access) ;
            m_Observers.clear() ;
            sem_post(&m_access) ;
        }

        /**
         * @brief If the object has changed, IObservers must be notified.
         *        The object is then set as not changed anymore.
         */
        virtual void notifyObservers() {
            notifyObservers(0) ;
        }

        /**
         * @brief If the object has changed, IObservers must be notified.
         *        The object is then set as not changed anymore.
         * @param arg   The argument to give to the IObservers.
         */
        virtual void notifyObservers(void* arg) {
            sem_wait(&m_access) ;
            /* Just make a "shot" of the current list of IObservers to safely
               iterate on it */
            std::set<IObserver*> copy = m_Observers ;
            // Fix the state of the object for the copied list of IObservers
            m_hasChanged = false ;
            sem_post(&m_access) ;


            std::set<IObserver*>::reverse_iterator it ;
            for (it = copy.rbegin() ; it != copy.rend() ; it++) {
                (*it) -> update(this, arg) ;
            }
        }

        /**
         * @brief To know if the object has changed.
         * @return TRUE if the object has changed, FALSE else.
         */
        virtual bool hasChanged() {
            sem_wait(&m_access) ;
            bool change = m_hasChanged ;
            sem_post(&m_access) ;
            return change ;
        }

        /**
         * @brief Count how many IObservers are listed for the current object.
         * @return Amount of IObservers on the current object.
         */
        virtual unsigned int countObservers() {
            sem_wait(&m_access) ;
            unsigned int count = m_Observers.size() ;
            sem_post(&m_access) ;
            return count ;
        }

    protected:
        /**
         * @brief Set the object as changed.
         */
        virtual void setChanged() {
            sem_wait(&m_access) ;
            m_hasChanged = true ;
            sem_post(&m_access) ;
        }

        /**
         * @brief Set the object as unchanged.
         */
        virtual void clearChanged() {
            sem_wait(&m_access) ;
            m_hasChanged = false ;
            sem_post(&m_access) ;
        }
} ;

#endif
