#ifndef PERSON_DATABASE_H
#define PERSON_DATABASE_H

#include"sales_structs.h"
#include<stdlib.h>
#include<stdio.h>

Customer_Node* CreateCustomerNode(Customer C);
Customer_Node* Customer_RotateRight(Customer_Node* root);
Customer_Node* Customer_RotateLeft(Customer_Node* root);
Customer_Node* Customer_BalanceRight(Customer_Node* root);
Customer_Node* Customer_BalanceLeft(Customer_Node* root);
Customer_Node* InsertIntoCustomerDatabase(Customer_Node *root,Customer C,Ht_Direction *increase);
Customer SearchCustomer(Customer_Node *root,int Customer_ID);


#endif