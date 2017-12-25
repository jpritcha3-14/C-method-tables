#import <stdlib.h>
#import <stdio.h>

/* BASE CLASS */
// Object type declaration
typedef struct Base {
    void (**vtable)();
    int x;
} Base;

// Object method declarations
void printBase(Base const* obj) {
    printf("Base: (%d)\n", obj->x);
}

void printFart(Base const* obj) {
    printf("*fart*\n");
}

// An array of pointers to base classes functions that return void
void (*baseVTable[])() = { &printBase, &printFart };

// Base class constructor
Base* newBase(int v) {
    Base* obj = (Base*)malloc(sizeof(Base));
    obj->vtable = baseVTable;
    obj->x = v;
    return obj;
}

// Wrapper funtions for calling object methods 
enum { call_print, call_fart};
void print(Base* obj) {
    obj->vtable[call_print](obj);
}
void fart(Base* obj) {
    obj->vtable[call_fart](obj);
}

/* CHILD CLASS */
// Object type declaration
typedef struct Child {
    void (**vtable)();
    int y;
    int x;
} Child;

// Child method
void printChild(Child* obj) {
    printf("Child: (%d, %d)\n", obj->x, obj->y);
}

// An array of pointers to child classes functions 
void (*childVTable[])() = { &printChild, &printFart };

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
    fart(testBase);
    print(testChild);
    fart(testChild); 
}
