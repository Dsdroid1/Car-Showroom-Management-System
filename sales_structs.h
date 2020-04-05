#ifndef SALES_STRUCTS_H
#define SALES_STRUCTS_H
#include"structs.h"
#define MAX_NAME 10
#define MAX_ADDRESS 15
#define MAX_PASSWORD 6

typedef enum {FULL_PAYMENT,
            INTEREST_RATE_9_FOR_84_MONTHS,
            INTEREST_RATE_8_75_FOR_60_MONTHS,
            INTEREST_RATE_8_5_FOR_36_MONTHS} Payment_type;//For interest,20%down payment is required

typedef enum {NO_CHANGE,LEFT,RIGHT} Ht_Direction;
typedef enum {LH,EH,RH} Balance_factor;

typedef struct Customer
{
    int ID;
    char Name[MAX_NAME];
    char Mobile[11];
    char Address[15];
    int Sold_Car_VIN;
    int Car_registration;
    Payment_type P;
}Customer;

typedef struct Customer_tree_node
{
    Customer C;
    Balance_factor BF;
    struct Customer_tree_node *right;
    struct Customer_tree_node *left;
}Customer_Node;

typedef struct Sales_person
{
    int ID;
    char Password[MAX_PASSWORD];
    char Name[MAX_NAME];
    int Sales_Target;
    int Sales_Achieved;
    int Sales_Commission;//2% of Sales_Achieved
    Car_Tree_Node *Sold_Cars_Database;
    Customer_Node *Customer_Database;//Database for customers...
}Sales_Person;



typedef struct Sales_Person_Node
{
    Sales_Person S;
    Balance_factor BF;
    struct Sales_Person_Node *right;
    struct Sales_Person_Node *left;
}Sales_Person_Node;

typedef struct Showroom
{
    struct Sales_Person_Node *Sales_Person_Database;
    Car_Tree_Node *Sold_Cars_Database;
    Car_Tree_Node *Stock_Cars_Database;
    Customer_Node *Customer_Database;//Maybe Customer database
}Car_Showroom;

#endif