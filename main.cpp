#include "LinkedSortedArray.h"
#include <iostream>
#include <list>

using namespace std;

void testInsert();
void testRemove();
void testSplit();
void testJoin();
void LLTest();

//    testInsert();
//    testRemove();
//    testSplit();
//    testJoin();
//    LLTest();

int main() {

    //FILE *file = fopen("simpleInput.txt","r");
    //Return type
    ReturnValues result;
    char line[2];
    //Read first line
    //fscanf(stdin, "%s", line);
    //fgets(line,2,stdin);
    cin >> line;
    int arraySize = atoi(line);
    LinkedSortedArray<int> array(arraySize);
    //while(fscanf(stdin,"%s",line) != EOF){
    //while (fgets(line, 2, stdin)) {
    while (cin >> line) {
        if (line[0] == 'O' || line[0] == 'o') {
            cout << array << endl;
            continue;
        }
        if (line[0] == 'I' || line[0] == 'i') {
            //Read another character
            //fgets(line, 2, stdin);
            cin >> line;
            //fscanf(stdin,"%s",line);
            int *num = new int(atoi(line));
            result = array.insert(*num);
            cout << result.linkedListIndex << " " << result.sortedArrayIndex << endl;
            continue;
        }
        if (line[0] == 'F' || line[0] == 'f') {
            //Read another character
            //fscanf(stdin,"%s",line);
            //fgets(line, 2, stdin);
            cin >> line;
            int *num = new int(atoi(line));
            result = array.find(*num);
            cout << result.linkedListIndex << " " << result.sortedArrayIndex << endl;
            continue;
        }
        if (line[0] == 'R' || line[0] == 'r') {
            //Read another character
            //fscanf(stdin,"%s",line);
            //fgets(line, 2, stdin);
            cin >> line;
            int *num = new int(atoi(line));
            result = array.remove(*num);
            cout << result.linkedListIndex << " " << result.sortedArrayIndex << endl;
        }

    }

    return 0;


}

// testing insert method of Sorted Array
void testInsert()
{
    cout << "insertion test begins..." << endl;

    SortedArray<int>* testInsertOrdered = new SortedArray<int>(4);
    int* a = new int(20);
    int* b = new int(30);
    int* c = new int(40);
    int* d = new int(50);

    testInsertOrdered->insert(*a);
    testInsertOrdered->insert(*b);
    testInsertOrdered->insert(*c);
    testInsertOrdered->insert(*d);

    // deep copy test
    a = new int(30);

    cout << "ordered insertion testing: " << *testInsertOrdered << endl;

    delete[] a, b, c, d;
    delete testInsertOrdered;
    testInsertOrdered = new SortedArray<int>(4);
    a = new int(100);
    testInsertOrdered->insert(*a);
    delete testInsertOrdered;
    delete a;

    SortedArray<int>* testInsertBackward = new SortedArray<int>(4);
    a = new int(20);
    b = new int(30);
    c = new int(40);
    d = new int(50);

    testInsertBackward->insert(*d);
    testInsertBackward->insert(*c);
    testInsertBackward->insert(*b);
    testInsertBackward->insert(*a);

    cout << "backward insertion testing: " << *testInsertBackward << endl;

    // deep copy test
    *a = 60;

    delete[] a, b, c, d;
    delete testInsertBackward;
    testInsertBackward = new SortedArray<int>(4);
    a = new int(100);
    testInsertBackward->insert(*a);
    delete testInsertBackward;
    delete a;

    SortedArray<int>* testInsertDisordered = new SortedArray<int>(4);
    a = new int(20);
    b = new int(30);
    c = new int(40);
    d = new int(50);

    testInsertOrdered->insert(*a);
    testInsertOrdered->insert(*c);
    testInsertOrdered->insert(*b);
    testInsertOrdered->insert(*d);

    cout << "disordered insertion testing: " << *testInsertOrdered << endl;

    // deep copy test
    *a = 60;

    delete[] a, b, c, d;
    delete testInsertDisordered;
    testInsertDisordered = new SortedArray<int>(4);
    a = new int(100);
    testInsertDisordered->insert(*a);
    delete testInsertDisordered;
    delete a;

    cout << "insertion test ends..." << endl;
    cout << endl;
}

// remove method of SortedArray test
void testRemove()
{
    cout << "removal test begins..." << endl;

    SortedArray<int>* testRemoveOrdered = new SortedArray<int>(4);
    int* a = new int(20);
    int* b = new int(30);
    int* c = new int(40);
    int* d = new int(50);

    testRemoveOrdered->insert(*a);
    testRemoveOrdered->insert(*b);
    testRemoveOrdered->insert(*c);
    testRemoveOrdered->insert(*d);

    testRemoveOrdered->remove(*a);
    testRemoveOrdered->remove(*c);

    // deep copy test
    a = new int(30);

    cout << "ordered removal testing: " << *testRemoveOrdered << endl;

    delete[] a, b, c, d;
    delete testRemoveOrdered;
    testRemoveOrdered = new SortedArray<int>(4);
    a = new int(100);
    testRemoveOrdered->insert(*a);
    delete testRemoveOrdered;
    delete a;

    SortedArray<int>* testRemovalBackward = new SortedArray<int>(4);
    a = new int(20);
    b = new int(30);
    c = new int(40);
    d = new int(50);

    testRemovalBackward->insert(*d);
    testRemovalBackward->insert(*c);
    testRemovalBackward->insert(*b);
    testRemovalBackward->insert(*a);

    testRemovalBackward->remove(*d);
    testRemovalBackward->remove(*a);

    cout << "backward removal testing: " << *testRemovalBackward << endl;

    // deep copy test
    *a = 60;

    delete[] a, b, c, d;
    delete testRemovalBackward;
    testRemovalBackward = new SortedArray<int>(4);
    a = new int(100);
    testRemovalBackward->insert(*a);
    delete testRemovalBackward;
    delete a;


    SortedArray<int>* testRemovalDisordered = new SortedArray<int>(4);
    a = new int(20);
    b = new int(30);
    c = new int(40);
    d = new int(50);

    testRemovalDisordered->insert(*a);
    testRemovalDisordered->insert(*c);
    testRemovalDisordered->insert(*b);
    testRemovalDisordered->insert(*d);

    testRemovalDisordered->remove(*c);

    cout << "disordered removal testing: " << *testRemovalDisordered << endl;

    // deep copy test
    *a = 60;

    delete[] a, b, c, d;

    cout << "removal test ends..." << endl;
    cout << endl;
}

void testSplit()
{
    cout << "split test begins..." << endl;

    SortedArray<int>* testSplitOrdered = new SortedArray<int>(10);
    int* a = new int(20);
    int* b = new int(30);
    int* c = new int(40);
    int* d = new int(50);
    int* e = new int(60);
    int* f = new int(70);
    int* g = new int(80);
    int* h = new int(90);


    testSplitOrdered->insert(*a);
    testSplitOrdered->insert(*b);
    testSplitOrdered->insert(*c);
    testSplitOrdered->insert(*d);
    testSplitOrdered->insert(*e);
    testSplitOrdered->insert(*f);
    testSplitOrdered->insert(*g);
    testSplitOrdered->insert(*h);

    SortedArray<int> *restOfArray = testSplitOrdered->split(5);

    // deep copy test
    a = new int(30);

    cout << "ordered split testing:... " << endl;
    cout << "First Array info: " << *testSplitOrdered << endl;
    cout << "Second Array info: " << *restOfArray << endl;

    delete[] a, b, c, d, e, f, g, h;

    SortedArray<int>* testSplitBackward = new SortedArray<int>(10);
    a = new int(20);
    b = new int(30);
    c = new int(40);
    d = new int(50);
    e = new int(60);
    f = new int(70);
    g = new int(80);
    h = new int(90);

    testSplitBackward->insert(*a);
    testSplitBackward->insert(*b);
    testSplitBackward->insert(*c);
    testSplitBackward->insert(*d);
    testSplitBackward->insert(*e);
    testSplitBackward->insert(*f);
    testSplitBackward->insert(*g);
    testSplitBackward->insert(*h);

    SortedArray<int> *restOfArrayBackward = testSplitBackward->split(5);

    // deep copy test
    a = new int(30);

    cout << "ordered split testing:... " << endl;
    cout << "First Array info: " << *testSplitBackward << endl;
    cout << "Second Array info: " << *restOfArrayBackward << endl;

    delete[] a, b, c, d, e, f, g, h;

    SortedArray<int>* testSplitDisordered = new SortedArray<int>(10);
    a = new int(20);
    b = new int(30);
    c = new int(40);
    d = new int(50);
    e = new int(60);
    f = new int(70);
    g = new int(80);
    h = new int(90);

    testSplitDisordered->insert(*a);
    testSplitDisordered->insert(*c);
    testSplitDisordered->insert(*e);
    testSplitDisordered->insert(*h);
    testSplitDisordered->insert(*b);
    testSplitDisordered->insert(*d);
    testSplitDisordered->insert(*f);
    testSplitDisordered->insert(*g);

    SortedArray<int> *restOfArrayDisordered = testSplitDisordered->split(5);

    // deep copy test
    a = new int(30);

    cout << "ordered split testing:... " << endl;
    cout << "First Array info: " << *testSplitDisordered << endl;
    cout << "Second Array info: " << *restOfArrayDisordered << endl;

    delete[] a, b, c, d, e, f, g, h;

    cout << "split test ends..." << endl;
    cout << endl;
}

void testJoin()
{
    cout << "join test begins..." << endl;

    SortedArray<int>* firstArrayOrdered = new SortedArray<int>(10);
    SortedArray<int> *secondArrayOrdered = new SortedArray<int>(10);
    int* a = new int(20);
    int* b = new int(30);
    int* c = new int(40);
    int* d = new int(50);
    int* e = new int(60);
    int* f = new int(70);
    int* g = new int(80);
    int* h = new int(90);

    firstArrayOrdered->insert(*a);
    firstArrayOrdered->insert(*b);
    firstArrayOrdered->insert(*c);
    firstArrayOrdered->insert(*d);
    secondArrayOrdered->insert(*e);
    secondArrayOrdered->insert(*f);
    secondArrayOrdered->insert(*g);
    secondArrayOrdered->insert(*h);

    firstArrayOrdered->join(*secondArrayOrdered);

    // deep copy test
    a = new int(30);

    cout << "ordered join testing:... " << endl;
    cout << "First Array info: " << *firstArrayOrdered << endl;

    delete[] a, b, c, d, e, f, g, h;

    SortedArray<int>* firstArrayBackward = new SortedArray<int>(10);
    SortedArray<int>* secondArrayBackward = new SortedArray<int>(10);
    a = new int(20);
    b = new int(30);
    c = new int(40);
    d = new int(50);
    e = new int(60);
    f = new int(70);
    g = new int(80);
    h = new int(90);

    firstArrayBackward->insert(*a);
    firstArrayBackward->insert(*b);
    firstArrayBackward->insert(*c);
    firstArrayBackward->insert(*d);
    secondArrayBackward->insert(*e);
    secondArrayBackward->insert(*f);
    secondArrayBackward->insert(*g);
    secondArrayBackward->insert(*h);

    firstArrayBackward->join(*secondArrayBackward);

    // deep copy test
    a = new int(30);

    cout << "ordered join testing:... " << endl;
    cout << "First Array info: " << *firstArrayBackward << endl;

    delete[] a, b, c, d, e, f, g, h;

    SortedArray<int>* firstArrayDisordered = new SortedArray<int>(10);
    SortedArray<int>* secondArrayDisordered = new SortedArray<int>(10);
    a = new int(20);
    b = new int(30);
    c = new int(40);
    d = new int(50);
    e = new int(60);
    f = new int(70);
    g = new int(80);
    h = new int(90);

    firstArrayDisordered->insert(*a);
    firstArrayDisordered->insert(*b);
    firstArrayDisordered->insert(*c);
    firstArrayDisordered->insert(*d);
    secondArrayDisordered->insert(*e);
    secondArrayDisordered->insert(*f);
    secondArrayDisordered->insert(*g);
    secondArrayDisordered->insert(*h);

    firstArrayDisordered->join(*secondArrayDisordered);

    // deep copy test
    a = new int(30);

    cout << "ordered join testing:... " << endl;
    cout << "First Array info: " << *firstArrayDisordered << endl;

    delete[] a, b, c, d, e, f, g, h;


    cout << "join test ends..." << endl;
    cout << endl;


}

void LLTest()
{
    cout << "LinkedList basic ordered insert test begins" << endl;

    LinkedSortedArray<int> array(4);
    int* a = new int(20);
    int* b = new int(30);
    int* c = new int(40);
    int* d = new int(50);
    int* e = new int(25);
    int* f = new int(35);
    int* g = new int(45);
    int* h = new int(55);
    int* i = new int(60);

    array.insert(*a);
    array.insert(*b);
    array.insert(*c);
    array.insert(*d);
    array.insert(*e);
    array.insert(*f);
    array.insert(*g);
    array.insert(*h);
    array.insert(*i);

    cout << array;

    cout << "LSA basic ordered insertion test ends" << endl;
    cout << "************************************" << endl;

    cout << "LSA basic backward insertion test begins" << endl;

    LinkedSortedArray<int> arrayBackwards(4);
    a = new int(20);
    b = new int(30);
    c = new int(40);
    d = new int(50);
    e = new int(25);
    f = new int(35);
    g = new int(45);
    h = new int(55);
    i = new int(60);

    arrayBackwards.insert(*i);
    arrayBackwards.insert(*h);
    arrayBackwards.insert(*g);
    arrayBackwards.insert(*f);
    arrayBackwards.insert(*e);
    arrayBackwards.insert(*d);
    arrayBackwards.insert(*c);
    arrayBackwards.insert(*b);
    arrayBackwards.insert(*a);

    cout << arrayBackwards;

    cout << "LSA basic backward insertion test ends" << endl;
    cout << "****************************************" << endl;

    cout << "LSA basic disordered insertion test begins" << endl;

    LinkedSortedArray<int> arrayDisordered(4);
    a = new int(20);
    b = new int(30);
    c = new int(40);
    d = new int(50);
    e = new int(25);
    f = new int(35);
    g = new int(45);
    h = new int(55);
    i = new int(60);

    arrayDisordered.insert(*a);
    arrayDisordered.insert(*c);
    arrayDisordered.insert(*e);
    arrayDisordered.insert(*g);
    arrayDisordered.insert(*i);
    arrayDisordered.insert(*b);
    arrayDisordered.insert(*d);
    arrayDisordered.insert(*f);
    arrayDisordered.insert(*h);

    cout << arrayDisordered;

    cout << "LSA basic disordered insertion test ends" << endl;
    cout << "****************************************" << endl;
}



