#include <bits/stdc++.h>
#include <charconv>
#include <cstdint>
#include <ios>
#include <stdexcept>
#include <string>
#include <system_error>
using namespace std;

// TODO (bit-tricks): implement per the lesson description.

uint32_t hex2int(const string &hex) {
    uint32_t value;
    auto [ptr, ec] = from_chars(hex.data(), hex.data() + hex.size(), value, 16);
    if (hex.empty() || ec != std::errc{} || ptr != hex.data() + hex.size()) {
        throw std::invalid_argument("Invalid hex string");
    }
    return value;
}
string int2hex(uint32_t value) {
    char buffer[9];
    auto [ptr, ec] = to_chars(buffer, buffer + 8, value, 16);
    if (ec != errc{}) {
        throw runtime_error("Hex conversion failed");
    }
    string result(buffer, ptr);
    result.insert(0, 8 - result.size(), '0');

    return result;
}
uint32_t ROTR(uint32_t x, int n) { return (x >> n) | (x << (32 - n)); }
uint32_t SIGMA0(uint32_t x) { return ROTR(x, 2) ^ ROTR(x, 13) ^ ROTR(x, 22); }
uint32_t SIGMA1(uint32_t x) { return ROTR(x, 6) ^ ROTR(x, 11) ^ ROTR(x, 25); }
uint32_t sigma0(uint32_t x) { return ROTR(x, 7) ^ ROTR(x, 18) ^ (x >> 3); }
uint32_t sigma1(uint32_t x) { return ROTR(x, 17) ^ ROTR(x, 19) ^ (x >> 10); }
uint32_t Ch(uint32_t x, uint32_t y, uint32_t z) { return (x & y) ^ (~x & z); }
uint32_t Maj(uint32_t x, uint32_t y, uint32_t z) {
    return (x & y) ^ (x & z) ^ (y & z);
}

int main() {
    string line;
    while (getline(cin, line)) {
        istringstream in(line);
        string cmd;
        if (!(in >> cmd)) {
            continue;
        } else if (cmd == "ROTR") {
            string h;
            int n;
            in >> h >> n;
            uint32_t res = ROTR(hex2int(h), n);
            cout << int2hex(res);
        } else if (cmd == "SIGMA0") {
            string h;
            in >> h;
            uint32_t res = SIGMA0(hex2int(h));
            cout << int2hex(res);
        } else if (cmd == "SIGMA1") {
            string h;
            in >> h;
            uint32_t res = SIGMA1(hex2int(h));
            cout << int2hex(res);
        } else if (cmd == "sigma0") {
            string h;
            in >> h;
            uint32_t res = sigma0(hex2int(h));
            cout << int2hex(res);
        } else if (cmd == "sigma1") {
            string h;
            in >> h;
            uint32_t res = sigma1(hex2int(h));
            cout << int2hex(res);
        } else if (cmd == "CH") {
            string x;
            string y;
            string z;
            in >> x >> y >> z;
            uint32_t res = Ch(hex2int(x), hex2int(y), hex2int(z));
            cout << int2hex(res);
        } else if (cmd == "MAJ") {
            string x;
            string y;
            string z;
            in >> x >> y >> z;
            uint32_t res = Maj(hex2int(x), hex2int(y), hex2int(z));
            cout << int2hex(res);
        }
    }
}
