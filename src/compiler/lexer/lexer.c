
#include "compiler/lexer/lexer.h"
#include "base/base_arena.h"
#include "base/base_defs.h"

inline static u8 lexer_peak(lexer *lexer) {
  return lexer->buff.str[lexer->position];
}

static void skip_whitespace(lexer *lexer) { lexer->position++; }

static token *read_identifier(lexer *lexer) {
  token *t = PUSH_STRUCT(lexer->arena, token);
  t->type = TOK_IDENT;
  u64 start = lexer->position;

  u8 c = lexer_peak(lexer);
  t->lexeme.str = &lexer->buff.str[start];
  while (c != ' ') {
    lexer->position++;
    lexer->column++;
    c = lexer_peak(lexer);
  }
  t->lexeme.len = lexer->position - start;

  // case 'v':
  //   t->keyword = KEY_VOID;
  //   break;
  // case 'i':
  //   t->keyword = KEY_INT;
  //   break;
  // case 'c':
  //   t->keyword = KEY_CHAR;
  //   break;
  // case 'r':
  //   t->keyword = KEY_RETURN;
  //   break;
  // }

  return t;
}

token *read_number(lexer *lexer) {
  token *t = PUSH_STRUCT(lexer->arena, token);
  t->type = TOK_NUMBER;
  i32 len = 0;
  u8 c = lexer_peak(lexer);
  t->lexeme.str = &lexer->buff.str[lexer->position];
  while (c != ' ') {
    lexer->position += len;
    lexer->column += len;
    c = lexer_peak(lexer);
  }
  t->lexeme.len = len;

  return t;
}

static token *read_string(lexer *lexer) {
  token *t = PUSH_STRUCT(lexer->arena, token);

  return t;
}

static token *read_operator(lexer *lexer) {
  token *t = PUSH_STRUCT(lexer->arena, token);

  return t;
}

static token *read_keyword(lexer *lexer) {
  token *t = PUSH_STRUCT(lexer->arena, token);
  switch (1) {
  case KEY_VOID:
  case KEY_RETURN:
  case KEY_INT:
  case KEY_CHAR:
  case KEY_OP:
  }

  return t;
}

static token *make_token(lexer *lexer, token_type type) {
  token *t = PUSH_STRUCT(lexer->arena, token);

  t->type = type;
  t->line = lexer->line;
  t->column = lexer->column;

  if (type == TOK_EOF) {
    t->lexeme = (string8){0};
  } else {
    t->lexeme.str = &lexer->buff.str[lexer->position];
    t->lexeme.len = 1;
    lexer->position++;
    lexer->column++;
  }

  return t;
}

static token_type char_to_token_type(u8 c) {
  switch (c) {
  case '(':
    return TOK_LPAREN;
  case ')':
    return TOK_RPAREN;
  case '{':
    return TOK_LBRACE;
  case '}':
    return TOK_RBRACE;
  case ';':
    return TOK_SEMI;
  case ',':
    return TOK_COMMA;
  default:
    return TOK_ERROR;
  }
}

token *lexer_next_token(lexer *lexer) {
  skip_whitespace(lexer);

  u8 c = lexer_peak(lexer);

  switch (c) {
  case '\0':
    return make_token(lexer, TOK_EOF);
  case 'a' ... 'z':
  case 'A' ... 'Z':
  case '_':
    return read_identifier(lexer);
  case '0' ... '9':
    return read_number(lexer);
  case '"':
  case '\'':
    return read_string(lexer);
  case '+':
  case '-':
  case '*':
  case '/':
  case '%':
  case '=':
  case '!':
  case '<':
  case '>':
  case '&':
  case '|':
  case ':':
  case '.':
    return read_operator(lexer);
  case '(':
  case ')':
  case '{':
  case '}':
  case ';':
  case ',':
    return make_token(lexer, char_to_token_type(c));
  default:
    return make_token(lexer, TOK_ERROR);
  }
}

void lexer_init(mem_arena *arena, lexer *lexer, string8 buff) {
  lexer->arena = arena;
  lexer->buff = buff;
  lexer->position = 0;
  lexer->column = 1;
  lexer->line = 1;
}
