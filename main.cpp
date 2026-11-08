#include <bits/stdc++.h>
#include <cstdint>
#include <vector>
using namespace std;

/*** bit operations ***/
uint32_t ROTR(uint32_t x, int n) { return (x >> n) | (x << (32 - n)); }
uint32_t SIGMA0(uint32_t x) { return ROTR(x, 2) ^ ROTR(x, 13) ^ ROTR(x, 22); }
uint32_t SIGMA1(uint32_t x) { return ROTR(x, 6) ^ ROTR(x, 11) ^ ROTR(x, 25); }
uint32_t sigma0(uint32_t x) { return ROTR(x, 7) ^ ROTR(x, 18) ^ (x >> 3); }
uint32_t sigma1(uint32_t x) { return ROTR(x, 17) ^ ROTR(x, 19) ^ (x >> 10); }
uint32_t Ch(uint32_t x, uint32_t y, uint32_t z) { return (x & y) ^ (~x & z); }
uint32_t Maj(uint32_t x, uint32_t y, uint32_t z) {
    return (x & y) ^ (x & z) ^ (y & z);
}

/*** frac parts of roots of primes ***/
constexpr int primes[] = {2,   3,   5,   7,   11,  13,  17,  19,  23,  29,  31,
                          37,  41,  43,  47,  53,  59,  61,  67,  71,  73,  79,
                          83,  89,  97,  101, 103, 107, 109, 113, 127, 131, 137,
                          139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193,
                          197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257,
                          263, 269, 271, 277, 281, 283, 293, 307, 311};
vector<uint32_t> generateConstants() {
    vector<uint32_t> K;
    for (int x = 0; K.size() < 64; ++x) {
        long double c = cbrtl((long double)primes[x]);
        long double frac = c - floor(c);
        K.push_back((uint32_t)(frac * 4294967296.0L));
    }
    return K;
}
vector<uint32_t> genetateInitialHash() {
    vector<uint32_t> H;
    for (int x = 0; H.size() < 8; ++x) {
        long double c = sqrtl((long double)primes[x]);
        long double frac = c - floor(c);
        H.push_back((uint32_t)(frac * 4294967296.0L));
    }
    return H;
}

/*** misc conversion functions ***/
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
// ints.size() must = 16
vector<uint32_t> generateWords(const vector<uint32_t> &ints) {
    vector<uint32_t> w;
    for (auto a : ints) {
        w.push_back(a);
    }
    for (int i = 16; i < 64; ++i) {
        uint32_t s0 = sigma0(w[i - 15]);
        uint32_t s1 = sigma1(w[i - 2]);
        w.push_back((w[i - 16] + s0 + w[i - 7] + s1));
    }
    return w;
}

/*** main ***/
int main() {
    string line;
    vector<uint32_t> K = generateConstants();
    vector<uint32_t> H = genetateInitialHash();
    while (getline(cin, line)) {
        istringstream in(line);
        string s;
        if (!(in >> s)) {
            continue;
        } else {
            vector<uint32_t> v;
            for (int i = 0; i < 16; ++i) {
                v.push_back(hex2int(s.substr(i * 8, 8)));
            }
            vector<uint32_t> r = generateWords(v);
            for (int i = 0; i < 64; ++i) {
                cout << "W[" << i << "]=" << int2hex(r[i]) << '\n';
            }
        }
    }
}
