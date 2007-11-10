//
// h4508.cxx
//
// Code automatically generated by asnparse.
//

#ifdef P_USE_PRAGMA
#pragma implementation "h4508.h"
#endif

#include <ptlib.h>
#include "asn/h4508.h"

#define new PNEW


#if ! H323_DISABLE_H4508



#ifndef PASN_NOPRINTON
const static PASN_Names Names_H4508_NameOperations[]={
        {"callingName",0}
       ,{"alertingName",1}
       ,{"connectedName",2}
       ,{"busyName",3}
};
#endif
//
// NameOperations
//

H4508_NameOperations::H4508_NameOperations(unsigned tag, PASN_Object::TagClass tagClass)
  : PASN_Enumeration(tag, tagClass, 3, FALSE
#ifndef PASN_NOPRINTON
    ,(const PASN_Names *)Names_H4508_NameOperations,4
#endif
    )
{
}


H4508_NameOperations & H4508_NameOperations::operator=(unsigned v)
{
  SetValue(v);
  return *this;
}


PObject * H4508_NameOperations::Clone() const
{
#ifndef PASN_LEANANDMEAN
  PAssert(IsClass(H4508_NameOperations::Class()), PInvalidCast);
#endif
  return new H4508_NameOperations(*this);
}



#ifndef PASN_NOPRINTON
const static PASN_Names Names_H4508_Name[]={
      {"namePresentationAllowed",0}
     ,{"namePresentationRestricted",1}
     ,{"nameNotAvailable",2}
};
#endif
//
// Name
//

H4508_Name::H4508_Name(unsigned tag, PASN_Object::TagClass tagClass)
  : PASN_Choice(tag, tagClass, 3, TRUE
#ifndef PASN_NOPRINTON
    ,(const PASN_Names *)Names_H4508_Name,3
#endif
)
{
}


#if defined(__GNUC__) && __GNUC__ <= 2 && __GNUC_MINOR__ < 9
H4508_Name::operator H4508_NamePresentationAllowed &() const
#else
H4508_Name::operator H4508_NamePresentationAllowed &()
{
#ifndef PASN_LEANANDMEAN
  PAssert(PIsDescendant(PAssertNULL(choice), H4508_NamePresentationAllowed), PInvalidCast);
#endif
  return *(H4508_NamePresentationAllowed *)choice;
}


H4508_Name::operator const H4508_NamePresentationAllowed &() const
#endif
{
#ifndef PASN_LEANANDMEAN
  PAssert(PIsDescendant(PAssertNULL(choice), H4508_NamePresentationAllowed), PInvalidCast);
#endif
  return *(H4508_NamePresentationAllowed *)choice;
}


#if defined(__GNUC__) && __GNUC__ <= 2 && __GNUC_MINOR__ < 9
H4508_Name::operator H4508_NamePresentationRestricted &() const
#else
H4508_Name::operator H4508_NamePresentationRestricted &()
{
#ifndef PASN_LEANANDMEAN
  PAssert(PIsDescendant(PAssertNULL(choice), H4508_NamePresentationRestricted), PInvalidCast);
#endif
  return *(H4508_NamePresentationRestricted *)choice;
}


H4508_Name::operator const H4508_NamePresentationRestricted &() const
#endif
{
#ifndef PASN_LEANANDMEAN
  PAssert(PIsDescendant(PAssertNULL(choice), H4508_NamePresentationRestricted), PInvalidCast);
#endif
  return *(H4508_NamePresentationRestricted *)choice;
}


BOOL H4508_Name::CreateObject()
{
  switch (tag) {
    case e_namePresentationAllowed :
      choice = new H4508_NamePresentationAllowed();
      return TRUE;
    case e_namePresentationRestricted :
      choice = new H4508_NamePresentationRestricted();
      return TRUE;
    case e_nameNotAvailable :
      choice = new PASN_Null();
      return TRUE;
  }

  choice = NULL;
  return FALSE;
}


PObject * H4508_Name::Clone() const
{
#ifndef PASN_LEANANDMEAN
  PAssert(IsClass(H4508_Name::Class()), PInvalidCast);
#endif
  return new H4508_Name(*this);
}



#ifndef PASN_NOPRINTON
const static PASN_Names Names_H4508_NamePresentationAllowed[]={
      {"simpleName",0}
     ,{"extendedName",1}
};
#endif
//
// NamePresentationAllowed
//

H4508_NamePresentationAllowed::H4508_NamePresentationAllowed(unsigned tag, PASN_Object::TagClass tagClass)
  : PASN_Choice(tag, tagClass, 2, TRUE
#ifndef PASN_NOPRINTON
    ,(const PASN_Names *)Names_H4508_NamePresentationAllowed,2
#endif
)
{
}


#if defined(__GNUC__) && __GNUC__ <= 2 && __GNUC_MINOR__ < 9
H4508_NamePresentationAllowed::operator H4508_SimpleName &() const
#else
H4508_NamePresentationAllowed::operator H4508_SimpleName &()
{
#ifndef PASN_LEANANDMEAN
  PAssert(PIsDescendant(PAssertNULL(choice), H4508_SimpleName), PInvalidCast);
#endif
  return *(H4508_SimpleName *)choice;
}


H4508_NamePresentationAllowed::operator const H4508_SimpleName &() const
#endif
{
#ifndef PASN_LEANANDMEAN
  PAssert(PIsDescendant(PAssertNULL(choice), H4508_SimpleName), PInvalidCast);
#endif
  return *(H4508_SimpleName *)choice;
}


#if defined(__GNUC__) && __GNUC__ <= 2 && __GNUC_MINOR__ < 9
H4508_NamePresentationAllowed::operator H4508_ExtendedName &() const
#else
H4508_NamePresentationAllowed::operator H4508_ExtendedName &()
{
#ifndef PASN_LEANANDMEAN
  PAssert(PIsDescendant(PAssertNULL(choice), H4508_ExtendedName), PInvalidCast);
#endif
  return *(H4508_ExtendedName *)choice;
}


H4508_NamePresentationAllowed::operator const H4508_ExtendedName &() const
#endif
{
#ifndef PASN_LEANANDMEAN
  PAssert(PIsDescendant(PAssertNULL(choice), H4508_ExtendedName), PInvalidCast);
#endif
  return *(H4508_ExtendedName *)choice;
}


BOOL H4508_NamePresentationAllowed::CreateObject()
{
  switch (tag) {
    case e_simpleName :
      choice = new H4508_SimpleName();
      return TRUE;
    case e_extendedName :
      choice = new H4508_ExtendedName();
      return TRUE;
  }

  choice = NULL;
  return FALSE;
}


PObject * H4508_NamePresentationAllowed::Clone() const
{
#ifndef PASN_LEANANDMEAN
  PAssert(IsClass(H4508_NamePresentationAllowed::Class()), PInvalidCast);
#endif
  return new H4508_NamePresentationAllowed(*this);
}



#ifndef PASN_NOPRINTON
const static PASN_Names Names_H4508_NamePresentationRestricted[]={
      {"simpleName",0}
     ,{"extendedName",1}
     ,{"restrictedNull",2}
};
#endif
//
// NamePresentationRestricted
//

H4508_NamePresentationRestricted::H4508_NamePresentationRestricted(unsigned tag, PASN_Object::TagClass tagClass)
  : PASN_Choice(tag, tagClass, 3, TRUE
#ifndef PASN_NOPRINTON
    ,(const PASN_Names *)Names_H4508_NamePresentationRestricted,3
#endif
)
{
}


#if defined(__GNUC__) && __GNUC__ <= 2 && __GNUC_MINOR__ < 9
H4508_NamePresentationRestricted::operator H4508_SimpleName &() const
#else
H4508_NamePresentationRestricted::operator H4508_SimpleName &()
{
#ifndef PASN_LEANANDMEAN
  PAssert(PIsDescendant(PAssertNULL(choice), H4508_SimpleName), PInvalidCast);
#endif
  return *(H4508_SimpleName *)choice;
}


H4508_NamePresentationRestricted::operator const H4508_SimpleName &() const
#endif
{
#ifndef PASN_LEANANDMEAN
  PAssert(PIsDescendant(PAssertNULL(choice), H4508_SimpleName), PInvalidCast);
#endif
  return *(H4508_SimpleName *)choice;
}


#if defined(__GNUC__) && __GNUC__ <= 2 && __GNUC_MINOR__ < 9
H4508_NamePresentationRestricted::operator H4508_ExtendedName &() const
#else
H4508_NamePresentationRestricted::operator H4508_ExtendedName &()
{
#ifndef PASN_LEANANDMEAN
  PAssert(PIsDescendant(PAssertNULL(choice), H4508_ExtendedName), PInvalidCast);
#endif
  return *(H4508_ExtendedName *)choice;
}


H4508_NamePresentationRestricted::operator const H4508_ExtendedName &() const
#endif
{
#ifndef PASN_LEANANDMEAN
  PAssert(PIsDescendant(PAssertNULL(choice), H4508_ExtendedName), PInvalidCast);
#endif
  return *(H4508_ExtendedName *)choice;
}


BOOL H4508_NamePresentationRestricted::CreateObject()
{
  switch (tag) {
    case e_simpleName :
      choice = new H4508_SimpleName();
      return TRUE;
    case e_extendedName :
      choice = new H4508_ExtendedName();
      return TRUE;
    case e_restrictedNull :
      choice = new PASN_Null();
      return TRUE;
  }

  choice = NULL;
  return FALSE;
}


PObject * H4508_NamePresentationRestricted::Clone() const
{
#ifndef PASN_LEANANDMEAN
  PAssert(IsClass(H4508_NamePresentationRestricted::Class()), PInvalidCast);
#endif
  return new H4508_NamePresentationRestricted(*this);
}


//
// SimpleName
//

H4508_SimpleName::H4508_SimpleName(unsigned tag, PASN_Object::TagClass tagClass)
  : PASN_OctetString(tag, tagClass)
{
  SetConstraints(PASN_Object::FixedConstraint, 1, 50);
}


H4508_SimpleName::H4508_SimpleName(const char * v)
{
  SetValue(v);
}


H4508_SimpleName::H4508_SimpleName(const PString & v)
{
  SetValue(v);
}


H4508_SimpleName::H4508_SimpleName(const PBYTEArray & v)
{
  SetValue(v);
}


H4508_SimpleName & H4508_SimpleName::operator=(const char * v)
{
  SetValue(v);
  return *this;
}


H4508_SimpleName & H4508_SimpleName::operator=(const PString & v)
{
  SetValue(v);
  return *this;
}


H4508_SimpleName & H4508_SimpleName::operator=(const PBYTEArray & v)
{
  SetValue(v);
  return *this;
}


PObject * H4508_SimpleName::Clone() const
{
#ifndef PASN_LEANANDMEAN
  PAssert(IsClass(H4508_SimpleName::Class()), PInvalidCast);
#endif
  return new H4508_SimpleName(*this);
}


//
// ExtendedName
//

H4508_ExtendedName::H4508_ExtendedName(unsigned tag, PASN_Object::TagClass tagClass)
  : PASN_BMPString(tag, tagClass)
{
  SetConstraints(PASN_Object::FixedConstraint, 1, 256);
}


H4508_ExtendedName & H4508_ExtendedName::operator=(const char * v)
{
  SetValue(v);
  return *this;
}


H4508_ExtendedName & H4508_ExtendedName::operator=(const PString & v)
{
  SetValue(v);
  return *this;
}


H4508_ExtendedName & H4508_ExtendedName::operator=(const PWCharArray & v)
{
  SetValue(v);
  return *this;
}


H4508_ExtendedName & H4508_ExtendedName::operator=(const PASN_BMPString & v)
{
  SetValue(v);
  return *this;
}


PObject * H4508_ExtendedName::Clone() const
{
#ifndef PASN_LEANANDMEAN
  PAssert(IsClass(H4508_ExtendedName::Class()), PInvalidCast);
#endif
  return new H4508_ExtendedName(*this);
}


#endif // if ! H323_DISABLE_H4508


// End of h4508.cxx
