#ifndef PARSED_STORAGE_H
#define PARSED_STORAGE_H

typedef struct ParsedStorage ParsedStorage;

void ParsedStorage_init(ParsedStorage *parsed);
void ParsedStorage_read(ParsedStorage *parsed, char* buffer);
void ParsedStorage_write(ParsedStorage *parsed, char* buffer);

#endif
