/*
    Cinnamon UCI chess engine
    Copyright (C) Giuseppe Cannella

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <fstream>
#include "Eval.h"

class OpenBook : public Singleton<OpenBook> {
    friend class Singleton<OpenBook>;

public:

    virtual ~OpenBook();

    bool load(const string &fileName = "cinnamon.bin");

    string search(const string &fen);

private:
    OpenBook();

    typedef struct {
        u64 key;
        unsigned short move;
        unsigned short weight;
        unsigned learn;
    } entry_t;

    FILE *openBookFile;

    u64 createKey(const string &fen);

    int intFromFile(int l, u64 *r);

    int entryFromFile(entry_t *entry);

    int findKey(u64 key, entry_t *entry);

    void moveToString(char move_s[6], unsigned short move);

    void dispose();

    u64 *Random64;
};

