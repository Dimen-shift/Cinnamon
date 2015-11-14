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


#include "WrapperCinnamon.h"

vector<string> WrapperCinnamon::getSuccessorsFen(const string &fen, const int depth) {
    PerftThread a;
    return a.getSuccessorsFen(fen, depth);
}

pair<int,int> WrapperCinnamon::getNtasks(const string &fen, const int reduce) {
    PerftThread a;
    int tasks =0;
    for(int i=1;i<=reduce;i++) {
        tasks = a.getSuccessorsFen(fen, i).size();
        if(tasks>=5000)return pair<int,int>(i,tasks);
    }
    pair<int,int>(reduce,tasks);
}

bool WrapperCinnamon::isValid(const string &fen) {
    ChessBoard a;
    if (a.loadFen(fen) == -1)return false;
    return true;
}
