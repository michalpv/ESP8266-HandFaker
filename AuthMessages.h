#ifndef AuthMessages_h
#define AuthMessages_h
// Helpful libray-making resource: https://www.arduino.cc/en/Hacking/libraryTutorial

// Packet dissections for handshake messages 1 through 4
uint8_t key1Temp[131] = {
      0x08, 0x02, // Frame Control (QoS Data Frame). For regular data frame, use 0x08, 0x02
      0x3a, 0x01, // Duration ID
      0x60, 0x01, 0x02, 0x03, 0x04, 0x05, // STA Address
      0x00, 0x01, 0x02, 0x03, 0x04, 0x05, // AP/Transmitter Address
      0x00, 0x01, 0x02, 0x03, 0x04, 0x05, // AP Address once again (Source Hardware Address)
      0x00, 0x00, // Sequence Number (Seq-ctl)
      // LLC (Logical-Link Control) Segment - Seems to be consistent between QoS and reg Data frames
      0xaa, 0xaa, // DSAP, SSAP
      0x03, // Control Field?
      0x00, 0x00, 0x00, // Organization code
      0x88, 0x8e, // Type: 802.1X Authentication
      // 802.1X Authentication Segment
      0x02, // Version: 2 - 802.1X-2004
      0x03, // Type - Key
      0x00, 0x5f, // EAPOL Length (Length of following packet information)
      0x02, // Key Descriptor Type (RSN Key)
      0x00, 0x8a, // Key Information (HMAC SHA-1 MIC, etc.)
      0x00, 0x10, // Key Length = 16
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, // Replay Counter = 1 (Acts as a sort of identifier that matches with message 2)
        //0x14, 0xac, 0x4b, 0x04, 0x87, 0x20, 0xf2, 0xdc, 0x38, 0x12, 0x1a, 0x73, 0x01,
        0x24, 0xac, 0x4b, 0x04, 0x87, 0x20, 0xf2, 0xdc, 0x38, 0x12, 0x1a, 0x73, 0x01, // |
        0xb7, 0x96, 0x19, 0x40, 0x4c, 0xce, 0x67, 0x62, 0x4a, 0x96, 0x0a, 0x14, 0x9d, // | - WPA Authenticator ANonce value (32 byte value)
        0x64, 0x01, 0xff, 0xd3, 0x36, 0x3d,                                           // |
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, // Key IV (16 bytes)
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Key RSC
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Key ID
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Key MIC (16 bytes)
      0x00, 0x00 // WPA Key Data Length (2 bytes)
      // No WPA Key Data as indicated by the above data length field
      };
uint8_t key2Temp[153] = {
      0x08, 0x01, // Frame Control (QoS Data Frame). For regular data frame, use 0x08, 0x01
      0x3a, 0x01, // Duration ID
      0x00, 0x01, 0x02, 0x03, 0x04, 0x05, // Reciever (AP) BSSID
      0x60, 0x01, 0x02, 0x03, 0x04, 0x05, // STA/Transmitter Address
      0x00, 0x01, 0x02, 0x03, 0x04, 0x05, // AP Address once again (Destination Hardware Address, this value is ALWAYS AP BSSID)
      0x00, 0x00, // Sequence Number (Seq-ctl)
      // LLC (Logical-Link Control) Segment - Seems to be consistent between QoS and reg Data frames
      // The LLC Segment stays consistent among all key messages
      0xaa, 0xaa, // DSAP, SSAP
      0x03, // Control Field?
      0x00, 0x00, 0x00, // Organization code
      0x88, 0x8e, // Type: 802.1X Authentication
      // 802.1X Authentication Segment
      0x01, // Version: 2 - 802.1X-2001 (0x02 is 802.1X-2004, either can be used)
      0x03, // Type - Key
      0x00, 0x75, // EAPOL Length (Length of following packet information)
      0x02, // Key Descriptor Type (RSN Key)
      0x01, 0x0a, // Key Information (HMAC SHA-1 MIC, Key Set = 1)
      0x00, 0x00, // Key Length = 0
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, // Replay Counter = 1 (Acts as a sort of identifier that matches with message 2)
        0xe8, 0x58, 0x96, 0xad, 0x03, 0xec, 0xd8, 0xa0, 0xed, 0xbb, 0x1f, 0xe4, 0x22, // |
        0xf8, 0xb2, 0x4d, 0xa5, 0x8b, 0x08, 0xfd, 0x00, 0x78, 0x40, 0x1b, 0xc5, 0x3b, // | - WPA Station/Supplicant SNonce value (32 byte value)
        0xb2, 0xaf, 0xef, 0x3a, 0x1a, 0xfd,                                           // |
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, // Key IV (16 bytes)
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Key RSC (8 bytes)
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Key ID (8 bytes)
      0xd4, 0x12, 0x6e, 0xe7, 0x45, 0x78, 0x84, 0x81, 0xb5, 0x70, 0xfa, 0x0f, 0x90, 0x8e, 0x60, 0xc3, // Key MIC (16 bytes)
      0x00, 0x16, // WPA Key Data Length - 22 (2 bytes) (Represents length of the following WPA Key Data field)
      // Following is WPA Key Data. This contains information regarding the key type used, WPA version, etc.
      // It is not featured in message 1 or 4, and is encrypted in message 3
      // After observing other WPA2 networks in my area, I can say the following data seems to be common among the other handshake messages I've gathered:
        0x30, 0x14, 0x01, 0x00, 0x00, 0x0f, 0xac, 0x02, 0x01, 0x00, 0x00, 0x0f, 0xac, 0x04, 0x01, 0x00,
        0x00, 0x0f, 0xac, 0x02, 0x00, 0x00 // Too lazy to detail specifics of each byte; use wireshark if interested, it's gotten me this far.
      };
uint8_t key3Temp[235] = {
      0x08, 0x02, // Frame Control (QoS Data Frame). For regular data frame, use 0x08, 0x02
      0x3a, 0x01, // Duration ID
      0x60, 0x01, 0x02, 0x03, 0x04, 0x05, // Reciever (STA) BSSID
      0x00, 0x01, 0x02, 0x03, 0x04, 0x05, // AP/Transmitter Address
      0x00, 0x01, 0x02, 0x03, 0x04, 0x05, // AP Address once again (Source Hardware Address, this value is ALWAYS AP BSSID)
      0x10, 0x00, // Sequence Number (Seq-ctl) -----****
      // LLC (Logical-Link Control) Segment - Seems to be consistent between QoS and reg Data frames
      // The LLC Segment stays consistent among all key messages
      0xaa, 0xaa, // DSAP, SSAP
      0x03, // Control Field?
      0x00, 0x00, 0x00, // Organization code
      0x88, 0x8e, // Type: 802.1X Authentication
      // 802.1X Authentication Segment
      0x02, // Version: 2 - 802.1X-2004 (0x01 is 802.1X-2001, either can be used)
      0x03, // Type - Key
      0x00, 0xc7, // EAPOL Length (Length of following packet information)
      0x02, // Key Descriptor Type (RSN Key)
      0x13, 0xca, // Key Information (HMAC SHA-1 MIC, Key Set = 1)
      0x00, 0x10, // Key Length = 16
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, // Replay Counter = 2 (Acts as a sort of identifier that matches with message 4)
        0x14, 0xac, 0x4b, 0x04, 0x87, 0x20, 0xf2, 0xdc, 0x38, 0x12, 0x1a, 0x73, 0x01, // |
        0xb7, 0x96, 0x19, 0x40, 0x4c, 0xce, 0x67, 0x62, 0x4a, 0x96, 0x0a, 0x14, 0x9d, // | - WPA Authenticator ANonce value (32 byte value)
        0x64, 0x01, 0xff, 0xd3, 0x36, 0x3d,                                           // | ^ This value is repeated from message 1
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, // Key IV (16 bytes)
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Key RSC (8 bytes) - Starting sequence number (Usually 0)
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Key ID (8 bytes) - Always 0
      0x36, 0x5e, 0xb4, 0xdc, 0x81, 0x43, 0xe2, 0xed, 0x63, 0xba, 0x4d, 0x92, 0xfd, 0xb2, 0xe3, 0x65, // Key MIC (16 bytes) - Unique to each message
      0x00, 0x68, // WPA Key Data Length - 104 (2 bytes) (Represents length of the following WPA Key Data field)
        0x97, 0xdf, 0xcb, 0xf3, 0x2d, 0x52, 0x80, 0x0d, 0xc1, 0x05, 0xd0, 0xb4, 0x2b, 0xa3, 0x1c, 0xbe,
        0x49, 0xbb, 0x87, 0x7d, 0x08, 0x3a, 0x06, 0x8b, 0x9b, 0x3b, 0xce, 0x96, 0xe8, 0xa3, 0x06, 0x44,
        0xf2, 0xf0, 0xab, 0xdf, 0xd5, 0x3f, 0x4a, 0xbb, 0x96, 0x4f, 0x44, 0x4f, 0x1f, 0xc3, 0x0c, 0xf1,
        0xe5, 0x1a, 0xff, 0x55, 0x08, 0x7d, 0x8b, 0xe7, 0xbd, 0x8d, 0x38, 0xbd, 0xae, 0xe9, 0xe3, 0x24,
        0x68, 0x97, 0xe6, 0x67, 0xb6, 0x34, 0xec, 0xd9, 0x42, 0x68, 0x8e, 0x0b, 0x44, 0xb8, 0x6e, 0x77,
        0x59, 0xdf, 0xe8, 0x3a, 0x8e, 0xa9, 0xf8, 0xa9, 0xa7, 0xc0, 0x31, 0x70, 0x39, 0x1e, 0xcf, 0xb7,
        0x2f, 0xb4, 0x7c, 0xa3, 0x8f, 0x49, 0x67, 0xbe // - WPA Key Data (Encrypted GTK)
      };
// ^ Message 3 contains a WPA Key Data field which contains the encrypted GTK (Group Transient Key) for multicast communications
// For the purposes of this project, this value will be randomized to a 104 byte value keeping speed and ease-of-use in mind
// ^ Implementing the necessary HMAC, PBKDF2, etc. cryptographic algorithms are a pain... Too lazy.
// http://etutorials.org/Networking/802.11+security.+wi-fi+protected+access+and+802.11i/Part+II+The+Design+of+Wi-Fi+Security/Chapter+10.+WPA+and+RSN+Key+Hierarchy/Details+of+Key+Derivation+for+WPA/
// OpenSSL has a cryptography library that I may use if I decide to write a similar program for linux devices.

uint8_t key4Temp[131] = {
      0x08, 0x01, // Frame Control (QoS Data Frame). For regular data frame, use 0x08, 0x01
      0x3a, 0x01, // Duration ID
      0x00, 0x01, 0x02, 0x03, 0x04, 0x05, // Reciever (AP) BSSID
      0x60, 0x01, 0x02, 0x03, 0x04, 0x05, // STA/Transmitter Address
      0x00, 0x01, 0x02, 0x03, 0x04, 0x05, // AP Address once again (Destination Hardware Address, this value is ALWAYS AP BSSID)
      0x10, 0x00, // Sequence Number (Seq-ctl) -----****
      // LLC (Logical-Link Control) Segment - Seems to be consistent between QoS and reg Data frames
      // The LLC Segment stays consistent among all key messages
      0xaa, 0xaa, // DSAP, SSAP
      0x03, // Control Field?
      0x00, 0x00, 0x00, // Organization code
      0x88, 0x8e, // Type: 802.1X Authentication
      // 802.1X Authentication Segment
      0x01, // Version: 2 - 802.1X-2001 (0x02 is 802.1X-2004, either can be used)
      0x03, // Type - Key
      0x00, 0x5f, // EAPOL Length (Length of following packet information)
      0x02, // Key Descriptor Type (RSN Key)
      0x03, 0x0a, // Key Information (HMAC SHA-1 MIC, Key Set = 1)
      0x00, 0x00, // Key Length = 0
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, // Replay Counter = 2 (Acts as a sort of identifier that matches with message 4)
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // | Nonce value (0)
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // |
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, // Key IV (16 bytes)
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Key RSC (8 bytes) - Starting sequence number (Usually 0)
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Key ID (8 bytes) - Always 0
      0xbd, 0x99, 0x36, 0x7f, 0xb4, 0x5b, 0xd4, 0xae, 0x42, 0xb2, 0xdb, 0x94, 0x22, 0x2b, 0x0b, 0x5d, // Key MIC (16 bytes) - Unique to each message
      0x00, 0x00 // WPA Key Data Length - 0 (2 bytes)
      };

#endif
