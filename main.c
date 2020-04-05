#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"car_database.h"
#include"person_database.h"
#include"sales_person_database.h"


//-------------------These are some auxilary functions to print data-------------------------
void PrintCar(Car car);
void PrintCustomer(Customer C,Car car);
void PrintData(Sales_Person S);
void Print_SalesPerson_Bio(Sales_Person_Node *root);
void PrintShowroom_SalesPersons(Car_Showroom A);
Sales_Person InitSalesPerson(char Filename[],Car_Tree_Node **Sold_Cars_Databaseptr,Customer_Node **Customer_Databaseptr);
//-------------------------------------------------------------------------------------------

//------------------Main Functions to do stuff-----------------------------------------------
void AddSalesPerson(Car_Showroom A);
void LocateMaxSales(Sales_Person_Node *root,int *curr_highest,Sales_Person_Node **retval);
void FindMaxSales(Car_Showroom A);
//-------------------------------------------------------------------------------------------

void main()
{
    
    Car_Showroom A;
    A.Customer_Database=NULL;
    A.Sales_Person_Database=NULL;
    A.Sold_Cars_Database=NULL;
    A.Stock_Cars_Database=NULL;
    Sales_Person S;

    //------To add SalesPerson to a given showroom--------------------------------------
    Ht_Direction h=NO_CHANGE;
    S=InitSalesPerson("SaleA1.txt",&A.Sold_Cars_Database,&A.Customer_Database);
    A.Sales_Person_Database=InsertIntoSalesPersonDatabase(A.Sales_Person_Database,S,&h);
    h=NO_CHANGE;
    PrintShowroom_SalesPersons(A);
    //----------------------------------------------------------------------------------


    /*-------------------PART A--------------------
    //Read Sales_person
    //Read sold cars(during sales person)
    //Read available cars
    
    ---------------------------------------------*/

    /*-------------------PART B--------------------
    //Create Sales Person.....Ask for id and password
    //Checks to be made....len(Pass)<6 and id not already present
    //Use InsertIntoSalesPersonDatabase method to complete
    ---------------------------------------------*/

        //------Find a good method to do this part
    /*-------------------PART C--------------------
    //For every showroom ,see which model is purchased max....
    //Use intermediate struct like Table to accumulate count
    ---------------------------------------------*/

    /*-------------------PART D--------------------
    //Search O(N) in SalesPerson database for one with max sales uptill now
    //See if his incentive is 2%,make it 3% and print it
    ---------------------------------------------*/

    /*-------------------PART E--------------------
    //Register Customer,add it to Sales Person selling database
    //Display available cars 
    //Select car via VIN
    //Set customer VIN to it,
    //Select payment type
    //Confirm current payment(>20% selling price)
    //Delete car from stock db,add to sold db of showroom as well as salesperson,and increase his/her sales
    ---------------------------------------------*/

    /*-------------------PART F--------------------
    //Keep data for 2 months
    //take their average to predict for next month
    ---------------------------------------------*/

    /*-------------------PART G--------------------
    //Search for this VIN in stock db,
    //If not found,search in sold db 
    //If in sold db,we have to see who sold it
    //Find method for that
    ---------------------------------------------*/

    /*-------------------PART H--------------------
    //Range search on B+ tree(simultaneous on stock and sold)
    ---------------------------------------------*/

}



//-------------------Definitions of the Aux. Functions------------------------------------------
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


void PrintCar(Car car)
{
    printf("\nCar VIN:%d",car.VIN);
            printf(", Car Name:%s",car.Name);
            printf(", CarPrice:%d",car.price);
            printf(", Color:");
            if(car.color==RED)
            {
                printf("RED");
            }
            else if(car.color==BLUE)
            {
                printf("BLUE");
            }
            else if(car.color==YELLOW)
            {
                printf("YELLOW");
            }
            printf(", Fuel Type:");
            if(car.fuel==PETROL)
            {
                printf("PETROL");
            }
            else
            {
                printf("DIESEL");
            }
            printf(", CARTYPE:");
            if(car.type==SEDAN)
            {
                printf("SEDAN");
            }
            else if(car.type==SUV)
            {
                printf("SUV");
            }
            else
            {
                printf("HATCHBACK");
            }
}

void PrintCustomer(Customer C,Car car)
{
    printf("\n");
    printf("Customer_ID:%d",C.ID);
    printf(", Name:%s",C.Name);
    printf(", Contact:%s",C.Mobile);
    printf(", Address:%s",C.Address);
    printf(", Car Reg.No:%d",C.Car_registration);
    printf("\n");
    if(C.P==FULL_PAYMENT)
    {
        printf(", Payment:COMPLETED(%d)",car.price);
    }
    else if(C.P==INTEREST_RATE_9_FOR_84_MONTHS)
    {
        printf(", Payment:INTEREST_RATE_9_FOR_84_MONTHS(Done=%d)",20*car.price/100);
    }
    else if(C.P==INTEREST_RATE_8_75_FOR_60_MONTHS)
    {
        printf(", Payment:INTEREST_RATE_8_75_FOR_60_MONTHS(Done=%d)",20*car.price/100);
    }
    else
    {
        printf(", Payment:INTEREST_RATE_8_5_FOR_36_MONTHS(Done=%d)",20*car.price/100);
    }
}



void Print_SalesPerson_Bio(Sales_Person_Node *root)
{
    if(root!=NULL)
    {
        Print_SalesPerson_Bio(root->left);
        printf("\n");
        printf("**********************************************");
        printf("\nName:%s",root->S.Name);
        printf("\nID:%d",root->S.ID);
        printf("\nSales Target:%d",root->S.Sales_Target);
        printf("\nSales Achieved:%d",root->S.Sales_Achieved);
        printf("\nSales Commission:%d",root->S.Sales_Commission);
        printf("\nCars sold:");
        PrintData(root->S);
        printf("\n**********************************************");
        Print_SalesPerson_Bio(root->right);
    }
}

void PrintShowroom_SalesPersons(Car_Showroom A)
{
    Sales_Person_Node* Sales_Person_Database;
    Sales_Person_Database=A.Sales_Person_Database;
    //Inorder traversal on this...
    Print_SalesPerson_Bio(A.Sales_Person_Database);
}


//-------------------For part A-------------------------
Sales_Person InitSalesPerson(char Filename[],Car_Tree_Node **Sold_Cars_Databaseptr,Customer_Node **Customer_Databaseptr)
{
    FILE *fp;
    Sales_Person S;
    Car_Tree_Node *Sold_Cars_Database;
    Sold_Cars_Database=*Sold_Cars_Databaseptr;
    Customer_Node *Customer_Database;
    Customer_Database=*Customer_Databaseptr;
    S.Customer_Database=NULL;
    S.Sold_Cars_Database=NULL;
    S.Sales_Achieved=0;
    S.Sales_Commission=0;

    fp=fopen(Filename,"r");

    if(fp!=NULL)
    {
        fscanf(fp,"%d%s%s%d",&S.ID,S.Password,S.Name,&S.Sales_Target);
    }

    int flag=0;
    int color,fuel,type,payment;
    Customer C;
    Car car;
    //From next line,scan car-customer
    while(flag==0)
    {
        if(fscanf(fp,"%d%s%d%d%d%d%d",&car.VIN,car.Name,&car.price,&color,&fuel,&type,&car.Customer_ID)!=EOF)
        {
            flag=0;
            car.color=color;
            car.fuel=fuel;
            car.type=type;
            //Insert car into sales person's car database and also sold cars database
            S.Sold_Cars_Database=InsertCar(S.Sold_Cars_Database,car);
            Sold_Cars_Database=InsertCar(Sold_Cars_Database,car);

            //Now scan its corresponding customer
            if(fscanf(fp,"%d%s%s%s%d%d%d",&C.ID,C.Name,C.Mobile,C.Address,&C.Sold_Car_VIN,&C.Car_registration,&payment)!=EOF)
            {
                C.P=payment;
                if(C.P==FULL_PAYMENT)
                {
                    S.Sales_Achieved+=car.price;
                    S.Sales_Commission+=(2*car.price)/100;
                }
                else
                {
                    //Bought on EMI....20% down payment
                    S.Sales_Achieved+=20*car.price/100;//diviode by 100
                    S.Sales_Commission+=20*(2*car.price)/10000;
                }
                Ht_Direction ht=NO_CHANGE;
                S.Customer_Database=InsertIntoCustomerDatabase(S.Customer_Database,C,&ht);
                ht=NO_CHANGE;
                Customer_Database=InsertIntoCustomerDatabase(Customer_Database,C,&ht);
            }
            else
            {
                flag=1;
            }
        }
        else
        {
            flag=1;
        }
    }
    *Sold_Cars_Databaseptr=Sold_Cars_Database;
    *Customer_Databaseptr=Customer_Database;
    return S;
}

void PrintData(Sales_Person S)
{
    //Prints The data of who bought which car and stuff
    Car_Data_Node *d=NULL;
    Car_Tree_Node *tptr=NULL;
    tptr=S.Sold_Cars_Database;

    while(tptr->isLeaf==FALSE)
    {
        tptr=tptr->children.child_t[0];
    }
    if(tptr->children.child_l[0]==NULL)
    {
        d=tptr->children.child_l[1];
    }
    else
    {
        d=tptr->children.child_l[0];
    }

    int Customer_ID=-1,i=0;
    Customer C;
    while(d!=NULL)
    {
        i=0;
        while(i<c && d->car[i].VIN!=-1)
        {
            printf("\n-----------------------------------------");
            Customer_ID=d->car[i].Customer_ID;
            PrintCar(d->car[i]);
            //Search for customer in customer database
            C=SearchCustomer(S.Customer_Database,Customer_ID);
            //print customer details
            printf("\nSOLD TO:");
            if(C.ID!=-1)
            {
                PrintCustomer(C,d->car[i]);
            }
           
            i++;
        }
        d=d->next;
    }
}

//----------------------------ENd of printing aux functions--------------------------

//--------"Mainstream Functions"-----------------------------------------------------

void AddSalesPerson(Car_Showroom A)
{
    Sales_Person S;
    S.Customer_Database=NULL;
    S.Sold_Cars_Database=NULL;
    S.Sales_Achieved=0;
    S.Sales_Commission=0;
    S.Sales_Target=20000;//Some predefined target
    printf("\nEnter The Sales Person's ID:");
    scanf("%d",&S.ID);
    printf("\nEnter the Sales Person's Name:");
    scanf("%s",S.Name);
    do{
    printf("\nWhat should be set as your password(6 chars at max):");
    scanf("%d",S.Password);
    }while(strlen(S.Password)<=7);
    Ht_Direction h=NO_CHANGE;
    A.Sales_Person_Database=InsertIntoSalesPersonDatabase(A.Sales_Person_Database,S,&h);
}

void LocateMaxSales(Sales_Person_Node *root,int *curr_highest,Sales_Person_Node **retval)
{
    //Sales_Person_Node *retval=NULL;
    if(root!=NULL)
    {
        if(root->left!=NULL)
        {
            LocateMaxSales(root->left,curr_highest,retval);
        }
        if(root->S.Sales_Achieved > *curr_highest)
        {
            *retval=root;
            *curr_highest=root->S.Sales_Achieved;
        }
        if(root->right!=NULL)
        {
            LocateMaxSales(root->right,curr_highest,retval);
        }
    }
    return retval;
}

void FindMaxSales(Car_Showroom A)
{
    Sales_Person_Node *retval=NULL;
    int current_max_sales=0;
    LocateMaxSales(A.Sales_Person_Database,&current_max_sales,&retval);
    //retval is the person who has highest sale
    (retval->S.Sales_Commission)+=(retval->S.Sales_Achieved)/100;//Award 1pc incentive
    printf("\nThe person with highest sales is :");
    printf("\nName:%s",retval->S.Name);
    printf("\nID:%d",retval->S.ID);
    printf("\nTotal Commission(Including 1pc extra incentive):%d",retval->S.Sales_Commission);
}

//-------------------------------------------------------------------------
