#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

// Moveクラス（手の情報を保持）
class Move {
public:
    int row;              // 縦軸
    int col;              // 横軸
    int player;           // プレイヤー（-1: 人間, -2: NPC）
    int expectedValue;    // 勝利への期待値（1〜5）
    Move* lastConnectedMove; // 直近の連続している手の情報（連続している場合）

    // コンストラクタ
    Move(int r, int c, int p, int e, Move* lastMove = nullptr)
        : row(r), col(c), player(p), expectedValue(e), lastConnectedMove(lastMove) {}

    void printMove() const {
        std::cout << "Row: " << row << ", Col: " << col
            << ", Player: " << (player == -1 ? "Human" : "NPC")
            << ", Expected Value: " << expectedValue;
        if (lastConnectedMove != nullptr) {
            std::cout << ", Last Connected Move: ("
                << lastConnectedMove->row << ", "
                << lastConnectedMove->col << ")";
        }
        std::cout << std::endl;
    }
};

// Boardクラス（盤面の状態と評価を管理）
class Board {
public:
    const int SIZE = 15; // 盤面サイズ（15x15）
    std::vector<std::vector<int>> board; // 盤面の状態（0: 空, -1: 人間, -2: NPC）

    std::vector<Move> moveList;  // Moveクラスのリスト（過去の手情報）

    Board() {
        board.resize(SIZE, std::vector<int>(SIZE, 0)); // 盤面の初期化（0で全て空）
    }

    // 盤面の状態を表示
    void printBoard() const {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                char c = '.';
                if (board[i][j] == -1) c = 'O'; // 人間の手
                else if (board[i][j] == -2) c = 'X'; // NPCの手
                std::cout << c << " ";
            }
            std::cout << std::endl;
        }
    }

    // 盤面に手を置く
    bool placeMove(int row, int col, int player) {
        if (board[row][col] == 0) { // もしその場所が空いていれば
            board[row][col] = player;
            return true;
        }
        return false;
    }

    // Moveオブジェクトをリストに追加
    void addMove(Move move) {
        moveList.push_back(move);
    }

    // 盤面の特定位置に対する評価を行う
    int evaluatePosition(int row, int col, int player) {
        // プレイヤーが置いた場合の横、縦、斜め方向の評価
        int score = 0;

        // プレイヤーの手をカウント
        score += checkLine(row, col, 0, 1, player);  // 横
        score += checkLine(row, col, 1, 0, player);  // 縦
        score += checkLine(row, col, 1, 1, player);  // 斜め（右下）
        score += checkLine(row, col, 1, -1, player); // 斜め（左下）

        return score;
    }

    // 特定の方向（dx, dy）に対する評価を計算
    int checkLine(int row, int col, int dx, int dy, int player) {
        int count = 0;
        int oppositePlayer = (player == -2) ? -1 : -2;

        // 同じプレイヤーの手をカウント
        for (int i = -4; i <= 4; ++i) {
            int r = row + i * dx;
            int c = col + i * dy;

            // 盤面の範囲外か、相手の手があった場合は無視
            if (r < 0 || r >= SIZE || c < 0 || c >= SIZE || board[r][c] == oppositePlayer) {
                continue;
            }

            // プレイヤーの手ならカウント
            if (board[r][c] == player) {
                count++;
            }
        }

        return count;  // 現在の線における同じプレイヤーの手の数
    }

    // 人間側の勝利が確定する場所（期待値5）を取得
    std::vector<Move> getHumanVictoryMoves() {
        std::vector<Move> victoryMoves;
        for (const auto& move : moveList) {
            if (move.player == -1 && move.expectedValue == 5) {  // 人間の勝利が確定する場所
                victoryMoves.push_back(move);
            }
        }
        return victoryMoves;
    }

    // MoveクラスのlastConnectedMoveを使用して、連続した場所を選ぶ
    Move* getBestConnectedMove(Move& move) {
        if (move.lastConnectedMove != nullptr) {
            // 連続した手の位置が空いていれば、その場所を選ぶ
            int r = move.lastConnectedMove->row;
            int c = move.lastConnectedMove->col;
            if (board[r][c] == 0) {  // 空いていれば
                return new Move(r, c, -2, move.expectedValue, move.lastConnectedMove);
            }
        }
        return nullptr;  // 連続した場所がない場合
    }

    // 空いている場所の中から期待値の高い場所を返す
    std::vector<Move> getHighValueMoves(int player) {
        std::vector<Move> highValueMoves;
        for (int row = 0; row < SIZE; ++row) {
            for (int col = 0; col < SIZE; ++col) {
                if (board[row][col] == 0) {
                    int score = evaluatePosition(row, col, player);
                    if (score > 3) {  // 期待値が高い場所（仮にスコアが3以上）
                        highValueMoves.push_back(Move(row, col, player, score));
                    }
                }
            }
        }
        return highValueMoves;
    }
};

// NPCのAI（過去の手を基にヒューリスティック評価を基に選択）
class NPC {
private:
    // NPCが選んだ場所を格納するMoveクラスのprivateなvector配列
    std::vector<Move> moves;  // NPCの選んだ場所

public:
    // NPCの次の手を選択する
    Move chooseMove(Board& board) {
        srand(time(0)); // ランダムシードの初期化

        // 1. 人間が次の手で勝利できる場所を妨害
        std::vector<Move> humanVictoryMoves = board.getHumanVictoryMoves();
        if (!humanVictoryMoves.empty()) {
            // 人間が次に勝つ場所を確認し、連続している場所があればそこを選択
            for (auto& victoryMove : humanVictoryMoves) {
                Move* connectedMove = board.getBestConnectedMove(victoryMove);
                if (connectedMove != nullptr) {
                    board.placeMove(connectedMove->row, connectedMove->col, -2);
                    moves.push_back(*connectedMove);
                    return *connectedMove;  // 人間の勝利を妨害する手を選択
                }
            }
        }

        // 2. 次にNPCが勝つ場所を選ぶ（期待値が5の場所）
        for (const auto& move : board.moveList) {
            if (move.player == -2 && move.expectedValue == 5) {  // NPCの勝利が確定する場所
                // 既にある勝利確定手を選択
                board.placeMove(move.row, move.col, -2);
                moves.push_back(move);
                return move;
            }
        }

        // 3. 最も期待値の高い場所を選ぶ（空いている場所の中から選ぶ）
        // 高い期待値の場所を事前に取得し、その中で最も良い場所を選ぶ
        std::vector<Move> highValueMoves = board.getHighValueMoves(-2);  // NPCの視点で期待値の高い場所
        if (!highValueMoves.empty()) {
            // 期待値が高い場所の中で、スコアが最も高いものを選択
            Move bestMove = *std::max_element(highValueMoves.begin(), highValueMoves.end(),
                [](const Move& a, const Move& b) { return a.expectedValue < b.expectedValue; });

            // 最適な場所に手を置く
            board.placeMove(bestMove.row, bestMove.col, -2);
            moves.push_back(bestMove);  // NPCが選んだ手を記録
            return bestMove;
        }

        // もしここまで到達した場合、最も期待値が高い場所は見つからなかったので、ランダムで選ぶ（最終手段）
        return randomMove(board);  // 最終的にランダムな場所を選ぶ
    }

    // ランダムに手を選択（最終手段）
    Move randomMove(Board& board) {
        std::vector<Move> possibleMoves;
        for (int row = 0; row < board.SIZE; ++row) {
            for (int col = 0; col < board.SIZE; ++col) {
                if (board.board[row][col] == 0) {
                    possibleMoves.push_back(Move(row, col, -2, 0));  // 評価無しで空いている場所を追加
                }
            }
        }

        // ランダムで選択
        int randomIndex = rand() % possibleMoves.size();
        Move randomMove = possibleMoves[randomIndex];
        board.placeMove(randomMove.row, randomMove.col, -2);
        moves.push_back(randomMove);
        return randomMove;
    }
};

int main() {
    // ゲームボードの初期化
    Board board;

    // NPCインスタンスを作成
    NPC npc;

    // ゲームの流れ
    while (true) {
        // NPCが次の手を選ぶ
        Move npcMove = npc.chooseMove(board);
        std::cout << "NPC moved to: (" << npcMove.row << ", " << npcMove.col << ")\n";
        board.printBoard();

        // ゲーム終了の判定（ここでは単純に手が終わった時点で終了）
        // 実際には勝利条件やその他の条件を確認する必要がある
        break;
    }

    return 0;
}
