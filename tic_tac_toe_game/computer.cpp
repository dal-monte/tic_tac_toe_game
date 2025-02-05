#include "computer.h"

// ���I��
int Computer::select(std::vector<int>& able_nums) {
	// able_nums����Ō�Ɏw���ꂽ��ƃ^�[���������߂�i���߂Ƀ��[�U�[���w������j
	auto turnCountIter = std::max_element(able_nums.begin(), able_nums.end());
	int recentNum = std::distance(able_nums.begin(), turnCountIter);

    // ����łȂ��ꍇ�̏����i�w�����Ԃ��R���s���[�^��s�ŁA���߂̎w����ȊO�̎��j
    if (recentNum != 0) {
        int turnCount = *turnCountIter;

        // ���z�{�[�h�ő���̎w��������Č�����
        markBoard(exchangeSelectNum(recentNum), marks["o"]);

        // �œK�Ȏ��I�ԁi���Ғl�v�Z�j
        std::pair<int, int> selectMove = findBestMove();

        // �w��������z�{�[�h�ɉ�����
        markBoard(selectMove, marks["x"]);

        // �{�[�h���̍��W�𐔎��ɕϊ����ĕԂ�
        selectNum = exchangeSelectMove(selectMove);

        return selectNum;
    }

	// �n�߂̎w����̎��̓����_���Ɏ�����߂�
	int rand_num;
	while (1) {
		rand_num = rand() % (boardSize * boardSize) + 1;
        // �����_���Ŏ擾���������̍��W���󔒂ł���΂����Ɏw���A�����łȂ��Ƃ��͂�����x�����_���ɐ������擾
		if (able_nums[rand_num] == 0) {
            // ���z�{�[�h�Ŏ����̎w��������Č�����
            markBoard(exchangeSelectNum(rand_num), marks["o"]);
			selectNum = rand_num;
			return rand_num;
		}
		else {
			continue;
		}
	}
}

// �w��������z�{�[�h�ɉ�����
void Computer::markBoard(std::pair<int, int> selectMove, int player) {
    virtualBoard[selectMove.first][selectMove.second] = player;
}

// �������{�[�h���̍��W�ɕϊ����ĕԂ�
std::pair<int, int> Computer::exchangeSelectNum(int recentNum) {
    int v = (recentNum - 1) / boardSize;
    int h = (recentNum - 1) % boardSize;
    return std::pair<int, int> {v, h};
}

// �{�[�h���̍��W�𐔎��ɕϊ����ĕԂ�
int Computer::exchangeSelectMove(std::pair<int, int> recentNum) {
    return (((recentNum.first) * boardSize) + ((recentNum.second + 1)));
}

// ���z�{�[�h�z��̗v�f�ɑ΂��āA�w��̕����̃X�R�A���Z�o����
int Computer::evaluateDirections(int v, int h, int player, int dir) {
    int score = 0;
    int count = 1;
    int enemyCount = 0;
    bool openEnds = false;  // ���[���J���Ă��邩�`�F�b�N
    int directions[4][2] = { {1, 0}, {0, 1}, {1, 1}, {1, -1} };  // �c�A���A�΂�

    // �O�������̃X�L����
    for (int step = 1; step < 5; step++) {
        int nv = v + step * directions[dir][0];
        int nh = h + step * directions[dir][1];
        // �{�[�h�͈̔͊O�ɏo���烋�[�v�I��
        if (nv < 0 || nh < 0 || nv >= boardSize || nh >= boardSize) {
            // �Ǎۂ̃X�R�A�������Ȃ肷���Ȃ��悤�ɒ���
            count -= 5 - step;
            break;
        }
        // ��ׂ̗��󂢂Ă��邩����i�J�E���g�����Ȃ��Ƃ��ɏd�v�ȗv�f�j
        if (step == 1 && virtualBoard[nv][nh] == 0) {
            openEnds = true;
        }
        // �R���s���[�^�̎肪�O���ɂ���Ή��_�i�N�_����߂��قǍ����_�j
        if (virtualBoard[nv][nh] == marks["x"]) {
            count += 5 - step;
        }
        // ����̎肪�O���ɂ���Ό��_�i�N�_����߂��قǌ��_�j
        if (virtualBoard[nv][nh] == marks["o"]) {
            count -= 5 - step;
            // ����̘A�����Ă���肪����ΕʂŃJ�E���g����i�N�_����߂��قǍ����_�j
            enemyCount += 5 - step;
        }
    }
    // ��������̃X�L����
    for (int step = 1; step < 5; step++) {
        int nv = v - step * directions[dir][0];
        int nh = h - step * directions[dir][1];
        // �{�[�h�͈̔͊O�ɏo���烋�[�v�I��
        if (nv < 0 || nh < 0 || nv >= boardSize || nh >= boardSize) {
            // �͈͊O�M���M���͊�������
            count -= 5 - step;
            break;
        }

        // ��ׂ̗��󂢂Ă��邩����i�J�E���g�����Ȃ��Ƃ��ɏd�v�ȗv�f�j
        if (step == 1 && virtualBoard[nv][nh] == 0) {
            openEnds = true;
        }

        // �R���s���[�^�̎肪�O���ɂ���Ή��_�i�N�_����߂��قǍ����_�j
        if (virtualBoard[nv][nh] == player) {
            count += 5 - step;
        }

        // ����̎肪�O���ɂ���Ό��_�i�N�_����߂��قǌ��_�j
        if (virtualBoard[nv][nh] == -1) {
            count -= 5 - step;
            // ����̘A�����Ă���肪����ΕʂŃJ�E���g����i�N�_����߂��قǍ����_�j
            enemyCount += 5 - step;
        }
    }

    // ���[�v���ʂ����Ƃɂ��̎��]������
    if (count >= 8) {
        score = count;  // ��������m�����������ߍŗD��
    }
    else if (enemyCount >= 8) {
        score = enemyCount;  // �G�ɂƂ���ƕ�����\�����������ߗD��
    }
    else if (count >= 5 && openEnds) {
        score = count + 2;  // �ׂ��󂢂Ă��ĕ]�����������ߗD��
    }
    else if (count <= 0) {
        score = 1;   // �]�����[���ȉ��ɂȂ�ƕ]���V�X�e�����@�\���Ȃ��Ȃ邽�ߏ����l������
    }
    else {
        score = count;
    }

    return score;
}

// ���z�{�[�h�z��̗v�f�ɑ΂��āA4�����i�c�E���E�΂߁j�̓��̍ő�X�R�A�𓱂�
void Computer::evaluatePosition(int v, int h, int player) {
    int score[4];

    // �S�������ꂼ��̈�ׂ̍��W�ֈړ�����Ƃ��̍��W���l���������w��@[0]�c�A[1]���A[2]���΂߁A[3]�E�΂�
    int directions[4][2] = { {1, 0}, {0, 1}, {1, 1}, {1, -1} };

    for (int dir = 0; dir < 4; dir++) {
        score[dir] = evaluateDirections(v, h, player, dir);
    }

    // �c�E���E�΂߂̂��ꂼ��̌����̔��茋�ʂ̃X�R�A����ł������l���擾�����z�{�[�h�ɔ��f
    virtualBoard[v][h] = *std::max_element(std::begin(score), std::end(score));
}

// �œK�Ȏ��I��
std::pair<int, int> Computer::findBestMove() {
    std::pair<int, int> bestMove = { -1, -1 };

    // �󂢂Ă���ꏊ�ɑ΂��čœK�Ȏ��]��
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            if (virtualBoard[i][j] >= 0) {  // �󂢂Ă���ꏊ
                evaluatePosition(i, j, marks["x"]);
            }
        }
    }

    // �ő�l��T�����߂̕ϐ�
    int max_value = virtualBoard[0][0];
    int max_row = 0, max_col = 0;

    // 2�����x�N�^�[�����Ԃɑ������čő�l��T��
    for (int i = 0; i < virtualBoard.size(); ++i) {
        auto max_iter = std::max_element(virtualBoard[i].begin(), virtualBoard[i].end());
        if (*max_iter > max_value) {
            max_value = *max_iter;
            max_row = i;
            max_col = std::distance(virtualBoard[i].begin(), max_iter);
        }
    }

    bestMove = { max_row,max_col };

    return bestMove;
}