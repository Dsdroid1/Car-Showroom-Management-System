#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"car_database.h"


//*****************This function reads car data from a file*************************************
Car_Tree_Node* Init_Cars(char filename[])
{
    Car_Tree_Node *root=NULL;
    FILE *fp;
    int VIN,color,fuel,type;
    char Name[MAX_CAR_NAME];
    Car car;
    fp=fopen(filename,"r");
    if(fp!=NULL)
    {
        while(fscanf(fp,"%d%d%d%d%s",&VIN,&color,&fuel,&type,Name)!=EOF)
        {
            car=MakeCar(VIN,Name,color,fuel,type);
            root=InsertCar(root,car);
        }
    }
    else
    {
        printf("\n Error In opening file!");
    }
    fclose(fp);
    return root;
}

void Print(Car_Tree_Node *root)
{
    Car_Data_Node *d;
    while(root->isLeaf==FALSE)
    {
        root=root->children.child_t[0];
    }
    if(root->children.child_l[0]!=NULL)
    {
        d=root->children.child_l[0];

    }
    else
    {
        d=root->children.child_l[1];
    }
    
    while(d!=NULL)
    {
        int i=0;
        while (i<c&&d->car[i].VIN!=-1)
        {
            printf("\nCar VIN:%d",d->car[i].VIN);
            printf(", Car Name:%s",d->car[i].Name);
            printf(", Color:");
            if(d->car[i].color==RED)
            {
                printf("RED");
            }
            else if(d->car[i].color==BLUE)
            {
                printf("BLUE");
            }
            else if(d->car[i].color==YELLOW)
            {
                printf("YELLOW");
            }
            printf(", Fuel Type:");
            if(d->car[i].fuel==PETROL)
            {
                printf("PETROL");
            }
            else
            {
                printf("DIESEL");
            }
            printf(", CARTYPE:");
            if(d->car[i].type==SEDAN)
            {
                printf("SEDAN");
            }
            else if(d->car[i].type==SUV)
            {
                printf("SUV");
            }
            else
            {
                printf("HATCHBACK");
            }
            i++;
        }
        d=d->next;
    }
}

void main()
{
    //Just to test insert
    Car_Tree_Node *root=NULL;
    Car car;
    int done=1,VIN;
    root=Init_Cars("Cars.txt");
    Print(root);
    while(done)
    {
        printf("\nEnter Car data:");
        scanf("%d",&VIN);
        //car=MakeCar(VIN,"a",YELLOW,DIESEL,SEDAN);
        //root=InsertCar(root,car);
        root=DeleteCar(root,VIN);
        Print(root);
        //printf("\nDO u want to continue?(0 to exit)");
        //scanf("%d",&done);
    }
}