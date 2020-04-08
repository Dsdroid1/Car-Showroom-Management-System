#ifndef SALES_PERSON_DATABASE_H
#define SALES_PERSON_DATABASE_H

#include<stdio.h>
#include<stdlib.h>
#include"sales_structs.h"



Sales_Person_Node* CreateSalesPersonNode(Sales_Person S);
Sales_Person_Node* RotateLeft(Sales_Person_Node* root);
Sales_Person_Node* RotateRight(Sales_Person_Node* root);
Sales_Person_Node* BalanceLeft(Sales_Person_Node* root);
Sales_Person_Node* BalanceRight(Sales_Person_Node* root);
Sales_Person_Node* InsertIntoSalesPersonDatabase(Sales_Person_Node *root,Sales_Person S,Ht_Direction *increase);
Sales_Person_Node* DeleteFromSalesPersonDatabase(Sales_Person_Node* root,int ID,Bool *height_decreased);
Sales_Person SearchSalesPerson(Sales_Person_Node *root,int ID);

#endif