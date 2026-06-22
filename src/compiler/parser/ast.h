#pragma once

typedef enum {
  AST_PROGRAM,
  AST_FUNC,
  AST_BLOCK,
  AST_RETURN,
  AST_CONST,
} ast_node_type;

typedef struct ast_node ast_node;

struct ast_node {
  ast_node_type type;
  ast_node *next;
  union {
    struct {
      ast_node *funcs;
    } prog;
    struct {
      keyword_type ret_type;
      string8 name;
      ast_node *body;
    } func;
    struct {
      ast_node *stmts;
    } block;
    struct {
      i64 value;
    } c;
  } as;
};
