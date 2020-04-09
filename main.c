#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"car_database.h"
#include"person_database.h"
#include"sales_person_database.h"

#define MAX_NUM_OF_CARS_IN_DATABASE 20


struct Dictionary
{
    char car_name[MAX_CAR_NAME];
    int count;
};

//-------------------These are some auxilary functions to print data-------------------------
void PrintCar(Car car);
void PrintCustomer(Customer C,Car car);
void PrintData(Sales_Person S);
void Print_SalesPerson_Bio(Sales_Person_Node *root);
void PrintShowroom_SalesPersons(Car_Showroom A);
Car_Tree_Node* Init_Cars(char filename[]);
Sales_Person InitSalesPerson(char Filename[],Car_Tree_Node **Sold_Cars_Databaseptr,Customer_Node **Customer_Databaseptr,int *no_of_cars_sold);
//-------------------------------------------------------------------------------------------

//------------------Main Functions to do stuff-----------------------------------------------
Car_Showroom AddSalesPerson(Car_Showroom A);
void LocateMaxSales(Sales_Person_Node *root,int *curr_highest,Sales_Person_Node **retval);
void FindMaxSales(Car_Showroom A);
void FindMaxCount(Car_Showroom A);
void MakeDictionary(Car_Tree_Node *root,struct Dictionary dptr[],int *num_valid_entries);
void FindMaxCountAcrossShowrooms(Car_Showroom A,Car_Showroom B,Car_Showroom C);
void SearchCarByVIN(Car_Showroom A,int VIN);
int GetThisMonthSales(Sales_Person_Node *root);
void GetPrevMonthsData(Car_Showroom A);
void StoreThisMonthData(Car_Showroom A);
status_code LoginAsSalesPerson(Car_Showroom *Aptr);
Car_Showroom InitUI(Sales_Person *Sptr,Car_Showroom A);
void ShowStockCars(Car_Showroom A);
Car_Data_Node* GetDataPointer(Car_Tree_Node *root,int VIN);
void RangeSearchOfCars(Car_Showroom A,int min,int max);
//-------------------------------------------------------------------------------------------

void main()
{
    
    Car_Showroom A,B,C;
    Sales_Person S;
    Ht_Direction h=NO_CHANGE;
//*----------------Initialising showroom A------------------------------*
    A.Customer_Database=NULL;
    A.Sales_Person_Database=NULL;
    A.Sold_Cars_Database=NULL;
    A.Stock_Cars_Database=NULL;
    A.no_of_cars_sold=0;
    A.no_of_cars_available=0;
    //------To add SalesPerson to a given showroom--------------------------------------
    S=InitSalesPerson("SaleA1.txt",&A.Sold_Cars_Database,&A.Customer_Database,&A.no_of_cars_sold);
    A.Sales_Person_Database=InsertIntoSalesPersonDatabase(A.Sales_Person_Database,S,&h);
    h=NO_CHANGE;
    S=InitSalesPerson("SaleA2.txt",&A.Sold_Cars_Database,&A.Customer_Database,&A.no_of_cars_sold);
    A.Sales_Person_Database=InsertIntoSalesPersonDatabase(A.Sales_Person_Database,S,&h);
    h=NO_CHANGE;
    //---Adding stock cars----------------------------------------------------------
    A.Stock_Cars_Database=Init_Cars("Cars.txt");
//----------------------End of initialising showroom A-----------------*


    char showroom;
    int exit=0,done=0;
    int choice=0;
    int VIN=0,min=0,max=100;
    //----Adding the UI part-----
    printf("\nInitialisation of Showrooms done!!");
    printf("\n-----------------------------------");
    printf("\nWhich Showroom would you like to visit:");
    printf("\nA->Showroom1 \nB->Showroom2 \nC->Showroom3 \nYour Choice:");
    scanf("%c",&showroom);
    switch(showroom)
    {
        case 'A':
            while(done==0)
            {
                printf("\nWhat would you like to do?:");
                printf("\n0.Get all data regarding this showroom");
                printf("\n1.Add a sales person");
                printf("\n2.Get the most popular car across showrooms");
                printf("\n3.Find the most successful sales person");
                printf("\n4.Sell a car to a customer");
                printf("\n5.Get current months sales prediction");
                printf("\n6.Get information related to a car(by VIN)");
                printf("\n7.Get info about cars in range(by VIN)");
                printf("\nYour choice:");
                scanf("%d",&choice);
                switch(choice)
                {
                    case 0:
                        PrintShowroom_SalesPersons(A);
                        break;

                    case 1://To be tested
                        A=AddSalesPerson(A);
                        break;

                    case 2:
                        FindMaxCount(A);
                        //FindMaxCountAcrossShowrooms(A,B,C);
                        break;

                    case 3:
                        FindMaxSales(A);
                        break;

                    case 4:
                        LoginAsSalesPerson(&A);
                        break;

                    case 5://Add filename as parameter because of multiple showrooms
                        GetPrevMonthsData(A);
                        break;

                    case 6:
                        printf("\nEnter the car VIN:");
                        scanf("%d",&VIN);
                        SearchCarByVIN(A,VIN);
                        break;

                    case 7:
                        printf("\nEnter the lower bound:");
                        scanf("%d",&min);
                        printf("\nEnter the upper bound:");
                        scanf("%d",&max);
                        RangeSearchOfCars(A,min,max);
                        break;

                    default:
                        done=1;
                        break;
                }
            }
            break;

        case 'B':
            break;

        case 'C':
            break;

        default:
            exit=1;
            break;
    }




/*
    PrintShowroom_SalesPersons(A);
    
    FindMaxSales(A);
    
    FindMaxCount(A);

    SearchCarByVIN(A,2);

    GetPrevMonthsData(A);
    //StoreThisMonthData(A);
*/
/*
    LoginAsSalesPerson(A);
    PrintShowroom_SalesPersons(A);
    ShowStockCars(A);
*/
/*    int min,max;
    printf("\n---------------------");
    printf("\nEnter min and max:");
    scanf("%d%d",&min,&max);
    RangeSearchOfCars(A,min,max);
*/
    //----------------------------------------------------------------------------------


    /*-------------------PART A--------------------//Make an enclosing function//
    //Read Sales_person
    //Read sold cars(during sales person)
    //Read available cars
    
    ---------------------------------------------*/

    /*-------------------PART B--------------------//FN DONE->AddSalesPerson//
    //Create Sales Person.....Ask for id and password
    //Checks to be made....len(Pass)<6 and id not already present
    //Use InsertIntoSalesPersonDatabase method to complete
    ---------------------------------------------*/

        //------Find a good method to do this part
    /*-------------------PART C--------------------//FN DONE->FindMaxCountAcrossShowrooms//
    //For every showroom ,see which model is purchased max....
    //Use intermediate struct like Table to accumulate count
    ---------------------------------------------*/

    /*-------------------PART D--------------------//********FN DONE->FindMaxSales//
    //Search O(N) in SalesPerson database for one with max sales uptill now
    //See if his incentive is 2%,make it 3% and print it
    ---------------------------------------------*/

    /*-------------------PART E--------------------//FN DONE->LoginAsSalesPerson,InitUI//
    //Register Customer,add it to Sales Person selling database
    //Display available cars 
    //Select car via VIN
    //Set customer VIN to it,
    //Select payment type
    //Confirm current payment(>20% selling price)
    //Delete car from stock db,add to sold db of showroom as well as salesperson,and increase his/her sales
    ---------------------------------------------*/

    /*-------------------PART F--------------------//FN DONE->GetPrevMonthsData,StoreThisMonthData//
    //Keep data for 2 months
    //take their average to predict for next month
    ---------------------------------------------*/

    /*-------------------PART G--------------------//FN DONE->SearchByCarVIN//
    //Search for this VIN in stock db,
    //If not found,search in sold db 
    //If in sold db,we have to see who sold it
    //Find method for that
    ---------------------------------------------*/

    /*-------------------PART H--------------------//FN DONE->RangeSearchOfCars//
    //Range search on B+ tree(simultaneous on stock and sold)
    ---------------------------------------------*/

}



//-------------------Definitions of the Aux. Functions------------------------------------------
//*****************This function reads car data from a file*************************************
Car_Tree_Node* Init_Cars(char filename[])
{
    Car_Tree_Node *root=NULL;
    FILE *fp;
    int VIN,color,fuel,type,price;
    char Name[MAX_CAR_NAME];
    Car car;
    fp=fopen(filename,"r");
    if(fp!=NULL)
    {
        while(fscanf(fp,"%d%d%d%d%d%s",&VIN,&color,&fuel,&type,&price,Name)!=EOF)
        {
            car=MakeCar(VIN,Name,color,fuel,type);
            car.price=price;
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
Sales_Person InitSalesPerson(char Filename[],Car_Tree_Node **Sold_Cars_Databaseptr,Customer_Node **Customer_Databaseptr,int *no_of_cars_sold)
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
            (*no_of_cars_sold)=(*no_of_cars_sold)+1;
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
    if(S.Sold_Cars_Database!=NULL)
    {
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
    else
    {
        printf("\n Nothing Sold yet");
    }
}

//----------------------------ENd of printing aux functions--------------------------

//--------"Mainstream Functions"-----------------------------------------------------

Car_Showroom AddSalesPerson(Car_Showroom A)
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
    scanf("%s",S.Password);
    }while(strlen(S.Password)>6);
    Ht_Direction h=NO_CHANGE;
    A.Sales_Person_Database=InsertIntoSalesPersonDatabase(A.Sales_Person_Database,S,&h);
    return A;
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
}

void FindMaxSales(Car_Showroom A)
{
    Sales_Person_Node *retval=NULL;
    int current_max_sales=0;
    LocateMaxSales(A.Sales_Person_Database,&current_max_sales,&retval);
    //retval is the person who has highest sale
    (retval->S.Sales_Commission)+=(retval->S.Sales_Achieved)/100;//Award 1pc incentive
    printf("\n---------------------------------------------------------------------");
    printf("\nThe person with highest sales is :");
    printf("\nName:%s",retval->S.Name);
    printf("\nID:%d",retval->S.ID);
    printf("\nTotal Commission(Including 1pc extra incentive):%d",retval->S.Sales_Commission);
    printf("\n---------------------------------------------------------------------");
}




void MakeDictionary(Car_Tree_Node *root,struct Dictionary dptr[],int *num_valid_entries)
{
    if(root!=NULL)
    {
        Car_Data_Node *data=NULL;
        while(root->isLeaf==FALSE)
        {
            root=root->children.child_t[0];
        }
        if(root->children.child_l[0]!=NULL)
        {
            data=root->children.child_l[0];
        }
        else
        {
            data=root->children.child_l[1];
        }
        int i=0;
        int j=0,found=0;
        while(data!=NULL)
        {
            i=0;
            while(i<c && data->car[i].VIN != -1)
            {
                //Search for this name in dictionary
                j=0;
                found=0;
                while(j<*num_valid_entries && found==0)
                {
                    if(strcmp(data->car[i].Name,dptr[j].car_name)==0)
                    {
                        dptr[j].count++;
                        found=1;
                    }
                    else
                    {
                        j++;
                    }
                }
                if(found==0)
                {
                    strcpy(dptr[*num_valid_entries].car_name,data->car[i].Name);
                    dptr[*num_valid_entries].count=1;
                    (*num_valid_entries)=(*num_valid_entries)+1;
                }
                i++;
            }
            data=data->next;
        }
    }
}

void FindMaxCount(Car_Showroom A)
{
    struct Dictionary Car_Data[MAX_NUM_OF_CARS_IN_DATABASE];//make init dict fn...
    struct Dictionary D;
    int num_valid_entries=0;
    //Traverse the tree to make this dictionary
    MakeDictionary(A.Sold_Cars_Database,Car_Data,&num_valid_entries);
    int i=0,max_count=0;
    for(i=0;i<num_valid_entries;i++)
    {
        if(Car_Data[i].count > max_count)
        {
            max_count=Car_Data[i].count;
            D=Car_Data[i];
        }
    }
    //This function has to be modified to take input as 3 showrooms,make their respective dicts,then merge these dicts
    printf("\n---------------------------------------------------------------------");
    printf("\nMax Sold Car:%s",D.car_name);
    printf("\nSold Units:%d",D.count);
    printf("\n---------------------------------------------------------------------");
}

void FindMaxCountAcrossShowrooms(Car_Showroom A,Car_Showroom B,Car_Showroom C)
{
    struct Dictionary Car_Data[MAX_NUM_OF_CARS_IN_DATABASE];
    int num_valid_entries=0;
    MakeDictionary(A.Sold_Cars_Database,Car_Data,&num_valid_entries);
    MakeDictionary(B.Sold_Cars_Database,Car_Data,&num_valid_entries);
    MakeDictionary(C.Sold_Cars_Database,Car_Data,&num_valid_entries);
    int i=0,max_count=0;
    struct Dictionary D;
    for(i=0;i<num_valid_entries;i++)
    {
        if(Car_Data[i].count > max_count)
        {
            max_count=Car_Data[i].count;
            D=Car_Data[i];
        }
    }
    printf("\n----------------------------------------------------");
    printf("\nMax Sold Car:%s",D.car_name);
    printf("\nSold Units:%d",D.count);
    printf("\n----------------------------------------------------");
}

void SearchCarByVIN(Car_Showroom A,int VIN)
{
    Car car;
    car.VIN=-1;
    //int VIN=23;//Scan search value
    car=SearchCarDatabase(A.Sold_Cars_Database,VIN);
    printf("\n---------------------------------------------------------------------");
    if(car.VIN==-1)
    {
        //Search in stock database...
        car=SearchCarDatabase(A.Stock_Cars_Database,VIN);
        if(car.VIN!=-1)
        {
            printf("\nCar details:");
            PrintCar(car);
        }
        else
        {
            printf("\n Not Found");
        }
    }
    else
    {
        printf("\nCar details:");
        PrintCar(car);
        Customer C=SearchCustomer(A.Customer_Database,car.Customer_ID);
        printf("\nSold To:");
        PrintCustomer(C,car);
    }
    printf("\n---------------------------------------------------------------------");
}


int GetThisMonthSales(Sales_Person_Node *root)
{
    int retval=0;
    if(root!=NULL)
    {
        retval=root->S.Sales_Achieved+GetThisMonthSales(root->left)+GetThisMonthSales(root->right);
    }
    return retval;
}

void GetPrevMonthsData(Car_Showroom A)
{
    FILE *fp;
    fp=fopen("PreviousSales.txt","r");
    int sum=0,no_of_months=0,temp=0;
    while(fscanf(fp,"%d",&temp)!=EOF)
    {
        sum+=temp;
        no_of_months++;
    }
    fclose(fp);
    int Prediction=0,Current=0;
    Prediction=sum/no_of_months;
    Current=GetThisMonthSales(A.Sales_Person_Database);
    printf("\n*************************************");
    printf("\nCurrent Months Sales:%d",Current);
    printf("\nPrediction According to previous months:%d",Prediction);
    printf("\n*************************************");
}

void StoreThisMonthData(Car_Showroom A)
{
    int Current=0;
    Current=GetThisMonthSales(A.Sales_Person_Database);
    FILE *fp;
    fp=fopen("PreviousSales.txt","a");
    fprintf(fp,"\n%d",Current);
    fclose(fp);
}

Car_Data_Node* GetDataPointer(Car_Tree_Node *root,int VIN)
{
    //Like search ,but returns the datapointer
    Car_Data_Node *retval=NULL;
    if(root!=NULL)
    {
        if(root->isLeaf==FALSE)
        {
            int i=0,found=0;
            while(i<k-1 && root->VIN[i]!=-1 && found==0)
            {
                if(root->VIN[i] <=  VIN)
                {
                    i++;
                }
                else
                {
                    found=1;
                }
            }
            //to chase the ith pointer
            retval=GetDataPointer(root->children.child_t[i],VIN);
        }
        else
        {
            Car_Data_Node *data;
            //Find which ptr to chase
            int i=0,found=0;
            while(i<c && root->VIN[i]!=-1 && found==0)
            {
                if(root->VIN[i] <=  VIN)
                {
                    i++;
                }
                else
                {
                    found=1;
                }
            }
            data=root->children.child_l[i];
            //Search for entry in datanode
            retval=data;
        }
    }
    return retval;
}
//RangeSearch and GetDataPointer need tto be debugged

void RangeSearchOfCars(Car_Showroom A,int min,int max)//Currently under dev.
{
    Car_Data_Node *sold=NULL,*stock=NULL;
    sold=GetDataPointer(A.Sold_Cars_Database,min);
    stock=GetDataPointer(A.Stock_Cars_Database,min);
    int sold_trav=0,stock_trav=0,valid=0,done=0;
    //First advance both the pointers till they become  vaild....i.e. their value is greater than min
    while(sold!=NULL && valid==0)
    {
        if(sold->car[sold_trav].VIN != -1 )
        {
            if(sold->car[sold_trav].VIN < min)
            {
                if(sold_trav<c-1)
                {
                    sold_trav++;
                }
                else
                {
                    sold_trav=0;
                    sold=sold->next;
                }
            }
            else
            {
                valid=1;
            }
        }
        else
        {
            sold=sold->next;
            sold_trav=0;
        }
    }
    valid=0;
    while(stock!=NULL && valid==0)
    {
        if(stock->car[stock_trav].VIN != -1 )
        {
            if(stock->car[stock_trav].VIN < min)
            {
                if(stock_trav<c-1)
                {
                    stock_trav++;
                }
                else
                {
                    stock_trav=0;
                    stock=stock->next;
                }
            }
            else
            {
                valid=1;
            }
        }
        else
        {
            stock=stock->next;
            stock_trav=0;
        }
    }
    printf("\n-------------------------------------");
    //Now ,we will traverse and print it
    while(sold!=NULL && stock!=NULL && !done)
    {
        if(sold->car[sold_trav].VIN < stock->car[stock_trav].VIN)
        {
            if(sold->car[sold_trav].VIN <= max)
            {
                //print this car
                PrintCar(sold->car[sold_trav]);
                printf(" :SOLD");
                //Advance the sold ptr
                if(sold_trav < c-1)
                {
                    sold_trav++;
                    if(sold->car[sold_trav].VIN==-1)//Vailidity checking
                    {
                        sold=sold->next;
                        sold_trav=0;
                    }
                }
                else
                {
                    sold=sold->next;
                    sold_trav=0;
                }
                
            }
            else
            {
                done=1;
            }
        }
        else
        {
            if(stock->car[stock_trav].VIN <= max)
            {
                //print this car
                PrintCar(stock->car[stock_trav]);
                //Advance the sold ptr
                if(stock_trav < c-1)
                {
                    stock_trav++;
                    if(stock->car[stock_trav].VIN==-1)
                    {
                        stock=stock->next;
                        stock_trav=0;
                    }
                }
                else
                {
                    stock=stock->next;
                    stock_trav=0;
                }
                
            }
            else
            {
                done=1;
            }
        }
    }
    if(done==0)
    {
        //One of the lists was exhausted
        while(sold!=NULL && done==0)
        {
            if(sold->car[sold_trav].VIN!=-1)
            {
                if(sold->car[sold_trav].VIN <= max)
                {
                    PrintCar(sold->car[sold_trav]);
                    printf(" :SOLD");
                    if(sold_trav < c-1)
                    {
                        sold_trav++;
                    }
                    else
                    {
                        sold_trav=0;
                        sold=sold->next;
                    }
                }
                else
                {
                    done=1;
                }
            }
            else
            {
                sold=sold->next;
                sold_trav=0;
            }
        }

        while(stock!=NULL && done==0)
        {
            if(stock->car[stock_trav].VIN!=-1)
            {
                if(stock->car[stock_trav].VIN <= max)
                {
                    PrintCar(stock->car[stock_trav]);
                    if(stock_trav < c-1)
                    {
                        stock_trav++;
                    }
                    else
                    {
                        stock_trav=0;
                        stock=stock->next;
                    }
                }
                else
                {
                    done=1;
                }
            }
            else
            {
                stock=stock->next;
                stock_trav=0;
            }
        }
    }
    printf("\n-------------------------------------");
}

status_code LoginAsSalesPerson(Car_Showroom *Aptr)
{
    int id;
    Car_Showroom A;
    A=*Aptr;
    char password[7];
    status_code sc=SUCCESS;
    printf("\nEnter your Sales Id:");
    scanf("%d",&id);
    //Sales_Person_Node *database=A.Sales_Person_Database;
    Sales_Person S;
    Sales_Person_Node *Sptr;
    Sptr=SearchSalesPersonNode(A.Sales_Person_Database,id);
    if(Sptr!=NULL)
    {
        S=Sptr->S;
        if(S.ID==-1)
        {
            printf("\nError!This sales person does not exist!");
            sc=FAILURE;
        }
        else
        {
            //Check for password
            printf("\nEnter Your Password:");
            scanf("%s",password);
            if(strcmp(S.Password,password)==0)
            {
                printf("\n--------------------------------");
                printf("\nSuccessful Login");
                sc=SUCCESS;
                //Init UI
                A=InitUI(&S,A);
                Sptr->S=S;
            }
            else
            {
                printf("\nWrong Credentials");
                sc=FAILURE;
            }
        }
    }
    else
    {
        printf("\nError!This sales person does not exist!");
        sc=FAILURE;
    }
    *Aptr=A;
    return sc;
}

void ShowStockCars(Car_Showroom A)
{
    Car_Data_Node *d=NULL;
    Car_Tree_Node *tptr=NULL;
    tptr=A.Stock_Cars_Database;
    if(tptr!=NULL)
    {
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

        int i=0;
        while(d!=NULL)
        {
            i=0;
            while(i<c && d->car[i].VIN!=-1)
            {
                printf("\n-----------------------------------------");
                PrintCar(d->car[i]);
                i++;
            }
            d=d->next;
        }
    }
}

Car_Showroom InitUI(Sales_Person *Sptr,Car_Showroom A)
{
    int choice;
    int done=0;
    Sales_Person S;
    S=*Sptr;
    Customer C;
    int id,VIN;
    while(!done)
    {
        printf("\nWelcome,%s",S.Name);
        printf("\nWhat would you like to do?");
        printf("\n1.Browse stock cars");
        printf("\n2.Sell car to customer");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                ShowStockCars(A);
                break;

            case 2:
                
                
                printf("\nEnter Customer ID:");
                scanf("%d",&C.ID);
                id=C.ID;
                C=SearchCustomer(A.Customer_Database,id);
                if(C.ID!=-1)
                {
                    //Customer exists
                    printf("\nThis customer has already purchased something this month....");
                }
                else
                {
                    C.ID=id;
                    printf("\nEnter customer details:");
                    printf("\nName:");
                    scanf("%s",C.Name);
                    do
                    {
                        printf("\nEnter Valid Mobile:");
                        scanf("%s",C.Mobile);
                    }while(strlen(C.Mobile)!=10);//10
                    printf("\nAddress:");
                    scanf("%s",C.Address);
                    
                    ShowStockCars(A);
                    printf("\nEnter the Car VIN to be purchased:");
                    scanf("%d",&VIN);
                    Car car;
                    int p_type;
                    car.VIN=-1;
                    //if VIN is valid,then 
                    car=SearchCarDatabase(A.Stock_Cars_Database,VIN);
                    if(car.VIN!=-1)
                    {
                        printf("Enter type of payment:");
                        printf("\n1.Full");
                        printf("\n2.INTEREST RATE OF 9 for 84 months");
                        printf("\n3.INTEREST RATE OF 8.75 for 60 months");
                        printf("\n4.INTEREST RATE OF 8.5 for 36 months");
                        scanf("%d",&p_type);
                        if(p_type>4 || p_type < 1)
                        {
                            p_type=0;//Full payment
                        }
                        C.P=p_type-1;
                        if(C.P==FULL_PAYMENT)
                        {
                            S.Sales_Achieved+=car.price;
                            S.Sales_Commission+=2*car.price/100;
                        }
                        else
                        {
                            //20% down payment
                            S.Sales_Achieved+=20*car.price/100;
                            S.Sales_Commission+=20*2*car.price/10000;
                        }
                        C.Car_registration=(C.ID*999+car.VIN*9)%10000;
                        Ht_Direction h=NO_CHANGE;
                        A.Customer_Database=InsertIntoCustomerDatabase(A.Customer_Database,C,&h);
                        h=NO_CHANGE;
                        S.Customer_Database=InsertIntoCustomerDatabase(S.Customer_Database,C,&h);
                        DeleteCar(A.Stock_Cars_Database,VIN);
                        A.no_of_cars_available--;
                        car.Customer_ID=id;
                        C.Sold_Car_VIN=VIN;
                        A.Sold_Cars_Database=InsertCar(A.Sold_Cars_Database,car);
                        A.no_of_cars_sold++;
                        S.Sold_Cars_Database=InsertCar(S.Sold_Cars_Database,car);
                        printf("\nSuccessful trasaction!");
                        done=1;
                        
                    }
                }
                break;
            default:
                done=1;
                break;


        }
    }
    *Sptr=S;
    return A;
}
//-------------------------------------------------------------------------
