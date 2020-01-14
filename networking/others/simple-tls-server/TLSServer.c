/*  Implementation of a TLS Server. You must have the .pem files (SSL Certifications) in order to run it. */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

int create_socket(int port) {
    int s;
    struct sockaddr_in addr;

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) {
        perror("Unable to create socket");
        exit(EXIT_FAILURE);
    }

    if (bind(s, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("Unable to bind");
        exit(EXIT_FAILURE);
    }

    if (listen(s, 1) < 0) {
        perror("Unable to listen");
        exit(EXIT_FAILURE);
    }

    return s;
}

/*  Initialise openssl by loading the strings used for error messages, and
    setting up the algorithms needed for TLS. */
void init_openssl() {
    /*  Registers the error strings for all libcrypto and libssl functions. */
    SSL_load_error_strings();
    /*  DEFINITION: Cipher
        Ciphers are algorithms, more specifically they are a set of steps for
        performing a cryptographic function. 
        DEFINITION: Message Digest
        A message digest is a cryptographic hash function containing a string of
        bits created by a one-way hashing formula. Message digests can be produced
        on UNIX systems with the MD5 (algorithm) command.
        See https://www.geeksforgeeks.org/message-digest-in-information-security/
    */
    /*  Registers the available SSL/TLS ciphers and digests. */
    OpenSSL_add_ssl_algorithms();
}

/*  Removes all ciphers and digests from the table */
void cleanup_openssl() {
    EVP_cleanup();
}

SSL_CTX *create_context() {
    /*  Describes the internal ssl library functions which implement the
        various protocol versions. */
    const SSL_METHOD *method;
    /*  Global context structure which holds mainly default values for the
        SSL structures which are later created for the connections. */
    SSL_CTX *ctx;

    /*  Indicates that the application is a server and supports TLSv1.2 */
    method = SSLv23_server_method();

    /*  Creates a new SSL_CTX object as framework to establish TLS/SSL enabled
        connections. */
    ctx = SSL_CTX_new(method);
    if (!ctx) {
        perror("Unable to create SSL context");
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }

    return ctx;
}

void configure_context(SSL_CTX *ctx) {
    /*  NOTE: Elliptic-curve cryptography
        ECC is an approach to public-key cryptography based on the algebraic
        structure of elliptic curves. A 256-bit elliptic curve private key is 
        just as secure as a 3072-bit RSA private key. 
        See https://hackernoon.com/what-is-the-math-behind-elliptic-curve-cryptography-f61b25253da3 */
    /*  Tell openssl to handle selecting the right elliptic curve. */
    SSL_CTX_set_ecdh_auto(ctx, 1);

    /*  Set the key and cert */
    if (SSL_CTX_use_certificate_file(ctx, "cert.pem", SSL_FILETYPE_PEM) <= 0) {
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }

    if (SSL_CTX_use_PrivateKey_file(ctx, "key.pem", SSL_FILETYPE_PEM) <= 0) {
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) {
    int sock;
    SSL_CTX *ctx;

    init_openssl();
    ctx = create_context();

    configure_context(ctx);

    sock = create_socket(12001);

    /*  Handle connections */
    while(1) {
        struct sockaddr_in addr;
        /*  It is a standard integer type that guarantees 32 bits. */
        uint32_t len = sizeof(addr);
        /*  Main SSL/TLS structure in the SSL API. */
        SSL *ssl;
        const char reply[] = "test\n";

        int client = accept(sock, (struct sockaddr*)&addr, &len);
        if (client < 0) {
            perror("Unable to accept");
            exit(EXIT_FAILURE);
        }

        /*  Creates a new SSL structure. It inherits the settings of the
            underlying context ctx. */
        ssl = SSL_new(ctx);
        /*  Sets the file descriptor fd as the input/output facility for the
            TLS/SSL (encrypted) side of ssl. */
        SSL_set_fd(ssl, client);
        /*  IMPORTANT
            SSL_accept() waits for a TLS/SSL client to initiate the TLS/SSL 
            handshake. The communication channel must already have been set 
            and assigned to the ssl by setting an underlying BIO.
        */
        if (SSL_accept(ssl) <= 0) {
            ERR_print_errors_fp(stderr);
        } else {
            SSL_write(ssl, reply, strlen(reply));
        }
        /*  Shut down a TLS/SSL connection */
        SSL_shutdown(ssl);
        /*  Free an allocated SSL structure */
        SSL_free(ssl);
        close(client);
    }

    /*  Clean up the various structures */
    close(sock);
    SSL_CTX_free(ctx);
    cleanup_openssl();
}

// See https://wiki.openssl.org/index.php/Simple_TLS_Server