/**
* @file  CSPtrTypeArray.h
* @brief An Array of pointers (not thread safe).
*/

#ifndef _INC_CSPTRTYPEARRAY_H
#define _INC_CSPTRTYPEARRAY_H

#include "CSTypedArray.h"

template<class TYPE>
class CSPtrTypeArray : public CSTypedArray<TYPE>
{
public:
    static const char * m_sClassName;

    /** @name Constructors, Destructor, Asign operator:
    */
    ///@{
    CSPtrTypeArray() {}
    virtual ~CSPtrTypeArray() {}
    /**
    * @brief Copy constructor.
    */
    CSPtrTypeArray<TYPE>(const CSPtrTypeArray<TYPE> & copy);
    /**
    * @brief Assign operator
    */
    CSPtrTypeArray<TYPE>& operator=(const CSPtrTypeArray<TYPE> & other);
private:
    ///@}
    /** @name Modifiers:
    */
    ///@{
public:
    /**
    * @brief if data is in array, rmove it.
    * @param pData data to remove from the array.
    */
    bool RemovePtr( TYPE pData );
    ///@}
    /** @name Operations:
    */
    ///@{
    /**
    * @brief check if data is in this array.
    * @param pData data to find in the array.
    * @return true if pData is in the array, BadIndex() otherwise.
    */
    bool ContainsPtr( TYPE pData ) const;
    /**
    * @brief get the position of a data in the array.
    * @param pData data to look for.
    * @return position of the data if data is in the array, BadIndex otherwise.
    */
    size_t FindPtr( TYPE pData ) const;
    ///@}
    /** @name Index Validation:
    */
    ///@{
    /**
    * @brief Check if an index is between 0 and element count.
    * @param i index to check.
    * @return true if index is valid, false otherwise.
    */
    bool IsValidIndex( size_t i ) const;
    ///@}
};

template<class TYPE>
CSPtrTypeArray<TYPE>::CSPtrTypeArray(const CSPtrTypeArray<TYPE> & copy) : CSTypedArray<TYPE>(static_cast<CSTypedArray<TYPE> >(copy)){
}

template<class TYPE>
CSPtrTypeArray<TYPE>& CSPtrTypeArray<TYPE>::operator=(const CSPtrTypeArray<TYPE> & other) {
    static_cast<CSTypedArray<TYPE> >(*this) = static_cast<CSTypedArray<TYPE> >(other);
    return *this;
}

// CSPtrTypeArray:: Modifiers.

template<class TYPE>
bool CSPtrTypeArray<TYPE>::RemovePtr( TYPE pData )
{
    size_t nIndex = FindPtr( pData );
    if ( nIndex == this->BadIndex() )
        return false;

    ASSERT( IsValidIndex(nIndex) );
    this->erase(nIndex);
    return true;
}

template<class TYPE>
bool CSPtrTypeArray<TYPE>::ContainsPtr( TYPE pData ) const
{
    size_t nIndex = FindPtr(pData);
    ASSERT((nIndex == this->BadIndex()) || IsValidIndex(nIndex));
    return nIndex != this->BadIndex();
}

template<class TYPE>
size_t CSPtrTypeArray<TYPE>::FindPtr( TYPE pData ) const
{
    if ( !pData )
        return this->BadIndex();

    for ( size_t nIndex = 0; nIndex < this->size(); ++nIndex )
    {
        if (this->at(nIndex) == pData )
            return nIndex;
    }

    return this->BadIndex();
}

template<class TYPE>
bool CSPtrTypeArray<TYPE>::IsValidIndex( size_t i ) const
{
    if ( i >= this->size() )
        return false;
    return (this->at(i) != NULL );
}

#endif // _INC_CSPTRTYPEARRAY_H
