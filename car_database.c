#include"car_database.h"

Car MakeCar(int VIN,char Name[],Car_Color color,Fuel_Type fuel,Car_Type type);
void setPrice(Car car,int price);
Car_Data_Node* MakeCarDataNode();
Car_Tree_Node* MakeCarTreeNode();
Car_Tree_Node* InsertIntoCarDatabase(Car_Tree_Node *root,Car car,int *make_new_node);
Car_Tree_Node* InsertCar(Car_Tree_Node *root,Car car);
Car_Tree_Node* DeleteFromCarDatabase(Car_Tree_Node *root,Car car,Bool *less);
Car_Tree_Node* DeleteCar(Car_Tree_Node *root,int VIN);


//-----------------To Initialise the various "objects" ;)--------------------------------------
Car MakeCar(int VIN,char Name[],Car_Color color,Fuel_Type fuel,Car_Type type)
{
    Car C;
    C.price=0;
    C.VIN=VIN;
    strcpy(C.Name,Name);
    C.color=color;
    C.fuel=fuel;
    C.type=type;
    C.Customer_ID=-1;
    return C;
}

void setPrice(Car car,int price)
{
    car.price=price;
}

Car_Data_Node* MakeCarDataNode()//Make empty car_data_node
{
    Car_Data_Node* node;
    node=(Car_Data_Node *)malloc(sizeof(Car_Data_Node));
    if(node!=NULL)
    {
        int i=0;
        for(i=0;i<c;i++)
        {
            node->car[i]=MakeCar(-1,"none",YELLOW,DIESEL,SUV);
        }
        node->next=NULL;
        node->prev=NULL;
    }
    return node;
}

Car_Tree_Node* MakeCarTreeNode()//Make empty car_tree_node
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
//------------------------End of Initialise functions------------------------------------------

//---------------------------Insert Functions--------------------------------------------------
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
                int check_space=i,res=0;
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
                if(res==1)
                {
                    //Space in this mode exists
                    //The to be inserted value will come via make_new_node contents
                    int move=(k-1)-1;//(k-1)-1
                    for(; move > i; move--)
                    {
                        root->VIN[move]=root->VIN[move-1];
                        root->VIN[move-1]=-1;
                        root->children.child_t[move+1]=root->children.child_t[move];
                        root->children.child_t[move]=NULL;
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
                            root->VIN[move-1]=-1;
                            root->children.child_t[move+1]=root->children.child_t[move];
                            root->children.child_t[move]=NULL;
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
                        root->VIN[(k-1)/2]=-1;
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
                        linker->prev=datanode;
                    }
                }
                
            }
            //int done=0;       
            if(j<c && datanode->car[j].VIN==-1)//free space exists in this datanode,//ADD j<c && ...(present condition)
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
                                root->VIN[shift]=-1;
                                root->children.child_l[shift+2]=root->children.child_l[shift+1];
                                root->children.child_l[shift+1]=NULL;
                            }
                            root->VIN[i]=newnode->car[0].VIN;
                            root->children.child_l[i+1]=newnode;
                        }

                        //The else part is when the tree node doesnt have any space
                        else
                        {
                            
                            int median;
                            
                            Car_Tree_Node *leafnode=NULL;
                            //Split the tree node into 2 about the median 
                            //Find median
                            
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
                                    root->VIN[copy-1]=-1;
                                    root->children.child_l[copy+1]=root->children.child_l[copy];
                                    root->children.child_l[copy]=NULL;
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
//InsertIntoCarDatabase should be tested more--------------------------------------------------
//--------------------------End of insert functions--------------------------------------------

//------------------------------------Delete Functions-----------------------------------------
Car_Tree_Node* DeleteCar(Car_Tree_Node *root,int VIN)
{
    //Currently it should exist in database
    Bool less=FALSE;
    Car_Tree_Node *retval=NULL;
    DeleteFromCarDatabase(root,(MakeCar(VIN,"A",0,0,0)),&less);
    retval=root;
    if(retval!=NULL)
    {
        if(retval->VIN[0]==-1)//if *less==TRUE
        {
            if(retval->isLeaf==FALSE)
            {
                retval=retval->children.child_t[0];
            }
            else
            {
                //just the root is present
                if(retval->children.child_l[1]==NULL)
                {
                    retval->children.child_l[1]=retval->children.child_l[0];
                    retval->children.child_l[0]=NULL;
                }//Above part to keep uniform as insertion
                retval->VIN[0]=(retval->children.child_l[1])->car[0].VIN;
            }
        }
        else
        {
            retval=root;
        }
    }
    return retval;
}



Car_Tree_Node* DeleteFromCarDatabase(Car_Tree_Node *root,Car car,Bool *less)//call with false
{
    Car_Tree_Node *retval=root;
    if(root!=NULL)
    {
        if(root->isLeaf==TRUE)
        {
            int i=0;
            int found=0;
            while(i < k-1 && found==0)
            {
                if(root->VIN[i]!=-1)
                {
                    if(car.VIN >= root->VIN[i])
                    {
                        i++;
                    }
                    else
                    {
                        found=1;
                    }
                }
                else
                {
                    found=1;
                }
            }
            //i is the link which can contain the given data item
            Car_Data_Node *datanode=NULL;
            datanode=root->children.child_l[i];
            int search=0,search_success=0;
            while(search < c && search_success==0)
            {
                if(datanode->car[search].VIN==car.VIN)
                {
                    search_success=1;
                }
                else
                {
                    search++;
                }
            }
            if(search_success==1)
            {
                int num_valid=c;
                while(datanode->car[num_valid-1].VIN==-1)
                {
                    num_valid--;
                }
                //Now we know how many entries are there in this node
                if(num_valid-1 >= (c+1)/2)
                {
                    //Direct deletion of this entry is possible
                    for(; search < num_valid-1 ;search++)
                    {
                        datanode->car[search]=datanode->car[search+1];
                    }   
                    datanode->car[search].VIN=-1;
                    printf("DELETE SUCCESS");
                }
                else
                {
                    //This node ,after deleteion will violate the min content property
                    //Check if sibling has extra....
                    int done=0;
                    //First Check right sibling......
                    Car_Data_Node *rsibling,*lsibling;
                    int num_in_rsib=c;
                    int num_in_lsib=c;
                    Bool rsib_exist=FALSE,lsib_exist=FALSE,rsib_can_donate=FALSE,lsib_can_donate=FALSE;
                    if(i < k-1)//Right sibling can exist
                    {
                        rsibling=root->children.child_l[i+1];
                        if(rsibling!=NULL)
                        {
                            rsib_exist=TRUE;
                            
                            while(rsibling->car[num_in_rsib-1].VIN==-1)
                            {
                                num_in_rsib--;
                            }
                            if(num_in_rsib-1 >= (c+1)/2)//rsibling can donate to datanode via parent
                            {
                                rsib_can_donate=TRUE;
                                for(; search < num_valid-1 ;search++)
                                {
                                    datanode->car[search]=datanode->car[search+1];
                                }   
                                datanode->car[search]=rsibling->car[0];
                                
                                int move=0;
                                for(; move < num_in_rsib-1 ;move++)
                                {
                                    rsibling->car[move]=rsibling->car[move+1];
                                }
                                rsibling->car[move].VIN=-1;
                                root->VIN[i]=rsibling->car[0].VIN;
                                printf("\nSuccessful Deletion");
                                done=1;
                            }
                            else
                            {
                                rsib_can_donate=FALSE;
                                //Check if lsibling exists
                            }
                        }
                    }
                    if(rsib_can_donate==FALSE)//either rsib doesnt exist or doesnt has enough to give
                    {
                        //Check if lsibling can donate
                        if(i-1 >= 0)//lsibling can exist
                        {
                            lsibling=root->children.child_l[i-1];
                            if(lsibling!=NULL)
                            {
                                lsib_exist=TRUE;
                                
                                while(lsibling->car[num_in_lsib-1].VIN==-1)
                                {
                                    num_in_lsib--;
                                }
                                if(num_in_lsib > (c+1)/2)
                                {
                                    lsib_can_donate=TRUE;
                                    //Donation to datanode possible
                                    root->VIN[i-1]=lsibling->car[num_in_lsib-1].VIN;
                                    //num_valid is for datanode
                                    //Delete the entry at 'search' index
                                    datanode->car[search].VIN=-1;
                                    //move prev entries here
                                    int move=search;
                                    for(; move > 0;move--)
                                    {
                                        datanode->car[move]=datanode->car[move-1];
                                    }
                                    datanode->car[move]=lsibling->car[num_in_lsib-1];
                                    lsibling->car[num_in_lsib-1].VIN=-1;
                                    done=1;
                                }
                                else
                                {
                                    lsib_can_donate=FALSE;
                                }
                            }
                        }
                    }
                    if(done==0)
                    {
                        //Donation was not possible,now try to merge
                        if(rsib_exist==TRUE)
                        {
                            //rsibling exists and cannot donate,hence merge datanode with rsibling
                            for(; search < num_valid-1 ;search++)
                            {
                                datanode->car[search]=datanode->car[search+1];
                            }   
                            datanode->car[search].VIN=-1;
                            //Now put the data of rsibling into datanode
                            int  move=0;
                            for(; move < num_in_rsib; move++,search++)
                            {
                                datanode->car[search]=rsibling->car[move];
                                rsibling->car[move].VIN=-1;
                            }
                            datanode->next=rsibling->next;
                            if(rsibling->next!=NULL)
                            {
                                (rsibling->next)->prev=datanode;
                            }
                            free(rsibling);
                            root->children.child_l[i+1]=NULL;
                            //Now we have to delete the root->VIN[i]

                            //Now the cases depend on how many nodes are present in the root node here
                            int num_item_in_root=k-1;//Make i-1 in root as -1,done in loop ahead
                            while(root->VIN[num_item_in_root-1]==-1)
                            {
                                num_item_in_root--;
                            }
                            int shift=i;
                            for(; shift < num_item_in_root-1 ; shift++)
                            {
                                root->VIN[shift]=root->VIN[shift+1];
                                root->children.child_l[shift+1]=root->children.child_l[shift+2];
                                root->children.child_l[shift+2]=NULL;
                            }
                            root->VIN[shift]=-1;
                            //Now we need to check how many items are present in this node
                            num_item_in_root--;
                                
                            if(num_item_in_root < (k+1)/2-1)//-1
                            {
                                //Now this node is devoid, unfolding of recursion should then adjust it
                               *less=TRUE;
                            }
                            else
                            {
                                //This node is alright after shifting,the operation was a success
                                printf("\nSuccessful Deletion");
                                *less=FALSE;
                            }
                        }
                        else if(lsib_exist==TRUE)
                        {
                            //This has to be merged with datanode
                            int move=0;
                            for(; move < c;move++)
                            {
                                if(datanode->car[move].VIN!=-1 && move!=search)
                                {
                                    lsibling->car[num_in_lsib]=datanode->car[move];
                                    num_in_lsib++;
                                }
                            }
                            root->VIN[i-1]=-1;
                            lsibling->next=datanode->next;
                            if(datanode->next!=NULL)
                            {
                                        (datanode->next)->prev=lsibling;
                            }
                            free(datanode);
                            root->children.child_l[i]=NULL;
                                    

                            //We need to know how many elements exist in the root....
                            //That is given by i as right sibling does not exist
                            if( i-1 >= (k+1)/2-1)//???????????-1?????????????????
                            {
                                        //The parent node is alright
                                *less=FALSE;
                            }
                            else
                            {
                                *less=TRUE;
                            }
                        }
                        else
                        {
                            //Both right and left sibling dont exist.....
                            //This is only possible if just the root remains
                            //Then simply delete this element
                            for(; search < num_valid-1 ;search++)
                            {
                                datanode->car[search]=datanode->car[search+1];
                            }   
                            datanode->car[search].VIN=-1;
                            num_valid--;
                            if(num_valid==0)
                            {
                                free(root);
                                free(datanode);
                                root=NULL;
                                retval=root;
                            }
                        }
                    }
                }
            }
        }
        else
        {
            //Check which pointer to chase
            int i=0;
            int found=0;
            while(i < k-1 && found==0)
            {
                if(root->VIN[i]!=-1)
                {
                    if(car.VIN >= root->VIN[i])
                    {
                        i++;
                    }
                    else
                    {
                        found=1;
                    }
                }
                else
                {
                    found=1;
                }
            }
            Car_Tree_Node *retval=NULL,*chased_node=NULL;
            DeleteFromCarDatabase(root->children.child_t[i],car,less);
            if(*less==FALSE)
            {
                //Simply return
                //return retval;
            }
            else
            {
                Car_Tree_Node *rsibling,*lsibling;
                int done=0;
                int rsize=0,lsize=0;
                Bool rsib_exist=FALSE,lsib_exist=FALSE,rsib_can_donate=FALSE,lsib_can_donate=FALSE;                
                if(i < k-1)//rsibling can exist
                {
                    rsibling=root->children.child_t[i+1];
                    if(rsibling!=NULL)//right sibling exists
                    {
                        rsib_exist=TRUE;
                        while(rsize < k-1 && rsibling->VIN[rsize]!=-1)
                        {
                            rsize++;
                        }
                        if(rsize-1 >= (k+1)/2-1)//(k+1)/2 min children...this -1 has to be done on prev(leaf part also)
                        {
                            rsib_can_donate=TRUE;
                            //sibling can donate
                            chased_node=root->children.child_t[i];
                            int pos=0;
                            while(chased_node->VIN[pos]!=-1)
                            {
                                pos++;
                            }
                            chased_node->VIN[pos]=root->VIN[i];
                            chased_node->children.child_t[pos+1]=rsibling->children.child_t[0];
                            root->VIN[i]=rsibling->VIN[0];
                            int shift=0;
                            for(; shift< (k-1)-1;shift++)
                            {
                                rsibling->VIN[shift]=rsibling->VIN[shift+1];
                                rsibling->VIN[shift+1]=-1;
                                rsibling->children.child_t[shift]=rsibling->children.child_t[shift+1];
                                rsibling->children.child_t[shift+1]=NULL;
                            }
                            rsibling->VIN[shift]=-1;
                            rsibling->children.child_t[shift]=rsibling->children.child_t[shift+1];
                            rsibling->children.child_t[shift+1]=NULL;
                            //Sibling donation completed....
                            *less=FALSE;
                            done=1;
                        }
                        else
                        {
                            rsib_can_donate=FALSE;
                        }
                    }
                }
                if(rsib_can_donate==FALSE)//either doesnt exist or cant donate
                {
                    lsibling=root->children.child_t[i-1];
                    if(lsibling!=NULL)
                    {
                        lsib_exist=TRUE;
                        while(lsize < k-1 && lsibling->VIN[lsize]!=-1)
                        {
                           lsize++;
                        }
                        if(lsize-1 >= (k+1)/2-1)//(k+1)/2 min children...this -1 has to be done on prev(leaf part also)
                        {
                            lsib_can_donate=TRUE;
                            //sibling can donate
                            chased_node=root->children.child_t[i];
                            int pos=(k-1)-1,flag=0;
                            for(; pos>0;pos--)
                            {
                                chased_node->VIN[pos]=chased_node->VIN[pos-1];
                                chased_node->children.child_t[pos+1]=chased_node->children.child_t[pos];
                            }
                            chased_node->children.child_t[pos+1]=chased_node->children.child_t[pos];                                        chased_node->children.child_t[0]=lsibling->children.child_t[lsize];
                            lsibling->children.child_t[lsize]=NULL;
                            chased_node->VIN[0]=root->VIN[i-1];
                            root->VIN[i-1]=lsibling->VIN[lsize-1];
                            lsibling->VIN[lsize-1]=-1;
                            lsize--;
                            *less=FALSE;
                            done=1;
                        }
                        else
                        {
                            lsib_can_donate=FALSE;
                        }
                    }
                }
                if(done==0)//No one could donate,try merge
                {
                    if(rsib_exist==TRUE)
                    {
                        //merge with rsib
                        chased_node=root->children.child_t[i];
                        int pos=0;
                        while(chased_node->VIN[pos]!=-1)
                        {
                           pos++;
                        }
                        chased_node->VIN[pos]=root->VIN[i];
                        chased_node->children.child_t[pos+1]=rsibling->children.child_t[0];
                        int copy=0;
                        int flag=0;
                        pos++;//Imp addition
                        for(; copy < k-1&&flag==0;copy++,pos++ )
                        {
                            if(rsibling->VIN[copy]!=-1)
                            {
                                chased_node->VIN[pos]=rsibling->VIN[copy];
                                chased_node->children.child_t[pos+1]=rsibling->children.child_t[copy+1];
                            }
                            else
                            {
                                flag=1;
                            }
                        }
                        free(rsibling);
                        int shift=0;
                        flag=0;
                        for(shift=i;shift<(k-1)-1&&flag==0;shift++)
                        {
                            if(root->VIN[shift]!=-1)
                            {
                                root->VIN[shift]=root->VIN[shift+1];
                                root->children.child_t[shift+1]=root->children.child_t[shift+2];
                            }
                            else
                            {
                                flag=0;
                            }
                        }
                        if(shift<k-1)
                        {
                            root->VIN[shift]=-1;
                            root->children.child_t[shift+1]=NULL;
                        }
                        //find the number of valid nodes
                        shift=k-1;
                        while(shift>0 && root->VIN[shift-1]==-1)
                        {
                            shift--;
                        }
                        if(shift < (k+1)/2-1)//Check if equal too required
                        {
                            *less=TRUE;
                        }
                        else
                        {
                            *less=FALSE;
                        }
                    }
                    else if(lsib_exist==TRUE)
                    {
                        lsibling->VIN[lsize]=root->VIN[i-1];
                                
                        chased_node=root->children.child_t[i];
                        lsibling->children.child_t[lsize+1]=chased_node->children.child_t[0];
                                
                        lsize++;
                        int pos=0,flag=0;
                        while(pos < k-1 && flag==0)
                        {
                            if(chased_node->VIN[pos]!=-1)
                            {
                                lsibling->VIN[lsize]=chased_node->VIN[pos];
                                lsibling->children.child_t[lsize+1]=chased_node->children.child_t[pos+1];
                                lsize++;
                            }
                            else
                            {
                                flag=1;
                            }
                            pos++;
                        }
                        free(chased_node);
                        //rsibling did not exist becoz right side would not have any valid data partition item
                        root->VIN[i-1]=-1;
                        root->children.child_t[i]=NULL;
                        if(i-1 < (k+1)/2-1)//i-1 is the number of valid elements
                        {
                            *less=TRUE;
                        }
                        else
                        {
                            *less=FALSE;
                        }
                    }
                }
            }
        }
    }
    return retval;
}

//-------------------------------End of delete functions--------------------------------------------

//---------------Simple search function------------------------------------------------------------
Car SearchCarDatabase(Car_Tree_Node *root,int VIN)
{
    Car retval;
    retval.VIN=-1;//to indicate invalid
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
            retval=SearchCarDatabase(root->children.child_t[i],VIN);
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
            i=0;
            found=0;
            while(i<c && found==0)
            {
                if(data->car[i].VIN!=-1)
                {
                    if(data->car[i].VIN < VIN)
                    {
                        i++;
                    }
                    else if(data->car[i].VIN > VIN)
                    {
                        //Does not exist
                        found=-1;
                        retval.VIN=-1;
                    }
                    else
                    {
                        retval=(data->car[i]);
                        found=1;
                    }
                }
            }
        }
    }
    return retval;
}