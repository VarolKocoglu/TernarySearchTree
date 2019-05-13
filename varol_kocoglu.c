//Varol Koçoðlu 150116045
#include <stdio.h>
#include <stdlib.h>

struct ter_tree { //creating ternary tree structure
		int data;
		struct ter_tree * right , * mid , * left ;
};
typedef struct ter_tree  node;

int maxval(node* nodec ) // for finding max value
{
		if (nodec->right != NULL)
		{
			while(nodec->right != NULL)
			nodec = nodec->right;
		}
	
		if(nodec->right == NULL && nodec->mid != NULL)
		{
			nodec = nodec->mid;
			maxval(nodec);
		}
		
		else
			return nodec->data;

}

int minval(node *nodec) // for finding min value
{ 
		while(nodec->left != NULL)
			nodec = nodec->left;
		return nodec->data;
}

void insert (node ** tree, int val){ // inserting function
		node *temp = NULL;
		if(!(*tree)){		// when there is no node in tree
			temp = (node *)malloc(sizeof(node));
			temp->left = temp->mid = temp->right = NULL;
			temp->data = val;
			*tree = temp;
			return ;
		}
		
		if(val > (*tree)->data *(*tree)->data ) // when value grather than  square of node's data 
		{
			insert(&(*tree)->right,val);
			return;
		}
		else if(val > (*tree)->data) // when value grather than node's data
		{
			insert(&(*tree)->mid,val);
			return;
		}
		else if(val == (*tree)->data)//when value equals to  node's data
		{
			return;
		}
		else if(val < (*tree)->data)//when value less than  node's data
		{
			insert(&(*tree)->left,val);	
		}	
}


void search(node **tree, int val , int *depthlvl) //for searching any number in tree
{	
		if(!(*tree)) //there is no value in tree
		{
			return ;
		}
		
		if(val > ((*tree)->data * (*tree)->data) &&	(*tree)->right != NULL)//when value grather than  square of node's data 
		{	perror("right\n");
			*depthlvl+=1;
			search(&(*tree)->right, val , &*depthlvl);//pointer goes to right
		}
		else if(val > (*tree)->data && (*tree)->mid != NULL)// when value grather than node's data
		{	perror("mid\n");
			*depthlvl+=1;
			search(&(*tree)->mid, val , &*depthlvl);//pointer goes to mid
		}
		else if(val < (*tree)->data && (*tree)->left != NULL)//when value less than  node's data
		{	perror("left\n");
			*depthlvl+=1;
			search(&(*tree)->left, val , &*depthlvl);//pointer goes to left
		}
		else if(val == (*tree)->data)//when value equals to  node's data printing
		{	
			printf("find '%d' in tree and  data's depth level is %d \n ",(*tree)->data , *depthlvl);
		}
		else 
		{	
			printf("%d not found",val);
		}
}


void print_preorder(node * tree)//printing to all of nodes in tree
{
	
	    if (tree)
	    {
	        printf("%d\n",tree->data);
	       // perror("1");
	        print_preorder(tree->left);
	       // perror("2");
			print_preorder(tree->mid);
		   //perror("3");
			print_preorder(tree->right);
	    	//perror("4");
	    	
	    	
		}
}
node* delete (node * tree, int val)//deleting and removing operation occurring in this function
{
		if(tree == NULL)//if there is no node in tree
		{	printf("Value not found\n");
			return NULL ;
		}
		
		
		else if(val == tree->data)//when value equals to  node's data	
		{
			
				if(tree->left==NULL && tree->mid==NULL && tree->right==NULL)//if there is no node
				{perror("1");
				
					return NULL;
				 		
				}
				
				else if(tree->left != NULL  && tree->mid == NULL && tree->right == NULL)//if there is only left node
				{perror("2");
					tree->data = maxval(tree->left);
					tree->left = delete(tree->left,maxval(tree->left));
					return tree; 			
				}
				
				else if(tree->mid != NULL  && tree->left == NULL && tree->right == NULL)//if there is only mid node
				{perror("3");
					tree->data = minval(tree->mid);
					tree->mid = delete(tree->mid,minval(tree->mid));
					return tree; 
				}
				
				else if(tree->right != NULL  && tree->left == NULL && tree->mid == NULL)//if there is only right node
				{perror("4");
					tree->data = minval(tree->right);
					tree->right = delete(tree->right,minval(tree->right));
					return tree; 
				}
				
				else if(tree->right == NULL  && tree->left != NULL && tree->mid != NULL)//if there no right node
				{perror("5");
					if(maxval(tree->left)*maxval(tree->left) > minval(tree->mid) )
					{
					tree->data = maxval(tree->left);
					tree->left = delete(tree->left,maxval(tree->left));
					return tree; 
					}
					else if(maxval(tree->left)*maxval(tree->left) <= minval(tree->mid))
					{perror("mert");
					tree->data = minval(tree->mid);
					tree->mid = delete(tree->mid,minval(tree->mid));
					return tree;
					}  
		  }
				
				else if(tree->mid == NULL  && tree->left != NULL && tree->right != NULL)//if there is no mid node
				{perror("6");
					tree->data = maxval(tree->left);
					tree->left = delete(tree->left,maxval(tree->left));
					return tree; 
				}
				
				else if(tree->left == NULL  && tree->mid != NULL && tree->right != NULL)//if there is no left node
				{perror("7");
					
					if(minval(tree->mid) * minval(tree->mid) < minval(tree->right))
					{
					tree->data = minval(tree->mid);
					tree->mid = delete(tree->mid,minval(tree->mid));
					return tree;
					}
					else if(minval(tree->mid) * minval(tree->mid) >= minval(tree->right))
					{
					tree->data = minval(tree->mid);
					tree->mid = delete(tree->mid,minval(tree->mid));
					insert(&tree,minval(tree->right));
					tree->right = delete (tree->right,minval(tree->right));
					return tree;
					}
				}
				
				else if(tree->right != NULL  && tree->left != NULL && tree->mid != NULL)//if there are all nodes
				{perror("8");
				
					if(maxval(tree->left)*maxval(tree->left) >= tree->mid->data)
					{
					tree->data = maxval(tree->left);
					tree->left = delete(tree->left,maxval(tree->left));
					return tree;
					}
					else if(maxval(tree->left)*maxval(tree->left) < tree->mid->data)
					{
					tree->data = maxval(tree->left);
					tree->left = delete(tree->left,maxval(tree->left));
					
					tree->mid = delete(tree->mid,minval(tree->mid));
					insert(&tree,minval(tree->right));
					return tree;
					}
					else
					{
					tree->data = minval(tree->left);
					tree->left = delete(tree->left,maxval(tree->left));
					return tree;
					}
					
				}
				
		}
		
		
		
		else if(val > tree->data * tree->data)//when value grather than  square of node's data 
		{
			
			tree->right = delete(tree->right,val);
			return tree;
		}
		
		else if(val > tree->data)// when value grather than node's data
		{
			tree->mid = delete(tree->mid,val);
			return tree;
		}
		
		else if(val < tree->data)//when value less than  node's data
		{
			tree->left=delete(tree->left,val);
			return tree;
		}
		
		else
		{
			printf("Error :(");
		}
			
}
 

int main()
{
	//reading the text file
	node *root;	
    int i;
    root = NULL;
    FILE *file ;
    file = fopen("C:/Users/varol/OneDrive/Masaüstü/Data Project 2/text/input.txt", "r");
    while(!feof(file))
    {
	    	fscanf(file,"%d", &i );
	    	insert(&root,i);// inserting
	}
   
   
   int z = -1;
   
  
	while(z!=0)
	{
	printf("\nSelect your operation\nFinish the program = 0\nPrinting the preorder = 1\nSearching = 2\nDeleting = 3\n");
   scanf("%d",&z);
   
   if(z==1)
   {
	//Printing nodes of tree
    printf("Pre Order Display\n");
    print_preorder(root);
	}
	
	if(z==2)
	{
	int v=0;	
	printf("Select your number\n");
   	scanf("%d",&v);
	int depthlvl= 0; 
	search(&root,v,&depthlvl);//searching
	}
			
	if(z==3)
	{
	int v=0;	
	printf("Select your number\n");
   	scanf("%d",&v);
	delete(root,v);//deleting
	}
}
	return;
}
