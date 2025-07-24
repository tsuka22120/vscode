// 配列の宣言と初期化
/*Ｃ言語の場合
 * int box[15]; //宣言
 * box[2] = 10; //初期化
 * 
 * int box[] = {1,2,3,4,5}; //宣言と初期化
 * 
 * 
 * Javaの場合
 * int box[]; //宣言
 * box = new int[15]; //割り当て
 * box[2] = 10; //初期化
 * 
 * int box[] = new int[5]; //宣言と割り当て
 * box[2] = 10; //初期化
 * 
 * int box[] = {1,2,3,4,5}; //宣言と割り当てと初期化
 * 
 * 配列はC言語と違い、配列数がオブジェクトとして確保されているため、
 * 配列名.lengthで配列数を取得できる
 */

// サブルーチン定義
/*C言語の場合
 * int main(void){
 *    int ans;
 *    ans = add(10,20);
 *   printf("%d\n",ans);
 *  return 0;
 * }
 * 
 * int add(int a,int b){
 *   return a + b;
 * }
 * 
 * 
 * Javaの場合
 * 
 * public class Function {
 *  public static void main(String[] args){
 *   int ans;
 *  ans = add(10,20);
 * System.out.println("答えは" + ans);
 * }
 * 
 * static int add(int a,int b){
 * return a + b;
 * }
 */



public class App {
    public static void main(String[] args) throws Exception {
        System.out.println("Hello, World!");
    }
}
