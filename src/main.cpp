// Independent harmless C++ fixture: square one integer in [-100,100].
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cerrno>
int main(int argc, char **argv) {
    char data[128] = {0};
    if (argc != 3 || strcmp(argv[1], "argv") || strlen(argv[2]) >= sizeof(data)) return 3;
    strcpy(data, argv[2]);
    char *end = nullptr; errno = 0;
    long value = strtol(data, &end, 10);
    if (errno || end == data || *end || value < -100 || value > 100 || data[0] == '+') {
        fputs("invalid\n", stderr); return 2;
    }
    printf("%ld\n", value * value); return 0;
}
