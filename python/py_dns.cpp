#include <pybind11/pybind11.h>
#include "dns.h"
#include "py_common.h"

namespace py = pybind11;

void init_dns(py::module& m)
{
    py::enum_<CDNS::OpCodes>(m, "OpCodes")
        .value("OP_QUERY", CDNS::OpCodes::OP_QUERY)
        .value("OP_IQUERY", CDNS::OpCodes::OP_IQUERY)
        .value("OP_STATUS", CDNS::OpCodes::OP_STATUS)
        .value("OP_NOTIFY", CDNS::OpCodes::OP_NOTIFY)
        .value("OP_UPDATE", CDNS::OpCodes::OP_UPDATE)
        .value("OP_DSO", CDNS::OpCodes::OP_DSO)
        .export_values();

    m.attr("OpCodesDefault") = &CDNS::OpCodesDefault;

    py::enum_<CDNS::RrTypes>(m, "RrTypes")
        .value("A", CDNS::RrTypes::A)
        .value("NS", CDNS::RrTypes::NS)
        .value("MD", CDNS::RrTypes::MD)
        .value("MF", CDNS::RrTypes::MF)
        .value("CNAME", CDNS::RrTypes::CNAME)
        .value("SOA", CDNS::RrTypes::SOA)
        .value("MB", CDNS::RrTypes::MB)
        .value("MG", CDNS::RrTypes::MG)
        .value("MR", CDNS::RrTypes::MR)
        .value("NULL_R", CDNS::RrTypes::NULL_R)
        .value("WKS", CDNS::RrTypes::WKS)
        .value("PTR", CDNS::RrTypes::PTR)
        .value("HINFO", CDNS::RrTypes::HINFO)
        .value("MINFO", CDNS::RrTypes::MINFO)
        .value("MX", CDNS::RrTypes::MX)
        .value("TXT", CDNS::RrTypes::TXT)
        .value("RP", CDNS::RrTypes::RP)
        .value("AFSDB", CDNS::RrTypes::AFSDB)
        .value("X25", CDNS::RrTypes::X25)
        .value("ISN", CDNS::RrTypes::ISDN)
        .value("RT", CDNS::RrTypes::RT)
        .value("NSAP", CDNS::RrTypes::NSAP)
        .value("NSAP_PTR", CDNS::RrTypes::NSAP_PTR)
        .value("SIG", CDNS::RrTypes::SIG)
        .value("KEY", CDNS::RrTypes::KEY)
        .value("PX", CDNS::RrTypes::PX)
        .value("GPOS", CDNS::RrTypes::GPOS)
        .value("AAAA", CDNS::RrTypes::AAAA)
        .value("LOC", CDNS::RrTypes::LOC)
        .value("NXT", CDNS::RrTypes::NXT)
        .value("EID", CDNS::RrTypes::EID)
        .value("NIMLOC", CDNS::RrTypes::NIMLOC)
        .value("SRV", CDNS::RrTypes::SRV)
        .value("ATMA", CDNS::RrTypes::ATMA)
        .value("NAPTR", CDNS::RrTypes::NAPTR)
        .value("KX", CDNS::RrTypes::KX)
        .value("CERTIFICATE", CDNS::RrTypes::CERTIFICATE)
        .value("A6", CDNS::RrTypes::A6)
        .value("DNAME", CDNS::RrTypes::DNAME)
        .value("SINK", CDNS::RrTypes::SINK)
        .value("OPT", CDNS::RrTypes::OPT)
        .value("APL", CDNS::RrTypes::APL)
        .value("DS", CDNS::RrTypes::DS)
        .value("SSHFP", CDNS::RrTypes::SSHFP)
        .value("IPSECKEY", CDNS::RrTypes::IPSECKEY)
        .value("RRSIG", CDNS::RrTypes::RRSIG)
        .value("NSEC", CDNS::RrTypes::NSEC)
        .value("DNSKEY", CDNS::RrTypes::DNSKEY)
        .value("DHCID", CDNS::RrTypes::DHCID)
        .value("NSEC3", CDNS::RrTypes::NSEC3)
        .value("NSEC3PARAM", CDNS::RrTypes::NSEC3PARAM)
        .value("TLSA", CDNS::RrTypes::TLSA)
        .value("SMIMEA", CDNS::RrTypes::SMIMEA)
        .value("HIP", CDNS::RrTypes::HIP)
        .value("NINFO", CDNS::RrTypes::NINFO)
        .value("RKEY", CDNS::RrTypes::RKEY)
        .value("TALINK", CDNS::RrTypes::TALINK)
        .value("CDS", CDNS::RrTypes::CDS)
        .value("CDNSKEY", CDNS::RrTypes::CDNSKEY)
        .value("OPENPGPKEY", CDNS::RrTypes::OPENPGPKEY)
        .value("CSYNC", CDNS::RrTypes::CSYNC)
        .value("ZONEMD", CDNS::RrTypes::ZONEMD)
        .value("SVCB", CDNS::RrTypes::SVCB)
        .value("HTTPS", CDNS::RrTypes::HTTPS)
        .value("SPF", CDNS::RrTypes::SPF)
        .value("UINFO", CDNS::RrTypes::UINFO)
        .value("UID", CDNS::RrTypes::UID)
        .value("GID", CDNS::RrTypes::GID)
        .value("UNSPEC", CDNS::RrTypes::UNSPEC)
        .value("NID", CDNS::RrTypes::NID)
        .value("L32", CDNS::RrTypes::L32)
        .value("L64", CDNS::RrTypes::L64)
        .value("LP", CDNS::RrTypes::LP)
        .value("EUI48", CDNS::RrTypes::EUI48)
        .value("EUI64", CDNS::RrTypes::EUI64)
        .value("TKEY", CDNS::RrTypes::TKEY)
        .value("TSIG", CDNS::RrTypes::TSIG)
        .value("IXFR", CDNS::RrTypes::IXFR)
        .value("AXFR", CDNS::RrTypes::AXFR)
        .value("MAILB", CDNS::RrTypes::MAILB)
        .value("MAILA", CDNS::RrTypes::MAILA)
        .value("TYPE_ANY", CDNS::RrTypes::TYPE_ANY)
        .value("URI", CDNS::RrTypes::URI)
        .value("CAA", CDNS::RrTypes::CAA)
        .value("AVC", CDNS::RrTypes::AVC)
        .value("DOA", CDNS::RrTypes::DOA)
        .value("AMTRELAY", CDNS::RrTypes::AMTRELAY)
        .value("TA", CDNS::RrTypes::TA)
        .value("DLV", CDNS::RrTypes::DLV)
        .value("NSEC3PARAMS", CDNS::RrTypes::NSEC3PARAMS)
        .value("CERT", CDNS::RrTypes::CERT)
        .export_values();

    m.attr("RrTypesDefault") = &CDNS::RrTypesDefault;
}
