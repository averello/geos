/*
* $Log$
* Revision 1.10  2003/10/16 17:05:07  strk
* Made TopologyException inherit from GEOSException. Adjusted IllegalArgumentException subclassing.
*
*/
#ifndef GEOS_UTIL_H
#define GEOS_UTIL_H

#include <memory>
#include <string>
#include "platform.h"
#include "geom.h"

using namespace std;

namespace geos {

class GEOSException {
public:
	GEOSException();
	GEOSException(string msg);
	GEOSException(string nname,string msg);
	virtual ~GEOSException();
	virtual string toString();
	virtual void setName(string nname);
	virtual void setMessage(string msg);
protected:
	string txt;
	string name;
};

class AssertionFailedException: public GEOSException {
public:
	AssertionFailedException();
	AssertionFailedException(string msg);
	~AssertionFailedException();
};

class IllegalArgumentException: public GEOSException {
public:
	IllegalArgumentException();
	IllegalArgumentException(string msg);
	~IllegalArgumentException();
};

/**
 * Indicates an invalid or inconsistent topological situation encountered during processing
 */
class TopologyException: public GEOSException {
public:
	TopologyException(string msg);
	TopologyException(string msg,const Coordinate *newPt);
	~TopologyException();
	Coordinate* getCoordinate();
private:
	Coordinate *pt;
};

class UnsupportedOperationException: public GEOSException {
public:
	UnsupportedOperationException();
	UnsupportedOperationException(string msg);
	~UnsupportedOperationException();
};

class Coordinate;
class Assert {
public:
	static void isTrue(bool assertion);
	static void isTrue(bool assertion, string message);

	static void equals(const Coordinate& expectedValue, const Coordinate& actualValue);
	static void equals(const Coordinate& expectedValue, const Coordinate& actualValue, string message);

	static void shouldNeverReachHere();
	static void shouldNeverReachHere(string message);
};

class CoordinateArrayFilter:public CoordinateFilter {
public:
	CoordinateList* pts;
	int n;
	CoordinateArrayFilter(int size);
	~CoordinateArrayFilter();
	virtual const CoordinateList* getCoordinates() const;
	virtual void filter_ro(const Coordinate &coord);
	virtual void filter_rw(Coordinate &coord); // Unsopported
};

class UniqueCoordinateArrayFilter:public CoordinateFilter {
public:
	CoordinateList *list;
	UniqueCoordinateArrayFilter();
	virtual ~UniqueCoordinateArrayFilter();
	virtual const CoordinateList* getCoordinates() const;
	virtual void filter_ro(const Coordinate &coord);
	virtual void filter_rw(Coordinate &coord); // Unsupported
};

}
#endif
