#include <iostream>
#include <vector>

class Board;  // 先に宣言しておく

// Move クラス
class Move {
public:
    int row;      // 縦軸
    int col;      // 横軸
    int player;   // -1: 人間, -2: NPC, 0: 空いている
    int expectedValue;  // 勝利への期待値 (1-5)
    // 追加する変数（盤面の数字を格納）
    // int boardNum; // 盤面での数字を格納

    // コンストラクタ
    Move(int r, int c, int p, int ev)
        : row(r), col(c), player(p), expectedValue(ev) {}
};

// NPC クラス
class NPC {
private:
    std::vector<Move> moveList;  // NPC専用のMoveリスト（内部でのみ使用）

public:
    NPC() {}

    // NPCの次の手を選ぶロジック
    Move chooseMove(Board& board);

private:
    // 人間の勝利が確定する手を取得
    std::vector<Move> getHumanVictoryMoves(Board& board) const;

    // 最も接続している場所を取得（連続している場所）
    const Move* getBestConnectedMove(const Board& board, const Move& move) const;

    // 最も期待値が高い場所を選ぶ
    Move getBestMove(const Board& board) const;

    // 実際に手を盤面に置く
    void placeMove(Board& board, const Move& move);
};

// Board クラス
class Board {
public:
    std::vector<Move> moveList;

    // Boardの状態を表示する（デバッグ用）
    void printBoard() const {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                bool found = false;
                for (const auto& move : moveList) {
                    if (move.row == i && move.col == j) {
                        std::cout << (move.player == -1 ? "X" : (move.player == -2 ? "O" : ".")) << " ";
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    std::cout << ". ";
                }
            }
            std::cout << std::endl;
        }
    }

    // ゲームが終了したかチェックする（デバッグ用）
    bool checkWin(int player) const {
        for (int i = 0; i < 3; i++) {
            // 横チェック
            if (moveList[i * 3].player == player && moveList[i * 3 + 1].player == player && moveList[i * 3 + 2].player == player)
                return true;
            // 縦チェック
            if (moveList[i].player == player && moveList[i + 3].player == player && moveList[i + 6].player == player)
                return true;
        }
        // 斜めチェック
        if (moveList[0].player == player && moveList[4].player == player && moveList[8].player == player)
            return true;
        if (moveList[2].player == player && moveList[4].player == player && moveList[6].player == player)
            return true;

        return false;
    }
};

// NPCの次の手を選ぶロジック
Move NPC::chooseMove(Board& board) {
    // まず、人間の勝利を妨害する手を選ぶ
    auto humanVictoryMoves = getHumanVictoryMoves(board);
    if (!humanVictoryMoves.empty()) {
        for (const auto& victoryMove : humanVictoryMoves) {
            const Move* connectedMove = getBestConnectedMove(board, victoryMove);
            if (connectedMove) {
                // 連続している手が見つかればその手を選ぶ
                placeMove(board, *connectedMove);
                return *connectedMove;
            }
        }
    }

    // 2. 次に自分が勝つ手を選ぶ
    for (const auto& move : board.moveList) {
        if (move.player == -2 && move.expectedValue == 5) {  // NPCの勝利が確定する場所
            placeMove(board, move);
            return move;
        }
    }

    // 3. 最後に期待値が高い場所を選ぶ
    Move bestMove = getBestMove(board);
    placeMove(board, bestMove);
    return bestMove;
}

// 人間の勝利が確定する手を取得
std::vector<Move> NPC::getHumanVictoryMoves(Board& board) const {
    std::vector<Move> victoryMoves;
    for (const auto& move : board.moveList) {
        if (move.player == -1 && move.expectedValue == 5) {  // 人間の勝利確定場所
            victoryMoves.push_back(move);
        }
    }
    return victoryMoves;
}

// 最も接続している場所を取得（連続している場所）
const Move* NPC::getBestConnectedMove(const Board& board, const Move& move) const {
    for (const auto& existingMove : board.moveList) {
        if (existingMove.row == move.row && existingMove.col == move.col && existingMove.expectedValue > 1) {
            return &existingMove;  // 連続している場所の判定（期待値が1より高いもの）
        }
    }
    return nullptr;
}

// 最も期待値が高い場所を選ぶ
Move NPC::getBestMove(const Board& board) const {
    int highestValue = -1;
    Move bestMove(0, 0, 0, 0);
    for (const auto& move : board.moveList) {
        if (move.expectedValue > highestValue) {
            highestValue = move.expectedValue;
            bestMove = move;
        }
    }
    return bestMove;
}

// 実際に手を盤面に置く
void NPC::placeMove(Board& board, const Move& move) {
    board.moveList.push_back(move);
}

int main() {
    // ボードとNPCを初期化
    Board board;
    NPC npc;

    // サンプルの盤面状態（デバッグ用）
    board.moveList.push_back(Move(0, 0, -1, 3)); // 人間の手
    board.moveList.push_back(Move(1, 1, -1, 4)); // 人間の手
    board.moveList.push_back(Move(2, 2, -2, 1)); // NPCの手

    // NPCの次の手を選択
    Move npcMove = npc.chooseMove(board);

    // 盤面の表示
    board.printBoard();
    std::cout << "NPC chose: (" << npcMove.row << ", " << npcMove.col << ")\n";

    return 0;
}
