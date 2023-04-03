#include <iostream>
#include "ArgumentManager.h"
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;


struct Node
{
  Node*next;
  string data;
  int priority;
};

class Queue
{
  private:
  Node* front;
  Node* rear;

  public:

  Queue()
{
  front = nullptr;
  rear = nullptr;
}

  bool isEmpty()
{
  return front ==nullptr;
}

  Node* getFront()
{
  if(!isEmpty())
  return front;
  else
  return nullptr;
}

  void enqueue(string x)
{
  Node* temp = new Node();
  temp ->data = x;
  
  if(isEmpty())
  {
    front = temp;
    rear = temp;
  }

  else
  {
    rear ->next = temp;
    rear = temp;
  }
}

  void dequeue()
{
  if(!isEmpty())
  {
  Node* cu = front;
  front = front->next;
  delete cu;
  }
}

  void print()
{
  Node* cu = front;
  while(cu != nullptr)
    {
      cout << cu ->data << endl;
      cu = cu->next;
    }    
}


};



class PQueue
{
  private:
  Node* front;
  Node* rear;

  public:

  PQueue()
{
  front = nullptr;
  rear = nullptr;
}

bool isEmpty()
{
  return front == nullptr;
}

Node* getFront()
{
  if(!isEmpty())
  return front;
  else
  return nullptr;
}

void dequeue()
{
  if(!isEmpty())
  {
  Node* cu = front;
  front = front->next;
  delete cu;
  }
}


void enqueue(string x, int p)
 {
  Node*temp = new Node();
  Node*cu = front;
  Node*prev = nullptr;
  temp->data = x;
  temp->priority = p;

  if(isEmpty())
  {
    front = temp;
    //rear = temp;
    return;
  }

    if(temp->priority < cu->priority)
    {
      temp->next = front;
      front = temp;
      return;
    }
   
     while(cu != nullptr && temp->priority >= cu->priority)
       {
         prev = cu;
         cu = cu ->next;
       }
    
     prev -> next = temp;
     temp ->next = cu;

  }


void print()
{
  Node* cu = front;
  while(cu != nullptr)
    {
      cout << cu ->data << endl;
      cu = cu->next;
    }    
}


};

struct TNode
{
  string data;
  TNode*left;
  TNode*right;

  TNode(string x) //Constructor
{
  data =x;
  left = nullptr;
  right = nullptr;
}
};

class BST
{
  private:
  TNode* root;
  public:

  BST()
{
  root = nullptr;
}

TNode* getRoot()
{
  return root;
}

void add(string x)
{
  root = insert(root,x);
}

TNode* insert(TNode*n, string x)
{
  if(n == nullptr)
    n = new TNode(x);
    
  else if(x.length() > n->data.length())
    n->right = insert(n->right, x);
    
  else if(x.length() < n->data.length())
    n->left = insert(n->left, x);
  else if (x.length() == n->data.length())
      n->data = x;
  return n;
}


void inorder(TNode *n, ofstream &output)
{
  if(n == nullptr)
  return;
  inorder(n->left, output);
  output << n->data << endl;
  inorder(n->right, output);
}


void preorder(TNode *n, ofstream &output)
{
  if(n == nullptr)
  return;
  output << n->data << endl;
  preorder(n->left, output);
  preorder(n->right, output);
}

  void postorder(TNode *n, ofstream &output)
{
  if(n == nullptr)
  return;
  postorder(n->left, output);
  postorder(n->right, output);
  output << n->data << endl;
}
  


};

int main(int argc, char *argv[]) {
  ArgumentManager am(argc, argv);
  string input(am.get("input"));
  string output(am.get("output"));

  //ifstream in(input);
 // ofstream out(output);
  ifstream in("input4.txt");
  ofstream out("output4.txt");
  
  PQueue commands;
  Queue messages;
  BST t;
  int pri;
  string prio;
  string line;
  string order;
  
   while(getline(in,line))
    {
      line.erase(remove(line.begin(), line.end(), '\n'), line.end());
      line.erase(remove(line.begin(), line.end(), '\r'), line.end());
      
      //if(line.find("DECODE:") != -1)
        if(!line.find("DECODE:"))
        {
          prio = line.substr(line.find("(")+1,1);
          pri = stoi(prio);
          string c;
          c = line.substr(0,line.length()-3);
          commands.enqueue(c,pri);
        }
      
      
      if(!line.find("REPLACE:") || !line.find("SWAP:") || !line.find("ADD:") || !line.find("REMOVE:"))
      {
      prio = line.substr(line.find("(")+1,1);
      pri = stoi(prio);
      string c;
      c = line.substr(0,line.length()-3);
      commands.enqueue(c, pri);
      }

      if(!line.find("BST:"))
      {
        prio = line.substr(line.find("(")+1,1);
        pri = stoi(prio);
        commands.enqueue(line.substr(0,3), pri);
      }

      if(!line.find("Inorder") || !line.find("Preorder") || !line.find("Postorder"))
      {
        //commands.enqueue(line, 99);
        order = line;
      }
      
    }
  
  while(!commands.isEmpty()){
    if(commands.getFront()->data.substr(0,7) == "DECODE:")
      {
        string m;
        m = commands.getFront()->data.substr(8, commands.getFront()->data.length() - 9);
        messages.enqueue(m);
        commands.dequeue();
      }
      
    else if(commands.getFront()->data.substr(0,7) == "REMOVE:")///////
      {
        string m = commands.getFront()->data;
        string one = m.substr(8,1);
        
        
        if(!messages.isEmpty())
        {
          string m =messages.getFront()->data;
          
          m.erase(remove(m.begin(), m.end(), one.at(0)), m.end());
          messages.dequeue();
          messages.enqueue(m);
        }
        
          commands.dequeue();
      }
      
    else if(commands.getFront()->data.substr(0,8) == "REPLACE:")
      {
        
        string first = commands.getFront()->data.substr(9,1);
        string second = commands.getFront()->data.substr(11,1);
       
        if(!messages.isEmpty())
        {
          string m =messages.getFront()->data;
          replace(m.begin(), m.end(), first.at(0), second.at(0));
          messages.dequeue();
          messages.enqueue(m);
        }
        
          commands.dequeue();
      }

      
    else if(commands.getFront()->data.substr(0,4) == "ADD:")
    {
      string addAfterThis = commands.getFront()->data.substr(commands.getFront()->data.find('[')+1, 1);
      string c = commands.getFront()->data.substr(commands.getFront()->data.find('[')+3, 1);
      if(messages.getFront() != NULL){
        string m = messages.getFront()->data;
        for(int i=0; i<m.size(); i++){
          if(m.at(i) == addAfterThis.at(0))
            m.insert(i+1, c);
        }
        
        messages.dequeue();
        messages.enqueue(m);
      }
      commands.dequeue();
    }

      
    else if(commands.getFront()->data.substr(0,5) == "SWAP:")///////
    {
     string m = commands.getFront()->data;
     string one = m.substr(6,1);
     string two = m.substr(8,1);
      
      if(!messages.isEmpty())
      {
        string message = messages.getFront()->data;
        for(int i = 0; i<message.size(); i++){
          if(message.at(i) == one.at(0))
            message.at(i) = two.at(0);
          else if(message.at(i) == two.at(0))
            message.at(i) = one.at(0);
        }
        messages.dequeue();
        messages.enqueue(message);
      }
      commands.dequeue();
    }

      
   else if(commands.getFront()->data.substr(0, commands.getFront()->data.find(':')) == "BST")
   {
      if(!messages.isEmpty())
      {
        t.add(messages.getFront()->data);
        messages.dequeue();
      }
      commands.dequeue();
    }
  

    
  }
  if(order == "Inorder")
      {
        t.inorder(t.getRoot(), out);
      }

      else if(order == "Preorder")
      {
        t.preorder(t.getRoot(), out);
      }

     else if(order == "Postorder")
      {
        t.postorder(t.getRoot(), out);
      }

/*
cout << "Last" << endl;
commands.print();
message.print();
*/
}