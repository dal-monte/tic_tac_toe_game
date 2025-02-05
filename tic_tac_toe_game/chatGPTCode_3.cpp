#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

class GomokuNPC {
private:
    std::vector<std::vector<int>> board;  // �Ֆ�
    int boardSize;  // �Ֆʂ̃T�C�Y
    int currentDepth;  // ���݂̐[��
    const int MAX_DEPTH = 6;  // �ő�[���i�Q�[���i�s�ɉ����ē��I�ɕύX�j
    const int WIN_SCORE = 1000000;
    const int MID_GAME_DEPTH = 4;
    const int EARLY_GAME_DEPTH = 3; // �R���X�g���N�^��currentDepth�̒l�̏����������Ă��鐔�l

public:
    GomokuNPC(int size = 15)
        : boardSize(size), currentDepth(3) {
        board.resize(boardSize, std::vector<int>(boardSize, 0));  // 0�ŏ�����
    }

    // �Ֆʂ̏�Ԃ�\��
    void printBoard() {
        for (int i = 0; i < boardSize; i++) {
            for (int j = 0; j < boardSize; j++) {
                std::cout << (board[i][j] == 0 ? '.' : (board[i][j] == 1 ? 'X' : 'O')) << " ";
            }
            std::cout << std::endl;
        }
    }

    // ���u��
    void placeMove(int x, int y, int player) {
        board[x][y] = player;
    }

    // �]���֐��i�Ǐ��I�ȕ]���ƘA�����̉��d�X�R�A�j
    int evaluatePosition(int x, int y, int player) {
        int score = 0;     // �ŏI�I�ɔ��f����Ƃ��Ɏg�p����X�R�A��������
        int directions[4][2] = { {1, 0}, {0, 1}, {1, 1}, {1, -1} };  // �c�A���A���΂߁A�E�΂߂̂��ꂼ������ɐi�ނ��߂̍��W�̑���

        // �Q�[���̐i�s�󋵂ɉ����ĕ]�����ύX
        if (currentDepth <= EARLY_GAME_DEPTH) {
            // ���Ղł͔Ֆʒ�����L������d��
            score += (boardSize / 2 - std::abs(x - boardSize / 2)) + (boardSize / 2 - std::abs(y - boardSize / 2));
        }

        // �c�A���A���΂߁A�E�΂߂̂��ꂼ��ɕ]���������s��
        for (int dir = 0; dir < 4; dir++) {
            int count = 1;  // �����̋�̐�
            bool openEnds = false;  // ���[���J���Ă��邩

            // �O�������̃X�L����
            for (int step = 1; step < 5; step++) {
                int nx = x + step * directions[dir][0];
                int ny = y + step * directions[dir][1];
                if (nx < 0 || ny < 0 || nx >= boardSize || ny >= boardSize) break;
                if (board[nx][ny] == player) {
                    count++;
                }
                else if (board[nx][ny] == 0) {
                    openEnds = true;
                    break;
                }
                else {
                    break;
                }
            }

            // ��������̃X�L����
            for (int step = 1; step < 5; step++) {
                int nx = x - step * directions[dir][0];
                int ny = y - step * directions[dir][1];
                if (nx < 0 || ny < 0 || nx >= boardSize || ny >= boardSize) break;
                if (board[nx][ny] == player) {
                    count++;
                }
                else if (board[nx][ny] == 0) {
                    openEnds = true;
                    break;
                }
                else {
                    break;
                }
            }

            /*
            * �����̋�A�����ĕ���ł��鐔�ɉ����ăX�R�A�����Z�B
            * �Ⴆ�΁A�A�������4�̏ꍇ�A���̗��[�ɋ󂢂Ă���ꏊ������΁A
            * ���ɋ��u�����Ƃł���ɘA����L�΂���\�����������߁A�����_��^����B
            */
            if (count == 4) {
                score += openEnds ? 1000 : 10000;
            }
            else if (count == 3) {
                score += openEnds ? 100 : 500;
            }
            else if (count == 2) {
                score += openEnds ? 10 : 50;
            }
        }

        return score;
    }

    // �~�j�}�b�N�X�@�ƃA���t�@�x�[�^�@
    int minimax(int depth, bool isMaximizingPlayer, int alpha, int beta) {
        if (depth == 0) {
            return 0;  // �]���֐����Ăяo��
        }

        int bestScore = isMaximizingPlayer ? INT_MIN : INT_MAX;

        for (int i = 0; i < boardSize; i++) {
            for (int j = 0; j < boardSize; j++) {
                if (board[i][j] == 0) {  // �󂢂Ă���ꏊ
                    board[i][j] = isMaximizingPlayer ? -1 : 1;  // NPC�܂��̓v���C���[�̎�
                    int score = minimax(depth - 1, !isMaximizingPlayer, alpha, beta);
                    board[i][j] = 0;  // �߂�

                    if (isMaximizingPlayer) {
                        bestScore = std::max(bestScore, score);
                        alpha = std::max(alpha, score);
                    }
                    else {
                        bestScore = std::min(bestScore, score);
                        beta = std::min(beta, score);
                    }

                    // ��-������
                    if (beta <= alpha) {
                        break;
                    }
                }
            }
        }
        return bestScore;
    }

    // �œK�Ȏ��I�ԁi�~�j�}�b�N�X�@ + ��-������j
    std::pair<int, int> findBestMove() {
        int bestScore = INT_MIN;
        std::pair<int, int> bestMove = { -1, -1 };

        // �Q�[���̐i�s�ɉ����ĒT���̐[���𓮓I�ɒ���
        if (currentDepth <= EARLY_GAME_DEPTH) {
            currentDepth = EARLY_GAME_DEPTH;  // ���Ղ͐󂢐[��
        }
        else if (currentDepth <= MID_GAME_DEPTH) {
            currentDepth = MID_GAME_DEPTH;  // ���Ղ͒����x�̐[��
        }
        else {
            currentDepth = MAX_DEPTH;  // �I�Ղ͐[���T��
        }

        for (int i = 0; i < boardSize; i++) {
            for (int j = 0; j < boardSize; j++) {
                if (board[i][j] == 0) {  // �󂢂Ă���ꏊ
                    placeMove(i, j, -1);  // NPC�̎�
                    int score = minimax(currentDepth, false, INT_MIN, INT_MAX);  // �v���C���[�i1�j�Ƃ̑Ό�
                    placeMove(i, j, 0);  // �߂�

                    if (score > bestScore) {
                        bestScore = score;
                        bestMove = { i, j };
                    }
                }
            }
        }
        return bestMove;
    }

    // ���݂̎�𓮓I�ɒ�������
    void updateGameProgress(int turnCount) {
        if (turnCount <= 20) {
            currentDepth = EARLY_GAME_DEPTH;  // ����
        }
        else if (turnCount <= 40) {
            currentDepth = MID_GAME_DEPTH;  // ����
        }
        else {
            currentDepth = MAX_DEPTH;  // �I��
        }
    }
};

int main() {
    GomokuNPC npc;

    // �Q�[���̗���
    npc.printBoard();

    int turnCount = 0;

    // �v���C���[�i1�j��NPC�i-1�j�̎�����݂ɒu��
    npc.placeMove(7, 7, 1);  // �v���C���[�̎�
    turnCount++;
    npc.placeMove(7, 8, -1); // NPC�̎�
    turnCount++;
    npc.updateGameProgress(turnCount);  // �Q�[���i�s�ɉ����Đ[������

    // NPC�����ɑłœK�Ȏ�����߂�
    auto bestMove = npc.findBestMove();
    std::cout << "NPC's best move is at (" << bestMove.first << ", " << bestMove.second << ")\n";

    // �œK�Ȏ��Ֆʂɔ��f
    npc.placeMove(bestMove.first, bestMove.second, -1);
    turnCount++;

    // �Ֆʂ��ĕ\��
    npc.printBoard();

    return 0;
}
