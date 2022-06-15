#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#pragma pack(1)
typedef struct S {
	char SAMID[9]; // Serial number of each group of data 
	int SDA; // status information a
	int SDB; // status information b
	int SDC; // status information c
	int SF;  // process result f
} S;
#pragma pack()
const char hello_msg_[72] = "Welcome to the computer running status monitoring system, U202010755! \n";
const char input_name_msg_[28] = "Please input Your name:   \n";
const char input_password_msg_[32] = "Please input Your password:   \n";
const char password_ok_[6] = "OK! \n";
const char username_err_[22] = "Incorrect username! \n";
const char password_err_[22] = "Incorrect password! \n";
const char midf_print_msg_[29] = "Here is the group of MIDF: \n";
const char option_msg_[37] = "Rerun¡¢Quit or Input (R / Q / M) ? \n";
const char exit_msg_[23] = "Goodbye, U202010755! \n";
const char input_s_msg_[62] = "Please enter your SAMID and your SDA¡¢SDB¡¢SDC information! \n";
const char username_[10] = "luhaodong"; // The true name
const char password_[11] = "U202010755"; // The true password
int low_cnt_; // The quantity of the input S with low SF
int mid_cnt_; // The quantity of the input S with mid SF
int high_cnt_; // The quantity of the input S with high SF
int sf_; // The result of the calculation of SF
char name_input_[20]; // Save the name you type in!
char password_input_[20]; // Save the password you type in!
int flag = 0; 
S LOWF[7];
S MIDF[7];
S HIGHF[7];
S INPUT[7] = {
	[0] = {
		.SAMID = "00000000",
		.SDA = 2539,
		.SDB = 6,
		.SDC = 1,
		.SF = 0
	}, [1] = {
		.SAMID = "00000001",
		.SDA = 2539,
		.SDB = 6,
		.SDC = 1,
		.SF = 0
	}, [2] = {
		.SAMID = "00000002",
		.SDA = 2540,
		.SDB = 1,
		.SDC = 1,
		.SF = 0
	}, [3] = {
		.SAMID = "00000003",
		.SDA = 2540,
		.SDB = 1000,
		.SDC = 1,
		.SF = 0
	}, [4] = {
		.SAMID = "00000004",
		.SDA = 2540,
		.SDB = 44,
		.SDC = 44,
		.SF = 0
	}, [5] = {
		.SAMID = "00000005",
		.SDA = 2540,
		.SDB = 666,
		.SDC = 666,
		.SF = 0
	}, [6] = {
		.SAMID = "00000006",
		.SDA = 5,
		.SDB = 4,
		.SDC = 1,
		.SF = 0
	},
};
extern void s_copy(S*, S*);
extern void f_calculate(S*);
void login();
void midf_print();
void options();
char input_option();
int main() {
	login();
	options();
}
void login() {
	printf(hello_msg_);
	for (int i = 0; i < 3; ++i)	{
		printf(input_name_msg_);
		scanf("%s", name_input_);
		flag = 0;
		for (int j = 0; name_input_[j] != 0 && username_[j] != 0; ++j) {
			if (name_input_[j] != username_[j]) {
				flag = 1;
				break;
			}
		}
		if (flag == 1) {
			printf(username_err_);
			continue;
		} else {
			for (int j = 0; j < 3; j++) {
				printf(input_password_msg_);
				scanf("%s", password_input_);
				flag = 0;
				for (int k = 0; password_input_[k] != 0 && password_[k] != 0; k++) {
					if (password_input_[k] != password_[k]) {
						flag = 1;
						break;
					}
				}
				if (flag == 0) {
					printf(password_ok_);
					break;
				} else {
					printf(password_err_);
				}
			}
			break;
		}
		printf(username_err_);
	}
	if (flag == 1) {
		exit(0);
	}
}
void midf_print() {
	for (int i = 0; i < mid_cnt_; ++i) {
		printf("ID: %s\n", MIDF[i].SAMID);
		printf("a: %d\n", MIDF[i].SDA);
		printf("b: %d\n", MIDF[i].SDB);
		printf("c: %d\n", MIDF[i].SDC);
	}
	printf("\n");
}
char input_option() {
	char c = getchar();
	while (c != 'R' && c != 'Q' && c != 'M') {
		c = getchar();
		if (((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) && c != 'R' && c != 'Q' && c != 'M') {
			printf("Please input the correct option! \n Again : ");
		}
		continue;
	}
	return c;
}
void options() {
	do {
		low_cnt_ = 0;
		mid_cnt_ = 0;
		high_cnt_ = 0;
		sf_ = 0;
		for (int i = 0; i < 7; i++)	{
			f_calculate(&INPUT[i]);
			if (INPUT[i].SF < 100) {
				s_copy(&LOWF[low_cnt_++], &INPUT[i]);
			} else if (INPUT[i].SF > 100) {
				s_copy(&HIGHF[high_cnt_++], &INPUT[i]);
			} else {
				s_copy(&MIDF[mid_cnt_++], &INPUT[i]);
			}
		}
		printf(midf_print_msg_);
		midf_print();
		printf(option_msg_);
		char c = input_option();
		if (c == 'R') {
			continue;
		} else if (c == 'Q') {
			printf(exit_msg_);
			break;
		} else if (c == 'M') {
			printf(input_s_msg_);
			S temp;
			printf("SAMID: ");
			scanf_s("%s", temp.SAMID, 8);
			printf("SDA: ");
			scanf_s("%d", &temp.SDA);
			printf("SDB: ");
			scanf_s("%d", &temp.SDB);
			printf("SDC: ");
			scanf_s("%d", &temp.SDC);
			temp.SF = 0;
			s_copy(&INPUT[0], &temp);
			printf("\n");
			continue;
		}
	} while (1);
}