#include <bits/stdc++.h>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <sstream>
using namespace std;

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
        } else if (cmd == "PACK") {
            string x;
            in >> x;
            uint32_t i = hex2int(x);
            cout << x << "\n";
        } else if (cmd == "UNPACK") {
            string x;
            in >> x;
            uint32_t i = hex2int(x);
            for (int i = 3; i >= 0; --i) {
                if (i != 3) {
                    cout << ' ';
                }
                cout << setw(2) << setfill('0') << x.substr(6 - i * 2, 2);
            }
            cout << "\n";
        }
    }
}
