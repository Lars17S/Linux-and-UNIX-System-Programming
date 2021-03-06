import socket
import struct
import textwrap

def main():
    conn = socket.socket(socket.AF_PACKET, socket.SOCK_RAW, socket.ntohs(3))
    maxBuffer = 65536
    
    while True:
        # Receive data from the socket. The return value is a pair (string, address)
        # where string is a string representing the data received and address is the
        # address of the socket sending the data
        raw_data, addr = conn.recvfrom(maxBuffer)
        dest_mac, src_mac, eth_proto, data = ethernet_frame(raw_data)
        print('\nEthernet frame:')
        print('Destination: {}, Source: {}, Protocol: {}'.format(dest_mac, src_mac, eth_proto))


# Unpack ethernet frame
def ethernet_frame(data):
    # '!' exclamation converts data from big-endian to little-endian
    dest_mac, src_mac, proto = struct.unpack('! 6s 6s H', data[:14])
    return get_mac_addr(dest_mac), get_mac_addr(src_mac), socket.htons(proto), data[14:]
    
# Return properly formatted MAC address
def get_mac_addr(bytes_addr):
    # Returns a map object (which is an iterator) list
    bytes_str = map(' {:02x}'.format, bytes_addr)
    # Takes all items in an iterable and joins them into one string
    return ':'.join(bytes_str).upper()

# Unpack IPv4 packet
def ipv4_packet(data):
    version_header_length = data[0]
    version = version_header_length >> 4
    header_length = (version_header_length & 15) * 4
    ttl, proto, src, dest = struct.unpack('! 8x B B 2x 4s 4s', data[:20])
    return version, header_length, ttl, proto, ipv4(src), ipv4(dest), data[header_length:]

# Returns properly formatted IPv4 address
def ipv4(addr):
    return '.'.join(map(str, addr))

# Unpacks ICMP packet
def icmp_packet(data):
    icmp_type, code, checksum = struct.unpack('! B B H', data[:4])
    return icmp_type, code, checksum, data[4:]

# Unpacks TCP segment
def tcp_segment(data):
    (src_port, dest_port, sequence, acknowledgement, offset_reserved_flags) = struct.unpack('! H H L L H', data[:14])
    offset = (offset_reserved_flags >> 12) * 4
    flag_urg = (offset_reserved_flags & 32) >> 5
    flag_ack = (offset_reserved_flags & 32) >> 4
    flag_psh = (offset_reserved_flags & 32) >> 3
    flag_rst = (offset_reserved_flags & 32) >> 2
    flag_syn = (offset_reserved_flags & 32) >> 1
    flag_fin = offset_reserved_flags & 1
    return src_port, dest_port, sequence, acknowledgement, flag_urg,
            flag_ack, flag_psh, flag_rst, flag_syn, flag_fin, data[offset:]
main()