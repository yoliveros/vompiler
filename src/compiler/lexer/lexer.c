
u8 lexer_peak(lexer *lexer) { return lexer->buff.str[lexer->position]; }

void skip_whitespace(lexer *lexer) { lexer_peak(lexer); }

token *make_token(lexer *lexer, token_type token_type) { token token; }

token *read_identifier(lexer *lexer) {}

token *read_number(lexer *lexer) {}

token *read_string(lexer *lexer) {}

token *read_operator(lexer *lexer) {}

token_type char_to_token_type(u8 c) {
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
