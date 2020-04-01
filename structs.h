#ifndef STRUCT_H
#define STRUCT_H
#define MAX_CAR_NAME 20
#define k 3//try to make a 5-ary B+ tree
//Max 3 children
#define c 3//capacity for B+ data node

typedef enum {PETROL,DIESEL} Fuel_Type;
typedef enum {HATCHBACK,SEDAN,SUV} Car_Type;
typedef enum {RED,BLUE,YELLOW} Car_Color;
typedef enum {FAILURE,SUCCESS} status_code;
typedef enum {FALSE,TRUE} Bool;

struct Car
{
    int VIN;//Unique Key in database,-1 if invalid
    char Name[MAX_CAR_NAME];
    Car_Color color;
    Fuel_Type fuel;
    Car_Type type;
};

typedef struct Car Car;

typedef struct Car_Data_Node
{
    Car car[c];
    struct Car_Data_Node *next;
    struct Car_Data_Node *prev;
}Car_Data_Node;

typedef struct Car_Tree_Node
{
    int VIN[k-1];
    Bool isLeaf;
    union Child_Pointers
    {
        struct Car_Tree_Node *child_t[k];
        struct Car_Data_Node *child_l[k];
    }children;
}Car_Tree_Node;
#endif