#pragma once

#include <cstdint>

namespace CDNS {

    /**
     * @enum OpCodes
     * @brief All supported DNS OpCodes
     */
    enum class OpCodes : uint8_t
    {
        OP_QUERY = 0,
        OP_IQUERY,
        OP_STATUS,
        OP_NOTIFY = 4,
        OP_UPDATE,
        OP_DSO
    };

    /**
     * @enum RrTypes
     * @brief All supported Resource records types
     */
    enum class RrTypes : uint16_t
    {
        A = 1,
        NS,
        MD,
        MF,
        CNAME,
        SOA,
        MB,
        MG,
        MR,
        NULL_R,
        WKS,
        PTR,
        HINFO,
        MINFO,
        MX,
        TXT,
        RP,
        AFSDB,
        X25,
        ISDN,
        RT,
        NSAP,
        NSAP_PTR,
        SIG,
        KEY,
        PX,
        GPOS,
        AAAA,
        LOC,
        NXT,
        EID,
        NIMLOC,
        SRV,
        ATMA,
        NAPTR,
        KX,
        CERTIFICATE,
        A6,
        DNAM,
        SINK,
        OPT,
        APL,
        DS,
        SSHFP,
        IPSECKEY,
        RRSIG,
        NSEC,
        DNSKEY,
        DHCID,
        NSEC3,
        NSEC3PARAM,
        TLSA,
        HIP = 55,
        NINFO,
        RKEY,
        TALINK,
        CDS,
        SPF = 99,
        UINFO,
        UID,
        GID,
        UNSPEC,
        NID,
        L32,
        L64,
        LP,
        EU148,
        EUI64,
        TKEY = 249,
        TSIG,
        IXFR,
        AXFR,
        MAILB,
        MAILA,
        TYPE_ANY,
        URI,
        CAA,
        TA = 32768,
        DLV,

        NSEC3PARAMS = NSEC3PARAM,
        CERT = CERTIFICATE
    };
}