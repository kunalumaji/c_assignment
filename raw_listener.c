#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <linux/if_packet.h>
#include <net/ethernet.h>
#include <net/if.h>


struct ip_header
{
    uint8_t version_hlen;
    uint8_t service_type;
    uint16_t total_length;
    uint16_t id_number;
    uint16_t frag_flags;
    uint8_t ttl;
    uint8_t protocol;
    uint16_t checksum;
    uint8_t source_1;
    uint8_t source_2;
    uint8_t source_3;
    uint8_t source_4;
    uint8_t dest_1;
    uint8_t dest_2;
    uint8_t dest_3;
    uint8_t dest_4;
};


struct tcp_header
{
    uint16_t sport;
    uint16_t dport;
    uint32_t seq_no;
    uint32_t ack_no;
};


//ip version and header len
void parse_version_ihl(uint8_t byte)
{
    uint8_t ihl_op = 15; // 0000 1111
    uint8_t ver_op = 240; // 1111 0000

    uint8_t version = (byte & ver_op) / 16;
    uint8_t header_length = byte & ihl_op;

    printf("version: %d \nheader length: %d\n", version, header_length);
}


//IP Header parser
void print_iph_fields(struct ip_header* iph)
{
    printf("\nIP Header Fields\n\n");

    parse_version_ihl(iph->version_hlen);

    printf("total length: %d\n", ntohs(iph->total_length));
    printf("identification: %d\n", ntohs(iph->id_number));
    printf("TTL: %d\n", iph->ttl);
    printf("protocol: %d\n", iph->protocol);

    printf("source ip: %d.%d.%d.%d destination ip: %d.%d.%d.%d\n",
        iph->source_1, iph->source_2, iph->source_3, iph->source_4,
        iph->dest_1, iph->dest_2, iph->dest_3, iph->dest_4);

}

//tcp header parser
void print_tcph_header_fields(struct tcp_header* tcph)
{
    printf("\nTransport Protocol Header\n\n");

    printf("source port: %d destination port: %d\n", ntohs(tcph->sport), ntohs(tcph->dport));
    printf("seq: %d ack: %d\n", ntohs(tcph->seq_no), ntohs(tcph->ack_no));

}


int main()
{
    int socket_identifier = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if (socket_identifier < 0)
    {
        printf("socket initialization failed\n");
        return 0;
    }

    struct sockaddr_ll socket_link = {0};
    socket_link.sll_family   = AF_PACKET;
    socket_link.sll_protocol = htons(ETH_P_ALL);
    socket_link.sll_ifindex  = if_nametoindex("vnic0");

    if (bind(socket_identifier, (struct sockaddr*)&socket_link, sizeof(socket_link)) < 0)
    {
        printf("bind unsuccessful\n");
        return 0;
    }

    char buffer[2048];

    while (1)
    {
        struct sockaddr_ll address;
        int address_len;

        int received_bytes = recvfrom(socket_identifier, buffer, sizeof(buffer), 0, (struct sockaddr*)&address, (socklen_t*)&address_len);
        if (received_bytes > 0)
        {
            if (address.sll_pkttype == PACKET_OUTGOING)
            {
                struct ip_header* iph = (struct ip_header*) buffer;
                struct tcp_header* tcph = (struct tcp_header*) (buffer+20);

                print_iph_fields(iph);
                print_tcph_header_fields(tcph);

                printf("packet transmitted %d bytes\n-----\n", received_bytes);

            }

            continue;
        }

        printf("nothing received. might be error\n");
    }

    return 0;
}