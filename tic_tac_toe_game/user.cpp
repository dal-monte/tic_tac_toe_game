#include "user.h"

// 手を選ぶ
int User::select(std::vector<int> &able_nums) {
	int ent_num;

	while (1) {
		std::cout << "あなたの番です。\n" << mark << "の手を選んでください" << std::endl;
		std::cin >> ent_num;

		// 0以下の数字を入力した場合にエラー文を表示する
		if (ent_num <=0) {
			std::cout << "\n盤上の数字を入力してください。\n" << std::endl;
			std::cin.clear();
			std::cin.ignore(256, '\n');
			continue;
		}

		// 盤面の範囲外の数字や数字以外を入力していた場合エラー文を表示する
		try { 
			able_nums.at(ent_num); 
		}
		catch(std::out_of_range& ex) {
			std::cout << "\n選択可能な数字を入力してください。\n" << std::endl;
			std::cin.clear();
			std::cin.ignore(256, '\n');
			continue;
		}

		// 問題なければ入力した数字を返す
		if (able_nums[ent_num] == 0) {
			selectNum = ent_num;
			return ent_num;
		}
		// すでに使用済みの場所を選択した場合にエラー文を表示する
		else {
			std::cout << "\n選択可能な数字を入力してください。\n" << std::endl;
			std::cin.clear();
			std::cin.ignore(256, '\n');
			continue;
		}
	};

}