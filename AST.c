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
    t->identifier = NULL;
    strcpy(t->rule,rule);
    t->left=left;
    t->right=right;
    if(left != NULL){
   	t->size = 1 + left->size +right->size;
    }
    else{
	t->size = 1 + right->size;
    }
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
    t->identifier = NULL;
    strcpy(t->rule, "N");
    t->number=number;
    if(t->number > 0)
	    strcpy(t->boolean, "True");
    else strcpy(t->boolean, "False");
    t->left=NULL;
    t->right=NULL;
    t->size = 1;
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
    t->identifier = NULL;
    t->boolean = malloc(sizeof(boolean));
    strcpy(t->boolean, boolean);
    if(strcmp(t->boolean, "True") == 0)
	    t->number = 1;
    else t->number = 0;
    t->left=NULL;
    t->right=NULL;
    t->size = 1;
  } else printf("ERR : MALLOC ");
  return t;
}

/* create an AST from a root value and two AST sons */
AST_expr new_import_expr(char* id) {
  AST_expr t=(struct _expr_tree*) malloc(sizeof(struct _expr_tree));
  if (t!=NULL){	/* malloc ok */
    t->rule = malloc(sizeof(char)+1);
    strcpy(t->rule, "I");
    t->identifier = malloc(sizeof(id)+1);
    strcpy(t->identifier, id);
    t->left=NULL;
    t->right=NULL;
    t->size = 1;
  } else printf("ERR : MALLOC ");
  return t;
}


/* create an ASSIGN */
AST_expr new_assign_expr(char* r, char* id, AST_expr right) {
  AST_expr t=(struct _expr_tree*) malloc(sizeof(struct _expr_tree));
  if (t!=NULL){	/* malloc ok */
    t->rule = malloc(sizeof(r)+1);
    strcpy(t->rule, r);
    t->identifier = malloc(sizeof(id) + 1);
    strcpy(t->identifier, id);
    t->right=right;
    t->left = NULL;
    t->size = 1 +right->size;
  } else printf("ERR : MALLOC ");
  return t;
}


/* create an ID*/
AST_expr new_id_expr(char* id) {
  AST_expr t=(struct _expr_tree*) malloc(sizeof(struct _expr_tree));
  if (t!=NULL){	/* malloc ok */
    t->rule = malloc(sizeof(char)+2);
    strcpy(t->rule, "id");
    t->identifier = malloc(sizeof(id) + 1);
    strcpy(t->identifier, id);
    t->right= NULL;
    t->left = NULL;
    t->size = 1;
 } else printf("ERR : MALLOC ");
  return t;
}


/* create an IF or WHILE AST */
AST_comm new_if_while_expr(char* r, AST_expr expr, AST_comm com1, AST_comm com2) {
  AST_comm t=(struct _command_tree*) malloc(sizeof(struct _expr_tree));
  if (t!=NULL){	/* malloc ok */
    t->rule = malloc(sizeof(r)+1);
    strcpy(t->rule, r);
    t->expr1=expr;
    t->com1 = com1;
    t->com1->rule = malloc(sizeof(char)+2);
    strcpy(t->com1->rule, "iw");
    t->com2 = com2;
    t->prog = NULL;
    if(com2 != NULL)
    {
	t->com2->rule = malloc(sizeof(char)+2);
	strcpy(t->com2->rule, "el");
    	t->size = 1 + com1->size + com2->size;
    }
    else
	t->size = 1 + com1->size;

  } else printf("ERR : MALLOC ");
  return t;
}

/* create an AST leaf from a value */
AST_comm new_command(AST_expr expression, AST_prog prog){
  AST_comm t =  malloc(sizeof(struct _command_tree));
  if (t!=NULL){	/* malloc ok */
    t->expr1 = expression;
    t->rule = malloc(sizeof(char)+2);
    strcpy(t->rule, "ex");
    t->prog = prog;
    if(prog != NULL && expression != NULL)
    	t->size = 1+  expression->size + prog->size;
    else if(prog == NULL && expression != NULL)
	t->size = 1+  expression->size;
    else if(prog != NULL && expression == NULL)
	t->size = 1 + prog->size;

  } else printf("ERR : MALLOC ");
  return t;

}

/* create an AST leaf from a value */

AST_prog new_program(AST_command_list command_list){
	AST_prog program = malloc(sizeof(struct _prog_tree));
 	program->command_list = command_list;
  	if(command_list !=NULL)
  		program->size = 1+command_list->size;
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

/*Open a file and prints its content*/
void print_file(char *filename) {
    FILE *file = fopen(filename, "r"); // open file in read mode
    if (file == NULL) { // check if file was successfully opened
        printf("Error: Unable to open file %s.\n", filename);
        return;
    }

    char line[1000];
    while (fgets(line, sizeof(line), file) != NULL) { // read file line by line
        printf("%s", line);
    }

    fclose(file); // close the file
}



/* infix print an AST*/
void print_expr(AST_expr t){
  if (t!=NULL) {
    printf("[ ");
    print_expr(t->left);
    if(t->left==NULL)
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
    if(strcmp(t->rule, "&&") == 0)
    {
	post_fix(t->left);
	printf("CondJmp %d\n", t->right->size + 1);
	post_fix(t->right);
	printf("Jump 1\n");
	printf("CsteBo False\n");
    }
     else if(strcmp(t->rule, "=") == 0)
    {
	post_fix(t->right);
	printf("SetVar %s\n", t->identifier);
	    
    }
    else if(strcmp(t->rule, "I") == 0)
    {
	    FILE *fp;
	    strcat(t->identifier, ".jsm");
            print_file(t->identifier); 
    }
    else if(strcmp(t->rule, "id") == 0)
    {
            printf("GetVar %s\n", t->identifier); 
    }

    else {
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
    
  
       }
    //else

}


void print_comm(AST_comm t, char* Lab){

  if (t!=NULL) {
    //printf("[ ");
   // printf(":%c: ",t->rule);
    //printf("] ");
    if(t->prog != NULL && t->expr1==NULL)
	    print_prog(t->prog);
    else if(t->expr1 != NULL){
    if(strcmp(t->rule, "if") == 0)
    {
    	post_fix(t->expr1);
	printf("CondJump if%d\n", t->com1->size);
	print_comm(t->com1, Lab);
	printf("Jump el%d\n", t->com2->size);
	printf("if%d ", t->com1->size);
	print_comm(t->com2, Lab);
	printf("el%d ", t->com2->size);
    }
    else if(strcmp(t->rule, "wh") == 0)
    {
	printf("wh%d ", t->com1->size);
    	print_comm(t->com1, NULL);
	post_fix(t->expr1);
	printf("CondJump wh%d\n", t->com1->size);
	//printf("Jump -%d\n", t->com1->size+t->expr1->size);
    }
    else if(strcmp(t->rule, "el") == 0)
    {
	post_fix(t->expr1);
    }
    else if(strcmp(t->rule, "iw") == 0)
    {
	post_fix(t->expr1);	
    }
     
    else if(strcmp(t->rule, "ex") == 0)
    {
	post_fix(t->expr1);
    }
    }
    else if (t->prog !=NULL && t->expr1 != NULL)
    {
	post_fix(t->expr1);
	print_prog(t->prog);
    }
  }
}

void print_prog(AST_prog program) {
  AST_command_list curr_command = program->command_list;
  char *Lab = malloc(sizeof(char)*7);

  while (curr_command != NULL) {
    print_comm(curr_command->command, Lab);
    curr_command = curr_command->next;
  }
  free_prog(program);
}

