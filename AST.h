
typedef struct _expr_tree* AST_expr;
typedef struct _command_tree* AST_comm;
typedef struct _prog_tree*    AST_prog;

/* unary-and-binary tree structure */
struct _expr_tree {
  char *rule;                    /* "name" of the rule/operation operation */
  double number;                   /* int  for value */			
  char *boolean;
  char *identifier;
  struct _expr_tree* left;           /* NULL if unary node or leaf*/
  struct _expr_tree* right;
};


struct _command_tree {
  char *rule;   /* "name" of the rule/operation operation */
  AST_expr expr1;
};


typedef struct _command_list {
  AST_comm command;
  struct _command_list *next;
} *AST_command_list;

struct _prog_tree {
	AST_command_list command_list;
};


/*Add a command in the program*/

void append_command_to_prog(AST_prog* prog, AST_comm *c);

/* create an AST from a root value and two AST sons */
AST_expr new_binary_expr(char *rule, AST_expr left, AST_expr right);

/* create an AST from a root value and one AST son */
AST_expr new_unary_expr(char *rule, AST_expr son);

/* create an AST leaf from a value */
AST_expr new_number_expr(double	number);

/* create an AST leaf from a BOOLEAN */
AST_expr new_boolean_expr(char *boolean);

/* create an import AST*/
AST_expr new_import_expr(char *identifier);


/* create an AST leaf from a value */
AST_comm new_command(AST_expr expression);

/* A new program */
AST_prog new_program(AST_command_list commande);

/* delete an AST */
void free_expr(AST_expr t);
void free_comm(AST_comm t);
void free_prog(AST_prog t);

/* print an AST*/
void print_expr(AST_expr t);
void print_comm(AST_comm t);
void print_prog(AST_prog t);
