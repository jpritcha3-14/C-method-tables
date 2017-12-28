#import <stdlib.h>
#import <stdio.h>

/* BASE CLASS */
// Object type declaration
typedef struct Base {
    int x;
    void* (**vtable)();
} Base;

// Base object method declarations
void* printBase(Base const* obj) {
    printf("Base: (%d)\n", obj->x);
}

void* returnVal(Base* obj) {
    return &(obj->x);
}

void* printHello(Base const* obj) {
    printf("*hello*\n");
}

void* destroyBase(Base* obj) { 
    free(obj);
}

// An array of pointers to base classes functions that return void
void* (*baseVTable[])() = { &printBase, &returnVal, &printHello, &destroyBase};

// Base class constructor
Base* newBase(int v) {
    Base* obj = (Base*)malloc(sizeof(Base));
    obj->vtable = baseVTable;
    obj->x = v;
    return obj;
}

// Wrapper funtions for calling object methods from their method tables
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
enum { call_print, call_return, call_hello, call_destroy};
void print(Base* obj) {
    obj->vtable[call_print](obj);
}
int* const ret(Base* obj) {
    return (int*)obj->vtable[call_return](obj);
} 
void hello(Base* obj) {
    obj->vtable[call_hello](obj);
}
void destroy(Base* obj) {
    obj->vtable[call_destroy](obj);
}
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/* CHILD CLASS */
// Object type declaration
typedef struct Child {
    int x; // Parameter shared with base class, must be in same place within struct!
    int y;
    void* (**vtable)();
} Child;

// Child methods
void* printChild(Child* obj) {
    printf("Child: (%d, %d)\n", obj->x, obj->y);
}

void* destroyChild(Child* obj) {
    free(obj);
}

// An array of pointers to child classes functions 
void* (*childVTable[])() = { &printChild, &returnVal, &printHello, &destroyChild};

// Child class constructor
Child* newChild(int v1, int v2) {
    Child* obj = (Child*)malloc(sizeof(Child));
    obj->vtable = childVTable;
    obj->x = v1;
    obj->y = v2;
}


void main() {
    Base* testBase = newBase(42);
    Base* testChild = (Base*)newChild(69, 101);

    print(testBase);    
    hello(testBase);
    print(testChild);
    hello(testChild); 

    printf("%d\n", *ret(testBase));
    printf("%d\n", *ret(testChild));

    destroy(testBase);
    destroy(testChild);
   
    // Any of these lines should now cause a segmentation fault
    //print(testBase);    
    //hello(testBase);
    //print(testChild);
    //hello(testChild); 
}
