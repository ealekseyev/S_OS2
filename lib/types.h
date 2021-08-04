#ifndef _TYPES_H_
#define _TYPES_H_
typedef unsigned char uint8_t;
typedef char int8_t;
typedef unsigned short uint16_t;
typedef short int int16_t;
typedef unsigned long uint32_t;
typedef long int32_t;

typedef char* cstring;

/*
typedef struct {
    uint32_t lowbits
    uint32_t highbits;

    uint64_t operator+(uint64_t num) const {
        uint64_t retval;
        uint32_t leftover;
        leftover = num.lowbits + highbits; // wraps around
        retval.lowbits = leftover;
        retval.highbits = num.highbits + highbits;
        if((num.lowbits >> 31 + lowbits >> 31) >= 0x10)
            retval.highbits += 1;
        return retval;
    }

    uint64_t operator-(uint64_t num) const {
        if(num.highbits != 0 && highbits != 0) {

        } else if(num.highbits == 0 && highbits == 0) {
            
        } else if(num.highbits > 0 && highbits == 0) {
            return 0; // error
        }
    }

    uint64_t operator*() const {
        
    }

    uint64_t operator/() const {
        
    }

    bool operator==() const {
        if(lowbits == num.lowbits && highbits == num.highbits)
            return true;
        return false;
    }

    void operator=(uint64_t num) {
        lowbits = num.lowbits;
        highbits = num.highbits;
    }
} __attribute__((__packed__)) uint64_t;
*/
#endif