//
// H46024B.h
//
// Code automatically generated by asnparse.
//

#include <opal_config.h>

#if ! H323_DISABLE_H46024B

#ifndef __H46024B_H
#define __H46024B_H

#ifdef P_USE_PRAGMA
#pragma interface
#endif

#include <ptclib/asner.h>

#include <asn/h245.h>


//
// AlternateAddress
//

class H46024B_AlternateAddress : public PASN_Sequence
{
#ifndef PASN_LEANANDMEAN
    PCLASSINFO(H46024B_AlternateAddress, PASN_Sequence);
#endif
  public:
    H46024B_AlternateAddress(unsigned tag = UniversalSequence, TagClass tagClass = UniversalTagClass);

    enum OptionalFields {
      e_rtpAddress,
      e_rtcpAddress
    };

    PASN_Integer m_sessionID;
    H245_TransportAddress m_rtpAddress;
    H245_TransportAddress m_rtcpAddress;

    PINDEX GetDataLength() const;
    PBoolean Decode(PASN_Stream & strm);
    void Encode(PASN_Stream & strm) const;
#ifndef PASN_NOPRINTON
    void PrintOn(ostream & strm) const;
#endif
    Comparison Compare(const PObject & obj) const;
    PObject * Clone() const;
};


//
// ArrayOf_AlternateAddress
//

class H46024B_AlternateAddress;

class H46024B_ArrayOf_AlternateAddress : public PASN_Array
{
#ifndef PASN_LEANANDMEAN
    PCLASSINFO(H46024B_ArrayOf_AlternateAddress, PASN_Array);
#endif
  public:
    H46024B_ArrayOf_AlternateAddress(unsigned tag = UniversalSequence, TagClass tagClass = UniversalTagClass);

    PASN_Object * CreateObject() const;
    H46024B_AlternateAddress & operator[](PINDEX i) const;
    PObject * Clone() const;
};


//
// AlternateAddresses
//

class H46024B_AlternateAddresses : public PASN_Sequence
{
#ifndef PASN_LEANANDMEAN
    PCLASSINFO(H46024B_AlternateAddresses, PASN_Sequence);
#endif
  public:
    H46024B_AlternateAddresses(unsigned tag = UniversalSequence, TagClass tagClass = UniversalTagClass);

    H46024B_ArrayOf_AlternateAddress m_addresses;

    PINDEX GetDataLength() const;
    PBoolean Decode(PASN_Stream & strm);
    void Encode(PASN_Stream & strm) const;
#ifndef PASN_NOPRINTON
    void PrintOn(ostream & strm) const;
#endif
    Comparison Compare(const PObject & obj) const;
    PObject * Clone() const;
};


#endif // __H46024B_H

#endif // if ! H323_DISABLE_H46024B


// End of H46024B.h
