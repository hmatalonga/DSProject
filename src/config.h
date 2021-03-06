// Files path defaults
#define DATA_FILE_PATH "dataset.txt"

#define PROGRAM_HEADER "=== PROJED (v2) Data Structures 2014 Hugo Matalonga ===\n\n"
#define HELP_INFO "Help\n\nPROJED (v2)\n\nNAME\n\tprojed - Programa de Estruturas de Dados com Estruturas compostas\n\nSYNOPSIS\n\t./projed [OPTIONS]\n\n\tUsage:\n\t\t./projed -v -f data.txt\n\n\tUsage inside the program:\n\t\tc12+16, c15+17c16-15, etc.\n\nOPTIONS\n\t-v\n\t\tRun program on verbose mode\n\n\t-f [FILE]\n\t\tRun program with a different source data file"
#define PAUSE_MESSAGE "\n\nPress any key to continue..."
#define MAX_RECORD_NUMBER 500000

// <dia>/<mês>/<ano>;<bi>;<curso>;<classificação>
#define DATA_RECORD_FORMAT "%hhu/%hhu/%hu;%ld;%hu;%hhu\n"
#define QUERY_FORMAT "%hu%c%hhu"

#define QUERY_MAX_SIZE 128
#define BUFFER_SIZE 1024
#define BUFFER_NUM 64

// Error messages
#define IO_ERROR_EXCEPTION "The file was not found...\n"
#define FORMAT_ERROR_EXCEPTION "Query format is not valid...\n"
#define MEMORY_ERROR_EXCEPTION "Memory Allocation error.\n"
#define QUERY_ERROR_EXCEPTION "Not a valid query...\nUsage: c12+16\n"