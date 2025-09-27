//sql connector hdrs
#include "../hdr/Utils.h"

int main() {

    Utils::Login("tcp://127.0.0.1:3306", "root", "Ddomo2001@", "paxel");
    return 0;
}