
#include "lexer.h"

inline static u8 lexer_peak(lexer *lexer) {
  return lexer->buff.str[lexer->position];
}

inline static token *alloc_token(lexer *lexer) {
  token *t = PUSH_STRUCT(lexer->arena, token);
  return t;
}

inline static bool lexeme_match(string8 lexeme, char *keyword) {
  return strncmp(keyword, lexeme.str, lexeme.len) == 0;
}

static void skip_whitespace(lexer *lexer) {
  u8 c = lexer_peak(lexer);
  while (c == ' ' || c == '\n' || c == '\t') {
    if (c == '\n') {
      lexer->line++;
      lexer->column = 1;
    } else {
      lexer->column++;
    }

    lexer->position++;
    c = lexer_peak(lexer);
  }
}

static token *read_identifier(lexer *lexer) {
  token *t = alloc_token(lexer);
  t->type = TOK_IDENT;
  u64 start = lexer->position;

  u8 c = lexer_peak(lexer);
  void *curr_buff = &lexer->buff.str[start];
  t->lexeme.str = curr_buff;
  while (isalnum(c) || c == '_') {
    lexer->position++;
    lexer->column++;
    c = lexer_peak(lexer);
  }

  t->lexeme.len = lexer->position - start;

  if (lexeme_match(t->lexeme, "void"))
    t->extra.keyword = KEY_VOID;
  else if (lexeme_match(t->lexeme, "int"))
    t->extra.keyword = KEY_INT;
  else if (lexeme_match(t->lexeme, "char"))
    t->extra.keyword = KEY_CHAR;
  else if (lexeme_match(t->lexeme, "return"))
    t->extra.keyword = KEY_RETURN;

  if (t->extra.keyword != KEY_NONE)
    t->type = TOK_KEYWORD;

  return t;
}

token *read_number(lexer *lexer) {
  token *t = alloc_token(lexer);
  t->type = TOK_NUMBER;
  i64 start = lexer->position;
  u8 c = lexer_peak(lexer);
  t->lexeme.str = &lexer->buff.str[lexer->position];

  while (isdigit(c)) {
    lexer->position++;
    lexer->column++;
    c = lexer_peak(lexer);
  }

  if (isalpha(c)) {
    t->type = TOK_ERROR;
    goto ret;
  }

  t->lexeme.len = lexer->position - start;

ret:
  return t;
}

static token *read_string(lexer *lexer) {
  token *t = alloc_token(lexer);
  t->type = TOK_STRING;
  lexer->position++; // Skipping the first doulbe quote
  lexer->column++;
  t->lexeme.str = &lexer->buff.str[lexer->position];
  i64 start = lexer->position;
  u8 c = lexer_peak(lexer);

  while (c != '\"' && c != '\0') {
    lexer->position++;
    lexer->column++;
    c = lexer_peak(lexer);
  }
  t->lexeme.len = lexer->position - start;

  lexer->position++;
  lexer->column++;

  return t;
}

static token *make_token(lexer *lexer, token_type type) {
  token *t = alloc_token(lexer);

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

static token *read_operator(lexer *lexer) {
  token *t = alloc_token(lexer);
  t->type = TOK_OP;
  t->lexeme.str = &lexer->buff.str[lexer->position];

  u8 c = lexer_peak(lexer);

  u8 next = lexer->buff.str[lexer->position + 1];

  switch (c) {
  case '+':
    if (next == '+')
      t->extra.op = OP_INC;
    else if (next == '=')
      t->extra.op = OP_ADD_ASSIGN;
    else {
      t->extra.op = OP_PLUS;
      goto sin;
    }

    goto dou;
  case '-':
    if (next == '-')
      t->extra.op = OP_DEC;
    else if (next == '=')
      t->extra.op = OP_SUB_ASSIGN;
    else {
      t->extra.op = OP_MINUS;
      goto sin;
    }

    goto dou;
  case '*':
    if (next == '=') {
      t->extra.op = OP_MUL_ASSIGN;
      goto dou;
    }

    t->extra.op = OP_STAR;
    goto sin;
  case '/':
    if (next == '=') {
      t->extra.op = OP_DIV_ASSIGN;
      goto dou;
    }

    t->extra.op = OP_DIV;
    goto sin;
  case '%':
    if (next == '=') {
      t->extra.op = OP_MOD_ASSIGN;
      goto dou;
    }

    t->extra.op = OP_MOD;
    goto sin;
  case '=':
    if (next == '=') {
      t->extra.op = OP_EQ;
      goto dou;
    }

    t->extra.op = OP_ASSIGN;
    goto sin;
  case '!':
    if (next == '=') {
      t->extra.op = OP_NEQ;
      goto dou;
    }

    t->extra.op = OP_NOT;
    goto sin;
  case '<':
    if (next == '=') {
      t->extra.op = OP_LEQ;
    } else if (next == '<')
      t->extra.op = OP_SHIFT_L;
    else {
      t->extra.op = OP_LT;
      goto sin;
    }

    goto dou;
  case '>':
    if (next == '=') {
      t->extra.op = OP_GEQ;
    } else if (next == '>')
      t->extra.op = OP_SHIFT_R;
    else {
      t->extra.op = OP_GT;
      goto sin;
    }

    goto dou;
  case '&':
    if (next == '&') {
      t->extra.op = OP_LAND;
      goto dou;
    }

    t->extra.op = OP_AND;
    goto sin;
  case '|':
    if (next == '|') {
      t->extra.op = OP_LOR;
      goto dou;
    }

    t->extra.op = OP_OR;
    goto sin;
  case '.':
    t->extra.op = OP_DOT;
    goto sin;
  default:
    t->extra.op = OP_NONE;
    goto sin;
  }

sin:
  t->lexeme.len = 1;
  lexer->position++;
  lexer->column++;
  return t;

dou:
  t->lexeme.len = 2;
  lexer->position += 2;
  lexer->column += 2;
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
  case '.':
    return read_operator(lexer);
  case ':':
    return make_token(lexer, TOK_COLON);
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
