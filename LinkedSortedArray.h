#ifndef LINKEDSORTEDARRAY_H
#define LINKEDSORTEDARRAY_H

#include "SortedArray.h"

struct ReturnValues
{
    int linkedListIndex = -1;
    int sortedArrayIndex = -1;
};

class template <class DT>
class LinkedSortedArray
{

    friend ostream& operator <<(ostream& s, LinkedSortedArray<DT>& ac)
    {
        bool first = true;
        typename list<SortedArray<DT>>::iterator it = ac.linkedList.begin();
        int k = 0;
        while (k < ac.linkedList.size()) {
            for (int i = 0; i < ( it->size() ); i++) {
                if (first) {
                    first = false;
                }
                else {
                    s << " ";
                }
                s << *((*it)[i]);
            }
            it++;
            k++;
        }
        return s;
    }

protected:
    list<SortedArray<DT>> linkedList;
    int arraySizeFactor; //The maximum size of the array in the SortedArray

public:
    LinkedSortedArray(int arraySizeFactor);
    ReturnValues find(const DT& lookFor);
    ReturnValues insert(const DT& newOne);
    ReturnValues remove(DT toRemove);
    void printStylized();
};

#endif //LINKEDSORTEDARRAY_H

template <class DT>
LinkedSortedArray<DT>::LinkedSortedArray(int arraySizeFactor) {
    this->arraySizeFactor = arraySizeFactor;
}

template <class DT>
ReturnValues LinkedSortedArray<DT>::find(const DT &lookFor) {
    ReturnValues result;
    result.linkedListIndex = -1;
    result.sortedArrayIndex = -1;
    //Iterator for the SortedArray list
    //Begin at the start
    typename list<SortedArray<DT>>::iterator it = linkedList.begin();
    //Until you reach the end of the linked list
    int i = 0;
    while (i < linkedList.size()) {
        //If the element we are looking for is smaller than the min value
        if (lookFor < *(it->getMinElement())) {
            //return -1;
            return result;
        }
        //Check if the element we are looking for is within the bounds
        if (lookFor >= *(it->getMinElement()) && lookFor <= *(it->getMaxElement())) {

            int index = it->find(lookFor);
            if (index != -1) {
                result.linkedListIndex = i;
                result.sortedArrayIndex = index;
            }
            return result;
        }
        it++;
        i++;
    }
    //if reached the end and yet couldn't find it
    return result;
}

template <typename DT>
ReturnValues LinkedSortedArray<DT>::insert(const DT &newOne) {
    ReturnValues returnValues;



    if (linkedList.size() == 0) {
        //If there are no SortedArrays in the linked list,
        //create a new one and insert it into the linked list
        SortedArray<DT> *sortedArray = new SortedArray<DT>(arraySizeFactor);
        int index = sortedArray->insert(newOne);
        linkedList.push_back(*sortedArray);
        returnValues.linkedListIndex = 0;
        returnValues.sortedArrayIndex = 0;
        return returnValues;
    }


    typename list<SortedArray<DT>>::iterator it = linkedList.begin(), it2;
    int i = 0;
    while (it != linkedList.end()) {
        int index = it->find(newOne);
        if (index != -1) {
            returnValues.linkedListIndex = i;
            returnValues.sortedArrayIndex = index;
            return returnValues;
        }
        i++;
        it++;
    }

    it = linkedList.begin();
    //Check if the newOne is greater than the max
    typename list<SortedArray<DT>>::reverse_iterator reverseIterator = linkedList.rbegin();
    DT max = *(reverseIterator->getMaxElement());
    //If that's the case, insert it into the last
    if (newOne > max) {
        //Try inserting into this
        int index = reverseIterator->insert(newOne);
        //If response is -1, then it means that the array is full
        if (index == -1) {
            //No room in this array
            SortedArray<DT> *secondHalf = reverseIterator->split(arraySizeFactor / 2);
            returnValues.linkedListIndex = linkedList.size() - 1;
            index = secondHalf->insert(newOne);
            linkedList.push_back(*secondHalf);
        }
        returnValues.linkedListIndex = linkedList.size() - 1;
        returnValues.sortedArrayIndex = index;
        return returnValues;
    }
    //Iterator for the SortedArray list
    //Begin at the start
    DT min;
    it = linkedList.begin();
    //Until you reach the end of the linked list
    i = 0;

    //merge
    while (it != linkedList.end()) {
        it2 = it;
        it2++;

        if (it2 != linkedList.end()) {
            if (it2->size() + it->size() <= arraySizeFactor) {
                it->join(*it2);
                linkedList.erase(it2);
            }
        }
        it++;
    }
    //end merge*/

    it = linkedList.begin();
    while (i < linkedList.size()) {
        max = *(it->getMaxElement());
        min = *(it->getMinElement());
        DT nextMin = NULL;
        typename list<SortedArray<DT>>::iterator nextIt = it;
        if (i < linkedList.size() - 1) {
            nextIt++;
        }
        nextMin = *(nextIt->getMinElement());
        //If the newOne is lesser than the current SortedArray's min.
        //Or if it's in the range
        //We should insert it here

        if (newOne < min ||
            (newOne >= min && newOne <= max) || newOne < nextMin) {
            //Try inserting into this
            int index = it->insert(newOne);
            returnValues.linkedListIndex = i;
            returnValues.sortedArrayIndex = index;
            //If response is -1, then it means that the array is full
            if (index == -1) {
                //No room in this array
                SortedArray<DT> *secondHalf = it->split(arraySizeFactor / 2);
                //After splitting, check if the new element should be inserted in
                if (*(secondHalf->getMinElement()) > newOne) {
                    index = it->insert(newOne);
                    returnValues.linkedListIndex = i;
                }
                else {
                    index = secondHalf->insert(newOne);
                    returnValues.linkedListIndex = i + 1;
                }
                //Add this SortedArray to the list after the iterator
                linkedList.insert(++it, *secondHalf);
                returnValues.sortedArrayIndex = index;
            }
            return returnValues;
        }
        i++;
        it++;
    }

}


template <typename DT>
ReturnValues LinkedSortedArray<DT>::remove(DT toRemove) {
    ReturnValues result;
    result.linkedListIndex = -1;
    result.sortedArrayIndex = -1;
    //Iterator for the SortedArray list
    //Begin at the start
    typename list<SortedArray<DT>>::iterator it = linkedList.begin(), it2;

    //Until you reach the end of the linked list
    int i = 0;
    while (i < linkedList.size()) {
        //If the element we are looking for is smaller than the min value
        if (toRemove < *(it->getMinElement())) {
            //return -1;
            return result;
        }
        //Check if the element we are looking for is within the bounds
        if (toRemove >= *(it->getMinElement()) && toRemove <= *(it->getMaxElement())) {

            int count = it->remove(toRemove);

            if (count == -1) {
                return result;
            }
            //After removing, check if the next SortedArray can be merged into this
            it2 = it;
            it2++;
            if (it2 != linkedList.end()) {
                if (it2->size() + it->size() <= arraySizeFactor) {
                    it->join(*it2);
                    linkedList.erase(it2);

                }

            }

            result.linkedListIndex = i;
            result.sortedArrayIndex = count;
            return result;
        }
        it++;
        i++;
    }
    //if reached the end and yet couldn't find it
    return result;
}

template <typename DT>
void LinkedSortedArray<DT>::printStylized() {
    typename list<SortedArray<DT>>::iterator tempIt = linkedList.begin();
    while (tempIt != linkedList.end()) {
        cout << *tempIt << ";";
        tempIt++;
    }
    cout << endl;
}

