#include<stdio.h>
#include"structs.h"

Car MakeCar(int VIN,char Name[],Car_Color color,Fuel_Type fuel,Car_Type type);
Car_Data_Node* MakeCarDataNode();
Car_Tree_Node* MakeCarTreeNode();
Car_Tree_Node* InsertIntoCarDatabase(Car_Tree_Node *root,Car car,int *make_new_node);
Car_Tree_Node* InsertCar(Car_Tree_Node *root,Car car);
Car_Tree_Node* DeleteFromCarDatabase(Car_Tree_Node *root,Car car,Bool *less);
Car_Tree_Node* DeleteCar(Car_Tree_Node *root,int VIN);



Car_Tree_Node* DeleteCar(Car_Tree_Node *root,int VIN)
{
    //Currently it should exist in database
    Bool less=FALSE;
    Car_Tree_Node *retval=NULL;
    DeleteFromCarDatabase(root,(MakeCar(VIN,"A",0,0,0)),&less);
    retval=root;
    if(retval!=NULL)
    {
        if(retval->VIN[0]==-1)
        {
            retval=retval->children.child_t[0];
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
                                root->VIN[i]=rsibling->car[0].VIN;
                                int move=0;
                                for(; move < num_in_rsib-1 ;move++)
                                {
                                    rsibling->car[move]=rsibling->car[move+1];
                                }
                                rsibling->car[move].VIN=-1;
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
                                
                            if(num_item_in_root < (k+1)/2)
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
                        //shift is also the number of valid nodes
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
                        *less=TRUE;
                    }
                }
            }
        }
    }
    return retval;
}