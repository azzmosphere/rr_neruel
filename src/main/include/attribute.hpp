/**
 * single observation object. 
 * 
 * Each observation MUST have an Observer ID (8 bit integer).  This identifies the observer for the observation.
 * The observer MAY also have a name which SHOULD be unique, this is part of the name field.
 * Finally an observaton has a value which is always float.
 */

#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <string>
#include <cstdint>

using namespace std;

class Attribute {

    public:
        void setOid(int8_t oid) 
        {
            _oid = oid;
        }

        void setName(string name) 
        {
            _name = name;
        }

        void setValue(float value) 
        {
            _value = value;
        }

        int8_t getOid()
        {
            return _oid;
        }

        string getName()
        {
            return _name;
        }

        float getValue()
        {
            return _value;
        }
    private:
       int8_t _oid;    // mapping variable for the observation.
       string _name;   // human readable name of the observation.
       float  _value;  // value.
};
#endif
