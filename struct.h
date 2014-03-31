struct addrinfo {

    int              ai_flags;      // This  field  specifies additional options.

    int              ai_family;     // IPv4, IPv6 or IP agnostic.

    int              ai_socktype;   // TCP or UDP.

    int              ai_protocol;   // The protocol for the returned socket addresses.

    size_t           ai_addrlen;    // Size of ai_addr in bytes

    struct sockaddr  *ai_addr;      // Containing the IP address and port.

    char             *ai_canonname; // The Canonical hostname.

    struct addrinfo *ai_next;       // linked list, next address.

};
