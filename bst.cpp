#include<iostream>
#include<queue>         // used for level ordering
using namespace std;

class node
{
	public:
	int data;
	node* left;
	node* right;	
};
node* root=NULL;

node* insert(node* root,int data);
void levelorder(node* root);
void preorder(node *root);
void inorder(node* root);
void postorder(node *root);
int search(node* root,int data);
void findmin(node* root);
void findmax(node* root);
node* Findmin(node* root);
node* Delete(node* root,int data);
int treeheight(node* root);

//////  (1) inserting elements into the tree////////////
node* insert(node* root,int data)
{
	node* newnode=new node();
	newnode->data=data;
	newnode->left=newnode->right=NULL;
	if(root==NULL)
		root=newnode;
	else if(data<=root->data)
		root->left=insert(root->left,data);
	else
		root->right=insert(root->right,data);
	
	return root;
}

/////////  (2)  print level order of the tree/////////
void levelorder(node* root)
{
	if(root==NULL)
		return;
	queue <node*> q; // defining a queue as a queue
	q.push(root);// pushing the address on to the queue
	while(!q.empty())
	{
		node* current=q.front(); // returns the address of current element
		cout<<current->data<<" ";
		if(current->left!=NULL)
			q.push(current->left);
		if(current->right!=NULL)
			q.push(current->right);
		q.pop();
	}
}

/////////  (3) pre order printing of tree ie( /_  )
void preorder(node* root)
{
	if(root==NULL)
		return;
	cout<<root->data<<" ";
	preorder(root->left);
	preorder(root->right);
}

///////// (4)  inorder printing or tree its also ascending order ie(  /\  )
void inorder(node* root)
{
	if(root==NULL)
		return;
	inorder(root->left);
	cout<<root->data<<" ";
	inorder(root->right);
}

////////// (5) post order printing of values ie (  _\ )
void postorder(node* root)
{
	if(root==NULL)
		return;
	postorder(root->left);
	postorder(root->right);
	cout<<root->data<<" ";
	
}

//////////// (6) search if  element is present or not
int search(node* root,int data)
{
	if(root==NULL)
		return 0;
	if(data==root->data)
		return 1;
	else if(data<root->data)
		return search(root->left,data);
	else if(data>root->data)
		return search(root->right,data);
	else
	return 0;
}

//////////  (7) find minimum value of the tree
void findmin(node* root)
{
	if(root==NULL)
		return;
	while(root->left!=NULL)
		root=root->left;
	cout<<"\nminimum value of tree is\n"<<root->data<<endl;
		
}

/////////// (8) to find maximum value of the tree
void findmax(node* root)
{
	if(root==NULL)
		return;
	while(root->right!=NULL)
		root=root->right;
	cout<<"\nmaximum value of the tree is\n"<<root->data<<endl;
}

//////////  (9) to find minimum value and return its address used in height calculation
node* Findmin(node* root)
{
	if(root==NULL)
		return root;
	while(root->left!=NULL)
		root=root->left;
	return root;
}

////////  (10)  delete the node
node* Delete(node* root,int data) /// returns pointer to the root node//////// imp
{
	if(root==NULL)
		return root;
	else if(data<root->data)
		root->left=Delete(root->left,data);
	else if(data>root->data)
		root->right=Delete(root->right,data);
	else
	{
		//case 1 : no child
		if(root->left==NULL && root->right==NULL)
		{
			delete root;// deallocate  the node from heap memory in c it is free function
			root=NULL;// root still has the address so reasssign it
			return root;
		}
		//case 2 : 1 child 
		else if(root->left==NULL)
		{
			node* t=root;
			root=root->right;
			delete t;
			return root;
		}
		else if(root->right==NULL)
		{
			node* t= root;
			root=root->left;
			delete t;
			return root;
		}
		//case 3 : 2 childs
		else
		{
			node* t=Findmin(root->right); //////min of right or else maximum of left can be implied
			root->data=t->data; /// set the current root to min value of right node
			root->right=Delete(root->right,t->data);
		}
	}
	
	
}

////////  (11) to print the height the tree
int treeheight(node* root)
{
	
	if(root==NULL)
		return -1;
	int left_height=treeheight(root->left);
	int right_height=treeheight(root->right);
	return max(left_height,right_height)+1;
	
}

int main()
{
	root=insert(root,15);
	root=insert(root,10);
	root=insert(root,5 );
	root=insert(root,12);
	root=insert(root,20);
	root=insert(root,17);
	root=insert(root,25);
	root=insert(root,26);
	root=insert(root,100);
	root=insert(root,15);
	cout<<"level order\n";
	levelorder(root);
	cout<<"\npreorder\n";
	preorder(root);
	cout<<"\ninorder\n";
	inorder(root);
	int y;
	cout<<"\nenter the value to be deleted\n";
	cin>>y;
	root=Delete(root,y);
	cout<<"\npostorder\n";
	postorder(root);
	cout<<"\nenter the value to be searched\n";
	int x;
	cin>>x;
	if(search(root,x)==1)
		cout<<"found\n";
	else
		cout<<"not found\n";
	findmin(root);
	findmax(root);
	cout<<"\nheight of the tree\n";
	cout<<treeheight(root);
	return 0;
}
