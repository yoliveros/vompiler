
#include "compiler.h"
#include "lexer/lexer.c"

static char *op_to_string(op_token op) {
  switch (op) {
  case OP_NONE:
    return "NONE";
  case OP_PLUS:
    return "PLUS";
  case OP_MINUS:
    return "MINUS";
  case OP_STAR:
    return "STAR";
  case OP_DIV:
    return "DIV";
  case OP_MOD:
    return "MOD";
  case OP_INC:
    return "INC";
  case OP_DEC:
    return "DEC";
  case OP_ADD_ASSIGN:
    return "ADD ASSIGN";
  case OP_SUB_ASSIGN:
    return "SUB ASSIGN";
  case OP_MUL_ASSIGN:
    return "MUL ASSIGN";
  case OP_DIV_ASSIGN:
    return "DIV ASSIGN";
  case OP_MOD_ASSIGN:
    return "MOD ASSIGN";
  case OP_ASSIGN:
    return "ASSIGN";
  case OP_EQ:
    return "EQ";
  case OP_NOT:
    return "NOT";
  case OP_NEQ:
    return "NEQ";
  case OP_LT:
    return "LT";
  case OP_GT:
    return "GT";
  case OP_LEQ:
    return "LEQ";
  case OP_GEQ:
    return "GEQ";
  case OP_AND:
    return "AND";
  case OP_OR:
    return "OR";
  case OP_LAND:
    return "LAND";
  case OP_LOR:
    return "LOR";
  case OP_DOT:
    return "DOT";
  case OP_ARROW:
    return "ARROW";
  case OP_SHIFT_L:
    return "SHIFT L";
  case OP_SHIFT_R:
    return "SHIFT R";
  default:
    return "UB";
  }
}

static char *keyword_to_string(keyword_type keyword) {
  switch (keyword) {
  case KEY_NONE:
    return "NONE";
  case KEY_VOID:
    return "VOID";
  case KEY_RETURN:
    return "RETURN";
  case KEY_INT:
    return "INT";
  case KEY_CHAR:
    return "CHAR";
  default:
    return "UB";
  }
}

static void print_tokens(token *t) {
  char token_msg[128];

  switch (t->type) {
  case TOK_EOF:
    snprintf(token_msg, sizeof(token_msg), "EOF");
    break;
  case TOK_ERROR:
    snprintf(
        token_msg, sizeof(token_msg), "ERROR(%.*s)", STRING8_FMT(t->lexeme)
    );
    break;
  case TOK_IDENT:
    snprintf(
        token_msg, sizeof(token_msg), "IDENT(%.*s)", STRING8_FMT(t->lexeme)
    );
    break;
  case TOK_NUMBER:
    snprintf(
        token_msg, sizeof(token_msg), "NUMBER(%.*s)", STRING8_FMT(t->lexeme)
    );
    break;
  case TOK_STRING:
    snprintf(
        token_msg, sizeof(token_msg), "STRING(%.*s)", STRING8_FMT(t->lexeme)
    );
    break;
  case TOK_KEYWORD:
    snprintf(
        token_msg,
        sizeof(token_msg),
        "KEYWORD(%.*s) - TYPE(%s)",
        STRING8_FMT(t->lexeme),
        keyword_to_string(t->extra.keyword)
    );
    break;
  case TOK_OP:
    snprintf(
        token_msg,
        sizeof(token_msg),
        "OPERATOR(%.*s) - TYPE(%s)",
        STRING8_FMT(t->lexeme),
        op_to_string(t->extra.op)
    );
    break;
  case TOK_LPAREN:
    snprintf(
        token_msg, sizeof(token_msg), "LPAREN(%.*s)", STRING8_FMT(t->lexeme)
    );
    break;
  case TOK_RPAREN:
    snprintf(
        token_msg, sizeof(token_msg), "RPAREN(%.*s)", STRING8_FMT(t->lexeme)
    );
    break;
  case TOK_LBRACE:
    snprintf(
        token_msg, sizeof(token_msg), "LBRACE(%.*s)", STRING8_FMT(t->lexeme)
    );
    break;
  case TOK_RBRACE:
    snprintf(
        token_msg, sizeof(token_msg), "RBRACE(%.*s)", STRING8_FMT(t->lexeme)
    );
    break;
  case TOK_SEMI:
    snprintf(
        token_msg, sizeof(token_msg), "SEMICOLON(%.*s)", STRING8_FMT(t->lexeme)
    );
    break;
  case TOK_COLON:
    snprintf(
        token_msg, sizeof(token_msg), "COLON(%.*s)", STRING8_FMT(t->lexeme)
    );
    break;
  case TOK_COMMA:
    snprintf(
        token_msg, sizeof(token_msg), "COMMA(%.*s)", STRING8_FMT(t->lexeme)
    );
    break;
  default:
    snprintf(token_msg, sizeof(token_msg), "UB");
    break;
  }

  printf("%s\n", token_msg);
}

string8 compiler(string8 flag, string8 buff) {
  mem_arena *perm_arena = arena_create(GiB(1), MiB(1));

  // TODO parser
  // TODO codegen
  // TODO Assembly

  // lexer
  lexer lexer = {0};
  mem_arena_temp scratch = arena_scratch_get(nullptr, 0);

  lexer_init(scratch.arena, &lexer, buff);

  b32 lex_print = (strncmp("--lex", flag.str, flag.len) == 0);

  token *t = lexer_next_token(&lexer);
  while (t->type != TOK_EOF) {
    if (lex_print)
      print_tokens(t);

    t = lexer_next_token(&lexer);
  }

  arena_scratch_release(scratch);
  // TODO parser
  if (strncmp("--parse", flag.str, flag.len)) {
    goto out;
  }
  // TODO codegen
  if (strncmp("--codegen", flag.str, flag.len)) {
    goto out;
  }
  // TODO Assembly
  if (strncmp("-S", flag.str, flag.len)) {
    goto out;
  }

out:
  arena_destroy(perm_arena);
  return (string8){0};
}
