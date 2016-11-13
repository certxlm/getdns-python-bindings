import unittest
import sys, platform


un = platform.uname()
d = 'lib.' + un[0].lower() + '-' + un[4] + '-' + '.'.join(platform.python_version().split('.')[:2])
sys.path.append(d)

import getdns


class TestGetdnsMethods(unittest.TestCase):

    def test_context(self):
        c = getdns.Context()
        self.assertIsNotNone(c)
        del(c)

    def test_bogus_attribute(self):
        c = getdns.Context()
        with self.assertRaises(AttributeError, c.asdf) as e:

        except
        del(c)
        
    def test_append_name(self):
        c = getdns.Context()
        c.append_name = getdns.APPEND_NAME_NEVER
        self.assertEqual(c.append_name, getdns.APPEND_NAME_NEVER)
        del(c)

    def test_dns_root_servers(self):
        c = getdns.Context()
        addrs = [ { 'address_type': 'IPv4', 'address_data': '127.0.0.254' } ]
        c.dns_root_servers = addrs
        self.assertEqual(c.dns_root_servers, addrs)
        del(c)

    def test_dns_transport_list(self):
        c = getdns.Context()
        transports = [ getdns.TRANSPORT_TLS, getdns.TRANSPORT_UDP, getdns.TRANSPORT_TCP ]
        c.dns_transport_list = transports
        self.assertEqual(c.dns_transport_list, transports)
        del(c)

    def test_sync_address(self):
        c = getdns.Context()
        c.resolution_type=getdns.RESOLUTION_STUB
        r = c.address('www.getdnsapi.net')
        self.assertEqual(r.status, getdns.RESPSTATUS_GOOD)
        self.assertTrue('185.49.141.37' in [ x['address_data'] for x in r.just_address_answers ])
        del(c)
        del(r)

    def test_sync_service(self):
        c = getdns.Context()
        c.resolution_type=getdns.RESOLUTION_STUB
        r = c.service('_xmpp-server._tcp.jabber.org')
        self.assertEqual(r.status, getdns.RESPSTATUS_GOOD)
        del(c)
        del(r)

    def test_sync_hostname(self):
        c = getdns.Context()
        c.resolution_type=getdns.RESOLUTION_STUB
        r = c.hostname( { 'address_type': 'IPv4', 'address_data': '185.49.141.37' } )
        self.assertEqual(r.status, getdns.RESPSTATUS_GOOD)
        del(c)
        del(r)

    def test_sync_general(self):
        c = getdns.Context()
        c.resolution_type=getdns.RESOLUTION_STUB
        r = c.general('nlnetlabs.nl', request_type=getdns.RRTYPE_NS)
        self.assertEqual(r.status, getdns.RESPSTATUS_GOOD)
        del(c)
        del(r)


if __name__ == "__main__":
    unittest.main(verbosity=2)
