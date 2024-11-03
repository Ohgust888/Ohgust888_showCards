//2�l�̃v���C���[�����J�[�h�̐������󂯎���āC�\������
//�J�[�h�͐����̑傫�����ɕ���
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <opencv2/opencv.hpp>
//#include<./opencv/sources/include/opencv2/opencv.hpp>
#ifdef _DEBUG
#pragma comment(lib, "opencv_world4100d.lib")
#else
#pragma comment(lib, "opencv_world4100.lib")
#endif
using namespace std;
using namespace cv;
#define MAXN 20 //2�l�̃v���C���[P0, P1�����ꂼ�ꎝ�J�[�h�̍ő吔
#define MAXS 2*MAXN //�J�[�h�̒l�̍ő�l
int main() {
    int n, m; //P0, P1�̃J�[�h��
    int i, j, k; //�����p
    string S0, S1;
    cout << "1�l�ڂ̃v���C���[�̃J�[�h������͂��Ă�������(1����" << MAXN << "�܂ł̐���)" << endl;
    cin >> n;
    cout << "2�l�ڂ̃v���C���[�̃J�[�h������͂��Ă�������(1����" << MAXN << "�܂ł̐���)" << endl;
    cin >> m;

    //�v���C���[�̃J�[�h�̐������i�[���Ă����z��, X0, X1�����ꂼ��v���C���[P0(1�l��), P1(2�l��)�̃J�[�h�ɑΉ�
    vector<int> X0(MAXN + 1, MAXS + 1), X1(MAXN + 1, MAXS + 1);
    //cerr << "n=" << n << ", m=" << m << endl;

    //�J�[�h�̓���
    cout << "1�l�ڂ̃v���C���[�̃J�[�h�ԍ����A�󔒋�؂�œ��͂��Ă�������(1����" << MAXS << "�܂ł̐����A�J�[�h��2���̂Ƃ��̗�F1 3)" << endl;
    for (i = 0; i < n; i++) {
        cin >> X0.at(i);
    }
    cout << "2�l�ڂ̃v���C���[�̃J�[�h�ԍ����A�󔒋�؂�œ��͂��Ă�������(1����" << MAXS << "�܂ł̐����A�J�[�h��5���̂Ƃ��̗�F3 3 4 6 10)" << endl;
    for (i = 0; i < m; i++) {
        cin >> X1.at(i);
    }

    //�J�[�h�����������Ƀ\�[�g
    sort(X0.begin(), X0.end());
    sort(X1.begin(), X1.end());

    //�J�[�h����ׂ��摜���쐬����
    Mat img, dst; //�摜�t�@�C�����i�[����ϐ�
    img = imread("canvas.png"); //���ƂȂ�摜��ǂݍ����img�Ɋi�[
    dst = img.clone(); //img���R�s�[����A�����dst�ŉ��H���Ă���

    //�摜�̉��H
    int left, WID_CARDX, WID_CARDY, WID_MARGIN; //�`��̍��[��x���W, �J�[�h1���̉���, �J�[�h1���̏c��, �J�[�h�Ԃ̋󔒂̃T�C�Y
    double SIZE_STRING; //�����̃T�C�Y
    int yP0, yP1; //P0, P1��`�悷��y���W(�����̉������ʒu����l)
    int curx, cury; //���ɕ`�悷��J�[�h�̍���̍��W
    int marx, mary; //�J�[�h�̍���ƕ�����̍����̍�
    string showS; //�\�����镶������i�[����
    left = 0;
    WID_CARDX = 100, WID_CARDY = 150;
    WID_MARGIN = 20;
    SIZE_STRING = 2.0;
    yP0 = 120, yP1 = 320;
    curx = 120, cury = 0;
    marx = 10, mary = 90;

    /*
    putText( //�������`��
        dst, //���H����摜
        "P0:", //�`�悷�镶����
        Point(left, yP0), //�`�悷��ꏊ(�����̓_)
        FONT_HERSHEY_SIMPLEX, //�t�H���g�̎��
        SIZE_STRING, //�����̑傫��
        Scalar(0, 0, 0), //�����̐F
        3 //�����̑���
    );

    rectangle( //�����`��`��
        dst, //���H����摜
        Point(curx, cury), //�����`�̍���
        Point(curx + WID_CARDX, cury + WID_CARDY), //�����`�̉E��
        Scalar(255, 0, 0), //�����̐F(BGR, RGB�ł͂Ȃ��̂Œ���)
        5 //���̑���
    );
    //*/

    //���ꂩ��`�悷��J�[�h���ǂ̃v���C���[�̂��̂��𕪂���悤��P0, P1�̕������`��
    putText(dst, "P0:", Point(left, yP0), FONT_HERSHEY_SIMPLEX, SIZE_STRING, Scalar(0, 0, 0), 3);
    putText(dst, "P1:", Point(left, yP1), FONT_HERSHEY_SIMPLEX, SIZE_STRING, Scalar(0, 0, 0), 3);

    //�������J�[�h���珇�ɁC������J�[�h��`�悵�Ă���
    i = 0; j = 0; //�ȉ��ł�X0��i�Ԗڂ�X1��j�Ԗڂ̃J�[�h�ɑ΂��đ召�֌W���r����
    for (k = 0; k < n + m; k++) { //�J�[�h�̖������J��Ԃ�
        showS = "";
        if (X0.at(i) > X1.at(j)) { //P0, P1�̃J�[�h���ׂ�C����������`�悷��
            cury = yP1 - WID_CARDY * 3 / 5;
            if (X1.at(j) < 10) { //�J�[�h�̐�����1���Ȃ�
                showS += " "; //�����̏ꏊ�𒲐�
            }
            showS += to_string(X1.at(j));
            //�J�[�h��`��
            rectangle(dst, Point(curx, cury), Point(curx + WID_CARDX, cury + WID_CARDY), Scalar(0, 0, 0), 5);
            putText(dst, showS, Point(curx+marx, cury+mary), FONT_HERSHEY_SIMPLEX, SIZE_STRING, Scalar(0, 0, 0), 3);
            j++;
            //cerr << "X1��" << to_string(X1.at(j)) << "��ǉ�" << endl;
        }
        else if (X0.at(i) < X1.at(j)) {
            cury = yP0 - WID_CARDY * 3 / 5;
            if (X0.at(i) < 10) {
                showS += " ";
            }
            showS += to_string(X0.at(i));
            rectangle(dst, Point(curx, cury), Point(curx + WID_CARDX, cury + WID_CARDY), Scalar(0, 0, 0), 5);
            putText(dst, showS, Point(curx + marx, cury + mary), FONT_HERSHEY_SIMPLEX, SIZE_STRING, Scalar(0, 0, 0), 3);
            i++;
            //cerr << "X0��" << to_string(X0.at(i)) << "��ǉ�" << endl;
        }
        else { //X0.at(i) == X1.at(j), 2�l�̃v���C���[�̍����Ă���J�[�h�����������̏ꍇ�́C�����`�悷��
            cury = yP0 - WID_CARDY * 3 / 5;
            if (X0.at(i) < 10) {
                showS += " ";
            }
            showS += to_string(X0.at(i));
            rectangle(dst, Point(curx, cury), Point(curx + WID_CARDX, cury + WID_CARDY), Scalar(0, 0, 0), 5);
            putText(dst, showS, Point(curx + marx, cury + mary), FONT_HERSHEY_SIMPLEX, SIZE_STRING, Scalar(0, 0, 0), 3);
            showS = "";
            cury = yP1 - WID_CARDY * 3 / 5;
            if (X1.at(j) < 10) {
                showS += " ";
            }
            showS += to_string(X1.at(j));
            rectangle(dst, Point(curx, cury), Point(curx + WID_CARDX, cury + WID_CARDY), Scalar(0, 0, 0), 5);
            putText(dst, showS, Point(curx + marx, cury + mary), FONT_HERSHEY_SIMPLEX, SIZE_STRING, Scalar(0, 0, 0), 3);
            i++; j++; k++; //��x��2������ǉ����Ă��邽�߁Ck���ǉ��ő��₷
            //cerr << "X0��" << to_string(X0.at(i)) << "��ǉ�" << endl;
            //cerr << "X1��" << to_string(X1.at(j)) << "��ǉ�" << endl;
        }
        curx += WID_CARDX + WID_MARGIN; //�J�[�h�̕`��ʒu���E���ɍX�V
    }

    imshow("cards", dst); //�^�C�g���ƕ\������摜�̕ϐ�����͂��ĕ\��
    imwrite("cards.png", dst); //�摜��ۑ�
    cv::waitKey(0); //�摜��\�����鎞�ԁA0�Ȃ�Enter�L�[���������܂�

    return 0;
}