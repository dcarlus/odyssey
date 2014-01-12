#ifndef __EASYSOCKET_NOCOPY_H__
#define __EASYSOCKET_NOCOPY_H__

/**
 * Class to create singletons.
 * @warning No copy into the subclasses.
 * @warning Private inheritage required.
 */
class NoCopy {
	private:
		/** Disable copy constructor. */
		NoCopy(NoCopy&) ;
	
		/** Disable affectation. */
		void operator= (const NoCopy&) ;
	
	protected:
		/** Allowed default constructor, only for subclasses. */
		NoCopy() throw() {}
		
		/** Destruction, only for subclasses.. */
		virtual ~NoCopy() throw() {}
} ;
#endif
