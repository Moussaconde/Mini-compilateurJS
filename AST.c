#include <stdio.h>
#include <stdlib.h>
#include "AST.h"

/* create an AST from a root value and two AST sons */
AST_expr new_binary_expr(char rule, AST_expr left, AST_expr right) {
  AST_expr t=(struct _expr_tree*) malloc(sizeof(struct _expr_tree));
  if (t!=NULL){	/* malloc ok */
    t->rule=rule;
    t->left=left;
    t->right=right;
  } else printf("ERR : MALLOC ");
  return t;
}

/* create an AST from a root value and one AST son */
AST_expr new_unary_expr(char rule, AST_expr son)
{
  return new_binary_expr(rule, NULL,son);
}

/* create an AST leaf from a value */
AST_expr new_number_expr(double number)
{
  AST_expr t=(struct _expr_tree*) malloc(sizeof(struct _expr_tree));
  if (t!=NULL){	/* malloc ok */
    t->rule='N';
    t->number=number;
    t->left=NULL;
    t->right=NULL;
  } else printf("ERR : MALLOC ");
  return t;
}

/* create an AST leaf from a value */
AST_comm new_command(AST_expr expression){
  AST_comm t =  malloc(sizeof(struct _command_tree));
  if (t!=NULL){	/* malloc ok */
    t->expr1 = expression;
  } else printf("ERR : MALLOC ");
  return t;

}

/* delete an AST */
void free_expr(AST_expr t)
{
  if (t!=NULL) {
    free_expr(t->left);
    free_expr(t->right);
    free(t);
  }
}
void free_comm(AST_comm t)
{
  if (t!=NULL) {
    free_expr(t->expr1);
    free(t);
  }
}

/* infix print an AST*/
void print_expr(AST_expr t){
  if (t!=NULL) {
    printf("[ ");
    print_expr(t->left);
    if (t->left==NULL) printf(":%f: ",t->number); else printf(":%c: ",t->rule);
    print_expr(t->right);
    printf("] ");
  }
}

/*Post_fix print an AST*/
void post_fix(AST_expr t) {
    if (t == NULL) return;

    post_fix(t->left);
    post_fix(t->right);

    switch (t->rule) {
        case '+':
            printf("AddiNb\n");
            break;
        case '-':
            printf("SubiNb\n");
            break;
        case '*':
            printf("MultNb\n");
            break;
        case 'M':
            printf("NegaNb\n");
            break;
	default:
	    printf("CsteNb %d\n", t->number);
	    break;
    }
}

void print_comm(AST_comm t){
  if (t!=NULL) {
    //printf("[ ");
   // printf(":%c: ",t->rule);
    post_fix(t->expr1);
    //printf("] ");
  }

}
