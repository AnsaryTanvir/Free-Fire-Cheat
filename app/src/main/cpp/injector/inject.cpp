#include "PtraceInject.h"

__attribute__ ((visibility ("hidden")))
int main(int argc, char *argv[]) {

    printf("[+] Start Inject\n" );

    /*  # Here are the parameters of the Inject command line tool:
        #   Some parameters are optional.
        #   -p process 's pid <-- optional
        #   -n process 's package name <-- optional
        #   -f whether to start App <-- optional
        #   -so so path for injection <-- mandatory
        #   -symbols specify a symbol in so <-- optional
        # Example: ./injector.so -p 12717 -so /data/local/libpayload.so
     */

    if (init_inject(argc, argv) == 0){
        printf("[+] Finish Inject\n" );
    } else {
        printf("[-] Inject Failed\n" );
    }

    return 0;
}