// Project Euler problem 59. XOR decryption.
#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <numeric>
#include <unordered_map>
#include <vector>

using Ciphertext = std::vector<int8_t>;

Ciphertext get_ciphertext_from_file(std::string filename)
{
    Ciphertext ciphertext;
    std::ifstream ifs(filename);
    int val;
    while (ifs >> val)
    {
        assert(val <= 127);
        ciphertext.push_back(static_cast<int8_t>(val));
        if (ifs.peek() == ',')
        {
            ifs.ignore();
        }
    }
    return ciphertext;
}

char get_key_char_from_ciphertext(const Ciphertext &ciphertext)
{
    // Get frequencies
    std::unordered_map<int8_t, int> um;
    for (const auto c : ciphertext)
    {
        auto it = um.find(c);
        if (it == um.end())
        {
            um.insert({c, 1});
        }
        else
        {
            it->second += 1;
        }
    }

    // Sort by frequency, most frequent at the front.
    std::vector<std::pair<uint8_t, int>> v;
    for (const auto p : um)
    {
        v.push_back(p);
    }
    std::sort(begin(v), end(v), [](const auto &p1, const auto &p2) {
        return (p1.second > p2.second);
    });

    assert(v.size() > 2);
    // Print top two.
    std::cout << "Top two values: "
              << static_cast<int16_t>(v[0].first) << ", count: " << v[0].second << "; "
              << static_cast<int16_t>(v[0].second) << ", count: " << v[1].second << "\n";

    const int8_t key_for_space = v[0].first ^ ' ';
    std::cout << "Key for space: " << static_cast<int16_t>(key_for_space)
              << ", " << static_cast<int16_t>(v[0].first ^ key_for_space)
              << ", " << static_cast<int16_t>(v[1].first ^ key_for_space)
              << "\n";

    const int8_t key_for_e = v[0].first ^ 'e';
    std::cout << "Key for e: " << static_cast<int16_t>(key_for_e)
              << ", " << static_cast<int16_t>(v[0].first ^ key_for_e)
              << ", " << static_cast<int16_t>(v[1].first ^ key_for_e)
              << "\n";

    // prefer space. return that one.
    return key_for_space;
}

std::string get_cleartext(const Ciphertext &ciphertext, const std::string &key)
{
    std::string s;
    size_t keyindex = 0;
    for (const auto c : ciphertext)
    {
        s += static_cast<char>(c ^ key[keyindex++]);
        if (keyindex >= key.size())
        {
            keyindex = 0;
        }
    }
    return s;
}

int64_t pe59()
{
    const Ciphertext ciphertext = get_ciphertext_from_file("p059_cipher.txt");
    const size_t KEY_LENGTH = 3;
    std::string key;
    for (size_t i = 0; i < KEY_LENGTH; ++i)
    {
        Ciphertext ct;
        for (size_t j = i; j < ciphertext.size(); j += KEY_LENGTH)
        {
            ct.push_back(ciphertext[j]);
        }
        key += get_key_char_from_ciphertext(ct);
    }
    const auto cleartext = get_cleartext(ciphertext, key);
    std::cout << cleartext << "\n";
    return std::accumulate(begin(cleartext), end(cleartext), static_cast<int64_t>(0), [&](const auto c1, const auto c2) {
        return static_cast<int64_t>(c1) + static_cast<int64_t>(c2);
    });
}

int main()
{
    std::cout << pe59() << "\n";
    return 0;
}
