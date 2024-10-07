#include "../include/dbms.h"

int main(int argc, char* argv[]) {
    char* filename = NULL;
    char* query = NULL;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--file") == 0) {
            filename = argv[++i];
        } else if (strcmp(argv[i], "--query") == 0) {
            query = argv[++i];
        }
    }

    if (filename == NULL || query == NULL) {
        fprintf(stderr, "Missing --file or --query argument\n");
        return 1;
    }

    DBMS dbms;
    QueryData q_data = parse_query(query);
    comand_handler(&dbms, q_data, filename);
    
    return 0;
}