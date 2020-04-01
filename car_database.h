#ifndef DATABASE_H
#define DATABASE_H
#include"structs.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
Car MakeCar(int VIN,char Name[],Car_Color color,Fuel_Type fuel,Car_Type type);
Car_Data_Node* MakeCarDataNode();
Car_Tree_Node* MakeCarTreeNode();
Car_Tree_Node* InsertIntoCarDatabase(Car_Tree_Node *root,Car car,int *make_new_node);
Car_Tree_Node* InsertCar(Car_Tree_Node *root,Car car);
Car_Tree_Node* DeleteFromCarDatabase(Car_Tree_Node *root,Car car,Bool *less);
Car_Tree_Node* DeleteCar(Car_Tree_Node *root,int VIN);

#endif