#include "user.h"

// ���I��
int User::select(std::vector<int> &able_nums) {
	int ent_num;

	while (1) {
		std::cout << "���Ȃ��̔Ԃł��B\n" << mark << "�̎��I��ł�������" << std::endl;
		std::cin >> ent_num;

		// 0�ȉ��̐�������͂����ꍇ�ɃG���[����\������
		if (ent_num <=0) {
			std::cout << "\n�Տ�̐�������͂��Ă��������B\n" << std::endl;
			std::cin.clear();
			std::cin.ignore(256, '\n');
			continue;
		}

		// �Ֆʂ͈̔͊O�̐����␔���ȊO����͂��Ă����ꍇ�G���[����\������
		try { 
			able_nums.at(ent_num); 
		}
		catch(std::out_of_range& ex) {
			std::cout << "\n�I���\�Ȑ�������͂��Ă��������B\n" << std::endl;
			std::cin.clear();
			std::cin.ignore(256, '\n');
			continue;
		}

		// ���Ȃ���Γ��͂���������Ԃ�
		if (able_nums[ent_num] == 0) {
			selectNum = ent_num;
			return ent_num;
		}
		// ���łɎg�p�ς݂̏ꏊ��I�������ꍇ�ɃG���[����\������
		else {
			std::cout << "\n�I���\�Ȑ�������͂��Ă��������B\n" << std::endl;
			std::cin.clear();
			std::cin.ignore(256, '\n');
			continue;
		}
	};

}