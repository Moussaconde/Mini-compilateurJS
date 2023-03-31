#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "AST.h"

/* create an AST from a root value and two AST sons */
AST_expr new_binary_expr(char *rule, AST_expr left, AST_expr right) {
  AST_expr t=(struct _expr_tree*) malloc(sizeof(struct _expr_tree));
  if (t!=NULL){	/* malloc ok */
    t->rule = malloc(sizeof(rule));
    strcpy(t->rule,rule);
    t->left=left;
    t->right=right;
    free(rule);
  } else printf("ERR : MALLOC ");
  return t;
}

/* create an AST from a root value and one AST son */
AST_expr new_unary_expr(char *rule, AST_expr son)
{
  return new_binary_expr(rule, NULL,son);
}

/* create an AST leaf from a value */
AST_expr new_number_expr(double number)
{
  AST_expr t=(struct _expr_tree*) malloc(sizeof(struct _expr_tree));
  if (t!=NULL){	/* malloc ok */
    t->boolean = malloc(6*sizeof(char));
    t->rule = malloc(sizeof(char)+1);
    strcpy(t->rule, "N");
    t->number=number;
    if(t->number > 0)
	    strcpy(t->boolean, "True");
    else strcpy(t->boolean, "False");
    t->left=NULL;
    t->right=NULL;
  } else printf("ERR : MALLOC ");
  return t;
}

/* create an AST leaf from a BOOLEAN */
AST_expr new_boolean_expr(char *boolean)
{
  AST_expr t=(struct _expr_tree*) malloc(sizeof(struct _expr_tree));
  if (t!=NULL){	/* malloc ok */
    t->rule = malloc(sizeof(char)+1);
    strcpy(t->rule, "B");
    t->boolean = malloc(sizeof(boolean));
    strcpy(t->boolean, boolean);
    if(strcmp(t->boolean, "True") == 0)
	    t->number = 1;
    else t->number = 0;
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

/* create an AST leaf from a value */

AST_prog new_program(AST_command_list command_list){
	AST_prog program = malloc(sizeof(struct _prog_tree));
  	program->command_list = command_list;
  	return program;
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

void free_prog(AST_prog program) {
  AST_command_list curr_command = program->command_list;
  while (curr_command != NULL) {
    AST_command_list next_command = curr_command->next;
    free_comm(curr_command->command);
    free(curr_command);
    curr_command = next_command;
  }
  free(program);
}



/* infix print an AST*/
void print_expr(AST_expr t){
  if (t!=NULL) {
    printf("[ ");
    print_expr(t->left);
    if (t->left==NULL)
	    printf(":%f: ",t->number); 
    else printf(":%s: ",t->rule);
    print_expr(t->right);
    printf("] ");
  }
}

/*Post_fix print an AST*/
void post_fix(AST_expr t) {
    if (t == NULL) 
	    return;

    post_fix(t->left);
    post_fix(t->right);

    if(strcmp(t->rule, "+") == 0)
	    printf("AddiNb\n");
    else if(strcmp(t->rule, "-") == 0)
	    printf("SubsNb\n");
    else if(strcmp(t->rule, "*") == 0)
	    printf("MultNb\n");
    else if(strcmp(t->rule, "/") == 0)
	    printf("DiviNb\n");
    else if(strcmp(t->rule, "!") == 0)
	    printf("Not\n");
    else if(strcmp(t->rule, "==") == 0)
	    printf("Equals\n");
    else if(strcmp(t->rule, "!=") == 0)
	    printf("NotEql\n");
    else if(strcmp(t->rule, "<=") == 0)
	    printf("LoEqNb\n");
    else if(strcmp(t->rule, ">=") == 0)
	    printf("GrEqNb\n");
    else if(strcmp(t->rule, "<") == 0)
	    printf("LowStNb\n");
    else if(strcmp(t->rule, ">") == 0)
	    printf("GrStNb\n");
    else if(strcmp(t->rule, "M") == 0)
	    printf("NegaNb\n");
    else if(strcmp(t->rule, "N") == 0)
    {
	    if (isnan(t->number))
		    printf("CsteNb NaN\n");
	    else
		    printf("CsteNb %f\n", t->number);
    }
    else if(strcmp(t->rule, "B") == 0)
	    printf("CsteBo %s\n", t->boolean);
    //else

}

void print_comm(AST_comm t){
  if (t!=NULL) {
    //printf("[ ");
   // printf(":%c: ",t->rule);
    post_fix(t->expr1);
    printf("Drop\n");
    //printf("] ");
  }
}

void print_prog(AST_prog program) {
  AST_command_list curr_command = program->command_list;
  while (curr_command != NULL) {
    print_comm(curr_command->command);
    curr_command = curr_command->next;
  }
  printf("Halt\n");
  free_prog(program);
}

