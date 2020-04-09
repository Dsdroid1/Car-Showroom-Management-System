#include"sales_person_database.h"

Sales_Person_Node* CreateSalesPersonNode(Sales_Person S)
{
    //Initializes a sales_person_node
    Sales_Person_Node *Sptr;
    Sptr=(Sales_Person_Node *)malloc(sizeof(Sales_Person_Node));
    Sptr->BF=EH;
    Sptr->S=S;
    Sptr->left=NULL;
    Sptr->right=NULL;
    return Sptr;
}


Sales_Person_Node* InsertIntoSalesPersonDatabase(Sales_Person_Node *root,Sales_Person S,Ht_Direction *increase)
{
    Sales_Person_Node *retval=NULL;
    Bool isleaf=FALSE;
    if(root!=NULL)
    {
        if(root->S.ID < S.ID)
        {
            if(root->right!=NULL)
            {
                root->right=InsertIntoSalesPersonDatabase(root->right,S,increase);
                
            }
            else
            {
                isleaf=TRUE;
                Sales_Person_Node *Sptr=CreateSalesPersonNode(S);
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
        else if(root->S.ID > S.ID)
        {
            if(root->left!=NULL)
            {
                root->left=InsertIntoSalesPersonDatabase(root->left,S,increase);
            }
            else
            {
                isleaf=TRUE;
                Sales_Person_Node *Sptr=CreateSalesPersonNode(S);
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
            printf("\nError,ID already exists!");
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
                        retval=BalanceLeft(root);
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
                        retval=BalanceRight(root);
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
        retval=CreateSalesPersonNode(S);
    }
    return retval;
}

Sales_Person_Node* BalanceLeft(Sales_Person_Node* root)
{
    Sales_Person_Node *retval=NULL,*r=NULL;//as in notebook
    if(root->left->BF==LH)
    {
        retval=RotateLeft(root);
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
        root->left=RotateRight(root->left);
        retval=RotateLeft(root);
    }
    return retval;
}

Sales_Person_Node* BalanceRight(Sales_Person_Node* root)
{
    Sales_Person_Node *retval=NULL,*r=NULL;//as in notebook
    if(root->right->BF==RH)
    {
        retval=RotateRight(root);
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
        root->right=RotateLeft(root->right);
        retval=RotateRight(root);
    }
    return retval;
}

Sales_Person_Node* RotateLeft(Sales_Person_Node* root)//Just adjusts links
{
    Sales_Person_Node *retval=NULL;
    if(root!=NULL&&root->left!=NULL)
    {
        retval=root->left;
        root->left=retval->right;
        retval->right=root;
    }
    return retval;
}

Sales_Person_Node* RotateRight(Sales_Person_Node* root)
{
    Sales_Person_Node *retval=NULL;
    if(root!=NULL&&root->right!=NULL)
    {
        retval=root->right;
        root->right=retval->left;
        retval->left=root;
    }
    return retval;
}



Sales_Person SearchSalesPerson(Sales_Person_Node *root,int ID)
{
    Sales_Person S;
    S.ID=-1;//Invalid
    if(root!=NULL)
    {
        if(root->S.ID < ID)
        {
            S=SearchSalesPerson(root->right,ID);
        }
        else if(root->S.ID > ID)
        {
            S=SearchSalesPerson(root->left,ID);
        }
        else
        {
            S=root->S;
        }
    }
    return S;
}

Sales_Person_Node* SearchSalesPersonNode(Sales_Person_Node *root,int ID)
{
    Sales_Person_Node *retval=NULL;
    //Sales_Person S;
    //S.ID=-1;//Invalid
    if(root!=NULL)
    {
        if(root->S.ID < ID)
        {
            retval=SearchSalesPersonNode(root->right,ID);
        }
        else if(root->S.ID > ID)
        {
            retval=SearchSalesPersonNode(root->left,ID);
        }
        else
        {
            retval=root;
        }
    }
    return retval;
}