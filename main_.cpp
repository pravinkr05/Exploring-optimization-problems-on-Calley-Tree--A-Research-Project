#include <bits/stdc++.h>
using namespace std;

int bitSize=4;

class Node{
    public:
    int state;
    vector<int> memory;
   
    int flag[3];
    int data;
    Node* left;
    Node* middle;
    Node* right;
  
    
    Node(int data){
       
        for(int i=0;i<3;i++)this->flag[i]=0;
        this->data=data;
        this->memory=decTobin(data, bitSize);  
        this->state=0; 
        this->left=NULL;
        this->right=NULL;
        this->middle=NULL;
        
    }
   
    vector<int> decTobin(int data, int bitSize){ 
        int ans=data;
        vector<int> temp(bitSize,0);
        for(int i=0;i<bitSize;i++){
            int bit=ans%2;
            ans=ans/2;
            temp[bitSize -1 - i]=bit;
        }
        return temp;
        
    }

    
    
};

class cayleyTree{
    public:
    vector<Node*> nodeStorage;
    Node* root;
    cayleyTree(){
        root=new Node(0);
    }
  
  
  void buildTree (vector<int> seq){ //tree initialization
    queue <Node*> q;
    q.push (root);
    int isRootMid=1;
    int i=0;
    while (!q.empty())
      {
      	Node *temp = q.front ();
    	q.pop ();
	
	    if(i<seq.size()){
	    temp->left = new Node (seq[i]);
	    q.push (temp->left);
	    i++;
	    }
	    
	    if(i<seq.size()){
	    temp->right = new Node (seq[i]);
	    q.push (temp->right);
	    i++;
	    }
	   
    	if (isRootMid)
    	  {
    	    temp->middle = new Node (seq[i]);
    	    q.push (temp->middle);
    	    isRootMid =0;
    	    i++;
    	  }
      }
  

  }
  
  void levelOrder (){
    queue < Node * >q;
    q.push (root);
    q.push (NULL);
    
    nodeStorage.push_back(root);
    nodeStorage.push_back(NULL);
    
    while (!q.empty ())
      {
	Node *temp = q.front ();
	q.pop ();
	if (temp == NULL)
	  {
	    cout << endl<<endl;
	    if (!q.empty ())
	      {
	       q.push (NULL);
	       nodeStorage.push_back(NULL);
	      }
	  }
	else
	  {
	    cout <<"{M:"; printArray(temp->memory);cout<<",F:"<<temp->flag[0]<<temp->flag[1]<<temp->flag[2]<<",S:"<<temp->state<< "}  ";
	    if (temp->left)
	      {
	      q.push (temp->left);
	      nodeStorage.push_back(temp->left);
	      }
	    if (temp->right)
	     { 
	      q.push (temp->right);
	      nodeStorage.push_back(temp->right);
	     }
	    if (temp->middle)
	     { 
	      q.push (temp->middle);
	      nodeStorage.push_back(temp->middle);
	     }
	  }
      }

  }
  
  void printArray(vector<int> v){
    
    for(int i=0;i<v.size();i++){
        cout<<v[i];
    }
    
   
}


  void funRoot(Node* root, int l, int m, int r, int j){
         if(l==0 && r==0 && m==0){
          root->state=0; 
          return;
      }
      
      if(l==1 && r==1 && m==1){
          root->state=1; 
     
      }
      
    if((l==0 && r==0 && root->flag[2]) || (r==0&&m==0&&root->flag[0]) || (m==0&&l==0&& root->flag[1])){ //2 0S AND flag true
          root->state=0; 
     
          return;
      }
      
      if((l==0 && root->flag[1]&&root->flag[2]) || (r==0 &&root->flag[0]&&root->flag[2]) || (m==0 && root->flag[0]&&root->flag[1])){
          root->state=0; 
     
          return;
      }
      
      if(l==0 && !root->flag[0]){
          root->flag[0] = 1;
      }
      if(r==0 && !root->flag[1]){
          root->flag[1] = 1;
      }
      if(m==0 && !root->flag[2]){
          root->flag[2] = 1;
      }
   
      
      
      if(root->flag[0]==0){
          root->state=l;
      }
      if(root->flag[1]==0){
          root->state=r;
      }
       if(root->flag[2]==0){
          root->state=m;
      }
      cout<<root->state;
      root->memory[j]=root->state;
      
      
  }
  
  void fun(Node* root, int l, int s, int r, int j){
      
      
      if(l==0 && r==0 && s==0){
          root->state=0; 
        //   root->flag[3]={1,1,1};
          return;
      }
      
      
      if((l==0 && r==0 && root->flag[2]) || (r==0&&s==0&&root->flag[0]) || (s==0&&l==0&& root->flag[1])){ //2 0S AND flag true
          root->state=0; 
 
          return;
      }
      
      if((l==0 && root->flag[1]&&root->flag[2]) || (r==0 &&root->flag[0]&&root->flag[2]) || (s==0 && root->flag[0]&&root->flag[1])){
          root->state=0; 
    
          return;
      }
      
      if(l==0 && !root->flag[0] ){
          root->flag[0] = 1;
      }
      if(r==0 && !root->flag[1]){
          root->flag[1] = 1;
      }
      if(s==0 && !root->flag[2]){
          root->flag[2] = 1;
      }
   
      
      
      if(root->flag[0]==0){
          root->state=l;
      }
      if(root->flag[1]==0){
          root->state=r;
      }
      
      
      
  }
  

  void inorder(Node* root, int i){
   
    if(root==NULL) return;
    if(i>bitSize) return;
    
    inorder(root->left,i);
    
    inorder(root->right,i);
   
    inorder(root->middle,i);
    
    
    if(root->left!=NULL && root->right!=NULL && root->middle!=NULL && i<bitSize)//layer=2=height
        {  
      cout<<"root node is exucuted"<<endl;
         int l = root->left->state;
         int r = root->right->state;
         int m = root->middle->state;
         
        
         funRoot(root,l,m,r,i);
         
        
        }
    
    if(root->left!=NULL && root->right!=NULL && root->middle==NULL  && i<bitSize)//i>=1
         { 
          cout<<"intermediate node is exucuted"<<endl; 
           root->state = root->memory[i];
           int l = root->left->state;
           int r = root->right->state;
           int m = root->state;
           
           fun(root,l,m,r,i);
           
         }
  
    if(root->left==NULL && root->right==NULL &&  i<bitSize)//i>=0
         {
             cout<<"leaf node is exucuted"<<endl;
             root->state = root->memory[i];
             root->flag[0]=1;
             root->flag[1]=1;
            
         }
          
          
}

  void searchOrder(){
 
    for(int i=0;i<bitSize;i++){
        
      cout<<"-------------------------------------------------------------"<<endl;
      cout<<"iteration : "<<i<<", memory index: "<<i<<endl;
    
      inorder(root,i);
     
      cout<<"\nCurrent State: "<<endl;
      levelOrder();
      cout<<endl;
      
    }
    

cout<<"-------------------------------------------------------------"<<endl;
cout<<"Searching Executed Successfully..."<<endl<<endl;

}


};

int main()
{
    //parallel
    vector<int> seq={5,1,6,1,1,1,11,8,9,5,1,6,1,1,1,1,8,9,12,13,12}; //bit size = 4
    
    cayleyTree T;
    T.buildTree(seq);
    
    cout<<"\nInitial State: "<<endl;
    T.levelOrder();
    cout<<endl;
    
    T.searchOrder();
    
    cout<<"Final State: "<<endl;
    T.levelOrder();
    
    return 0;
}





