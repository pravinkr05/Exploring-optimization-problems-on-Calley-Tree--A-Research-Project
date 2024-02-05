#include <bits/stdc++.h>
using namespace std;

int bitSize;

class Node
{
public:
  int state;
    vector < int >memory;

  int flag[4];
  int data;
  int counter;
  Node *left;
  Node *middle;
  Node *right;


    Node (int data)
  {

	for (int i = 0; i < 4; i++)
	  this->flag[i] = 0;

	this->data = data;
	this->memory = decTobin (data, bitSize);
	this->state = 0;
	this->counter = 0;
	this->left = NULL;
	this->right = NULL;
	this->middle = NULL;

  }

  vector < int >decTobin (int data, int bitSize)
  {
	int ans = data;
	vector < int >temp (bitSize, 0);
	for (int i = 0; i < bitSize; i++)
	  {
		int bit = ans % 2;
		ans = ans / 2;
		temp[bitSize - 1 - i] = bit;
	  }
	return temp;

  }



};

class cayleyTree
{
public:
  vector < Node * >nodeStorage;
  Node *root;
    cayleyTree ()
  {
	root = new Node (0);
  }


  void buildTree (vector < int >seq)
  {								//tree initialization
	queue < Node * >q;
	q.push (root);
	int isRootMid = 1;
	int i = 0;
	while (!q.empty ())
	  {
		Node *temp = q.front ();
		q.pop ();

		if (i < seq.size ())
		  {
			temp->left = new Node (seq[i]);
			q.push (temp->left);
			i++;
		  }

		if (i < seq.size ())
		  {
			temp->right = new Node (seq[i]);
			q.push (temp->right);
			i++;
		  }

		if (isRootMid)
		  {
			temp->middle = new Node (seq[i]);
			q.push (temp->middle);
			isRootMid = 0;
			i++;
		  }
	  }


  }

  void levelOrder ()
  {
	queue < Node * >q;
	q.push (root);
	q.push (NULL);

	nodeStorage.push_back (root);
	nodeStorage.push_back (NULL);

	while (!q.empty ())
	  {
		Node *temp = q.front ();
		q.pop ();
		if (temp == NULL)
		  {
			cout << endl << endl;
			if (!q.empty ())
			  {
				q.push (NULL);
				nodeStorage.push_back (NULL);
			  }
		  }
		else
		  {
			cout << "{M:";
			printArray (temp->memory);
			cout << ",F:" << temp->flag[0] << temp->flag[1] << temp->
			  flag[2] << ",U:" << temp->flag[3] << ",S:" << temp->
			  state << ",C:" << temp->counter << "}  ";
			if (temp->left)
			  {
				q.push (temp->left);
				nodeStorage.push_back (temp->left);
			  }
			if (temp->right)
			  {
				q.push (temp->right);
				nodeStorage.push_back (temp->right);
			  }
			if (temp->middle)
			  {
				q.push (temp->middle);
				nodeStorage.push_back (temp->middle);
			  }
		  }
	  }

  }

  void printArray (vector < int >v)
  {

	for (int i = 0; i < v.size (); i++)
	  {
		cout << v[i];
	  }


  }


  void fun (Node * root, int l, int s, int r)
  {


	if (l == 1 && r == 1 && s == 1)
	  {
		root->state = 1;
		return;
	  }


	if ((l == 1 && r == 1 && root->flag[2])
		|| (r == 1 && s == 1 && root->flag[0]) || (s == 1 && l == 1
												   && root->flag[1]))
	  {							//2 0S AND flag true
		root->state = 1;
		return;
	  }

	if ((l == 1 && root->flag[1] && root->flag[2])
		|| (r == 1 && root->flag[0] && root->flag[2]) || (s == 1
														  && root->flag[0]
														  && root->flag[1]))
	  {
		root->state = 1;
		return;
	  }

	if (l == 1 && !root->flag[0])
	  {
		root->flag[0] = 1;
	  }
	if (r == 1 && !root->flag[1])
	  {
		root->flag[1] = 1;
	  }
	if (s == 1 && !root->flag[2])
	  {
		root->flag[2] = 1;
	  }



	if (root->flag[0] == 0)
	  {
		root->state = l;
	  }
	if (root->flag[1] == 0)
	  {
		root->state = r;
	  }
	if (root->flag[2] == 0)
	  {
		root->state = s;
	  }



  }


  void copyNode (Node * originalNode, Node * copiedNode)
  {
	copiedNode->state = originalNode->state;
	for (int i = 0; i < bitSize; i++)
	  {
		copiedNode->memory[i] = originalNode->memory[i];
	  }
	copiedNode->flag[0] = originalNode->flag[0];
	copiedNode->flag[1] = originalNode->flag[1];
	copiedNode->flag[2] = originalNode->flag[2];
	copiedNode->flag[3] = originalNode->flag[3];
	copiedNode->counter = originalNode->counter;

  }

  void storeOrder (Node * root, vector < Node * >&v)
  {
	queue < Node * >q;
	q.push (root);
	q.push (NULL);
	v.push_back (root);
	v.push_back (NULL);


	while (!q.empty ())
	  {

		Node *temp = q.front ();
		q.pop ();

		if (temp == NULL)
		  {
			if (!q.empty ())
			  {
				q.push (NULL);
				v.push_back (NULL);

			  }
		  }
		else
		  {

			if (temp->left)
			  {
				q.push (temp->left);
				v.push_back (temp->left);
			  }
			if (temp->right)
			  {
				q.push (temp->right);
				v.push_back (temp->right);
			  }
			if (temp->middle)
			  {
				q.push (temp->middle);
				v.push_back (temp->middle);

			  }
		  }
	  }

  }

  Node *copyTreeWithoutRecursion (Node * originalRoot)
  {

	queue < Node * >originalQueue;
	queue < Node * >copiedQueue;

	Node *newRoot = new Node (originalRoot->data);
	copyNode (originalRoot, newRoot);

	originalQueue.push (originalRoot);
	copiedQueue.push (newRoot);

	while (!originalQueue.empty () && !copiedQueue.empty ())
	  {
		Node *originalNode = originalQueue.front ();
		Node *copiedNode = copiedQueue.front ();

		originalQueue.pop ();
		copiedQueue.pop ();

		// Copy left child
		if (originalNode->left != nullptr)
		  {
			originalQueue.push (originalNode->left);
			copiedNode->left = new Node (originalNode->left->data);

			copyNode (originalNode->left, copiedNode->left);
			copiedQueue.push (copiedNode->left);
		  }

		// Copy right child
		if (originalNode->right != nullptr)
		  {
			originalQueue.push (originalNode->right);
			copiedNode->right = new Node (originalNode->right->data);
			copyNode (originalNode->right, copiedNode->right);
			copiedQueue.push (copiedNode->right);
		  }

		// Copy middle child
		if (originalNode->middle != nullptr)
		  {
			originalQueue.push (originalNode->middle);
			copiedNode->middle = new Node (originalNode->middle->data);
			copyNode (originalNode->middle, copiedNode->middle);
			copiedQueue.push (copiedNode->middle);
		  }
	  }

	return newRoot;
  }


  void parallelComputation (int height)
  {
	vector < Node * >originalNode;
	storeOrder (root, originalNode);

	int n = originalNode.size ();

	int clock = 0;
	while (true)
	  {

		vector < Node * >tempNode;
		Node *temp = copyTreeWithoutRecursion (root);
		storeOrder (temp, tempNode);

		cout <<
		  "-------------------------------------------------------------"
		  << endl;
		cout << "Iteration(clock pulse) : " << clock << endl;
		for (int p = 0; p < n - 1; p++)
		  {

			Node *curr = originalNode[p];
			Node *copy = tempNode[p];
			if (curr != NULL)
			  {
				int ind = copy->counter;

				if (curr->left == NULL && curr->right == NULL)
				  {
					cout << "leaf node is executed" << endl;

					if (ind < bitSize)
					  {
						
						if(curr->flag[3]==0){
						   curr->flag[3] = 1; 
						   curr->state = curr->flag[3];
						}
                        else{
                            int m = copy->memory[ind];
    						curr->flag[0] = 1;
    						curr->flag[1] = 1;
    						curr->flag[2] = 0;
    						fun (curr, 0, m, 0);
    						curr->counter = ind + 1;
                        }
                        
					  }



				  }

				if (curr->left != NULL && curr->right != NULL
					&& curr->middle == NULL)
				  {
					cout << "intermediate node is executed" << endl;

					if (ind < bitSize)
					  {
					      
						int l = copy->left->state;
						int r = copy->right->state;
						
						if(copy->flag[3]==0){
						    if(l && r)
						  { 
						   curr->flag[3] = 1;
						   curr->state = 1;; 
						  }
						}
						else
						  {
						     
						    curr->state = curr->memory[ind];
						    int m = curr->state;
							fun (curr, l, m, r);
							curr->counter = ind + 1;
						  }
					  }
				  }

				if (curr->left != NULL && curr->right != NULL
					&& curr->middle != NULL)
				  {

					cout << "root node is exucuted" << endl;
					if (ind < bitSize)
					  {
						int l = copy->left->state;
						int r = copy->right->state;
						int m = copy->middle->state;
					
						if(copy->flag[3]==0){
						   if(l&&r&&m)
						   {
						   curr->flag[3] = 1;
						   curr->state = curr->flag[3]; 
						       
						   }
						}
                       else
						  {
						     
							fun (curr, l, m, r);
							curr->memory[ind] = curr->state;
							curr->counter = ind + 1;
						  }
					  }
				  }
			  }
		  }
        cout<<endl;
		levelOrder ();
		clock++;
		if (root->counter == bitSize)
		  break;
	  }
	cout << "-------------------------------------------------------------" <<
	  endl;
	cout << "Searching Executed Successfully..." << endl << endl;

  }		
  
};


int
main ()
{

 
  int height = 3;
   bitSize = 4;
   int totalNodes = 3*pow(2,height-1)-2;
   cout<<"Height of the Tree: "<<height<<endl;
   cout<<"Total Nodes: "<<totalNodes<<endl; 
   cout<<"Memory bitSize: "<<bitSize<<endl;

  int a = 1;
  int b=16;

   vector<int> seq;

   for(int i=1;i<totalNodes;i++){
     int temp = rand() % (b-a) + a;
     seq.push_back(temp);
   }




//   vector < int >seq = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,14,9,10,11,12,13,14};   //bit size = 4
//   vector < int >seq = { 11, 12, 14, 8, 3, 6, 12, 0, 7 };
 


  random_device rd;
  default_random_engine rng (rd ());
  shuffle (seq.begin (), seq.end (), rng);


  cout << endl<< "sequence value : ";

  int w = INT_MAX;
  for (int i = 0; i < seq.size (); i++)
	{
	  w = min(w, seq[i]);
	  cout<<seq[i]<<" ";
	}
  cout <<"\nMin Value: "<< w;

	
  cayleyTree T;

  T.buildTree (seq);

  cout << "\nInitial State: " << endl;
  T.levelOrder ();
  cout << endl;

  T.parallelComputation (height);

  cout << "Final State: " << endl;
  T.levelOrder ();

  
  return 0;

}



