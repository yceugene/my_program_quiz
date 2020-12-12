/* binary tree */
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
/*
typedef enum
{
    FALSE,
    TRUE,
} BOOL;

typedef enum
{
	frOK,
  frQuit,
	frError,
	frSyntaxError,
	frFileOpenError,
	frINVALID,
} eFUNCTIONRETURN;

typedef struct tagNODE {
  struct tagNODE* left;
  struct tagNODE* right;
  int data;
} sNODE, *psNODE;
*/
void traversal_preorder(psNODE p)
{
  if(!p) return;
  printf("%d,",p->data);
  traversal_preorder(p->left);
  traversal_preorder(p->right);
}

void traversal_inorder(psNODE p)
{
  if(!p) return;
  traversal_inorder(p->left);
  printf("%d,",p->data);
  traversal_inorder(p->right);
}

void traversal_postorder(psNODE p)
{
  if(!p) return;
  traversal_postorder(p->left);
  traversal_postorder(p->right);
  printf("%d,",p->data);
}

// struct sNODE* CreateNode(int* pData)
// {
//   // eFUNCTIONRETURN eRet = frError;
//   struct sNODE* root, pNode = NULL;
//   if(!pData) return root;
//   while(pDAta)
//   {
//     pNode = new Node(pData*);
//     if(!root) root = pNode;
//     pData++;
//     if(!pData) return frOK;
//     psNode = l
//
//   }
// }

eFUNCTIONRETURN eConsole(void)
{
  eFUNCTIONRETURN eRet = frOK;
  char cInput[10];
  // if(fgets(cInput, ))
  return eRet;
}

int main()
{
  // int iArray = {0,1,2,3,4,5,6,7,8,9};
  psNODE psROOT = malloc(sizeof(sNODE));
  psNODE psNode = psROOT;

  printf("\n hello!\n\n");

}
