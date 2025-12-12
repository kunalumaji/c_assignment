from scapy.all import *

# TCP Headers set
source_port = 120
dest_port = 89

sequence_number = 0
ack_number = 0

header_len = 24
window_size = 2048

data = "Hello daemon here..."


tcp_packet = TCP(
    sport = source_port,
    dport = dest_port,
    seq = sequence_number,
    ack = ack_number,
    window = window_size
)

# IP Headers
version = 6
id_number = 3
ttl = 8
source_address = '1.1.1.11'
dest_address = '20.2.2.2'

ip_packet = IP(
    src = source_address,
    dst = dest_address,
    id = id_number,
    version = version,
    ttl = ttl
)

final_packet = ip_packet / tcp_packet

final_packet.show()

sendp(final_packet, iface="vnic0")