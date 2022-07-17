// Copyright (c) 2018 The LiquidLabs Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef MARIA_INVALID_H
#define MARIA_INVALID_H

#include <set>
#include <string>

class COutPoint;
class UniValue;

namespace invalid_out
{
    extern std::set<COutPoint> setInvalidOutPoints;

    UniValue read_json(const std::string& jsondata);

    bool ContainsOutPoint(const COutPoint& out);
    bool LoadOutpoints();
}

#endif //MARIA_INVALID_H
