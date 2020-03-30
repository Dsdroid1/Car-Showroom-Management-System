#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

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

Car MakeCar(int VIN,char Name[],Car_Color color,Fuel_Type fuel,Car_Type type)
{
    Car C;
    //C=(Car *)malloc(sizeof(Car));
    C.VIN=VIN;
    //strcpy(C.Name,Name);
    C.color=color;
    C.fuel=fuel;
    C.type=type;
    return C;
}

Car_Data_Node* MakeCarDataNode()
{
    Car_Data_Node* node;
    node=(Car_Data_Node *)malloc(sizeof(Car_Data_Node));
    if(node!=NULL)
    {
        int i=0;
        for(i=0;i<c;i++)
        {
            node->car[i]=MakeCar(-1,'\0',YELLOW,DIESEL,SUV);
        }
        node->next=NULL;
        node->prev=NULL;
    }
    return node;
}

Car_Tree_Node* MakeCarTreeNode()
{
    Car_Tree_Node* node;
    node=(Car_Tree_Node *)malloc(sizeof(Car_Tree_Node));
    if(node!=NULL)
    {
        int i=0;
        for(i=0;i<k-1;i++)
        {
            node->VIN[i]=-1;
            node->children.child_l[i]=NULL;
        }
        node->isLeaf=TRUE;//By default
        node->children.child_l[k-1]=NULL;
    }
    return node; 
}

/////////////////////////////////Try To write insert fn
Car_Tree_Node* InsertIntoCarDatabase(Car_Tree_Node *root,Car car,int *make_new_node);
Car_Tree_Node* InsertCar(Car_Tree_Node *root,Car car)
{
    int make_new_node=-1;
    Car_Tree_Node *retval=NULL;
    retval=InsertIntoCarDatabase(root,car,&make_new_node);
    if(root==NULL)
    {
        root=retval;
    }
    if(make_new_node!=-1||retval==NULL)//Height has to be increased
    {
        Car_Tree_Node *true_root=NULL;
        true_root=MakeCarTreeNode();
        true_root->isLeaf=FALSE;
        true_root->VIN[0]=make_new_node;
        true_root->children.child_t[0]=root;
        true_root->children.child_t[1]=retval;
        root=true_root;
    }
    return root;
}

Car_Tree_Node* InsertIntoCarDatabase(Car_Tree_Node *root,Car car,int *make_new_node)//Initial call with *make_new_node==-1
{
    Car_Tree_Node *retval;
    //Recursive by nature
    if(root==NULL)
    {
        root=MakeCarTreeNode();
        root->VIN[0]=car.VIN;
        root->isLeaf=TRUE;
        Car_Data_Node *node=NULL;
        node=MakeCarDataNode();
        node->car[0]=car;
        root->children.child_l[1]=node;//Currently we have only single element ,so equal to element on right of tree
        
        return root;
    }
    else
    {
        //Tree already exists,search here
        if(root->isLeaf==FALSE)
        {
            //Here B Tree insertion
            int i=0,flag=0;
            while(i<k-1 && flag==0)
            {
                if(root->VIN[i]!=-1)
                {
                    if(root->VIN[i] < car.VIN )
                    {
                        i++;
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
            //After this loop ,we know towards i'th child to go
            retval=InsertIntoCarDatabase(root->children.child_t[i],car,make_new_node);
            //maybe some work required? 
            if(retval==NULL||*make_new_node == -1)
            {
                //Basically no new node formed,directly return
                return retval;
            }
            else
            {
                //Check if this node has space
                int check_space=i+1,res=0;
                while(check_space<k-1 && res==0)
                {
                    if(root->VIN[check_space]==-1)
                    {
                        res=1;
                    }
                    else
                    {
                        check_space++;
                    }
                }
                if(check_space!=k-1)
                {
                    //Space in this mode exists
                    //The to be inserted value will come via make_new_node contents
                    int move=k-1;
                    for(; move > i; move--)
                    {
                        root->VIN[move]=root->VIN[move-1];
                        root->children.child_t[move+1]=root->children.child_t[move];
                    }
                    root->VIN[move]=*make_new_node;
                    root->children.child_t[move+1]=retval;
                    printf("\nSuccessful Insertion!!");
                    *make_new_node=-1;
                }
                else
                {
                    //This node has to be split
                    int median;
                    Car_Tree_Node *new=NULL;
                    if(i==(k-1)/2)
                    {
                        //the returned value will be the median
                        new=MakeCarTreeNode();
                        new->isLeaf=FALSE;
                        int move=(k-1)/2,pos=0;
                        for(; move<k-1;move++,pos++)
                        {
                            new->VIN[pos]=root->VIN[move];
                            root->VIN[move]=-1;
                            new->children.child_t[pos+1]=root->children.child_t[move+1];
                            root->children.child_t[move+1]=NULL;
                        }
                        new->children.child_t[0]=retval;
                        median=*make_new_node;
                        return new;
                    }
                    else if(i < (k-1)/2)
                    {
                        median=root->VIN[(k-1)/2-1];
                        new=MakeCarTreeNode();
                        int move=(k-1)/2,pos=0;
                        for(; move<k-1;move++,pos++)
                        {
                            new->VIN[pos]=root->VIN[move];
                            root->VIN[move]=-1;
                            new->children.child_t[pos+1]=root->children.child_t[move+1];
                            root->children.child_t[move+1]=NULL;
                        }
                        new->children.child_t[0]=root->children.child_t[(k-1)/2];
                        
                        for(move=(k-1)/2-1;move>i;move--)
                        {
                            root->VIN[move]=root->VIN[move-1];
                            root->children.child_t[move+1]=root->children.child_t[move];
                        }
                        root->VIN[move]=*make_new_node;
                        root->children.child_t[move+1]=retval;
                        *make_new_node=median;
                        retval=new;
                        return new;
                    }
                    else
                    {
                        median=root->VIN[(k-1)/2];
                        new=MakeCarTreeNode();
                        new->isLeaf=FALSE;
                        int move=(k-1)/2+1,pos=0;
                        for(; move < i ;move++,pos++)
                        {
                            new->VIN[pos]=root->VIN[move];
                            root->VIN[move]=-1;
                            new->children.child_t[pos]=root->children.child_t[move];
                            root->children.child_t[move]=NULL;
                        }
                        new->VIN[pos]=*make_new_node;
                        new->children.child_t[pos]=root->children.child_t[move];
                        root->children.child_t[move]=NULL;
                        new->children.child_t[pos+1]=retval;
                        pos++;
                        for(; move<k-1;move++,pos++)
                        {
                            new->VIN[pos]=root->VIN[move];
                            root->VIN[move]=-1;
                            new->children.child_t[pos+1]=root->children.child_t[move+1];
                            root->children.child_t[move+1]=NULL;
                        }
                        *make_new_node=median;
                        retval=new;
                        return new;
                    }
                }
                
            }


        }
        else
        {
            //Recursively, we reached to the leaf level
            int i=0,flag=0;
            while(i<k-1 && flag==0)
            {
                if(root->VIN[i]!=-1)
                {
                    if(root->VIN[i] < car.VIN )
                    {
                        i++;
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

            Car_Data_Node* datanode;
            datanode=root->children.child_l[i];
            int j=0,valid=1;
            if(datanode!=NULL)
            {
                //int j=0,valid=1;
                while(j<c && valid==1)
                {
                    if(datanode->car[j].VIN!=-1)
                    {
                        if(datanode->car[j].VIN < car.VIN)
                        {
                            j++;
                        }
                        else
                        {
                            valid=-1;
                        }
                        
                    }
                    else
                    {
                        valid=-1;   
                    }
                }
            } 
            else
            {
                //Typically ,i=0
                datanode=MakeCarDataNode();
                root->children.child_l[i]=datanode;
                Car_Data_Node *linker;
                if(i<k-1)
                {
                    linker=root->children.child_l[i+1];
                    if(root!=NULL)
                    {
                        //Adjust the links
                        datanode->next=linker;
                        datanode->prev=linker->prev;
                        if(linker->prev!=NULL)
                        {
                            (linker->prev)->next=datanode;
                        }
                    }
                }
                
            }
            //int done=0;       
            if(datanode->car[j].VIN==-1)//free space exists in this datanode
            {
                datanode->car[j]=car;
                
                printf("\nSucccessful Insertion!!");
                //done=1;
            }
                  
            else
            {
                int done=0;
                //Check if node has any free space elsewhere
                int check=c-1;      
                while(check>=0&&done==0)
                {
                    if(datanode->car[check].VIN==-1)
                    {
                        done=1;
                    }
                    check--;
                }
                if(done==1)
                {
                    //Stuff will work by shifting
                    while(datanode->car[check].VIN==-1)
                    {
                        check--;
                    }
                    check++;
                    for(; check>j;check--)
                    {
                        datanode->car[check]=datanode->car[check-1];
                    }
                    datanode->car[j]=car;
                }
                else if(done==0)
                {
                    //This datanode is already full
                    //We need to split this datanode into 2 parts
                    Car_Data_Node *newnode;
                    newnode=MakeCarDataNode();
                    int loop=0,pos=0;
                    int insert=0;
                    loop=(c+1)/2-1;
                    if(car.VIN >= datanode->car[loop].VIN)
                    {   
                        loop++;
                        while(loop<c)
                        {
                            if(insert==0)//car not yet inserted
                            {
                                if(car.VIN < datanode->car[loop].VIN)
                                {
                                    insert=1;
                                    newnode->car[pos]=car;
                                }
                                else
                                {
                                    newnode->car[pos]=datanode->car[loop];
                                    datanode->car[loop].VIN=-1;
                                    loop++;
                                }
                            
                            }
                            else
                            {
                                newnode->car[pos]=datanode->car[loop];
                                datanode->car[loop].VIN=-1;
                                loop++;
                            }
                        
                            pos++;
                        }
                        if(insert==0)
                        {
                            newnode->car[pos]=car;
                        }
                    }
                    else
                    {
                        //To be inserted in first part of the node
                        loop=0;
                        while(car.VIN > datanode->car[loop].VIN )
                        {
                            loop++;
                        }   
                        int copy=0;
                        for(copy=(c+1)/2-1;copy<c;copy++)
                        {
                            newnode->car[pos]=datanode->car[copy];
                            datanode->car[copy].VIN=-1;
                            pos++;
                        }
                        for(copy=(c-1)/2;copy>loop;copy--)
                        {
                            datanode->car[copy]=datanode->car[copy-1];
                        }
                        datanode->car[loop]=car;
                    }
                
                    /*for(loop=(c+1)/2;loop<c;loop++,pos++)//c is typically odd
                    {
                        if(firsttime==0&&car.VIN > datanode->car[loop].VIN)
                        {
                            newnode->car[pos]=datanode->car[loop];
                            datanode->car[loop].VIN=-1;
                            //firsttime=1;
                        }
                        else if(firsttime=0)
                        {
                            firsttime=1;
                            newnode->car[pos]=car;
                            pos++;
                            newnode->car[pos]=datanode->car[loop];
                            datanode->car[loop].VIN=-1;
                        }
                        else
                        {
                            newnode->car[pos]=datanode->car[loop];
                            datanode->car[loop].VIN=-1;
                        }
                        
                    } */  


                    //The above loop manages to split stuff into 2 different nodes
                    //Now maintaining the doubly linked list structure
                    newnode->next=datanode->next;
                    datanode->next=newnode;
                    if(newnode->next!=NULL)
                    {
                        (newnode->next)->prev=newnode;
                    } 
                    newnode->prev=datanode;

                    //Now links to be adjusted in The B tree part
                    //if(i<k-1)
                    //{
                        //The current leaf node of the B tree part has some space in it
                        //But to verify it ,we need to check if next entry is valid or not
                        int check_for_empty=i,result=0;
                        while(check_for_empty<k-1 && result==0)
                        {
                            if(root->VIN[check_for_empty]==-1)
                            {
                                result=1;
                            }
                            else
                            {
                                check_for_empty++;   
                            }
                        }

                        if(result==1)//Some empty space does exist in the treenode
                        {
                            //Now we need to shift the keys in this node correspondingly

                            int shift=check_for_empty;
                            for(shift=check_for_empty-1;shift>i-1;shift--)
                            {
                                root->VIN[shift+1]=root->VIN[shift];
                                root->children.child_l[shift+2]=root->children.child_l[shift+1];
                            }
                            root->VIN[i]=newnode->car[0].VIN;
                            root->children.child_l[i+1]=newnode;
                        }

                        //The else part is when the tree node doesnt have any space
                        else
                        {
                            //Write correct loops ...currently they seem to be buggy
                            int median;
                            //-----buggy part
                            /*
                            int value=(root->children.child_l[i+1])->car[0].VIN;
                            */
                            //
                            Car_Tree_Node *leafnode=NULL;
                            //Split the tree node into 2 about the median 
                            //Find median
                            //Ignore this comment->//i+1 is the ptr whose 1st value will be pushed up to compare for the median
                            if(i==(k-1)/2)//K is typically odd
                            {
                                //median is in this node
                                median=newnode->car[0].VIN;
                                //Now split the node into 2 parts
                                //Car_Tree_Node *leafnode;
                                leafnode=MakeCarTreeNode();
                                int copy=(k-1)/2,pos=0;
                                for(;copy<k-1;copy++,pos++)
                                {
                                    leafnode->VIN[pos]=root->VIN[copy];
                                    root->VIN[copy]=-1;
                                    leafnode->children.child_l[pos+1]=root->children.child_l[copy+1];
                                    root->children.child_l[copy+1]=NULL;
                                }
                                leafnode->children.child_l[0]=newnode;
                                //Stuff adjusted at this level
                                //Now to as recursion goes back,we need to implement addition of this median node to the parent

                            }
                            else if(i<(k-1)/2)
                            {
                                median=root->VIN[(k-1)/2-1];
                                
                                leafnode=MakeCarTreeNode();
                                int copy=(k+1)/2-1,pos=0;
                                for(;copy<k-1;copy++,pos++)
                                {
                                    leafnode->VIN[pos]=root->VIN[copy];
                                    root->VIN[copy]=-1;
                                    leafnode->children.child_l[pos+1]=root->children.child_l[copy+1];
                                    root->children.child_l[copy+1]=NULL;
                                }
                                leafnode->children.child_l[0]=root->children.child_l[(k-1)/2];
                                //Shift items from i+1 to median position
                                copy=(k-1)/2-1;
                                for(; copy<k-1&&copy > i ;copy--)
                                {
                                    root->VIN[copy]=root->VIN[copy-1];
                                    root->children.child_l[copy+1]=root->children.child_l[copy];
                                }
                                
                                root->children.child_l[copy+1]=newnode;
                                root->VIN[copy]=newnode->car[0].VIN;
                                //Stuff to be done
                            }
                            else
                            {
                                median=root->VIN[(k+1)/2-1];
                                //To be corrected
                                root->VIN[(k-1)/2]=-1;
                                leafnode=MakeCarTreeNode();
                                int copy=(k+1)/2;
                                int pos=0;
                                for(; copy < i;copy++,pos++)
                                {
                                    leafnode->VIN[pos]=root->VIN[copy];
                                    root->VIN[copy]=-1;
                                    leafnode->children.child_l[pos]=root->children.child_l[copy];
                                    root->children.child_l[copy]=NULL;
                                }
                                leafnode->children.child_l[pos]=root->children.child_l[copy];
                                root->children.child_l[copy]=NULL;
                                leafnode->VIN[pos]=newnode->car[0].VIN;
                                leafnode->children.child_l[pos+1]=newnode;
                                pos++;
                                for(; copy < k-1 ;copy++)
                                {
                                    leafnode->VIN[pos]=root->VIN[copy];
                                    root->VIN[copy]=-1;
                                    leafnode->children.child_l[pos+1]=root->children.child_l[copy+1];
                                    root->children.child_l[copy+1]=NULL;
                                }
                                /*
                                for(; copy<k-1&&copy<i+1 ;copy++,pos++)
                                {
                                    leafnode->VIN[pos]=root->VIN[copy];
                                    root->VIN[copy]=-1;
                                    leafnode->children.child_l[pos]=root->children.child_l[copy];
                                    root->children.child_l[copy]=NULL;
                                }
                                if(i+1==k)//The new node is greater
                                {
                                    leafnode->children.child_l[pos]=root->children.child_l[copy];
                                    root->children.child_l[copy]=NULL;

                                    leafnode->VIN[pos]==newnode->car[0].VIN;
                                    leafnode->children.child_l[pos+1]=newnode;
                                }
                                else
                                {
                                    //newnode is somewhere in between
                                    leafnode->VIN[pos]=newnode->car[0].VIN;
                                    leafnode->children.child_l[pos]=newnode;
                                    pos++;
                                    for(; copy<k-1;copy++,pos++)
                                    {
                                        leafnode->VIN[pos]=root->VIN[copy];
                                        root->VIN[copy]=-1;
                                        leafnode->children.child_l[pos]=root->children.child_l[copy];
                                        root->children.child_l[copy]=NULL;
                                    }
                                    leafnode->children.child_l[pos]=root->children.child_l[copy];
                                    root->children.child_l[copy]=NULL;
                                }*/
                                /*
                                leafnode->VIN[pos]=newnode->car[0].VIN;
                                leafnode->children.child_l[pos]=newnode;
                                pos++;
                                for(; copy<k-1;copy++,pos++)
                                {
                                    leafnode->VIN[pos]=root->VIN[copy];
                                    root->VIN[copy]=-1;
                                    leafnode->children.child_l[pos]=root->children.child_l[copy];
                                    root->children.child_l[copy]=NULL;
                                }
                                if(copy>i+1)
                                {
                                    leafnode->children.child_l[pos]=root->children.child_l[copy];
                                }*/
                                //Stuff to be done
                            }
                            *make_new_node=median;
                            return leafnode;
                        }
                //}
                }
            }
            
        }
    }
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
            printf("\n%d",d->car[i].VIN);
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
    while(done)
    {
        printf("\nEnter Car data:");
        scanf("%d",&VIN);
        car=MakeCar(VIN,"a",YELLOW,DIESEL,SEDAN);
        root=InsertCar(root,car);
        Print(root);
        //printf("\nDO u want to continue?(0 to exit)");
        //scanf("%d",&done);
    }
}