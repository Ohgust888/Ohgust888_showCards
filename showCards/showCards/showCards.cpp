//2人のプレイヤーが持つカードの数字を受け取って，表示する
//カードは数字の大きさ順に並ぶ
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
#define MAXN 20 //2人のプレイヤーP0, P1がそれぞれ持つカードの最大数
#define MAXS 2*MAXN //カードの値の最大値
int main() {
    int n, m; //P0, P1のカード数
    int i, j, k; //処理用
    string S0, S1;
    cout << "1人目のプレイヤーのカード数を入力してください(1から" << MAXN << "までの整数)" << endl;
    cin >> n;
    cout << "2人目のプレイヤーのカード数を入力してください(1から" << MAXN << "までの整数)" << endl;
    cin >> m;

    //プレイヤーのカードの数字を格納しておく配列, X0, X1がそれぞれプレイヤーP0(1人目), P1(2人目)のカードに対応
    vector<int> X0(MAXN + 1, MAXS + 1), X1(MAXN + 1, MAXS + 1);
    //cerr << "n=" << n << ", m=" << m << endl;

    //カードの入力
    cout << "1人目のプレイヤーのカード番号を、空白区切りで入力してください(1から" << MAXS << "までの整数、カードが2枚のときの例：1 3)" << endl;
    for (i = 0; i < n; i++) {
        cin >> X0.at(i);
    }
    cout << "2人目のプレイヤーのカード番号を、空白区切りで入力してください(1から" << MAXS << "までの整数、カードが5枚のときの例：3 3 4 6 10)" << endl;
    for (i = 0; i < m; i++) {
        cin >> X1.at(i);
    }

    //カードを小さい順にソート
    sort(X0.begin(), X0.end());
    sort(X1.begin(), X1.end());

    //カードを並べた画像を作成する
    Mat img, dst; //画像ファイルを格納する変数
    img = imread("canvas.png"); //元となる画像を読み込んでimgに格納
    dst = img.clone(); //imgをコピーする、今後はdstで加工していく

    //画像の加工
    int left, WID_CARDX, WID_CARDY, WID_MARGIN; //描画の左端のx座標, カード1枚の横幅, カード1枚の縦幅, カード間の空白のサイズ
    double SIZE_STRING; //文字のサイズ
    int yP0, yP1; //P0, P1を描画するy座標(文字の下部が位置する値)
    int curx, cury; //次に描画するカードの左上の座標
    int marx, mary; //カードの左上と文字列の左下の差
    string showS; //表示する文字列を格納する
    left = 0;
    WID_CARDX = 100, WID_CARDY = 150;
    WID_MARGIN = 20;
    SIZE_STRING = 2.0;
    yP0 = 120, yP1 = 320;
    curx = 120, cury = 0;
    marx = 10, mary = 90;

    /*
    putText( //文字列を描く
        dst, //加工する画像
        "P0:", //描画する文字列
        Point(left, yP0), //描画する場所(左下の点)
        FONT_HERSHEY_SIMPLEX, //フォントの種類
        SIZE_STRING, //文字の大きさ
        Scalar(0, 0, 0), //文字の色
        3 //文字の太さ
    );

    rectangle( //長方形を描く
        dst, //加工する画像
        Point(curx, cury), //長方形の左上
        Point(curx + WID_CARDX, cury + WID_CARDY), //長方形の右下
        Scalar(255, 0, 0), //文字の色(BGR, RGBではないので注意)
        5 //線の太さ
    );
    //*/

    //これから描画するカードがどのプレイヤーのものかを分かるようにP0, P1の文字列を描画
    putText(dst, "P0:", Point(left, yP0), FONT_HERSHEY_SIMPLEX, SIZE_STRING, Scalar(0, 0, 0), 3);
    putText(dst, "P1:", Point(left, yP1), FONT_HERSHEY_SIMPLEX, SIZE_STRING, Scalar(0, 0, 0), 3);

    //小さいカードから順に，左からカードを描画していく
    i = 0; j = 0; //以下ではX0のi番目とX1のj番目のカードに対して大小関係を比較する
    for (k = 0; k < n + m; k++) { //カードの枚数分繰り返す
        showS = "";
        if (X0.at(i) > X1.at(j)) { //P0, P1のカードを比べる，小さい方を描画する
            cury = yP1 - WID_CARDY * 3 / 5;
            if (X1.at(j) < 10) { //カードの数字が1桁なら
                showS += " "; //数字の場所を調整
            }
            showS += to_string(X1.at(j));
            //カードを描画
            rectangle(dst, Point(curx, cury), Point(curx + WID_CARDX, cury + WID_CARDY), Scalar(0, 0, 0), 5);
            putText(dst, showS, Point(curx+marx, cury+mary), FONT_HERSHEY_SIMPLEX, SIZE_STRING, Scalar(0, 0, 0), 3);
            j++;
            //cerr << "X1に" << to_string(X1.at(j)) << "を追加" << endl;
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
            //cerr << "X0に" << to_string(X0.at(i)) << "を追加" << endl;
        }
        else { //X0.at(i) == X1.at(j), 2人のプレイヤーの今見ているカードが同じ強さの場合は，両方描画する
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
            i++; j++; k++; //一度に2枚分を追加しているため，kも追加で増やす
            //cerr << "X0に" << to_string(X0.at(i)) << "を追加" << endl;
            //cerr << "X1に" << to_string(X1.at(j)) << "を追加" << endl;
        }
        curx += WID_CARDX + WID_MARGIN; //カードの描画位置を右側に更新
    }

    imshow("cards", dst); //タイトルと表示する画像の変数を入力して表示
    imwrite("cards.png", dst); //画像を保存
    cv::waitKey(0); //画像を表示する時間、0ならEnterキーが押されるまで

    return 0;
}