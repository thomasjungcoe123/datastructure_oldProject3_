

#ifndef PROJ3FIRSTTRY_SORTEDARRAY_H
#define PROJ3FIRSTTRY_SORTEDARRAY_H

using namespace std;

#include <iostream>
#include <list>

template <class DT>
class SortedArray
{
    const int ARRAY_CLASS_DEFAULT_SIZE = 1;

    friend ostream& operator <<(ostream& s, SortedArray<DT>& ac)
    {
        s << "[";
        for (int i = 0; i < ac.size(); i++)
        {
            if (i > 0)
            {
                s << ',';
            }
            s << *ac[i];
        }
        s << "]";
        return s;
    }

private:
    int binarySearch(int, int, const DT& lookFor);
    // obj data of DT -- elements are not by themselves stored in the array but rather pointers to the elements are
    DT** _data;
    // max size of the array
    int _capacity;
    // curr size of the array
    int _size;

public:

    SortedArray ();
    SortedArray (int n);
    SortedArray (const SortedArray<DT>& ac);
    void copy(const SortedArray<DT>& ac);
    virtual ~SortedArray ();
    int size() const;
    int capacity() const;
    SortedArray<DT>& operator= (const SortedArray<DT>& ac);
    DT* operator[] (int k);
    // overloaded >, <, == operators
    // for operator operator DT&
    // >, < returns boolean

    int find(const DT& lookFor);
    int insert(const DT& newElement);
    int remove(DT& oldElement);
    SortedArray<DT>* split(int i);
    void join(SortedArray<DT> &P);
    /*
    void split(int i);
    void join (SortedArray<DT>& P);*/

    // getters
    DT* getMaxElement();
    DT* getMinElement();
    int getCapacity();
    // setters
    /*void setData(DT** data);
    void setMaxElement(DT& maxElement);
    void setMinElement(DT& minElement);
    void setCapacity(int capacity);
    void setSize(int size);*/

};

#endif //PROJ3FIRSTTRY_SORTEDARRAY_H

template <class DT>
SortedArray<DT>::SortedArray()
{
    _data = new DT*[ARRAY_CLASS_DEFAULT_SIZE];
    if (_data == NULL) { _size = ARRAY_CLASS_DEFAULT_SIZE; }
    _capacity = ARRAY_CLASS_DEFAULT_SIZE;
    _size = 0;

}

template <class DT>
SortedArray<DT>::SortedArray(int n)
{
    _capacity = 0; // default in case allocation fails
    _size = 0;

    _data = new DT*[n];
    _capacity = n;
}


template <class DT>
SortedArray<DT>::SortedArray(const SortedArray<DT>& ac) {
    if (&ac != this)    // disallow copying the obj on to itself
        copy (ac);
}

template <class DT>
void SortedArray<DT>::copy(const SortedArray<DT>& ac) {
    if(&ac != this)
    {// disallow copying the obj on to itself{

        _data = new DT*[ac._capacity];
        _capacity = ac._capacity;
        _size = ac._size;

        for(int i = 0; i < ac._size; i++) {
            _data[i] = ac._data[i];
        }

    }
}

template <class DT>
SortedArray<DT>& SortedArray<DT>::operator= (const SortedArray<DT>& ac) {
    if (&ac != this) {
        if (_data != NULL)
            delete[] _data;
        copy (ac);
    }
    return *this;
}

template <class DT>
int SortedArray<DT>:: size() const { return _size; }

template <class DT>
int SortedArray<DT>:: capacity() const { return _capacity; }

template <class DT>
DT* SortedArray<DT>::operator[] (int k) {
    if((k<0)||(k>= size())){
        return NULL;
    }
    return _data[k];
}

template <class DT>
int SortedArray<DT>::binarySearch(int l, int r,const DT& lookFor){
    if(r >= l){
        int mid = l + (r-l)/2;
        if(_data[mid]!= NULL){
            if(*_data[mid] == lookFor){
                return mid;
            }
            if(*_data[mid] > lookFor){
                return binarySearch(l, mid-1, lookFor);
            }

            return binarySearch(mid+1, r, lookFor);
        }
    }
    return -1;



}
// find method of Sorted Array
// performs binary search to return the index position of the element at the location,
// otherwise returns a -1
template <class DT>
int SortedArray<DT>::find(const DT& lookFor)
{
    return binarySearch(0, size()-1, lookFor);
}

// insert method of Sorted Array
// it returns a -1 if there is no room to insert in to the array,
// otherwise it inserts it in the sorted order and returns the new index.
// Make sure to perform a binary search to determine if the element is already stored and
// to locate the position where to insert the element to
template <class DT>
int SortedArray<DT>::insert(const DT& newElement)
{
    DT* newEle = new DT(newElement);
    int index;

    // it returns a -1 if there is no room to insert in to the array,
    if(size() == capacity()){
        return -1;
    }

    // Make sure to perform a binary search to determine if the element is already stored and
    // to locate the position where to insert the element to
    int findResult = find(newElement);
    if(findResult != -1){
        //Element already exists
        return findResult;
    }

    //Otherwise, insert
    for(int i=0; i<size(); i++){
        //If value of _data[i] > newElement
        if(*_data[i] > newElement){
            //shift right
            for(int j= (size()-1); j >= i; j--){
                _data[j+1] = _data[j];
            }
            //insert
            _data[i] = newEle;
            _size++;
            return i;
        }
        //Otherwise, just continue
    }
    //If we have reached the end and haven't inserted yet,
    //insert at the last index
    index = _size;
    _data[index] = newEle;
    _size++;

    return index;
}


// remove method of Sorted Array
// it returns a -1 if the element is not present in the array,
// otherwise it removes the element by shifting the elements to the left by one and
// returns the number of elements in the array after the removal. Use binary search to find the element.
template <class DT>
int SortedArray<DT>::remove(DT& oldElement)
{
    // it returns a -1 if the element is not present in the array,
    int index = find(oldElement);
    if(index == -1){
        //If element not found, return -1
        return -1;
    }
    else{
        //Shift element to the left
        for(int i = index; i < (_size - 1); i++){
            *_data[i] = *_data[i + 1];
        }
        //decrement size
        _size--;
        //Return the updated size
        return _size;
    }
}


// split function of Sorted Array
// returns a SortedArray containing elements from position i through the last element of the array.
// The elements from i through the last element is removed from this array ( set the pointers to NULL) and
// adjust the variable numElements of this array.
template <class DT>
SortedArray<DT>* SortedArray<DT>::split(int i) {
    if(i >= size() || i < 0){
        return NULL;
    }
    //Create a new sorted array
    SortedArray<DT> *newArray = new SortedArray<DT>(_capacity);
    //Make a backup of the size
    int count = 0;
    for(int index=i; index<_size; index++){
        //Copy all the elements starting at i to the end into the new array
        newArray->insert(*_data[index]);
        //Remove the element from this array
        _data[index] = NULL;
        count++;
    }
    //Reduce the size of this array
    _size -= count;
    //Return the new array
    return newArray;
}

template <class DT>
void SortedArray<DT>::join(SortedArray<DT> &P) {
    if(this->_capacity >= this->_size + P.size()){
        //If this array has enough capacity to store the
        for(int i=0; i<P.size(); i++){
            this->insert(*P[i]);
        }
    }
}



template <class DT>
DT* SortedArray<DT>::getMaxElement() {
    if(_data == NULL || _size == 0){
        return NULL;
    }
    else{
        return _data[_size-1];
    }
}
template <class DT>
DT* SortedArray<DT>::getMinElement() {
    if(_data == NULL || _size == 0){
        return NULL;
    }
    else{
        return _data[0];
    }
}
template <class DT> int SortedArray<DT>::getCapacity() { return _capacity; }

// destructor
template <class DT>
SortedArray<DT>::~SortedArray() {
    if(_data != NULL) delete[] _data;
    _data = NULL;
    _size = 0;
    _capacity = 0;
}