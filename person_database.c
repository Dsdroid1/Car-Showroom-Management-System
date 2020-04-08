#include"person_database.h"

Customer_Node* CreateCustomerNode(Customer C)
{
    //Initializes a sales_person_node
    Customer_Node *Cptr;
    Cptr=(Customer_Node *)malloc(sizeof(Customer_Node));
    Cptr->BF=EH;
    Cptr->C=C;
    Cptr->left=NULL;
    Cptr->right=NULL;
    return Cptr;
}


Customer_Node* InsertIntoCustomerDatabase(Customer_Node *root,Customer C,Ht_Direction *increase)
{
    Customer_Node *retval=NULL;
    Bool isleaf=FALSE;
    if(root!=NULL)
    {
        if(root->C.ID < C.ID)
        {
            if(root->right!=NULL)
            {
                root->right=InsertIntoCustomerDatabase(root->right,C,increase);
                
            }
            else
            {
                isleaf=TRUE;
                Customer_Node *Sptr=CreateCustomerNode(C);
                root->right=Sptr;
                switch(root->BF)
                {
                    case LH:
                        root->BF=EH;
                        *increase=NO_CHANGE;
                        break;

                    case EH:
                        root->BF=RH;
                        *increase=RIGHT;
                        break;

                    default:
                        break;

                }
                retval=root;
            }
        }
        else if(root->C.ID > C.ID)
        {
            if(root->left!=NULL)
            {
                root->left=InsertIntoCustomerDatabase(root->left,C,increase);
            }
            else
            {
                isleaf=TRUE;
                Customer_Node *Sptr=CreateCustomerNode(C);
                root->left=Sptr;
                switch(root->BF)
                {
                    case EH:
                        root->BF=LH;
                        *increase=LEFT;
                        break;

                    case RH:
                        root->BF=EH;
                        *increase=NO_CHANGE;
                        break;

                    default:
                        break;

                }
                retval=root;
            }
        }
        else
        {
            printf("\nError,ID Already exists!");
            //Somehow ,this error needs to be indicated to other functions.....
        }
        if(isleaf==FALSE)//Now,recursion unfolding part
        {
            if(*increase==NO_CHANGE)
            {
                //Do nothing
                retval=root;
            }
            else if(*increase==LEFT)
            {
                //Height has increased in the left direction of the current root
                switch(root->BF)
                {
                    case LH:
                        //Node was already tilted to left,now double tilt occured
                        retval=Customer_BalanceLeft(root);
                        *increase=NO_CHANGE;
                        break;

                    case EH:
                        root->BF=LH;
                        *increase=LEFT;
                        retval=root;
                        break;

                    case RH:
                        root->BF=EH;
                        *increase=NO_CHANGE;
                        retval=root;
                        break;
                
                    default:
                        break;
                }
            }
            else
            {
                //Height has increased in the right direction of the current root
                switch(root->BF)
                {
                    case LH:
                        root->BF=EH;
                        *increase=NO_CHANGE;
                        retval=root;
                        break;

                    case EH:
                        root->BF=RH;
                        *increase=RIGHT;
                        retval=root;
                        break;

                    case RH:
                        retval=Customer_BalanceRight(root);
                        *increase=NO_CHANGE;
                        break;

                
                    default:
                        break;
                }
            }
        }
    }
    else
    {
        retval=CreateCustomerNode(C);
    }
    return retval;
}

Customer_Node* Customer_BalanceLeft(Customer_Node* root)
{
    Customer_Node *retval=NULL,*r=NULL;//as in notebook
    if(root->left->BF==LH)
    {
        retval=Customer_RotateLeft(root);
        root->BF=EH;
        retval->BF=EH;
    }
    else if(root->left->BF==RH)
    {
        r=(root->left)->right;
        if(r->BF==RH)
        {
            //After the rotations
            root->left->BF=LH;
            r->BF=EH;
            root->BF=LH;
        }
        else if(r->BF==LH)
        {
            root->left->BF=EH;
            r->BF=RH;
            root->BF=EH;
            
        }
        root->left=Customer_RotateRight(root->left);
        retval=Customer_RotateLeft(root);
    }
    return retval;
}

Customer_Node* Customer_BalanceRight(Customer_Node* root)
{
    Customer_Node *retval=NULL,*r=NULL;//as in notebook
    if(root->right->BF==RH)
    {
        retval=Customer_RotateRight(root);
        root->BF=EH;
        retval->BF=EH;
    }
    else if(root->right->BF==LH)
    {
        r=(root->right)->left;
        if(r->BF==LH)
        {
            //After the rotations
            root->right->BF=RH;
            r->BF=EH;
            root->BF=RH;
        }
        else if(r->BF==RH)
        {
            root->right->BF=EH;
            r->BF=LH;
            root->BF=EH;
            
        }
        root->right=Customer_RotateLeft(root->right);
        retval=Customer_RotateRight(root);
    }
    return retval;
}

Customer_Node* Customer_RotateLeft(Customer_Node* root)//Just adjusts links
{
    Customer_Node *retval=NULL;
    if(root!=NULL&&root->left!=NULL)
    {
        retval=root->left;
        root->left=retval->right;
        retval->right=root;
    }
    return retval;
}

Customer_Node* Customer_RotateRight(Customer_Node* root)
{
    Customer_Node *retval=NULL;
    if(root!=NULL&&root->right!=NULL)
    {
        retval=root->right;
        root->right=retval->left;
        retval->left=root;
    }
    return retval;
}

Customer SearchCustomer(Customer_Node *root,int Customer_ID)
{
    Customer C;
    C.ID=-1;//Invalid
    if(root!=NULL)
    {
        if(root->C.ID < Customer_ID)
        {
            C=SearchCustomer(root->right,Customer_ID);
        }
        else if(root->C.ID > Customer_ID)
        {
            C=SearchCustomer(root->left,Customer_ID);
        }
        else
        {
            C=root->C;
        }
    }
    return C;
}