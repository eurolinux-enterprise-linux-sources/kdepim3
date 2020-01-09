/*
* polldrop.h -- Declaration of class KPollableDrop.
* Generated by newclass on Sun Nov 30 22:41:49 EST 1997.
*/
#ifndef SSK_POLLDROP_H
#define SSK_POLLDROP_H

#include"maildrop.h"

class QTimerEvent;

/**
* Superclass for all pollable maildrop monitors.
* 
* To implement a polling maildrop, reimplement recheck and emit
* changed(int) in recheck if new messages have been received.
*
* @author Sirtaj Singh Kang (taj@kde.org)
* @version $Id: polldrop.h 371522 2004-12-17 23:16:06Z mkelder $
*/
class KPollableDrop : public KMailDrop
{
	Q_OBJECT
public:
	static const char *PollConfigKey;
	static const int DefaultPoll;

private:
	int _freq;
	int _timerId;
	bool _timerRunning;

public:
	/**
	* KPollableDrop Constructor
	*/
	KPollableDrop();

	virtual bool startMonitor();
	virtual bool stopMonitor();
	virtual bool startProcess() { return true; } //Start en stop-functions for progress; it is not pollable, but a member of kio
	virtual bool stopProcess() { return true; }
	
	virtual bool running() { return _timerRunning; };

	int freq() const { return _freq; }
	void setFreq( int freq );

	virtual bool readConfigGroup ( const KConfigBase& cfg );
	virtual bool writeConfigGroup ( KConfigBase& cfg ) const;

	//virtual void addConfigPage( KDropCfgDialog * );

protected:
	void timerEvent( QTimerEvent * );
};

inline void KPollableDrop::setFreq( int freq ) 
{  
	bool r = running();

	if( r ) stopMonitor();

	_freq = freq; 
 
	if( r ) startMonitor(); 
}

#endif // SSK_POLLDROP_H
