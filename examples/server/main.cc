#include <iostream>
#include "callme/server.h"
#include "callme/detail/uv_loop.h"

void foo() { std::cout << "foo was called!" << std::endl; }

void bad(int x) {
    if (x == 5) {
        throw std::runtime_error("x == 5. I really don't like 5.");
    }
}

int main(int argc, char *argv[]) {
    // Create a server that listens on port 8080
    callme::server srv("0.0.0.0", 8080);

    // Binding the name "foo" to free function foo.
    // note: the signature is automatically captured
    srv.bind("foo", &foo);

    // Binding a lambda function to the name "add".
    srv.bind("add", [](int a, int b) { return a + b; });

    // Throwing an exception will cause the server to write
    // an error response. This call will make it also
    // suppress the exception (note that this is not default
    // because this behavior might hide errors in the
    // code).
    srv.suppress_exceptions(true);
    srv.bind("bad", &bad);

    // Run the server loop.
    srv.run();
    srv.start();

    return 0;
}
